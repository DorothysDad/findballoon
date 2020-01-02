
# Find balloon
Find white balloon using linemod and contours

# overview

The project aims at to locate the white balloon accurately and know whether the balloon is unbroken.

- 滤波,形态学操作对图像进行滤波

- 设置阈值寻找轮廓,并根据几何特征约束,初步得到气球位置

- 预训练气球多角度的图片,得到linemod所需参数

- 使用linemod算法,设置阈值再次筛选出气球

- 根据linemod反馈的气球信息,随机取100个像素点,若为白色,则反馈为气球

  ![2019-12-22 17-52-34屏幕截图](https://github.com/DorothysDad/findballoon/blob/master/doc/1.png)

## Prepare

- PC：i5
- Software environment：Ubuntu16.04、 opencv3 or higher version, MIPP library

## How to used
## Test
- 训练文件为test.cpp,需更改相应路径训练得yaml配置文件
- 以test/case3为例训练了不同大小的气球
- 若训练完,则需修改CmakeLists文件并加载配置文件
### build

```
cd findballoon
cd build
cmake ..
make -j
cd ..&& ./bin/hello
```
## Improevd
- ~~增加了多角度多大小的配置文件,提高了linemod的稳定性,确保气球能被识别~~
- 重叠问题

  ![2019-12-22 17-52-34屏幕截图](https://github.com/DorothysDad/findballoon/blob/master/doc/x.gif)

# Contributor 
  ### [shisanchuan](https://github.com/ShiSanChuan)

