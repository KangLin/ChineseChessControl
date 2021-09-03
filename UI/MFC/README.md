## 中国象棋 MFC 扩展动态库

作者：康林(kl222@126.com)

---------------------------------

此模块实现中国象棋 MFC 扩展动态库。
它是一个 MFC 扩展动态库。实现了中国象棋界面功能。
它只能由 MFC 应用程序使用。
它依赖：

## 功能
- VC MFC
- 中国象棋库

## 使用 ChineseChessView ，只能由 MFC 程序使用

    find_package(ChineseChessView)  #查找 ChineseChessView 库
    if(ChineseChessView_FOUND)
        target_link_libraries(${PROJECT_NAME} PUBLIC ChineseChessControl::ChineseChessView)  # 应用链接 ChineseChessView 库
    endif()
