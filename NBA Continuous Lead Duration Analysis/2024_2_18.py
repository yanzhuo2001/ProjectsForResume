import json
import matplotlib.pyplot as plt
import numpy as np

# 加载 JSON 数据
with open('data_handled/Lead_Duration_2000.json.json', 'r') as file:
    data = json.load(file)

# 分析数据并计算平均建立时间
lead_range = range(10, 31)  # 领先分数从 10 到 20
average_build_times = []

for lead in lead_range:
    total_time = 0
    count = 0
    for game_id, leads in data.items():
        for lead_info in leads:
            if lead_info['maxlead'] == lead:
                build_time = lead_info['buildtime']
                total_time += build_time
                count += 1
    average_time = total_time / count if count else 0
    average_build_times.append(average_time)

# 绘制折线图
plt.figure(figsize=(10, 6))
plt.plot(lead_range, average_build_times, marker='o')
plt.title('Average Time to Establish Lead (10-30 points) in 2000')
plt.xlabel('Lead Points')
plt.ylabel('Average Build Time (seconds)')
plt.grid(True)
plt.xticks(lead_range)

# 保存图像
plt.savefig('images/2000.png')