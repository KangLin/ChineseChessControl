# Author: Kang Lin <kl222@126.com>

# 设置传递给 CPack 的配置文件
configure_file("${CMAKE_SOURCE_DIR}/cmake/CMakeCPackOptions.cmake.in"
	"${CMAKE_BINARY_DIR}/CMakeCPackOptions.cmake" @ONLY)
set(CPACK_PROJECT_CONFIG_FILE "${CMAKE_BINARY_DIR}/CMakeCPackOptions.cmake")

# Generate .txt license file for CPack (PackageMaker requires a file extension)
configure_file(${CMAKE_SOURCE_DIR}/License.md ${CMAKE_BINARY_DIR}/LICENSE.txt @ONLY)

set(CPACK_SOURCE_IGNORE_FILES
    ${CMAKE_SOURCE_DIR}/build
    ${CMAKE_SOURCE_DIR}/.cache
    ${CMAKE_SOURCE_DIR}/.git
    ${CMAKE_SOURCE_DIR}/.github
    ${CMAKE_SOURCE_DIR}/.gitignore
    ${CMAKE_SOURCE_DIR}/.dockerignore
    ${CMAKE_SOURCE_DIR}/CMakeCache.txt)

set(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_TOPLEVEL_TAG "${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}")

# 设置安装包的文件名
string(TOLOWER ${CMAKE_PROJECT_NAME} CMAKE_PROJECT_NAME_lower)
# 设置二进制安装包的文件名
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME_lower}_${ChineseChessControl_VERSION}_${CPACK_SYSTEM_NAME}_setup")
# 设置源码安装包的文件名
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME_lower}_${ChineseChessControl_VERSION}_${CPACK_SYSTEM_NAME}_source")
#set(CPACK_PACKAGE_DIRECTORY ${CMAKE_BINARY_DIR}/package)

#包名。建议用英文。在NSIS 安装选项中不能正确解码
set(CPACK_PACKAGE_NAME "ChineseChessControl")
set(CPACK_PACKAGE_VENDOR "康林工作室")
set(CPACK_PACKAGE_VERSION ${ChineseChessControl_VERSION})
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "中国象棋控件")

# 将在安装程序（由 GUI 安装程序使用）中显示的图标。
set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}\\Src\\Res\\Picture\\Chess.ico")

#set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
#set(CPACK_RESOURCE_FILE_WELCOME )
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_BINARY_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/KangLin/ChineseChessControl")
set(CPACK_PACKAGE_CONTACT "康 林 <kl222@126.com>")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "ChineseChessControl")
# 设置注册表健。仅用于 WINDOWS
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "ChineseChessControl")

set(CPACK_PACKAGE_CHECKSUM "MD5")

############### Debian ###################
if(UNIX)
    set(CPACK_DEBIAN_PACKAGE_DEBUG ON)
    
    set(CPACK_DEBIAN_PACKAGE_SOURCE ChineseChessControl)
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Kang Lin <kl222@126.com>")
    #set(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
    set(CPACK_DEBIAN_PACKAGE_SECTION "main")
    set(CPACK_DEBIAN_PACKAGE_PREDEPENDS "debhelper (>= 6), cmake (>= 2.8.0), dh-systemd (>= 1.5)")
    #set(CMAKE_INSTALL_RPATH )
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS_PRIVATE_DIRS)
    set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS ON)
    #set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS_POLICY ">=")
    set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
        "${CMAKE_SOURCE_DIR}/debian/postinst;${CMAKE_SOURCE_DIR}/debian/postrm"
        "${CMAKE_SOURCE_DIR}/debian/preinst;${CMAKE_SOURCE_DIR}/debian/prerm"
    )
    
endif()
############### Debian ###################

