## 编译

- [依赖](#依赖)
- [CMake 配置参数](#CMake-配置参数)
- [各平台编译](#各平台编译)
  - [linux 平台编译说明](#linux-平台编译说明)
  - [windows 平台编译说明](#windows-平台编译说明)
  - [Android 平台编译说明](#Android-平台编译说明)
- [安装目录](#安装目录)

### 依赖
+ 工具
  + 编译器
    - For linux or android
        + GNU GCC
        + Clang
    - For windows
        + [Microsoft Visual studio c++](http://msdn.microsoft.com/zh-cn/vstudio)
        + [MSYS2/MinGW](http://sourceforge.net/projects/msys2/)
  + [CMake](http://www.cmake.org/)
  + [可选，linux平台] Automake and autoconfig
  + [可选，编译ChineseChessQt时] [Qt](http://qt.io/)
  + [可选，编译Android时] android sdk and ndk  
+ 依赖库
  - [可选] 玉兔公共库: https://github.com/KangLin/RabbitCommon
 
### CMake 配置参数
  - [可选] Qt5_DIR: qt 安装位置(指向Qt5Config.cmake的目录，默认为 安装目录/lib/cmake/Qt5)。
                   详见：https://doc.qt.io/qt-5/cmake-get-started.html
  - [可选] RabbitCommon_DIR: RabbitCommon 源码位置
  - [可选] BUILD_CHINESE_CHESS_MFC_VIEW：编译中国象棋 MFC 扩展动态库
  - [可选] BUILD_CHINESE_CHESS_ACTIVEX：编译中国象棋 ActiveX
  - [可选] BUILD_CHINESE_CHESS_APP_MFC：编译中国象棋 MFC 程序
  - [可选] BUILD_CHINESE_CHESS_QT：编译中国象棋 QT 插件
  - [可选] BUILD_CHINESE_CHESS_QT_APP：编译中国象棋 QT 应用程序

### 各平台编译
#### 下载源码

- 下载本项目源码

      git clone https://github.com/KangLin/ChineseChessControl.git

- 下载必选库（玉兔公共）库源码

      git clone https://github.com/KangLin/RabbitCommon.git

#### linux 平台编译说明
- 编译

      git clone https://github.com/KangLin/RabbitCommon.git
      git clone https://github.com/KangLin/ChineseChessControl.git
      cd ChineseChessControl
      mkdir build
      cd build
      cmake .. -G"Unix Makefiles" \
            -DCMAKE_INSTALL_PREFIX=`pwd`/install \
            -DCMAKE_BUILD_TYPE=Release \
            -DQt5_DIR= \
            -DRabbitCommon_DIR= \
            [其它可选 CMake 配置参数]
      cmake --build . --config Release 

- 安装
  + 安装库和程序

        cmake --build . --config Release --target install    # --target install/strip stip 目标
    
  + 仅安装程序

        cmake --build . --config Release --target install-runtime

- 运行例子
  + 把生成库的目录加入到变量 LD_LIBRARY_PATH 中
 
        cd ChineseChessControl
        cd build/install
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/bin:[可选库的目录]

  + 执行安装目录 bin 目录下的程序

        cd build/install/bin
        ./ChineseChess

#### windows 平台编译说明
  - 使用 cmake-gui.exe 工具编译。打开 cmake-gui.exe 配置
  - 命令行编译
    + 把 cmake 命令所在目录加入到环境变量 PATH 中
    + 从开始菜单打开 “VS2015开发人员命令提示”，进入命令行
      - 编译

            git clone https://github.com/KangLin/RabbitCommon.git
            git clone https://github.com/KangLin/ChineseChessControl.git
            cd ChineseChessControl
            mkdir build
            cd build
            cmake .. -DCMAKE_INSTALL_PREFIX=install ^
                 -DCMAKE_BUILD_TYPE=Release ^
                 -DQt5_DIR= ^
                 -DRabbitCommon_DIR= ^
                 [其它可选 CMake 配置参数]
            cmake --build . --config Release

      - 安装
        + 安装库和程序
        
              cmake --build . --config Release --target install
        
        + 仅安装程序
        
              cmake --build . --config Release --target install-runtime

      - 运行例子
        + 执行安装目录 bin 目录下的程序

              cd ChineseChessControl
              cd build/install/bin
              ChineseChess.exe
              或者：
              ChineseChessMfcApp.exe

#### Android 平台编译说明
+ 安装 ndk 编译工具
  - 从 https://developer.android.com/ndk/downloads 下载 ndk，并安装到：/home/android-ndk
  - 设置环境变量：

        export ANDROID_NDK=/home/android-ndk
        
+ 安装 sdk 工具
  - 从 https://developer.android.google.cn/studio/releases 下载 sdk tools, 并安装到 /home/android-sdk
  - 设置环境变量：
  
        export ANDROID_SDK=/home/android-sdk

+ 编译
  - 主机是 linux
    + 编译

          git clone https://github.com/KangLin/RabbitCommon.git
          git clone https://github.com/KangLin/ChineseChessControl.git
          cd ChineseChessControl
          mkdir build
          cd build
          cmake .. -G"Unix Makefiles" \
                   -DCMAKE_INSTALL_PREFIX=`pwd`/android-build \
                   -DCMAKE_BUILD_TYPE=Release \
                   -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/build/cmake/android.toolchain.cmake \
                   -DANDROID_ABI="armeabi-v7a with NEON" \
                   -DANDROID_PLATFORM=android-24 \
                   -DQt5_DIR= \
                   -DRabbitCommon_DIR= \                   
                   [其它可选 CMake 配置参数]
          cmake --build . --config Release

    + 安装
      - 安装库和程序

          cmake --build . --config Release --target install/strip

      - 仅安装程序

          cmake --build . --config Release --target install-runtime

    + 生成 APK

	      cmake --build . --config Release --target APK

  - 主机是 windows
    + windows 控制台
      - 编译

            git clone https://github.com/KangLin/RabbitCommon.git
            git clone https://github.com/KangLin/ChineseChessControl.git
            cd ChineseChessControl
            mkdir build
            cd build
            cmake .. -DCMAKE_INSTALL_PREFIX=%cd%\android-build ^
                     -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ^
                     -DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK%/build/cmake/android.toolchain.cmake ^
                     -DCMAKE_MAKE_PROGRAM=%ANDROID_NDK%/prebuilt/windows-x86_64/bin/make.exe ^
                     -DANDROID_ABI=arm64-v8a ^
                     -DANDROID_ARM_NEON=ON ^
                     -DANDROID_PLATFORM=android-24 ^
                     -DQt5_DIR= ^
                     -DRabbitCommon_DIR= ^
                     [其它可选 CMake 配置参数]
            cmake --build . --config Release

      - 安装
        + 安装库和程序

              cmake --build . --config Release --target install/strip

        + 仅安装程序

              cmake --build . --config Release --target install-runtime

        + 生成 APK

              cmake --build . --config Release --target APK

    + msys2 或 cygwin

          git clone https://github.com/KangLin/RabbitCommon.git
          git clone https://github.com/KangLin/ChineseChessControl.git
          cd ChineseChessControl
          mkdir build
          cd build
          cmake .. -DCMAKE_INSTALL_PREFIX=`pwd`/android-build \
                   -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release \
                   -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/build/cmake/android.toolchain.cmake \
                   -DCMAKE_MAKE_PROGRAM=${ANDROID_NDK}/prebuilt/windows-x86_64/bin/make.exe \
                   -DANDROID_ABI=arm64-v8a \
                   -DANDROID_ARM_NEON=ON \
                   -DANDROID_PLATFORM=android-24 \
                   -DQt5_DIR= \
                   -DRabbitCommon_DIR= \
                   [其它可选 CMake 配置参数]

      - 安装
        + 安装库和程序

              cmake --build . --config Release --target install/strip

        + 仅安装程序

              cmake --build . --config Release --target install-runtime

        + 生成 APK

              cmake --build . --config Release --target APK

  - CMake for android 参数说明：https://developer.android.google.cn/ndk/guides/cmake
    + ANDROID_ABI: 可取下列值：
      目标 ABI。如果未指定目标 ABI，则 CMake 默认使用 armeabi-v7a。  
      有效的目标名称为：
      - armeabi：带软件浮点运算并基于 ARMv5TE 的 CPU。
      - armeabi-v7a：带硬件 FPU 指令 (VFPv3_D16) 并基于 ARMv7 的设备。
      - armeabi-v7a with NEON：与 armeabi-v7a 相同，但启用 NEON 浮点指令。这相当于设置 -DANDROID_ABI=armeabi-v7a 和 -DANDROID_ARM_NEON=ON 。
      - arm64-v8a：ARMv8 AArch64 指令集。
      - x86：IA-32 指令集。
      - x86_64 - 用于 x86-64 架构的指令集。
    + ANDROID_NDK <path> 主机上安装的 NDK 根目录的绝对路径
    + ANDROID_PLATFORM: 如需平台名称和对应 Android 系统映像的完整列表，请参阅 [Android NDK 原生 API](https://developer.android.google.cn/ndk/guides/stable_apis.html)
    + ANDROID_ARM_MODE
    + ANDROID_ARM_NEON
    + ANDROID_STL: 指定 CMake 应使用的 STL。默认情况下，CMake 使用 c++_static。 
      - c++_shared: 使用 libc++ 动态库
      - c++_static: 使用 libc++ 静态库
      - none: 没有 C++ 库支持
      - system: 用系统的 STL
  - 安装 apk 到设备

       adb install android-build-debug.apk 

### 安装目录

```
ROOT
  |------- bin    ：存放应用程序
  |------- lib    ：存放库文件
  |         |-- cmake
  |               |---- ChineseChess：存放 CMAKE 配置文件
  |------- include
              |--- ChineseChess： 存放头文件
```
