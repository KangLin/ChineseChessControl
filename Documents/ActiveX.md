## 中国象棋 ActiveX 控件

作者： 康林(kl222@126.com)

---------------------------------------

### 编译

- 用 cmake , 建议使用此方法编译

      git clone https://github.com/KangLin/ChineseChessControl.git
      mkdir build
      cd build
      cmake .. -DCMAKE_INSTALL_PREFIX=`pwd`/install -DCMAKE_BUILD_TYPE=Release  #配置
      cmake --build . --config=Release                   #编译
      cmake --build . --config=Release --target install  #安装

### 调试
#### VC6.0

- 打开 ActiveX control test container 工具  
![打开 ActiveX control test container 工具](Image/OpenActivexControlTestContainer.png)
- 注册中国象棋控件  
  这一步在编译或安装时，会自动完成。如果没有成功，可以按下面方法之一注册：  
  **注意**:需要管理员权限
  + 手工注册，使用 regsvr32 命令

        regsvr32 /s /c "D:\Source\ChineseChessControl\Src\.\DebugU\ChineseChessControl.ocx" 

  + 用 ActiveX control test container 注册
    - 打开注册控件  
![打开注册控件](Image/OpenRegisterControl.png)
    - 注册中国象棋控件  
      + ![](Image/RegisterControl.PNG)
      + ![](Image/RegisterChineseChessControl.PNG)
      + ![](Image/RegisteredChineseChessControl.PNG)
- 插入中国象棋控件  
![](Image/InsertChineseChessControl.PNG)
- 调试  
![](Image/Debug.PNG)

#### VS 2017

- 从 VS 2010 没有自带 ActivX control test container 工具，而是以例子程序的方式提供。所以你可以从 vc6.0 中复制过来，或者，从 VS 2017 安装的例子程序中编译得到。

[Testing Properties and Events with Test Container](https://docs.microsoft.com/en-us/cpp/mfc/testing-properties-and-events-with-test-container)

如果没安装，则可从 github 上下载[源码](https://github.com/microsoft/VCSamples/tree/master/VC2010Samples/MFC/ole/TstCon)

- 工具->外部工具->添加
  + ![](Image/OpenActivexControlTestContainerVC2013.png)
  + ![](Image/AddActivexControlTestContainer.PNG)
- 剩下的调试步骤与上面VC6.0的一样

### 使用

- [如何：向 Windows 窗体添加 ActiveX 控件](https://docs.microsoft.com/zh-cn/dotnet/framework/winforms/controls/how-to-add-activex-controls-to-windows-forms)

### 控件

[接口文件](../Src/ActiveX/ChineseChessActiveX.idl)

#### 属性:

- Enabled: 允许或禁止控件
- QiPangColor: 棋盘颜色
- TiShiBoxColor: 提示框的颜色
- QiPangPicture: 棋盘图片
- BoardLayout: 棋盘布局。取下列值：
  + NoQi = 0,
  + OnlyTopBlack = 1,
  + OnlyBottomRed = 2,
  + SwapRedBetweenBlack = 4,
  + OnlyTopRed = OnlyTopBlack | SwapRedBetweenBlack,
  + OnlyBottomBlack = OnlyBottomRed | SwapRedBetweenBlack,
  + TopBlackAndBottomRed = OnlyTopBlack | OnlyBottomRed,
  + TopRedAndBottomBlack = TopBlackAndBottomRed | SwapRedBetweenBlack  
  **注意**：如果布局不完全，则由用户控制属性（Enabled）以决定是否下棋。
- EnablePromptSound: 允许提示音
- EnablePromptMessage: 允许提示消息
- RedName: 设置红方名
- BlackName: 设置黑方名
- StartTime: 设置开始时间
- EndTime: 设置结束时间
- GameTags: 设置标签

#### 方法:

- NextStep(): 下一步
- PreviouStep(): 上一步
- GoChess(SHORT i, SHORT j): 走棋
- SaveChessGame(BSTR szFile): 保存棋局
- LoadChessGame(BSTR szFile): 装载棋局并设置为初始状态

#### 事件:

- EventGoChess(short i, short i, ENUM_QiZi chess): 走棋。

棋盘描述

       [0][0] ------------------> i 或 x 方向
              |
              |
              |
              |
              |
              |
             \|/                 [9][10]
              
         j 或 y 方向
 
### 开发
#### 字符编码

WIndows 中文系统字符编码默认为GB2313。
linux系统下字符编码一般使用 UTF-8 。
所以本项目跨平台部分的文件中的字符釆用**多字节编码**，
而与VC相关的部分文件使用 UNICODE 编码（位于：Src\ActiveX 和 App\MFC）。
