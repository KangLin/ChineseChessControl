## 开发者文档
作者：康林 (kl222@126.com)

--------------------------

- [设计思想](#设计思想)
  + [中国象棋库](#中国象棋库)
  + [界面适配](界面适配)
    - [中国象棋 MFC 扩展动态库](#中国象棋-MFC-扩展动态库)
    - [中国象棋 ActiveX 控件](ActiveX.md)
    - [中国象棋 Qt 插件](#中国象棋-Qt-插件)
- [编译](Build.md)
- [使用](#使用)

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
  + [中国象棋 MFC 扩展动态库](#中国象棋-MFC-扩展动态库)，代码位于 [UI/MFC](../UI/MFC) 下
  + [中国象棋 ActiveX 控件](ActiveX.md)，代码位于 [UI/ActiveX](../UI/ActiveX) 下
  + [中国象棋 Qt 插件](#中国象棋-Qt-插件)，代码位于 [UI/Qt](../UI/Qt) 下

### 中国象棋库

代码位于源码树中的 [Src](../Src) 目录下。
它提供中国象棋的基本规则算法与结构。接口详见：[ChineseChess.h](../Src/ChineseChess.h)

+ 中国象棋流程控制
+ 中国象棋基本规则
+ 棋局保存和复盘

### 界面适配
#### 中国象棋 MFC 扩展动态库

它实现了中国象棋 MFC 扩展动态库。只能由 MFC 程序使用。代码位于 [UI/MFC](../UI/MFC) 下，接口详见：[ChineseChessView.h](../UI/MFC/ChineseChessView.h)。
其使用方式与使用普通的 MFC 类一样。  
**注意**:在使用时，必须在程序初始化时（一般在 main 函数开始时)，必须先调用 ChineseChessViewNewDynLinkLibrary() 初始化资源。

#### 中国象棋 Qt 插件

它实现了中国象棋 Qt 插件，代码位于 [UI/Qt](../UI/Qt) 下。接口详见：[FrmChineseChess.h](../UI/Qt/FrmChineseChess.h)。
其使用方式与使用普通Qt控件类一样。它还能在 Qt 设计器中使用。
使用：
- 在程序开始时调用一次 InitResource() 函数，初始化资源。
- 在程序结束时调用一次 CleanResource() 函数，释放资源;
- Qt 设计器中使用
  + 复制安装目录（bin、lib）下的所有动态库文件到 ${Qt_Install_Root}/plugins/designer 下。
  就可以在 qt 设计器的控件窗口中看到此插件。然后就与使用普通Qt控件一样。

### [编译](Build.md)

### 使用
#### 使用 cmake 项目管理工具（建议使用此方法）
- 使用 ChineseChess
  + 使用 find_package 查找你需要的库。例如,你需要从 ChineseChess 为一个新的界面框架实现中国象棋：

        find_package(ChineseChess)  #查找 ChineseChess 库
        if(ChineseChess_FOUND)
            target_link_libraries(${PROJECT_NAME} PUBLIC ChineseChess)  # 应用链接 ChineseChess 库
        endif()
      
- 使用 ChineseChessView ，只能由 MFC 程序使用

      find_package(ChineseChessView)  #查找 ChineseChessView 库
      if(ChineseChessView_FOUND)
          target_link_libraries(${PROJECT_NAME} PUBLIC ChineseChessView)  # 应用链接 ChineseChessView 库
      endif()

- 使用 ChineseChessActiveX ，只能由 WINDOWS 程序使用。参见：[ActiveX](ActiveX.md#使用)

- 使用 ChineseChessQt 

      find_package(ChineseChessQt)  #查找 ChineseChessQt 库
      if(ChineseChessQt_FOUND)
          target_link_libraries(${PROJECT_NAME} PUBLIC ChineseChessQt)  # 应用链接 ChineseChessQt 库
      endif()

#### 使用其它项目管理工具
请详见[安装后的目录](Build.md#安装目录)。然后使用相应项目管理工具特定的方式指定头文件目录与链接库。
