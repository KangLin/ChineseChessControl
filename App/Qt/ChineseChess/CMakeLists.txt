project(ChineseChessApp)

GET_VERSION(OUT_VERSION ChineseChessApp_VERSION
    OUT_REVISION ChineseChessApp_REVISION
)
if(NOT ChineseChessApp_VERSION)
    set(ChineseChessApp_VERSION ${ChineseChessControl_VERSION})
endif()
message("ChineseChessApp_VERSION: ${ChineseChessApp_VERSION}; ChineseChessApp_REVISION: ${ChineseChessApp_REVISION}")

#需要的QT组件
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core)
if((QT_VERSION_MAJOR LESS 6) AND ANDROID)
    message(FATAL_ERROR "Qt version must great 6.0.0 in android")
endif()
SET(QT_LIBRARIES)
SET(QT_COMPONENTS Core Gui Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${QT_COMPONENTS})
if(Qt${QT_VERSION_MAJOR}_FOUND)
    message("QT_VERSION:${Qt${QT_VERSION_MAJOR}_VERSION}")

    if (NOT BUILD_SHARED_LIBS)
        # Qt 静态插件
        add_definitions(-DQT_STATICPLUGIN)
    endif()

    FOREACH(_COMPONENT ${QT_COMPONENTS})
	    SET(QT_LIBRARIES ${QT_LIBRARIES} Qt${QT_VERSION_MAJOR}::${_COMPONENT})
    ENDFOREACH()
    get_filename_component(QT_INSTALL_DIR "${Qt${QT_VERSION_MAJOR}_DIR}/../../.." ABSOLUTE)
endif()

set(SOURCES_FILES
    main.cpp
    MainWindow.cpp
    )

set(INSTALLHEADER_FILES
    )

set(HEADER_FILES
    ${INSTALLHEADER_FILES}
    MainWindow.h
    )

set(SOURCE_UI_FILES
    MainWindow.ui)

if(WIN32)
    SET(RCC_FILES ${RCC_FILES} Resource/AppIcon.rc)
endif()
LIST(APPEND RCC_FILES Resource/Resource.qrc)

#翻译
GENERATED_QT_TRANSLATIONS(ALL
    SOURCES ${SOURCES_FILES} ${SOURCE_UI_FILES}
    OUT_QRC TRANSLATIONS_QRC_FILES)
if("debug" STREQUAL CHINESE_CHESS_CONTROL_BUILD_TYPE)
    LIST(APPEND RCC_FILES ${TRANSLATIONS_QRC_FILES})
endif()

if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        ${SOURCES_FILES}
        ${HEADER_FILES}
        ${SOURCE_UI_FILES}
        ${RCC_FILES}
    )
else()
    if(ANDROID)
        add_library(${PROJECT_NAME}
            ${SOURCES_FILES}
            ${HEADER_FILES}
            ${SOURCE_UI_FILES}
            ${RCC_FILES})
    else()
        add_executable(${PROJECT_NAME} ${SOURCES_FILES}
            ${HEADER_FILES} ${SOURCE_UI_FILES} ${RCC_FILES})
    endif()
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE
    ChineseChessQt RabbitCommon ${QT_LIBRARIES})
