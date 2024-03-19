- v2.0.12
  - CI: 修改 GITHUB action 发布
  - 增加 vcpkg.json
  - 使用 RabbitCommon v2.2.0
  - 复制 ChangLog.md 等文件到 ${CMAKE_INSTALL_DOCDIR}
  
- v2.0.11
  - CI: 更新 VCPKG。修复CPAKE错误。详见： https://github.com/microsoft/vcpkg/issues/32560

- v2.0.10
  - 用 QFileDialog::getOpenFileName 替换 RabbitCommon::CDir::GetOpenFileName
  - 用 QFileDialog::getSaveFileName 替换 RabbitCommon::CDir::GetSaveFileName

- v2.0.9
  - 修改 INSTALL.nsi

- v2.0.8
  - Modify CI

- v2.0.7
  - 使用 RabbitCommon v2
  - 编译 Android 时，Qt 版本必须大于6.0.0
  - 修复 org.Rabbit.ChineseChess.desktop 错误
  - 自动化编译：
    - Android
    - macos

- v2.0.6
  - 使用 RabbitCommon v1.0.10
  - 重命名 tag.sh 到 deploy.sh
  - 修改 CI: 使用 github action
  - Qt: 使用图标主题
  - 重构 CMakeLists.txt
  - 重构 CPack

- v2.0.5
  - 增加残局支持
  - 增加 FEN 支持
  - 增加 PGN 支持
  - 界面框架从 Src 移到 UI 目录下
  - 增加 CMake 导出配置文件
  - 修复除 0 引起的崩溃。影响前面所有发行版本。此错误是 RabbitCommon 引起的。
    详见：RabbitCommon: 7ed300a206d8a36c30003b6c19ad181682d0ff5f

- v2.0.4
  - 用 CChineseChessView 修改 MFC 应用程序
  - 修改 MFC 中国象棋资源图片

- v2.0.3
  - 修改ci
  - 修改 tag.sh
  - 修改资源图片
  
- v2.0.2
  - 增加保存棋局标签
  - 修改加载棋局时没有初始化 ActiveX 属性错误
  - 保存和加载棋局
  - 完成 android 版本中国象棋应用程序
  - 修复重构时引入的将军错误

- v2.0.1
  - Qt 中国象棋程序增加关于
  - Qt 中国象棋程序增加更新功能
  - Qt 中国象棋程序增加翻译
  - 增加 ANDROID 下 Qt 中国象棋程序
  - 增加 linux 下 Qt 中国象棋程序
  - 清理以前的无用代码
  
- v2.0.0
  - 增加中国象棋 Qt 插件
  - 增加中国象棋 Qt 应用程序

- v1.2.0
  - 增加 MFC 中国象棋类
  - 修复保存棋局时没有保存布局的错误。
  - 使用 MFC 中国象棋类重构中国象棋 ActiveX

- v1.1.2
  - 重新新建中国象棋 ActiveX
  - 完成界面功能
  - 完成走棋功能
  - 完成复盘功能
  - 完成棋局从文件加载和保存到文件
  - 允许/禁止错误提示音与提示消息
  - 中国象棋程序使用新的 ActiveX 控件

- v1.1.1
  - 字符编码使用多字节编码
 
- v1.1.0
  - 重构程序
    - 按[象棋竞赛规则(2011)](Documents/ChineseChessRule2011.pdf)重构棋盘布局
  - 优化程序可读性
  - 优化算法性能

- v1.0.2
  - 固定棋盘初始化不正确错误
  - 修改 VC--6.0 不能打开项目错误
  - 增加 MFC 中国象棋程序

- v1.0.1
  - 修改文档
  - 修改文件名大小写

- v1.0.0
  - 整理以前的代码
  - 使用 CMake 管理本项目
  - 增加自动化编译

- 中国象棋的历史变更
  - 生命不息，维护不止！
  - 2020年5月：整理项目代码
  - 2014年：开源到 [github](https://github.com/KangLin/ChineseChessControl/)
  - 2003年~2005年：VC6.0 写的中国象棋控件。本项目的[原始版本](https://github.com/KangLin/pre2006/tree/master/Programe/VC/%E4%B8%AD%E5%9B%BD%E8%B1%A1%E6%A3%8B%E6%8E%A7%E4%BB%B6)。
  - 2000年~2002年：VB6.0 写的中国象棋控件, 源码丢失。
  - 1994年~2000年：[QBasic 写的中国象棋程序](https://github.com/KangLin/pre2006/tree/master/Programe/VB/XQ)
