# Author: Kang Lin <kl222@126.com>

#参考： https://zhuanlan.zhihu.com/p/377131996
#      https://github.com/medInria/medinria-superproject/blob/master/packaging/Packaging.cmake

# Generate .txt license file for CPack (PackageMaker requires a file extension)
configure_file(${CMAKE_SOURCE_DIR}/License.md ${CMAKE_BINARY_DIR}/LICENSE.txt)

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

# 包名。建议用英文。
set(CPACK_PACKAGE_NAME "ChineseChessControl")
set(CPACK_PACKAGE_VENDOR "康林工作室")

# 设置安装包的文件名
string(TOLOWER ${CPACK_PACKAGE_NAME} CPACK_PACKAGE_NAME_lower)
# 设置二进制安装包的文件名
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME_lower}_${ChineseChessControl_VERSION}_${CPACK_SYSTEM_NAME}_setup")
# 设置源码安装包的文件名
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME_lower}_${ChineseChessControl_VERSION}_${CPACK_SYSTEM_NAME}_source")
# 不设置，默认为编译目录
#set(CPACK_PACKAGE_DIRECTORY ${CMAKE_BINARY_DIR})

#set(CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR})
#set(CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR})
#set(CPACK_PACKAGE_VERSION_PATCH ${${PROJECT_NAME}_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION ${${PROJECT_NAME}_VERSION})

# 将在安装程序（由 GUI 安装程序使用）中显示的图标。
if(WIN32)
    set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}\\Src\\Res\\Picture\\Chess.ico")
else()
    set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/Src/Res/Picture/Chess.ico")
endif()

