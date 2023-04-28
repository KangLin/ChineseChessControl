project(ChineseChessApp)

GET_VERSION(OUT_VERSION ChineseChessApp_VERSION
    OUT_REVISION ChineseChessApp_REVISION
)
if(NOT ChineseChessApp_VERSION)
    set(ChineseChessApp_VERSION ${ChineseChessControl_VERSION})
endif()
message("ChineseChessApp_VERSION:${ChineseChessApp_VERSION};ChineseChessApp_REVISION:${ChineseChessApp_REVISION}")

#需要的QT组件
SET(QT_LIBRARIES)
SET(QT_COMPONENTS Core Gui Widgets)
if(ANDROID AND (Qt${QT_VERSION_MAJOR}_VERSION VERSION_LESS 6.0.0))
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
    
    if(Qt${QT_VERSION_MAJOR}_VERSION VERSION_LESS 5.10.0 AND ANDROID)
        message(FATAL_ERROR "Qt must great 5.10.0")
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
include(${RabbitCommon_DIR}/cmake/Translations.cmake)
GENERATED_QT_TRANSLATIONS(SOURCES ${SOURCES_FILES} ${SOURCE_UI_FILES}
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
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    VERSION ${ChineseChessApp_VERSION})
# 程序以windows方式启动，不出现控制台窗口,加 /ENTRY:mainCRTStartup
if(MSVC)
    if(CMAKE_WINDOWS_VERSION STREQUAL "WINXP")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "/SUBSYSTEM:WINDOWS\",5.01\" /ENTRY:mainCRTStartup")
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    endif()
else(MINGW)
    set_target_properties(${PARA_NAME} PROPERTIES LINK_FLAGS "-mwindows")
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
    INSTALL(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            COMPONENT QtApplications
        )        
endif()

if(UNIX AND NOT ANDROID)
    INSTALL(PROGRAMS ${CMAKE_SOURCE_DIR}/Package/share/applications/ChineseChess.sh
        DESTINATION "${CMAKE_INSTALL_BINDIR}"
            COMPONENT QtApplications)
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/Package/share/applications/org.Rabbit.ChineseChess.desktop
        DESTINATION "share/applications"
            COMPONENT QtApplications)
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/Src/Res/Picture/69/bjiang.png
        RENAME org.Rabbit.ChineseChess.png
        DESTINATION "share/pixmaps"
            COMPONENT QtApplications)
endif()

IF(ANDROID)
    Set(JSON_FILE ${CMAKE_CURRENT_BINARY_DIR}/android_deployment_settings.json)
    GENERATED_DEPLOYMENT_SETTINGS(NAME ${JSON_FILE}
        APPLACTION "${CMAKE_BINARY_DIR}/bin/lib${PROJECT_NAME}.so")

    add_custom_target(APK #注意 需要把 ${QT_INSTALL_DIR}/bin 加到环境变量PATH中
            COMMAND "${QT_INSTALL_DIR}/bin/androiddeployqt"
                --output ${CMAKE_INSTALL_PREFIX}
                --input ${JSON_FILE}
                --verbose
                --gradle
                --android-platform ${ANDROID_PLATFORM}
        )
ENDIF(ANDROID)

IF( WIN32 AND BUILD_SHARED_LIBS )

    IF( ("Release" STREQUAL CMAKE_BUILD_TYPE)
        OR ("MinSizeRel" STREQUAL CMAKE_BUILD_TYPE)
        AND MINGW )
        #windeployqt 分发时，是根据是否 strip 来判断是否是 DEBUG 版本,而用mingw编译时,qt没有自动 strip
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND strip "$<TARGET_FILE:${PROJECT_NAME}>"
            )
    ENDIF()

    #注意 需要把 ${QT_INSTALL_DIR}/bin 加到环境变量PATH中
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${QT_INSTALL_DIR}/bin/windeployqt"
        --no-compiler-runtime
        --verbose 7
        --dir "${CMAKE_BINARY_DIR}/DependLibraries"
        --libdir "${CMAKE_BINARY_DIR}/DependLibraries"
        --plugindir "${CMAKE_BINARY_DIR}/DependLibraries"
        "$<TARGET_FILE:${PROJECT_NAME}>"
        )
    INSTALL(DIRECTORY "${CMAKE_BINARY_DIR}/DependLibraries/"
        DESTINATION "${CMAKE_INSTALL_BINDIR}"
            COMPONENT DependLibraries)
        
ENDIF()

if(NOT EXISTS ${CMAKE_BINARY_DIR}/etc/ChineseChess_logqt.ini)
    configure_file(${CMAKE_SOURCE_DIR}/etc/ChineseChess_logqt.ini
        ${CMAKE_BINARY_DIR}/etc/ChineseChess_logqt.ini
        COPYONLY)
endif()
INSTALL(FILES ${CMAKE_SOURCE_DIR}/etc/ChineseChess_logqt.ini
    DESTINATION etc
    COMPONENT Runtime)
