# Author: Kang Lin <kl222@126.com>

configure_file("${CMAKE_SOURCE_DIR}/cmake/CMakeCPackOptions.cmake.in"
	"${CMAKE_BINARY_DIR}/CMakeCPackOptions.cmake" @ONLY)
set(CPACK_PROJECT_CONFIG_FILE "${CMAKE_BINARY_DIR}/CMakeCPackOptions.cmake")

# Generate .txt license file for CPack (PackageMaker requires a file extension)
configure_file(${CMAKE_SOURCE_DIR}/License.md ${CMAKE_BINARY_DIR}/LICENSE.txt @ONLY)

SET(CPACK_BINARY_ZIP "ON")

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
string(TOLOWER ${CMAKE_PROJECT_NAME} CMAKE_PROJECT_NAME_lower)
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME_lower}_${ChineseChessControl_VERSION}_${CPACK_SYSTEM_NAME}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME_lower}_${ChineseChessControl_VERSION}_${CPACK_SYSTEM_NAME}")
#set(CPACK_PACKAGE_DIRECTORY ${CMAKE_BINARY_DIR}/package)

#set(CPACK_PACKAGE_NAME "ChineseChessControl")
set(CPACK_PACKAGE_VENDOR "Kang Lin <kl222@126.com>")
set(CPACK_PACKAGE_VERSION ${ChineseChessControl_VERSION})
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "中国象棋控件")
#set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
#set(CPACK_RESOURCE_FILE_WELCOME )
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_BINARY_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/KangLin/ChineseChessControl")
set(CPACK_PACKAGE_CONTACT "Kang Lin <kl222@126.com>")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "ChineseChessControl")
set(CPACK_PACKAGE_CHECKSUM "MD5")

############### Debian ###################
if(UNIX)
	set(CPACK_BINARY_DEB ON)
endif()
set(CPACK_DEBIAN_PACKAGE_SOURCE ChineseChessControl)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Kang Lin <kl222@126.com>")
#set(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
set(CPACK_DEBIAN_PACKAGE_SECTION "main")
set(CPACK_DEBIAN_PACKAGE_PREDEPENDS "debhelper (>= 6), cmake (>= 2.8.0), dh-systemd (>= 1.5)")
#set(CMAKE_INSTALL_RPATH )
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS ON)
#set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS_POLICY ">=")
#set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
#    "${CMAKE_CURRENT_SOURCE_DIR}/prerm;${CMAKE_CURRENT_SOURCE_DIR}/postrm")
############### Debian ###################

#set(CPACK_PACKAGE_EXECUTABLES )
#set(CPACK_CREATE_DESKTOP_LINKS )

############### NSIS ###################
if(WIN32)
	set(CPACK_BINARY_NSIS ON)
endif()
#set(CPACK_NSIS_INSTALL_ROOT "$LOCALAPPDATA")
set(CPACK_NSIS_MODIFY_PATH ON)
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
#set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/resources\\\\coturn_Install.bmp")
#set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/resources\\\\coturn_Icon_96px.ico")
#set(CPACK_NSIS_MUI_UNICON "${CMAKE_SOURCE_DIR}/resource\\\\coturn_Icon_96px.ico")
############### NSIS ###################

include(CPack)

cpack_add_component(Qt
    DISPLAY_NAME  "Qt"
    DESCRIPTION   "Qt"
    DEPENDS Runtime
    )

cpack_add_component(MFC
    DISPLAY_NAME  "MFC"
    DESCRIPTION   "MFC"
    DEPENDS Runtime
    )

cpack_add_component(ActiveX
    DISPLAY_NAME  "ActiveX"
    DESCRIPTION   "ActiveX"
    DEPENDS Runtime
    )
