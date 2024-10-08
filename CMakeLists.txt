cmake_minimum_required(VERSION 3.21)
MESSAGE(STATUS "Found CMake ${CMAKE_VERSION}")

project(ChineseChessControl)

if(MSVC)
    if(MSVC_TOOLSET_VERSION VERSION_LESS 140)
        message(FATAL_ERROR "MSVC must be MSVC2015 and later")
    endif()
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

if(POLICY CMP0083)
    cmake_policy(SET CMP0083 NEW)
endif()

if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()

if(POLICY CMP0021)
    cmake_policy(SET CMP0021 NEW)
endif()

# 设置版本号

# 用 GIT 得到版本号
IF(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    if(NOT GIT)
        SET(GIT $ENV{GIT})
    endif()
    if(NOT GIT)
        FIND_PROGRAM(GIT NAMES git git.exe git.cmd)
    endif()
    IF(GIT)
        EXECUTE_PROCESS(
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMAND ${GIT} describe --tags
            OUTPUT_VARIABLE GIT_VERSION  OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        if(NOT GIT_VERSION)
            EXECUTE_PROCESS(
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMAND ${GIT} rev-parse --short HEAD
                OUTPUT_VARIABLE GIT_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE
            )
        endif()
        SET(ChineseChessControl_VERSION ${GIT_VERSION})
    ENDIF()
ENDIF()
if(NOT ChineseChessControl_VERSION)
    SET(ChineseChessControl_VERSION "2.0.13")
endif()
string(REPLACE "v" "" ChineseChessControl_VERSION ${ChineseChessControl_VERSION})
message("ChineseChessControl_VERSION:${ChineseChessControl_VERSION}")

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()
string(TOLOWER "${CMAKE_BUILD_TYPE}" CHINESE_CHESS_CONTROL_BUILD_TYPE)

IF(MSVC)
    # This option is to enable the /MP switch for Visual Studio 2005 and above compilers
    OPTION(WIN32_USE_MP "Set to ON to build with the /MP option (Visual Studio 2005 and above)." ON)
    MARK_AS_ADVANCED(WIN32_USE_MP)
    IF(WIN32_USE_MP)
        #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
        add_compile_options(/MP)
    ENDIF(WIN32_USE_MP)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
ENDIF(MSVC)

SET(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libs")
if (BUILD_SHARED_LIBS)
    add_definitions(-DBUILD_SHARED_LIBS)
    if (CMAKE_COMPILER_IS_GNUCXX AND NOT MINGW)
       # Just setting CMAKE_POSITION_INDEPENDENT_CODE should be enough to set
       # -fPIC for GCC but sometimes it still doesn't get set, so make sure it
       # does.
       add_compile_options("-fPIC")
    endif()
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

include(CMakeDependentOption)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(GenerateExportHeader)
include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckFunctionExists)

set(BUILD_PLATFORM "${CMAKE_SYSTEM_NAME}")
# ----------------------------------------------------------------------------
# Detect compiler and target platform architecture
# ----------------------------------------------------------------------------
if(NOT ANDROID)
    if(X86_64 OR CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(BUILD_ARCH x86_64)
    elseif(X86 OR CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(BUILD_ARCH x86)
    endif()
else()
    set(BUILD_ARCH ${CMAKE_SYSTEM_PROCESSOR})
endif()

add_subdirectory(Src)

find_package(MFC)
cmake_dependent_option(BUILD_CHINESE_CHESS_MFC_VIEW "Build MFC chinese chess mfc view" ON
        "MSVC;MFC_FOUND" OFF)
if(BUILD_CHINESE_CHESS_MFC_VIEW)
    add_subdirectory(UI/MFC)
 endif()
cmake_dependent_option(BUILD_CHINESE_CHESS_ACTIVEX "Build MFC chinese chess activex" ON
        BUILD_CHINESE_CHESS_MFC_VIEW OFF)
if(BUILD_CHINESE_CHESS_ACTIVEX)
   add_subdirectory(UI/ActiveX)
endif()
cmake_dependent_option(BUILD_CHINESE_CHESS_APP_MFC "Build MFC chinese chess applaction" ON
    BUILD_CHINESE_CHESS_MFC_VIEW OFF)
if(BUILD_CHINESE_CHESS_APP_MFC AND MSVC)
    add_subdirectory(App/MFC/ChineseChessMFC)
endif()

#需要的QT组件
SET(QT_COMPONENTS Core)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${QT_COMPONENTS})
if(Qt${QT_VERSION_MAJOR}_FOUND)
    message("QT_VERSION:${Qt${QT_VERSION_MAJOR}_VERSION}")
    
    if (NOT BUILD_SHARED_LIBS)
        # Qt 静态插件
        add_definitions(-DQT_STATICPLUGIN)
    endif()
    
    if(Qt${QT_VERSION_MAJOR}_VERSION VERSION_LESS 6.0.0 AND ANDROID)
        message(FATAL_ERROR "Qt version must great 6.0.0 in android")
    endif()
    get_filename_component(QT_INSTALL_DIR "${Qt${QT_VERSION_MAJOR}_DIR}/../../.." ABSOLUTE)
    
    #打开 qt 编译工具
    SET(CMAKE_AUTOUIC ON)
    SET(CMAKE_AUTOMOC ON)
    SET(CMAKE_AUTORCC ON)
    
    option(BUILD_CHINESE_CHESS_QT "Build chinese chess library for qt" ON)
    if(BUILD_CHINESE_CHESS_QT)
        if(NOT RabbitCommon_DIR)
            set(RabbitCommon_DIR $ENV{RabbitCommon_DIR})
            if(NOT RabbitCommon_DIR)
                set(RabbitCommon_DIR ${CMAKE_SOURCE_DIR}/../RabbitCommon)
            endif()
        endif()
        if(RabbitCommon_DIR AND EXISTS ${RabbitCommon_DIR}/Src)
            message("Use RabbitCommon source code")
            add_subdirectory(${RabbitCommon_DIR}/Src ${CMAKE_BINARY_DIR}/RabbitCommon)
        else()
            find_package(RabbitCommon)
            if(NOT RabbitCommon_FOUND)
                message("RabbitCommon_DIR is not found. Please use one of the following ways to set it:")
                message("1. Set RabbitCommon_DIR to the install prefix of RabbitCommon.")
                message("2. Set RabbitCommon_DIR to source code root of RabbitCommon.")
                message("2.1 Please download the source code of RabbitCommon from https://github.com/KangLin/RabbitCommon")
                message("   ag:")
                message("       git clone https://github.com/KangLin/RabbitCommon.git")
                message("2.2 Then set cmake variable or environment variable RabbitCommon_DIR to download root directory.")
                message("   ag:")
                message("       cmake -DRabbitCommon_DIR= ")
                message(FATAL_ERROR "RabbitCommon_DIR isn't set.")
            endif()
        endif()
        
        add_subdirectory(UI/Qt)
        
        option(BUILD_CHINESE_CHESS_QT_APP "Build chinese chess application for qt " ON)
        if(BUILD_CHINESE_CHESS_QT_APP)
            add_subdirectory(App/Qt/ChineseChess)
        endif()
    endif()
endif()

IF(WIN32)
    # 替换 Install.nsi 中的 MSVC_VERSION 和 BUILD_ARCH
    configure_file(Install/Install.nsi ${CMAKE_BINARY_DIR}/Install.nsi @ONLY)
    INSTALL(FILES ${CMAKE_BINARY_DIR}/Install.nsi Install/InstallRedistributables.nsh
        DESTINATION ..
            COMPONENT Runtime)
ENDIF()

# 安装系统运行库
if("debug" STREQUAL CHINESE_CHESS_CONTROL_BUILD_TYPE)
    set(CMAKE_INSTALL_DEBUG_LIBRARIES TRUE)
endif()
set(CMAKE_INSTALL_SYSTEM_RUNTIME_COMPONENT DependLibraries)
if(MFC_FOUND)
    set(CMAKE_INSTALL_MFC_LIBRARIES ON)
endif()
include(InstallRequiredSystemLibraries)
# CPack 制作包
include(Package/CMakeCPack.cmake)

# 产生文档
option(BUILD_DOCS "Generating API documentation" OFF)
if(BUILD_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Doxygen)
        configure_file(${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
        add_custom_target(doc ALL
            ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile # &> doxygen.log
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM
            )
        install(DIRECTORY ${CMAKE_BINARY_DIR}/Doxygen/
            DESTINATION ${CMAKE_INSTALL_DOCDIR}
            COMPONENT Runtime)
    endif(DOXYGEN_FOUND)
endif(BUILD_DOCS)

message(STATUS "Build shared library: ${BUILD_SHARED_LIBS}")
message(STATUS "Build MFC chinese chess mfc view: ${BUILD_CHINESE_CHESS_MFC_VIEW}")
message(STATUS "Build MFC chinese chess activex: ${BUILD_CHINESE_CHESS_ACTIVEX}")
message(STATUS "Build MFC chinese chess applaction: ${BUILD_CHINESE_CHESS_APP_MFC}")
message(STATUS "Build chinese chess qt: ${BUILD_CHINESE_CHESS_QT}")
message(STATUS "Build MFC chinese chess qt application: ${BUILD_CHINESE_CHESS_QT_APP}")
message(STATUS "Generating API documentation: ${BUILD_DOCS}")
message(STATUS "With QT: ${Qt${QT_VERSION_MAJOR}_VERSION}")
