import pandas as pd
import json
import numpy as np

years = [2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021, 2022]

def time_str_to_seconds(time_str):
    minutes, seconds = map(int, time_str.split(':'))
    return minutes * 60 + seconds

def convert_numpy_int(obj):
    if isinstance(obj, np.integer):
        return int(obj)
    elif isinstance(obj, dict):
        return {key: convert_numpy_int(value) for key, value in obj.items()}
    elif isinstance(obj, list):
        return [convert_numpy_int(element) for element in obj]
    else:
        return obj

def handle_data(year):
    # 读取数据集
    file_name = f'data/pbpstats_{year}.csv'
    df = pd.read_csv(file_name)

    # 反转DataFrame
    df = df.iloc[::-1]

    # 转换时间格式并调整时间
    df['ENDTIME'] = pd.to_datetime(df['ENDTIME'], format='%M:%S')
    df['STARTTIME'] = pd.to_datetime(df['STARTTIME'], format='%M:%S')
    df.loc[df['PERIOD'] == 1, ['ENDTIME', 'STARTTIME']] += pd.to_timedelta('36 minutes')
    df.loc[df['PERIOD'] == 2, ['ENDTIME', 'STARTTIME']] += pd.to_timedelta('24 minutes')
    df.loc[df['PERIOD'] == 3, ['ENDTIME', 'STARTTIME']] += pd.to_timedelta('12 minutes')
    df['ENDTIME'] = df['ENDTIME'].dt.strftime('%M:%S')
    df['STARTTIME'] = df['STARTTIME'].dt.strftime('%M:%S')

    # 在时间调整之后对数据进行排序
    df['ENDTIME'] = pd.to_datetime(df['ENDTIME'], format='%M:%S')
    df['STARTTIME'] = pd.to_datetime(df['STARTTIME'], format='%M:%S')

    # 对每场比赛的事件进行排序
    df.sort_values(by=['GAMEID', 'STARTTIME'], ascending=[True, False], inplace=True)

    # 将时间转换回字符串格式，以便之后的处理
    df['ENDTIME'] = df['ENDTIME'].dt.strftime('%M:%S')
    df['STARTTIME'] = df['STARTTIME'].dt.strftime('%M:%S')

    # 识别每场比赛中的两支球队并统一分差视角
    for gameid in df['GAMEID'].unique():
        game_data = df[df['GAMEID'] == gameid]

        # 确定两支球队（假设每场比赛只有两支球队参与）
        teams = game_data['OPPONENT'].unique()
        if len(teams) != 2:
            raise ValueError(f"Unexpected number of teams in game {gameid}")

        # 选择球队1作为参考
        team1 = teams[0]

        # 调整 STARTSCOREDIFFERENTIAL，使其始终从球队1的视角表示
        for index, row in game_data.iterrows():
            if row['OPPONENT'] != team1:
                df.at[index, 'STARTSCOREDIFFERENTIAL'] = -row['STARTSCOREDIFFERENTIAL']

    # 创建 ABSOLUTESCOREDIFFERENTIAL 列
    df['ABSOLUTESCOREDIFFERENTIAL'] = df['STARTSCOREDIFFERENTIAL']

    # 初始化字典以存储所有比赛的连续领先情况
    all_games_leads = {}

    # 处理每场比赛
    for gameid in df['GAMEID'].unique():
        game_data = df[df['GAMEID'] == gameid].sort_values(by='STARTTIME')
        current_state = None
        consecutive_leads = []

        for index, row in game_data.iterrows():
            margin = row['ABSOLUTESCOREDIFFERENTIAL']

            # 检查领先状态是否改变
            if margin > 0:
                state = 'positive'
            elif margin < 0:
                state = 'negative'
            else:
                state = 'neutral'

            if current_state != state:
                if current_state is not None and consecutive_leads:
                    # 结束上一个领先段落，只有当列表不为空时
                    consecutive_leads[-1]['end_time'] = row['STARTTIME']
                if state != 'neutral':
                    # 开始新的领先段落
                    consecutive_leads.append({'start_time': row['STARTTIME'],
                                              'end_time': None,
                                              'state': state,
                                              'maxlead': abs(margin),
                                              'maxlead_time': row['STARTTIME']})

            current_state = state

            # 更新连续领先的最大领先分差及其时间
            if consecutive_leads:
                if abs(margin) > consecutive_leads[-1]['maxlead']:
                    consecutive_leads[-1]['maxlead'] = abs(margin)
                    consecutive_leads[-1]['maxlead_time'] = row['STARTTIME']

        # 确保最后一个领先段落有结束时间
        if consecutive_leads and consecutive_leads[-1]['end_time'] is None:
            consecutive_leads[-1]['end_time'] = game_data.iloc[-1]['ENDTIME']

        all_games_leads[gameid] = consecutive_leads

    # 重新格式化结果以包括每次领先的分界线时间和计算建立和消失时间
    formatted_results = {}
    for gameid, leads in all_games_leads.items():
        formatted_leads = []
        for lead in leads:
            start_time_seconds = time_str_to_seconds(lead['start_time'])
            maxlead_time_seconds = time_str_to_seconds(lead['maxlead_time'])
            end_time_seconds = time_str_to_seconds(lead['end_time'])

            # 计算领先建立和消失的时间
            build_time = maxlead_time_seconds - start_time_seconds if maxlead_time_seconds > start_time_seconds else 0
            disappear_time = end_time_seconds - maxlead_time_seconds if end_time_seconds > maxlead_time_seconds else 0

            formatted_lead = {
                'id': gameid,
                'maxlead': lead['maxlead'],
                'dividing_line': lead['maxlead_time'],
                'starttime': lead['start_time'],
                'endtime': lead['end_time'],
                'state': lead['state'],
                'buildtime': build_time,
                'disappeartime': disappear_time
            }
            formatted_leads.append(formatted_lead)

        formatted_results[gameid] = formatted_leads

        # 转换 formatted_results 字典中的所有 NumPy int64 类型的值
        converted_formatted_results = convert_numpy_int(formatted_results)

        # 转换键为字符串并保存为 JSON 文件
        converted_all_games_leads = {str(gameid): leads for gameid, leads in converted_formatted_results.items()}
        output_file = 'data_handled/'+'Lead_Duration_'+str(year)+'.json'
        with open(output_file, 'w') as file:
            json.dump(converted_all_games_leads, file)

for year in years:
    handle_data(year)