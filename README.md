# myVO
跟着SLAM十四讲写一写VO！！！！

# Version0.4 and before

是直接抄的SLAM十四讲第一版书的第九章的代码，给过了一遍。


# Version0.5

## 修改version0.4的两个BUG
1.
当我使用Version0.4版本直接跑完整的f1_xyz数据时，会出现段错误这个报错，经过调试后，发现这个报错是因为再特征匹配的函数中，得到的匹配结果是空，而因为没有盼空的操作，所以就导致使用了空指针；这里我实现了初始化函数，当跟踪丢失时，就让VO初始化，并且初始化地图资源。

2.（terminate called after throwing an instance of 'std::out_of_range'），就是再rgb_files读取名字的时候，他把最后一行空行也读进去了，然后当数据跑完的时候，就该把空行给弄进去了，然后就报错了，因为读不出来图片什么的。。把这个空行去除就行了 。



实现RGBD数据下的长时间的VO


# Version0.6

## 添加了evaluation文件夹可以进行算法评价。
如果要使用trajectoryError.cpp这个脚本，请根据文件内的estimated.txt和groundtruth.txt的格式要求；如果你的groundtruth.txt是通过associate.py生成的，可以运行一下processGroundTruth.cpp这个脚本

### 目前已知的存在的bug
其实都还好，就是莫名奇妙的estimated.txt和groundtruth的大小不等，estimated居然会比groundtruth多两行。。这个没有解决，然后就是我发现estimated和groundtruth画的图大致上很想，但是数据却差别，感觉是挺大的，是否有什么转换还是什么的我没弄清楚？

## 在run_vo.cpp中添加了fps的显示，以及代码总运行时间的测试（从开始处理图像开始计算）

## 在map中添加了一个新的成员frames_来存放位姿估计成功的，帧。
