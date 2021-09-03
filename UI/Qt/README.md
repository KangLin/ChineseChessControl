## 中国象棋 Qt 插件模块

作者：康林(kl222@126.com)

------------------------------------------------

中国象棋 Qt 插件模块。它依赖中国象棋库。
它实现了中国象棋Qt界面功能。并支持设计师插件。
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
