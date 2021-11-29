cmake_minimum_required(VERSION 2.8)

project(ChineseChessControl)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
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

SET(BUILD_VERSION "v2.0.4")
# Find Git Version Patch
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
        SET(BUILD_VERSION ${GIT_VERSION})
    ENDIF()
ENDIF()
message("BUILD_VERSION:${BUILD_VERSION}")
set(VERSION ${BUILD_VERSION})

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif(NOT DEFINED CMAKE_BUILD_TYPE)
string(TOLOWER "${CMAKE_BUILD_TYPE}" CHINESE_CHESS_CONTROL_BUILD_TYPE)
if("debug" STREQUAL CHINESE_CHESS_CONTROL_BUILD_TYPE)
    add_definitions(-D_DEBUG -DDEBUG)
endif()

IF(MSVC)
    # This option is to enable the /MP switch for Visual Studio 2005 and above compilers
    OPTION(WIN32_USE_MP "Set to ON to build with the /MP option (Visual Studio 2005 and above)." ON)
    MARK_AS_ADVANCED(WIN32_USE_MP)
    IF(WIN32_USE_MP)
        #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
        add_compile_options(/MP)
    ENDIF(WIN32_USE_MP)
ENDIF(MSVC)
IF(CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
    OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

    if("debug" STREQUAL CHINESE_CHESS_CONTROL_BUILD_TYPE)    
        add_compile_options(-g -ggdb)
    else()
        add_compile_options(-O3)
    endif()
ENDIF()
SET(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libs")
if (BUILD_SHARED_LIBS)
    add_definitions(-DBUILD_SHARED_LIBS)
    if (CMAKE_COMPILER_IS_GNUCXX AND NOT MINGW)
       # Just setting CMAKE_POSITION_INDEPENDENT_CODE should be enough to set
       # -fPIC for GCC but sometimes it still doesn't get set, so make sure it
       # does.
       add_definitions("-fPIC")
    endif()
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(GenerateExportHeader)
include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckFunctionExists)
include(${CMAKE_SOURCE_DIR}/cmake/Utils.cmake)

#CHECK_INCLUDE_FILE_CXX("string" HAVE_STRING_H)
#check_include_file("math.h" HAVE_MATH_H)

#check_function_exists("fabs" HAVE_FABS)

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
if(MSVC)
    option(BUILD_CHINESE_CHESS_MFC_VIEW "Build MFC chinese chess mfc view" ON)
    if(BUILD_CHINESE_CHESS_MFC_VIEW)
        add_subdirectory(UI/MFC)
        
        option(BUILD_CHINESE_CHESS_ACTIVEX "Build MFC chinese chess activex" ON)
        if(BUILD_CHINESE_CHESS_ACTIVEX)
            add_subdirectory(UI/ActiveX)
        endif()
    endif()
    
    option(BUILD_CHINESE_CHESS_APP_MFC "Build MFC chinese chess applaction" ON)
    if(BUILD_CHINESE_CHESS_APP_MFC AND MSVC)
        add_subdirectory(App/MFC/ChineseChessMFC)
    endif()
endif()

#需要的QT组件
SET(QT_COMPONENTS Core Gui Widgets Multimedia)
if(ANDROID)
    SET(QT_COMPONENTS ${QT_COMPONENTS} AndroidExtras)
ELSE()
    LIST(APPEND QT_COMPONENTS Designer)
endif()
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${QT_COMPONENTS})
if(Qt${QT_VERSION_MAJOR}_FOUND)
    message("QT_VERSION:${Qt${QT_VERSION_MAJOR}_VERSION}")
    
    if (NOT BUILD_SHARED_LIBS)
        # Qt 静态插件
        add_definitions(-DQT_STATICPLUGIN)
    endif()
    
    if(Qt5_VERSION VERSION_LESS 5.10.0 AND ANDROID)
        message(FATAL_ERROR "Qt must great 5.10.0")
    endif()
    FOREACH(_COMPONENT ${QT_COMPONENTS})
	    SET(QT_LIBRARIES ${QT_LIBRARIES} Qt${QT_VERSION_MAJOR}::${_COMPONENT})
    ENDFOREACH()
    get_filename_component(QT_INSTALL_DIR "${Qt${QT_VERSION_MAJOR}_DIR}/../../.." ABSOLUTE)
    
    #打开 qt 编译工具
    SET(CMAKE_AUTOUIC ON)
    SET(CMAKE_AUTOMOC ON)
    SET(CMAKE_AUTORCC ON)
    SET(CMAKE_INCLUDE_CURRENT_DIR ON)
    SET(CMAKE_VERBOSE_MAKEFILE ON)
    
    option(BUILD_CHINESE_CHESS_QT "Build chinese chess qt" ON)
    if(BUILD_CHINESE_CHESS_QT)
        if(NOT RabbitCommon_DIR)
            set(RabbitCommon_DIR $ENV{RabbitCommon_DIR})
            if(NOT RabbitCommon_DIR)
                set(RabbitCommon_DIR ${CMAKE_SOURCE_DIR}/../RabbitCommon)
            endif()
        endif()
        if(DEFINED RabbitCommon_DIR AND EXISTS ${RabbitCommon_DIR}/Src)
            add_subdirectory(${RabbitCommon_DIR}/Src ${CMAKE_BINARY_DIR}/RabbitCommon)
        else()
            message("1. Please download RabbitCommon source code from https://github.com/KangLin/RabbitCommon")
            message("   ag:")
            message("       git clone https://github.com/KangLin/RabbitCommon.git")
            message("2. Then set cmake value or environment variable RabbitCommon_DIR to download root dirctory.")
            message("   ag:")
            message(FATAL_ERROR "       cmake -DRabbitCommon_DIR= ")
        endif()
        
        add_subdirectory(UI/Qt)
        
        option(BUILD_CHINESE_CHESS_QT_APP "Build MFC chinese chess qt application" ON)
        if(BUILD_CHINESE_CHESS_QT_APP)
            add_subdirectory(App/Qt/ChineseChess)
        endif()
    endif()
