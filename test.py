 # -*- coding: utf-8 -*
import sys
sys.path.remove('/usr/local/lib/python2.7/dist-packages')
import cv2
import numpy as np
import pyrealsense2 as rs
pipeline = rs.pipeline()
config = rs.config()
config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
pipeline.start(config)
 
# image = cv2.imread('/home/allen/detect/cap0.jpg') # 根据路径读取一张图片
# info = image.shape    #获取图片的宽 高 颜色通道信息
# height = info[0]  #高
# width = info[1]   #宽
# dstheight = int(height*0.5)   #缩小为原来的0.5倍   可根据自己的要求定义
# dstwidth = int(width*0.5) 
# dst = cv2.resize(image,(dstwidth,dstheight),0,0) 
# cv2.imshow("BGR", dst) # 显示图片

hsv_low = np.array([0, 0, 0])
hsv_high = np.array([0, 0, 0])

# 下面几个函数，写得有点冗余

def h_low(value):
    hsv_low[0] = value

def h_high(value):
    hsv_high[0] = value

def s_low(value):
    hsv_low[1] = value

def s_high(value):
    hsv_high[1] = value

def v_low(value):
    hsv_low[2] = value

def v_high(value):
    hsv_high[2] = value

cv2.namedWindow('image')
cv2.createTrackbar('H low', 'image', 0, 180, h_low) 
cv2.createTrackbar('H high', 'image', 0, 180, h_high)
cv2.createTrackbar('S low', 'image', 0, 255, s_low)
cv2.createTrackbar('S high', 'image', 0, 255, s_high)
cv2.createTrackbar('V low', 'image', 0, 255, v_low)
cv2.createTrackbar('V high', 'image', 0, 255, v_high)

while True:
   
    frames = pipeline.wait_for_frames()
   
    color_frame = frames.get_color_frame()
    
    color_image = np.asanyarray(color_frame.get_data())
    dst = cv2.cvtColor(color_image, cv2.COLOR_BGR2HSV) # BGR转HSV
    print(dst[20,20])
    print(dst[350,350])
    cv2.imshow('dst', dst)
    dst = cv2.inRange(dst, hsv_low, hsv_high) # 通过HSV的高低阈值，提取图像部分区域
    cv2.imshow('ddd',dst)
    
    # Show images
    cv2.namedWindow('RealSense', cv2.WINDOW_AUTOSIZE)
    cv2.imshow('RealSense',color_image)
 
    key = cv2.waitKey(1)
    # Press esc or 'q' to close the image window
    if key & 0xFF == ord('q') or key == 27:
        cv2.destroyAllWindows()
        pipeline.stop()
        break
cv2.destroyAllWindows()
