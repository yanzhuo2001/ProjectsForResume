def check_file_content(filename):
    try:
        with open(filename, 'r', encoding='Windows-1252') as f:
            for i in range(5):  # 打印前5行内容
                print(repr(f.readline().strip()))
    except Exception as e:
        print("Error reading file:", e)

filename = "BaconCastFull.txt"
check_file_content(filename)
