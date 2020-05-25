## 开发者文档
作者：康林 (kl222@126.com)

--------------------------

- [设计思想](#设计思想)
  + [中国象棋基本规则算法与结构](#中国象棋基本规则算法与结构)
  + [MFC 扩展动态库](#MFC-扩展动态库)
  + [中国象棋 ActiveX 控件](ActiveX.md)

### 设计思想

本项目建立一个 C++ 中国象棋组件。方便集成到应用程序中。
由于界面开发有着不同的开发框架，所以针对界面需要对不同框架进行适配。
而中国象棋算法与结构与界面相对独立，所以本项目把它单独做为一部分。
针对不同的界面开发框架，本项目提供相应的适配。

- [中国象棋基本规则算法与结构](#中国象棋基本规则算法与结构)，代码位于 Src 下
- 界面适配
  + 中国象棋 MFC 扩展动态库，代码位于 Src/MFC 下
  + [中国象棋 ActiveX 控件](ActiveX.md)，代码位于 Src/ActiveX 下
  + 中国象棋 Qt 插件

### 中国象棋基本规则算法与结构

代码位于源码树中的 Src 目录下。
它提供中国象棋的基本规则算法与结构。

### MFC 扩展动态库

它实现了中国象棋 MFC 扩展动态库。只能由 MFC 程序使用。
**注意**:在使用时，必须在程序初始化时（一般在 main 函数开始时)，必须先调用 ChineseChessViewNewDynLinkLibrary() 初始化资源。

### 编译

- 用 cmake , 建议使用此方法编译

      git clone https://github.com/KangLin/ChineseChessControl.git
      mkdir build
      cd build
      cmake .. -DCMAKE_INSTALL_PREFIX=`pwd`/install      #配置
      cmake --build . --config=Release                   #编译
      cmake --build . --config=Release --target install  #安装
