## 中国象棋 Qt 插件模块

作者：康林(kl222@126.com)

------------------------------------------------

中国象棋 Qt 插件模块。它依赖中国象棋库。
它实现了中国象棋Qt界面功能。并可作为 Qt 设计器中控件使用。
它被应用于Qt的中国象棋开发。支持多平台。

- windows
- linux
- android
- mac、ios

## 使用 ChineseChessQt 

    find_package(ChineseChessQt)  #查找 ChineseChessQt 库
    if(ChineseChessQt_FOUND)
        target_link_libraries(${PROJECT_NAME} PUBLIC ChineseChessControl::ChineseChessQt)  # 应用链接 ChineseChessQt 库
    endif()

## 在 Qt 设计器中使用
复制安装目录（bin、lib）下的所有动态库文件到 ${Qt_Install_Root}/plugins/designer 下。
就可以在 qt 设计器的控件窗口中看到此插件。然后就与使用普通Qt控件一样。
