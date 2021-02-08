#### 0.0.3 version

该版本在 0.0.2 的基础上，完善了 Line2d::checkSegment 和 Segment2d::splitLineSegment. 并将 Line2d.h 和 Segment2d.h 合并至 Line2d.h, 增加了Line2d.cpp 和 bsp.cpp 文件用于部分函数的实现.

##### 注:

1. 由于电脑环境配置问题, 原版本中的 #include\<Eigen/Dense\> 改为了 #include\<eigen3/Eigen/Dense\>. 
2. 合并和增加文件的原因是为了避免可能的编译问题.
3. 以上代码虽然可以运行, 但是未经测试, 如果出 bug 了我可以快乐甩锅 :laughing:

#### 0.0.4 version

该版本在 0.0.3 的基础上，修复了函数中的部分bug，补充了部分注释。