if(ANDROID)

    if(QT_VERSION GREATER_EQUAL 6.11.0)
        set(ANDROID_BUILD ${CMAKE_CURRENT_BINARY_DIR}/android-build-${PROJECT_NAME})
    else()
        set(ANDROID_BUILD ${CMAKE_CURRENT_BINARY_DIR}/android-build)
    endif()
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "copy directory ${CMAKE_BINARY_DIR}/assets to ${ANDROID_BUILD}/assets"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_BINARY_DIR}/assets" "${ANDROID_BUILD}/assets"
        COMMENT "Copy directory ${CMAKE_BINARY_DIR}/assets/ to ${ANDROID_BUILD}/assets"
        COMMAND_EXPAND_LISTS
        VERBATIM)
    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY
        QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)

    # 设置 Android 相关属性
    # See: https://doc.qt.io/qt-6/zh/qt-android-generate-deployment-settings.html
    set_target_properties(${PROJECT_NAME} PROPERTIES
        # Android 包名
        QT_ANDROID_PACKAGE_NAME "io.github.KangLinStudio.ChineseChess"
        # 最小 SDK 版本
        QT_ANDROID_MIN_SDK_VERSION 28
        # 目标 SDK 版本
        QT_ANDROID_TARGET_SDK_VERSION 34
    )

    # 创建临时 CMake 脚本来修改 build.gradle
    set(FIX_SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/fix_build_gradle.cmake")

    file(WRITE "${FIX_SCRIPT}"
        "
        if(EXISTS \"\${BUILD_DIR}/build.gradle\")
            file(READ \"\${BUILD_DIR}/build.gradle\" CONTENT)

            # 方式1：添加中文支持
            #string(REPLACE \"resConfig \\\"en\\\"\" \"resConfig \\\"en\\\", \\\"zh\\\"\" CONTENT \"\${CONTENT}\")

            # 方式2：或者直接注释掉 resConfigs 行
            string(REGEX REPLACE \"resConfig \\\"en\\\"\" \"// resConfig \\\"en\\\"  // Disabled for multi-language\" CONTENT \"\${CONTENT}\")

            file(WRITE \"\${BUILD_DIR}/build.gradle\" \"\${CONTENT}\")
            message(STATUS \"Updated build.gradle for multi-language\")
        else()
            message(FATAL_ERROR \"\${BUILD_DIR}/build.gradle not found\")
        endif()
        "
    )

    # 创建一个独立的目标，在 androiddeployqt 之后运行
    add_custom_target(fix_build_gradle ALL
        COMMAND ${CMAKE_COMMAND}
            -DBUILD_DIR="${ANDROID_BUILD}"
            -P "${FIX_SCRIPT}"
        DEPENDS ${PROJECT_NAME}_make_apk  # 依赖 APK 生成目标
        COMMENT "Patching build.gradle after androiddeployqt"
    )

else()
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${ChineseChessApp_VERSION})

# setup rpath to where binary is at.
if(APPLE)
    SET_TARGET_PROPERTIES(${PROJECT_NAME}
        PROPERTIES INSTALL_RPATH
        "lib;../lib;../lib/${CMAKE_LIBRARY_ARCHITECTURE};@executable_path/../lib;@executable_path;@executable_path/../lib/${CMAKE_LIBRARY_ARCHITECTURE}")
else()
    SET_TARGET_PROPERTIES(${PROJECT_NAME}
        PROPERTIES INSTALL_RPATH
            "$ORIGIN;$ORIGIN/../lib;$ORIGIN/../lib/${CMAKE_LIBRARY_ARCHITECTURE};lib;../lib;../lib/${CMAKE_LIBRARY_ARCHITECTURE}")
endif()

# 程序以windows方式启动，不出现控制台窗口,加 /ENTRY:mainCRTStartup
if(MSVC)
    if(CMAKE_WINDOWS_VERSION STREQUAL "WINXP")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "/SUBSYSTEM:WINDOWS\",5.01\" /ENTRY:mainCRTStartup")
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    endif()
elseif(MINGW)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows")
endif()

if(UNIX AND NOT ANDROID)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_NAME ${PROJECT_NAME})
endif()

target_compile_options(${PROJECT_NAME} PRIVATE
    "$<$<C_COMPILER_ID:MSVC>:/utf-8>"
    "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
    $<$<CXX_COMPILER_ID:GNU,Clang>:$<IF:$<CONFIG:Debug>, -g -ggdb, -O3>>
    )

if(NOT MINGW)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang>:-fPIC>
    )
endif()
target_compile_definitions(${PROJECT_NAME} PRIVATE
    ChineseChessApp_VERSION="${ChineseChessApp_VERSION}"
    ChineseChessApp_REVISION="${ChineseChessApp_REVISION}"
    $<$<CONFIG:Debug>:_DEBUG DEBUG>
    )
target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_BINARY_DIR}
    )

# Install target
if(ANDROID)
    INSTALL(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "libs/${ANDROID_ABI}"
            COMPONENT QtApplications
        LIBRARY DESTINATION "libs/${ANDROID_ABI}"
            COMPONENT QtApplications
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            COMPONENT QtDevelopment
        )
else()
    SET(INSTALL_RUNTIME "${CMAKE_INSTALL_BINDIR}")
    if(APPLE)
        # See: https://doc.qt.io/qt-6/macos-deployment.html
        # See: [Apple's Developer Website](https://developer.apple.com/library/archive/documentation/CoreFoundation/Conceptual/CFBundles/Introduction/Introduction.html#//apple_ref/doc/uid/10000123i-CH1-SW1)
        SET(INSTALL_RUNTIME "MacOS")
    endif()
    INSTALL(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${INSTALL_RUNTIME}"
            COMPONENT QtApplications
        )        
endif()

SET(APP_ID io.github.KangLin.ChineseChess)
IF(APPLE)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resource/App.Info.plist
        ${CMAKE_CURRENT_BINARY_DIR}/Info.plist
        @ONLY)
    INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/Info.plist
        DESTINATION "." COMPONENT QtApplications)
    target_add_resources(${PROJECT_NAME} . "${CMAKE_CURRENT_SOURCE_DIR}/Resource/Image/${APP_ID}.icns")
    cmake_minimum_required(VERSION 3.16)
    project(ChineseChessApp)

