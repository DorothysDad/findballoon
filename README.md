# Find balloon
Find white balloon using linemod and contours

# overview

The project aims at to locate the white balloon accurately and know whether the balloon is unbroken.

- 滤波,形态学操作对图像进行滤波

- 设置阈值寻找轮廓,并根据几何特征约束,初步得到气球位置

- 预训练气球多角度的图片,得到linemod所需参数

- 使用linemod算法,设置阈值再次筛选出气球

- 根据linemod反馈的气球信息,随机取100个像素点,若为白色,则反馈为气球

  ![2019-12-22 17-52-34屏幕截图](/home/allen/图片/2019-12-22 17-52-34屏幕截图.png)

## Prepare

- PC：i5
- Software environment：Ubuntu16.04、 opencv3 or higher version, MIPP library

## How to used

### build

```
cd findballoon
cd build
cmake ..
make -j
cd ..&& ./bin/hello
```

<video id="video" controls="" preload="none">
    <source id="mp4" src="/home/allen/视频/1.mp4" type="video/mp4">
</video>



