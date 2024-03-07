import json
import numpy as np

years = [2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017,
         2018, 2019, 2020, 2021, 2022]

def summarize_and_save_lead_data(years, lead_range=range(10, 31)):
    for year in years:
        with open('data_handled/Lead_Duration_'+str(year)+'.json', 'r') as file:
            data = json.load(file)

        summary_data = {
            'average_build_times': {},
            'standard_deviations': {},
            'lead_counts': {},
            'lead_details': {}
        }

        for lead in lead_range:
            build_times = [lead_info['buildtime'] for game_id, leads in data.items() for lead_info in leads if
                            lead_info['maxlead'] == lead]

            # 如果没有数据点，为了避免除以零的错误，跳过这个领先分数
            if not build_times:
                continue

            average_time = np.mean(build_times)
            std_dev = np.std(build_times)
            count = len(build_times)

            summary_data['average_build_times'][lead] = average_time
            summary_data['standard_deviations'][lead] = std_dev
            summary_data['lead_counts'][lead] = count
            summary_data['lead_details'][lead] = build_times

        # 将摘要数据保存为JSON
        with open(f'summary_data/summary_data_{year}.json', 'w') as file:
            json.dump(summary_data, file, indent=4)

summarize_and_save_lead_data(years)