# 项目描述，用于 CPack 生成的 Windows 安装程序的介绍屏幕等位置。如果未设置，则从 CPACK_PACKAGE_DESCRIPTION_FILE 命名的文件填充此变量的值。
set(CPACK_PACKAGE_DESCRIPTION "中国象棋控件")
#set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
# 设置简短的描述摘要。
# 如果 CMAKE_PROJECT_DESCRIPTION 设置，用于默认值，
# 否则默认值由 CMAKE 基于 CMAKE_PROJECT_NAME 产生.
#SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "中国象棋控件")

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
    set(CPACK_GENERATOR "DEB;STGZ;TGZ;TZ")
    set(CPACK_DEBIAN_PACKAGE_DEBUG ON)

    #set(CPACK_DEB_COMPONENT_INSTALL ON)

    ##### 产生 control 文件 #####

    # 设置 Package 字段（自动转换成小写）。 默认使用 CPACK_PACKAGE_NAME
    #set(CPACK_DEBIAN_PACKAGE_NAME ${CPACK_PACKAGE_NAME})

    # 更改 CPACK 包的默认安装路径前缀。
    # 或者在 cpack 时传递参数 -DCPACK_PACKAGING_INSTALL_PREFIX=/opt
    set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/${CPACK_PACKAGE_NAME}")

    # 设置包文件名。默认使用 CPACK_PACKAGE_FILE_NAME
    # 也能设置为 DEB-DEFAULT，允许由DEB产生者产生它自己的 deb 格式：
    # <PackageName>_<VersionNumber>-<DebianRevisionNumber>_<DebianArchitecture>.deb
    #set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

    # 默认： CPACK_PACKAGE_CONTACT
    # set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Kang Lin <kl222@126.com>")

    # 默认：
    # - 如果设置 CPACK_PACKAGE_DESCRIPTION。则用于默认值。
    # - 如果设置  CPACK_PACKAGE_DESCRIPTION_FILE 。则默认值是此文件的内容。
    # set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "中国象棋控件")

    # 默认： CMAKE_PROJECT_HOMEPAGE_URL
    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE ${CPACK_PACKAGE_HOMEPAGE_URL})

    # Default : Output of dpkg --print-architecture (or i386 if dpkg is not found)
    # 注意：要用默认的才会得到正确的目标架构
    #set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})

    # 默认值： CPACK_PACKAGE_VERSION
    string(REPLACE "v" "" _DEBIAN_VERSION ${CPACK_PACKAGE_VERSION})
    set(CPACK_DEBIAN_PACKAGE_VERSION ${_DEBIAN_VERSION})
    #set(CPACK_DEBIAN_PACKAGE_RELEASE ${CPACK_PACKAGE_VERSION})
    #set(CPACK_DEBIAN_PACKAGE_EPOCH)

    #set(CMAKE_INSTALL_RPATH )
    # 设置包的依赖
    # set(CPACK_DEBIAN_PACKAGE_DEPENDS)
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    # May be set to a list of directories that will be given to dpkg-shlibdeps via its -l option. These will be searched by dpkg-shlibdeps in order to find private shared library dependencies.
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS_PRIVATE_DIRS ${QT_INSTALL_DIR}/lib;${CMAKE_BINARY_DIR}/_CPack_Packages/${CPACK_SYSTEM_NAME}/DEB/${CPACK_PACKAGE_FILE_NAME}${CPACK_PACKAGING_INSTALL_PREFIX}/lib)
    message("CPACK_DEBIAN_PACKAGE_SHLIBDEPS_PRIVATE_DIRS:${CPACK_DEBIAN_PACKAGE_SHLIBDEPS_PRIVATE_DIRS}")
    set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS ON)
    #set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS_POLICY ">=")

    set(CPACK_DEBIAN_PACKAGE_PREDEPENDS "debhelper (>= 6), cmake (>= 2.8.0)")

    # See: https://www.debian.org/doc/debian-policy/ch-relationships.html#s-binarydeps
    #set(CPACK_DEBIAN_PACKAGE_ENHANCES)

    # 设置 Source 字段
    set(CPACK_DEBIAN_PACKAGE_SOURCE ChineseChessControl)
    set(CPACK_DEBIAN_PACKAGE_SECTION "games")
    set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

    ##### 产生自定义脚本 #####
    # 增加自定义脚本到 control.tar.gz. Typical usage is for conffiles, postinst, postrm, prerm.
    # 看 ${CMAKE_SOURCE_DIR}/cmake/CMakeCPackOptions.cmake.in 中脚本设置
    set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
        "${CMAKE_BINARY_DIR}/postinst;${CMAKE_BINARY_DIR}/postrm"
        "${CMAKE_BINARY_DIR}/preinst;${CMAKE_BINARY_DIR}/prerm"
        )

endif()
############### Debian ###################

############### RPM ###################
execute_process(COMMAND lsb_release -a
                COMMAND grep "^Distributor ID:" 
                COMMAND sed -e "s/Distributor ID:[ \t]*//ig"
                OUTPUT_VARIABLE DISTRIBUTOR_ID
                OUTPUT_STRIP_TRAILING_WHITESPACE)
  
execute_process(COMMAND lsb_release -a
                COMMAND grep "^Release:"
                COMMAND sed -e "s/Release:[ \t]*//ig"
                OUTPUT_VARIABLE RELEASE
                OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND arch 
                OUTPUT_VARIABLE ARCH 
                OUTPUT_STRIP_TRAILING_WHITESPACE)

if(${DISTRIBUTOR_ID} MATCHES fc|fedora|Fedora|Centos|centos|SUSE|Suse|suse)
    set(CPACK_GENERATOR "RPM;STGZ;TGZ;TZ")
endif()
############### RPM ###################

# 设置开始菜单快捷方式。格式： "程序文件名" "菜单名"
# 仅在 NSIS, WIX 中有效。
# 与 CPACK_NSIS_MENU_LINKS 功能类似
#set(CPACK_PACKAGE_EXECUTABLES "ChineseChessApp" "中国象棋")
#set(CPACK_CREATE_DESKTOP_LINKS "中国象棋")

############### NSIS ###################
if(WIN32)

    #set(CPACK_GENERATOR "NSIS;NSIS64;ZIP")
    
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