endif()

# Create install runtime target
add_custom_target(install-runtime
  COMMAND
     "${CMAKE_COMMAND}" -DCMAKE_INSTALL_COMPONENT=Runtime 
     -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake"
)
# Create uninstall runtime target
add_custom_target(uninstall-runtime
  COMMAND
     "${CMAKE_COMMAND}" -DCMAKE_INSTALL_COMPONENT=Runtime 
     -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
)
# Create will be delete files
CONFIGURE_FILE(
    "${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
# Create unistall target
ADD_CUSTOM_TARGET(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
    DEPENDS uninstall-runtime)

IF(WIN32)
    # 替换 Install.nsi 中的 MSVC_VERSION
    configure_file(Install/Install.nsi ${CMAKE_BINARY_DIR}/Install.nsi @ONLY)
    INSTALL(FILES ${CMAKE_BINARY_DIR}/Install.nsi Install/InstallRedistributables.nsh DESTINATION "${CMAKE_BINARY_DIR}"
        COMPONENT Runtime)
endif()
# Install other files
set(OTHER_FILES
    License.md
    Authors.md
    ChangeLog.md
    )
if(ANDROID)
    INSTALL(FILES ${OTHER_FILES} DESTINATION "assets" COMPONENT Runtime)
else()
    INSTALL(FILES ${OTHER_FILES} DESTINATION "." COMPONENT Runtime)
endif()

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

message(STATUS "== Build shared library: ${BUILD_SHARED_LIBS}")
message(STATUS "== Build arch: ${BUILD_ARCH}")
message(STATUS "== Build MFC chinese chess mfc view: ${BUILD_CHINESE_CHESS_MFC_VIEW}")
message(STATUS "== Build MFC chinese chess activex: ${BUILD_CHINESE_CHESS_ACTIVEX}")
message(STATUS "== Build MFC chinese chess applaction: ${BUILD_CHINESE_CHESS_APP_MFC}")
message(STATUS "== With QT: ${Qt5_VERSION}")