# 设置开始菜单快捷方式。格式： "程序文件名" "菜单名"
# 仅在 NSIS, WIX 中有效。
# 与 CPACK_NSIS_MENU_LINKS 功能类似
#set(CPACK_PACKAGE_EXECUTABLES "ChineseChessApp" "中国象棋")
#set(CPACK_CREATE_DESKTOP_LINKS "中国象棋")

############### NSIS ###################
if(WIN32)
    
    #NSIS 安装程序提供给最终用户的默认安装目录位于此根目录下。提供给最终用户的完整目录是：${CPACK_NSIS_INSTALL_ROOT}/${CPACK_PACKAGE_INSTALL_DIRECTORY}
    #set(CPACK_NSIS_INSTALL_ROOT "$LOCALAPPDATA")
    set(CPACK_NSIS_MODIFY_PATH ON)
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
    set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}\\Src\\Res\\Picture\\Chess.ico")
    set(CPACK_NSIS_MUI_UNICON "${CMAKE_SOURCE_DIR}\\Src\\Res\\Picture\\Chess.ico")
    #set(CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP "${CMAKE_SOURCE_DIR}\\Src\\Res\\Picture\\CHESS.BMP")
    #set(CPACK_NSIS_MUI_UNWELCOMEFINISHPAGE_BITMAP "${CMAKE_SOURCE_DIR}\\Src\\Res\\Picture\\CHESS.BMP")
    
    #set(CPACK_NSIS_EXTRA_PREINSTALL_COMMANDS )
    #set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS )
    #设置安装包的编码。默认为：lzma
    #set(CPACK_NSIS_COMPRESSOR lzma)
    
    #如果设置为 ON，则安装程序中将出现一个额外的页面，允许用户选择是否应将程序目录添加到系统 PATH 变量中。
    set(CPACK_NSIS_MODIFY_PATH OFF)
    
    #设置在“控制面板->程序->程序和功能->卸载或更改程序”中的图标
    #包含安装者图标的执行程序（相对于安装根目录）
    set(CPACK_NSIS_INSTALLED_ICON_NAME "bin/ChineseChessApp.exe")
    
    #显示在安装对话框中的包名
    set(CPACK_NSIS_PACKAGE_NAME "中国象棋控件")
    
    #显示在“控制面板->程序->程序和功能->卸载或更改程序”
    set(CPACK_NSIS_DISPLAY_NAME "中国象棋控件")
    set(CPACK_NSIS_HELP_LINK "https://github.com/KangLin/ChineseChessControl/issues")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/KangLin/ChineseChessControl")
    set(CPACK_NSIS_CONTACT "康 林 <kl222@126.com>")
    
    # 设置开始菜单快捷方式。格式： "程序位置（相对于安装根目录）" "菜单名"
    # 与 CPACK_PACKAGE_EXECUTABLES 功能类似
    set(CPACK_NSIS_MENU_LINKS
        "bin/ChineseChessApp.exe" "中国象棋"
        "https://github.com/KangLin/ChineseChessControl" "项目主页"
    )
    set(CPACK_NSIS_MUI_FINISHPAGE_RUN ChineseChessApp.exe)
    # 建立桌面快捷方式
    set(CPACK_NSIS_CREATE_ICONS_EXTRA "
         CreateShortCut '$DESKTOP\\中国象棋.lnk\' '$INSTDIR\\bin\\ChineseChessApp.exe\'
         ")
    # Delete the Startup menu link after uninstallation
    set(CPACK_NSIS_DELETE_ICONS_EXTRA "
        Delete '$DESKTOP\\中国象棋.lnk\'
    ")
endif()
############### NSIS ###################

include(CPack)

cpack_add_component(Development
    DISPLAY_NAME  "Development"
    DESCRIPTION   "开发库"
    DEPENDS Runtime
    )

cpack_add_component(Runtime
    DISPLAY_NAME  "Runtime"
    DESCRIPTION   "运行库"
    )

cpack_add_component(Application
    DISPLAY_NAME  "Application"
    DESCRIPTION   "应用程序"
    DEPENDS Runtime
    )
