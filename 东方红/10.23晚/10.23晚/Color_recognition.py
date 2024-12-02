import sensor
import image
import time
import pyb

# 初始化摄像头
sensor.reset()
sensor.set_pixformat(sensor.RGB565)  # 设置摄像头格式为 RGB565
sensor.set_framesize(sensor.QVGA)    # 设置帧大小为 QVGA (320x240)
sensor.skip_frames(time=2000)        # 跳过一些帧，让摄像头稳定下来
sensor.set_auto_whitebal(False)      # 关闭自动白平衡，使颜色更稳定

# 初始化串口
uart = pyb.UART(3, 115200, timeout_char=1000)  # UART3, 波特率 115200

# 设置 LED 常亮 (选择你想要的颜色)
led = pyb.LED(3)  # LED(1) 为红色，LED(2) 为绿色，LED(3) 为蓝色
led.on()  # 开启LED，使其常亮

# 红色和绿色的阈值范围
#red_threshold = (10, 72, 25, 55, 15, 58)   # 红色的 HSV 范围
red_threshold = (9, 49, 3, 74, -86, 96)   # 红色的 HSV 范围

green_threshold = (47, 86, -67, -28, -26, 30) # 绿色的 HSV 范围
#green_threshold = (27, 67, -66, -27, 10, 62) # 绿色的 HSV 范围
data=[9,0]
clock = time.clock()
while(True):
    clock.tick()
    img = sensor.snapshot()  # 捕获一帧图像

    # 查找红色和绿色的物体
    red_blobs = img.find_blobs([red_threshold], pixels_threshold=200, area_threshold=1000)
    green_blobs = img.find_blobs([green_threshold], pixels_threshold=200, area_threshold=1000)

    if red_blobs:
        # 如果检测到红色
        data=[9,1]
        print("Red detected")
    elif green_blobs:
        # 如果检测到绿色
        data=[9,2]

        print("Green detected")
    else:
        # 没有检测到红色或绿色
        data=[9,0]
        print("No color detected")
    data_out = bytearray(data)
    uart.write(data_out)

