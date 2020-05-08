## 中国象棋控件

作者：康林(kl222@126.com)

-------------------------

- [简介](#简介)
- [捐赠](#捐赠)
- [屏幕截图](#屏幕截图)
- [许可协议](License.md)
- [修改日志](ChangeLog.md)
- [下载安装包](#下载安装包)
- [开发](#开发)
  + [编译](#编译)
  + [调试](#调试)
  + [使用](#使用)
    - [属性](#属性)
    - [方法](#方法)
    - [事件](#事件)

-------------------------

#### 简介
中国象棋控件。

- 中国象棋 ActivX 控件

- 项目主页：https://github.com/KangLin/ChineseChessControl

[![Build status](https://ci.appveyor.com/api/projects/status/lxs0mxtdl238yrq4?svg=true)](https://ci.appveyor.com/project/KangLin/chinesechesscontrol)

#### 捐赠
本软件如果对你有用，或者你喜欢它，请你捐赠，支持作者。谢谢！

[![捐赠](https://gitee.com/kl222/RabbitCommon/raw/master/Src/Resource/image/Contribute.png "捐赠")](https://github.com/KangLin/RabbitCommon/raw/master/Src/Resource/image/Contribute.png "捐赠")

#### 屏幕截图

![屏幕截图](Documents/Image/ShotScreen.png)

#### [许可协议](License.md)
#### [修改日志](ChangeLog.md)
#### [下载安装包](https://github.com/KangLin/ChineseChessControl/releases/latest)

- windows
    - [ChineseChessControl-Setup-v1.0.0.exe](https://github.com/KangLin/ChineseChessControl/releases/download/v1.0.0/ChineseChessControl-Setup-v1.0.0.exe)
  Windows安装包，支持 Windows xp 以上系统

#### 开发

##### 编译
- 用 cmake , 建议使用此方法编译

      mkdir build
      cd build
      cmake ..
      cmake --build .

- 用VC6.0打开 Src/ChineseChessControl.dsw,直接编译。不再支持此方法编译
- 用 VC2017 打开 Src/ChineseChessControl.sln ,直接编译。不再支持此方法编译

##### 调试
###### VC6.0
- 打开 ActiveX control test container 工具  
![打开 ActiveX control test container 工具](Documents/Image/OpenActivexControlTestContainer.png)
- 注册中国象棋控件  
  这一步在编译后，会自动执行。如果没有成功，可以按下面方法之一注册：  
  **注意**:需要管理员权限
  + 手工注册

				regsvr32 /s /c "D:\Source\ChineseChessControl\Src\.\DebugU\ChineseChessControl.ocx" 

  + 用 ActiveX control test container 注册
    - 打开注册控件  
![打开注册控件](Documents/Image/OpenRegisterControl.png)
    - 注册中国象棋控件  
      + ![](Documents/Image/RegisterControl.PNG)
      + ![](Documents/Image/RegisterChineseChessControl.PNG)
      + ![](Documents/Image/RegisteredChineseChessControl.PNG)
- 插入中国象棋控件  
![](Documents/Image/InsertChineseChessControl.PNG)
- 调试  
![](Documents/Image/Debug.PNG)

###### VS 2017

- 从 VS 2010 没有自带 ActivX control test container 工具，而是以例子程序的方式提供。所以你可以从 vc6.0 中复制过来，或者，从 VS 2017 安装的例子程序中编译得到。

[Testing Properties and Events with Test Container](https://docs.microsoft.com/en-us/cpp/mfc/testing-properties-and-events-with-test-container)

如果没安装，则可从 github 上下载[源码](https://github.com/microsoft/VCSamples/tree/master/VC2010Samples/MFC/ole/TstCon)

- 工具->外部工具->添加
  + ![](Documents/Image/OpenActivexControlTestContainerVC2013.png)
  + ![](Documents/Image/AddActivexControlTestContainer.PNG)
- 剩下的调试步骤与上面VC6.0的一样

#### 使用
##### 属性:
- Enabled: 允许或禁止控件
- QiPangColor: 棋盘颜色
- TiShiBoxColor: 提示框的颜色
- QiPangPicture: 棋盘图片
- QiPangLayout: 棋盘布局。取下列值：
  + NoQi：无棋子
  + OnlyTopRed = 1：只有上面红棋子
  + OnlyBottomBlack = 2：只有下面红棋子
  + SwapRedBetweenBlack = 4：交换棋子
  + OnlyTopBlack = OnlyTopRed | SwapRedBetweenBlack：只有上面黑棋子
  + OnlyBottomRed = OnlyBottomBlack | SwapRedBetweenBlack：只有下面红棋子
  + TopRedAndBottomBlack = OnlyTopRed |      OnlyBottomBlack：上红下黑
  + TopBlackAndBottomRed = OnlyTopBlack | OnlyBottomRed | SwapRedBetweenBlack：上黑下红

注意：如果布局不完全，则由用户控制属性（Enabled）以决定是否下棋。

- StartSide: 开始走棋时的状态。这个要在 ReStart 前设置。取下列值：
  + RedReadly：红棋准备走
  + RedWalked：红棋正在走
  + BlackReadly：黑棋准备走
  + BlackWalked：黑棋正在走

- CurrentSide：走棋时的状态。取上面的值。

##### 方法:
- NextStep(): 下一步
- PreviouStep(): 上一步
- ReStart(): 重新开始
- SaveChess(BSTR lpcszFileName): 保存棋局
- LoadChess(BSTR lpcszFileName): 装载棋局并设置为结束状态
- LoadChessStart(BSTR lpcszFileName): 装载棋局并设置为开始状态
- QiPangInterconvert():

##### 事件:
- MoveChess(short x, short y, ENUM_QiZi chess):走棋。此事件在属性 CurrentSide 改变前发生。