ELSEIF(UNIX AND NOT ANDROID)

    INSTALL(PROGRAMS ${CMAKE_SOURCE_DIR}/Package/share/applications/ChineseChess.sh
        DESTINATION "${CMAKE_INSTALL_BINDIR}"
            COMPONENT QtApplications)
    configure_file(${CMAKE_SOURCE_DIR}/Package/share/applications/${APP_ID}.desktop.in
        ${CMAKE_BINARY_DIR}/${APP_ID}.desktop)
    INSTALL(FILES ${CMAKE_BINARY_DIR}/${APP_ID}.desktop
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
            COMPONENT QtApplications
        PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/Src/Res/Picture/69/bjiang.png
        RENAME ${APP_ID}.png
        DESTINATION "${CMAKE_INSTALL_DATADIR}/pixmaps"
            COMPONENT QtApplications)

ELSEIF(WIN32 AND BUILD_SHARED_LIBS)

    if(RABBIT_ENABLE_INSTALL_DEPENDENT)
        set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION "${CMAKE_INSTALL_BINDIR}")
        set(CMAKE_INSTALL_SYSTEM_RUNTIME_COMPONENT QtApplications)
        set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
        include(InstallRequiredSystemLibraries)
    endif()

    IF( ("Release" STREQUAL CMAKE_BUILD_TYPE)
        OR ("MinSizeRel" STREQUAL CMAKE_BUILD_TYPE)
        AND MINGW )
        #windeployqt 分发时，是根据是否 strip 来判断是否是 DEBUG 版本,而用mingw编译时,qt没有自动 strip
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND strip "$<TARGET_FILE:${PROJECT_NAME}>"
            )
    ENDIF()

    #注意 需要把 ${QT_INSTALL_DIR}/bin 加到环境变量PATH中
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt
        HINTS ${QT_INSTALL_DIR}/bin
        DOC "Path to windeployqt executable"
    )
    if(WINDEPLOYQT_EXECUTABLE)
        message("find windeployqt: ${WINDEPLOYQT_EXECUTABLE}")
        string(CONFIGURE [[
            message(STATUS "Exec windeployqt for @PROJECT_NAME@ ......")
            execute_process(
                COMMAND "@WINDEPLOYQT_EXECUTABLE@"
                #--compiler-runtime # 因为已用了 include(InstallRequiredSystemLibraries)
                --verbose 7
                --no-quick-import
                --dir "@CMAKE_BINARY_DIR@/DependLibraries"
                --libdir "@CMAKE_BINARY_DIR@/DependLibraries"
                --plugindir "@CMAKE_BINARY_DIR@/DependLibraries"
                "$<TARGET_FILE:@PROJECT_NAME@>"
            )
        ]] code_windeployqt @ONLY)
        INSTALL(CODE ${code_windeployqt}
            COMPONENT DependLibraries
        )
        INSTALL(DIRECTORY "${CMAKE_BINARY_DIR}/DependLibraries/"
            DESTINATION "${CMAKE_INSTALL_BINDIR}"
            COMPONENT DependLibraries)
    else()
        message(WARNING "Don't find windeployqt in ${QT_INSTALL_DIR}/bin")
    endif()

ENDIF()

if(NOT EXISTS ${CMAKE_BINARY_DIR}/etc/ChineseChess_logqt.ini)
    configure_file(${CMAKE_SOURCE_DIR}/etc/ChineseChess_logqt.ini
        ${CMAKE_BINARY_DIR}/etc/ChineseChess_logqt.ini
        COPYONLY)
endif()
INSTALL(FILES ${CMAKE_SOURCE_DIR}/etc/ChineseChess_logqt.ini
    DESTINATION etc
    COMPONENT QtApplications)

# Install other files
set(OTHER_FILES
    ${CMAKE_SOURCE_DIR}/License.md
    ${CMAKE_SOURCE_DIR}/Authors.md
    ${CMAKE_SOURCE_DIR}/ChangeLog.md
    )

INSTALL_FILE(SOURCES ${OTHER_FILES}
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
        COMPONENT QtApplications)
