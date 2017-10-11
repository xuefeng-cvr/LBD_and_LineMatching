
## LBD_and_LineMatching
本代码基于origin
http://www.mip.informatik.uni-kiel.de/tiki-download_file.php?fileId=1965
基于github用户mtamburrano的修改版本
https://github.com/mtamburrano/LBD_Descriptor


#### 依赖项

 - OpenCV
 - Arpack
 - superlu


#### 实现功能
通过EDlines算法提取图像的线段特征，再用LBD构建线段的描述子信息，并用图匹配的方法进行两张图之间的特征线段的匹配，其中test.hpp用于记录matching的结果和线段提取的结果


