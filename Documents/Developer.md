## 开发者文档
作者：康林 (kl222@126.com)

--------------------------

- [设计思想](#设计思想)
  + [中国象棋库](#中国象棋库)
  + [界面适配](界面适配)
    - [中国象棋 MFC 扩展动态库](#中国象棋-MFC-扩展动态库)
    - [中国象棋 ActiveX 控件](ActiveX.md)
    - [中国象棋 Qt 插件](#中国象棋-Qt-插件)
- [编译](#编译)

--------------------------

### 设计思想

本项目建立一个 C++ 中国象棋组件。方便集成到应用程序中。
由于界面开发有着不同的开发框架，所以针对界面需要对不同框架进行适配。
而中国象棋算法与结构与界面相对独立，所以本项目把它单独做为一部分。
针对不同的界面开发框架，本项目提供相应的适配。

- [中国象棋库](#中国象棋库)，代码位于 [Src](../Src) 下
  + 中国象棋基本规则
  + 棋局保存和复盘
- 界面适配
  + [中国象棋 MFC 扩展动态库](#中国象棋-MFC-扩展动态库)，代码位于 [Src/MFC](../Src/MFC) 下
  + [中国象棋 ActiveX 控件](ActiveX.md)，代码位于 [Src/ActiveX](../Src/ActiveX) 下
  + [中国象棋 Qt 插件](#中国象棋-Qt-插件)，代码位于 [Src/Qt](../Src/Qt) 下

### 中国象棋库

代码位于源码树中的 [Src](../Src) 目录下。
它提供中国象棋的基本规则算法与结构。详见接口：[ChineseChess.h](../Src/ChineseChess.h)

+ 中国象棋流程控制
+ 中国象棋基本规则
+ 棋局保存和复盘

### 界面适配
#### 中国象棋 MFC 扩展动态库

它实现了中国象棋 MFC 扩展动态库。只能由 MFC 程序使用。代码位于 [Src/MFC](../Src/MFC) 下，详见：[ChineseChessView.h](../Src/MFC/ChineseChessView.h)。
其使用方式与使用普通的 MFC 类一样。  
**注意**:在使用时，必须在程序初始化时（一般在 main 函数开始时)，必须先调用 ChineseChessViewNewDynLinkLibrary() 初始化资源。

#### 中国象棋 Qt 插件

它实现了中国象棋 Qt 插件，代码位于 [Src/Qt](../Src/Qt) 下。详见：[FrmChineseChess.h](../Src/Qt/FrmChineseChess.h)。
其使用方式与使用普通Qt控件类一样。它还能在 Qt 设计器中使用。
使用：
- 在程序开始时调用一次 InitResource() 函数，初始化资源。
- 在程序结束时调用一次 CleanResource() 函数，释放资源;
- Qt 设计器中使用
  + 复制安装目录（bin、lib）下的所有动态库文件到 ${Qt_Install_Root}/plugins/designer 下。
  就可以在 qt 设计器的控件窗口中看到此插件。然后就与使用普通Qt控件一样。

### 编译

- 依赖
  + 工具
    - Microsoft Visual studio c++
    - GNU c++
    - android sdk and ndk
    - [CMake](https://www.cmake.org)
    - Automake and autoconfig
  + 库
    - [可选] Qt: https://www.qt.io/
    - [可选] RabbitCommon: https://github.com/KangLin/RabbitCommon
- 用 cmake , 建议使用此方法编译

      git clone https://github.com/KangLin/RabbitCommon.git
      git clone https://github.com/KangLin/ChineseChessControl.git
      mkdir build
      cd build
      cmake .. -DCMAKE_INSTALL_PREFIX=`pwd`/install -DCMAKE_BUILD_TYPE=Release     #配置
      cmake --build . --config=Release                   #编译
      cmake --build . --config=Release --target install  #安装


**注意**：如果使用 MSVC ,则需要加上 -DCMAKE_BUILD_TYPE=Debug ，否则当编译 Debug 时会出现下面错误：

    RabbitCommonTools.obj : error LNK2019: 无法解析的外部符号 "int __cdecl qInitResources_translations_RabbitCommon(void)" (?qInitResources_translations_RabbitCommon@@YAHXZ)，该符号在函数 "void __cdecl g_RabbitCommon_InitResource(void)" (?g_RabbitCommon_InitResource@@YAXXZ) 中被引用
    RabbitCommonTools.obj : error LNK2019: 无法解析的外部符号 "int __cdecl qCleanupResources_translations_RabbitCommon(void)" (?qCleanupResources_translations_RabbitCommon@@YAHXZ)，该符号在函数 "void __cdecl g_RabbitCommon_CleanResource(void)" (?g_RabbitCommon_CleanResource@@YAXXZ) 中被引用