# 设置传递给 CPack 的配置文件。主要作用是把 CMAKE_* 变量传递到 CPACK 中
configure_file("${CMAKE_SOURCE_DIR}/Package/CMakeCPackOptions.cmake.in"
	"${CMAKE_BINARY_DIR}/CMakeCPackOptions.cmake" @ONLY)
set(CPACK_PROJECT_CONFIG_FILE "${CMAKE_BINARY_DIR}/CMakeCPackOptions.cmake")

include(CPack)

cpack_add_install_type(All
    DISPLAY_NAME "全部")

cpack_add_install_type(Developer
    DISPLAY_NAME "开发者")

cpack_add_install_type(EndUser
    DISPLAY_NAME "应用程序")

cpack_add_component_group(Runtimes
    DISPLAY_NAME "运行库"
	DESCRIPTION "运行库"
	EXPANDED
	)

cpack_add_component_group(Developments
    DISPLAY_NAME "开发库"
	DESCRIPTION "开发库"
	EXPANDED
	)

cpack_add_component_group(Applications
    DISPLAY_NAME "应用程序"
	DESCRIPTION "应用程序"
	EXPANDED
	)

cpack_add_component(DependLibraries
    DISPLAY_NAME  "依赖库"
    DESCRIPTION   "依赖库"
    GROUP Runtimes
    )

cpack_add_component(Development
    DISPLAY_NAME  "开发库"
    DESCRIPTION   "开发库"
	GROUP Developments
	INSTALL_TYPES Developer
    DEPENDS Runtime
    )

cpack_add_component(Runtime
    DISPLAY_NAME  "运行库"
    DESCRIPTION   "运行库"
    GROUP Runtimes
    DEPENDS DependLibraries
	REQUIRED
    )

####### QT #######
if(Qt${QT_VERSION_MAJOR}_FOUND)
    cpack_add_install_type(QtDeveloper
        DISPLAY_NAME "Qt 开发者")

    cpack_add_install_type(QtEndUser
        DISPLAY_NAME "Qt 应用程序")

    cpack_add_component(QtRuntime
        DISPLAY_NAME  "Qt 运行库"
        DESCRIPTION   "Qt 运行库"
        GROUP Runtimes
        DEPENDS Runtime
	    )

    cpack_add_component(QtDevelopment
        DISPLAY_NAME  "Qt 开发库"
        DESCRIPTION   "Qt 开发库"
	    GROUP Developments
	    INSTALL_TYPES All QtDeveloper Developer 
        DEPENDS QtRuntime Development
        )

    cpack_add_component(QtApplications
        DISPLAY_NAME  "Qt 应用程序"
        DESCRIPTION   "Qt 应用程序"
        DEPENDS QtRuntime
	    INSTALL_TYPES All EndUser QtEndUser
	    GROUP Applications
        )
endif()

####### MFC #######
if(MFC_FOUND)
    cpack_add_install_type(MFCDeveloper
        DISPLAY_NAME "MFC 开发者")

    cpack_add_install_type(MFCEndUser
        DISPLAY_NAME "MFC 应用程序")

    cpack_add_component(MFCRuntime
        DISPLAY_NAME  "MFC 运行库"
        DESCRIPTION   "MFC 运行库"
        GROUP Runtimes
        DEPENDS Runtime
        )

    cpack_add_component(MFCDevelopment
        DISPLAY_NAME  "MFC 开发库"
        DESCRIPTION   "MFC 开发库"
	    GROUP Developments
	    INSTALL_TYPES MFCDeveloper Developer All
        DEPENDS MFCRuntime Development
        )

    cpack_add_component(MFCApplications
        DISPLAY_NAME  "MFC 应用程序"
        DESCRIPTION   "MFC 应用程序"
        DEPENDS MFCRuntime
	    INSTALL_TYPES MFCEndUser EndUser All
	    GROUP Applications
        )
endif()