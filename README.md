## [<img src="Src/Res/Picture/69/bjiang.png" title="中国象棋控件" width="32" height="32"/>中国象棋控件](https://github.com/KangLin/ChineseChessControl)

作者：康林 (kl222@126.com)

------------------------

[![Gitter](https://badges.gitter.im/ChineseChessControl/community.svg)](https://gitter.im/ChineseChessControl/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)
[![Build status](https://ci.appveyor.com/api/projects/status/lxs0mxtdl238yrq4?svg=true)](https://ci.appveyor.com/project/KangLin/chinesechesscontrol)
[![Build Status](https://travis-ci.org/KangLin/ChineseChessControl.svg)](https://travis-ci.org/KangLin/ChineseChessControl)

-------------------------

- [简介](#简介)
- [屏幕截图](#屏幕截图)
- [下载安装包](#下载安装包)
- [贡献](#贡献)
  - [捐赠](#捐赠)
- [许可协议](License.md)
- [修改日志](ChangeLog.md)
- [文档](#文档)

-------------------------

#### 简介
中国象棋控件。

- 项目主页: http://kanglin.github.io/ChineseChessControl/
- 项目位置：
  + 主库: https://github.com/KangLin/ChineseChessControl
  + 镜像:
    - https://gitee.com/kl222/ChineseChessControl
    - https://sourceforge.net/projects/chinesechesscontrol/
    - https://gitlab.com/kl222/ChineseChessControl
    - https://launchpad.net/chinesechesscontrol

##### 功能
- 控件
  + [x] [中国象棋库](Documents/Developer.md#中国象棋库)
    - [x] 中国象棋基本规则
    - [x] 棋局保存和复盘
  + [x] [中国象棋 MFC 扩展动态库](Documents/Developer.md#中国象棋-MFC-扩展动态库)
  + [x] [中国象棋 ActiveX 控件](ActiveX.md)
  + [x] [中国象棋 Qt 插件](Documents/Developer.md#中国象棋-Qt-插件)
- [ ] 中国象棋博弈引擎与通信协议
- [x] 中国象棋程序
  + [x] 单机版本
      + [x] MFC 版本
      + [x] Qt 版本
  + [ ] 联网版本。欢迎使用本项目库应用到你的中国象棋程序。

*图例：*

+ [x] 表示已完成的功能
+ [ ] 表示尚未完成的功能

- 支持平台：
  + [x] Windows
  + [x] Linux
  + [x] Android
  + [ ] mac、IOS 本人无此设备，请你自行编译、测试

#### 屏幕截图

![屏幕截图](Documents/Image/ShotScreen.png "屏幕截图")
![Windows 屏幕截图](Documents/Image/windowsShotScreen.png "Windows 屏幕截图")
![Qt 屏幕截图](Documents/Image/QtShotScreen.png "Qt 屏幕截图")
![Android 屏幕截图](Documents/Image/androidShotScreen.jpg "Android 屏幕截图")

#### [下载安装包](https://github.com/KangLin/ChineseChessControl/releases/latest)
+ [最后版本](https://github.com/KangLin/ChineseChessControl/releases/latest)
+ 当前版本：
  - windows x86
      - [MSVC 2017 x86 v2.0.5](https://github.com/KangLin/ChineseChessControl/releases/download/v2.0.5/ChineseChessControl-Setup-msvc1916-x86-v2.0.5.exe)
      - [MSVC 2015 x86 v2.0.5](https://github.com/KangLin/ChineseChessControl/releases/download/v2.0.5/ChineseChessControl-Setup-msvc1900-x86-v2.0.5.exe)
      - [MSVC 2013 x86 v2.0.5](https://github.com/KangLin/ChineseChessControl/releases/download/v2.0.5/ChineseChessControl-Setup-msvc1800-x86-v2.0.5.exe)

  - windows x86_64
      - [MSVC 2017 x86_64 v2.0.5](https://github.com/KangLin/ChineseChessControl/releases/download/v2.0.5/ChineseChessControl-Setup-msvc1916-x86_64-v2.0.5.exe)
      - [MSVC 2015 x86_64 v2.0.5](https://github.com/KangLin/ChineseChessControl/releases/download/v2.0.5/ChineseChessControl-Setup-msvc1900-x86_64-v2.0.5.exe)
      - [MSVC 2013 x86_64 v2.0.5](https://github.com/KangLin/ChineseChessControl/releases/download/v2.0.5/ChineseChessControl-Setup-msvc1800-x86_64-v2.0.5.exe)

  Windows安装包，支持 Windows xp 以上系统。安装完成后，使用请详见：[开发者文档](Documents/Developer.md#调试)

  - android
      + [ChineseChess_arm64-v8a_v2.0.5.apk](https://github.com/KangLin/ChineseChessControl/releases/download/v2.0.5/ChineseChess_arm64-v8a_v2.0.5.apk)
      + [ChineseChess_armeabi-v7a_v2.0.5.apk](https://github.com/KangLin/ChineseChessControl/releases/download/v2.0.5/ChineseChess_armeabi-v7a_v2.0.5.apk)

  - linux
      - [ChineseChess_v2.0.5.tar.gz](https://github.com/KangLin/ChineseChessControl/releases/download/v2.0.5/ChineseChess_v2.0.5.tar.gz)  
      AppImage格式的执行程序，可直接运行在linux系统，详见：https://appimage.org/  
      使用:    
        1. 解压。复制ChineseChess_v2.0.5.tar.gz到安装目录，然后解压：

                mkdir ChineseChess
                cd ChineseChess
                cp $DOWNLOAD/ChineseChess_v2.0.5.tar.gz .
                tar xvfz ChineseChess_v2.0.5.tar.gz

        2. 安装
        
                ./install1.sh install ChineseChess
        
        3. 如果需要，卸载
        
                ./install1.sh remove ChineseChess

  - ubuntu
      - [ChineseChess_2.0.5_amd64.deb](https://github.com/KangLin/ChineseChessControl/releases/download/v2.0.5/chinesechess_2.0.5_amd64.deb)  
  deb 安装包,可用于 Ubuntu

#### 贡献
- 欢迎大家参与本项目开发，共同完成[功能](#功能)列表中未完成的功能。
  + [问题与讨论](https://github.com/KangLin/ChineseChessControl/issues)
  + [感谢贡献者](https://github.com/KangLin/ChineseChessControl/graphs/contributors)
- 使用本项目用于你的项目。

##### 捐赠
本软件如果对你有用，或者你喜欢它，请你捐赠，支持作者。谢谢！

[![捐赠](https://gitlab.com/kl222/RabbitCommon/-/raw/master/Src/Resource/image/Contribute.png "捐赠")](https://gitlab.com/kl222/RabbitCommon/-/raw/master/Src/Resource/image/Contribute.png "捐赠")

如果不能显示，请打开：
- https://gitlab.com/kl222/RabbitCommon/-/raw/master/Src/Resource/image/Contribute.png
- https://sourceforge.net/p/rabbitcommon/code/ci/master/tree/Src/Resource/image/Contribute.png

#### [许可协议](License.md)
#### [修改日志](ChangeLog.md)
#### 文档
- [开发者文档](Documents/Developer.md)
- COM 文档
  + [COM学习笔记](Documents/COM/COM学习笔记.html)
  + [COM中的事件响应](Documents/COM/COM中的事件响应.html)
- ActiveX 控件
  + [建立ActiveX控件](Documents/ActiveX控件/建立ActiveX控件.html)
  + [VC下使用ActiveX控件的问题](Documents/ActiveX控件/VC下使用ActiveX控件的问题.html)

