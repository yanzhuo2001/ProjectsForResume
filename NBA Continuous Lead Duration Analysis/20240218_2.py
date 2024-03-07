import json
import matplotlib.pyplot as plt
import numpy as np  # 导入 NumPy 库来计算标准差

years = [2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017,
         2018, 2019, 2020, 2021, 2022]

def draw_graphs(year):
    # 加载 JSON 数据
    with open(f'data_handled/Lead_Duration_{year}.json', 'r') as file:
        data = json.load(file)

    lead_range = range(10, 31)  # 领先分数从 10 到 30
    average_build_times = []
    standard_deviations = []
    lead_counts = []  # 记录每个领先分数的出现次数

    for lead in lead_range:
        build_times = []  # 记录建立时间
        for game_id, leads in data.items():
            for lead_info in leads:
                if lead_info['maxlead'] == lead:
                    build_times.append(lead_info['buildtime'])

        # 计算平均建立时间和标准差
        average_time = np.mean(build_times) if build_times else 0
        std_dev = np.std(build_times) if build_times else 0
        average_build_times.append(average_time)
        standard_deviations.append(std_dev)
        lead_counts.append(len(build_times))  # 记录次数

    # 绘制平均时间图表
    plt.figure(figsize=(10, 6))
    plt.errorbar(lead_range, average_build_times, yerr=standard_deviations, marker='o', capsize=5)
    plt.title(f'Average Time to Establish Lead (10-30 points) with Std Dev in {year}')
    plt.xlabel('Lead Points')
    plt.ylabel('Average Build Time (seconds)')
    plt.grid(True)
    plt.xticks(lead_range)
    plt.savefig(f'images/AverageTimeToGenerateLeads_{year}.png')

    # 绘制领先分数的总次数图表
    plt.figure(figsize=(10, 6))
    plt.bar(lead_range, lead_counts)
    plt.title(f'Number of Leads by Score in {year}')
    plt.xlabel('Lead Points')
    plt.ylabel('Number of Occurrences')
    plt.xticks(lead_range)
    plt.grid(axis='y')
    plt.savefig(f'images/LeadCounts_{year}.png')

for year in years:
    draw_graphs(year)