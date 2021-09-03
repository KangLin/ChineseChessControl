## 中国象棋库

作者：康林(kl222@126.com)

-------------------------

本模块完成中国象棋的基本规则及流程。它仅依赖于 C++ 。
它提供中国象棋的基础数据结构、规则。不与相关平台产生依赖。
不同界面平台开发框架只需要从 CChineseChess 类派生，
并实现其平台相关的虚拟函数。

## 它实现的功能：

- [x] 中国象棋基本规则
- [x] 棋局保存和复盘

## 使用 ChineseChess
+ 使用 find_package 查找你需要的库。例如,你需要从 ChineseChess 为一个新的界面框架实现中国象棋：

      find_package(ChineseChess)  #查找 ChineseChess 库
      if(ChineseChess_FOUND)
          target_link_libraries(${PROJECT_NAME} PUBLIC ChineseChessControl::ChineseChess)  # 应用链接 ChineseChess 库
      endif()
