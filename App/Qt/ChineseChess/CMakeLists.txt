project(ChineseChessApp)

GET_VERSION(OUT_VERSION ChineseChessApp_VERSION
    OUT_REVISION ChineseChessApp_REVISION
)
if(NOT ChineseChessApp_VERSION)
    set(ChineseChessApp_VERSION ${ChineseChessControl_VERSION})
endif()
message("ChineseChessApp_VERSION:${ChineseChessApp_VERSION};ChineseChessApp_REVISION:${ChineseChessApp_REVISION}")

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
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "copy directory ${CMAKE_BINARY_DIR}/assets to ${CMAKE_CURRENT_BINARY_DIR}/android-build/assets"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_BINARY_DIR}/assets" "${CMAKE_CURRENT_BINARY_DIR}/android-build/assets"
        COMMENT "Copy directory ${CMAKE_BINARY_DIR}/assets/ to ${CMAKE_CURRENT_BINARY_DIR}/android-build/assets"
        COMMAND_EXPAND_LISTS
        VERBATIM)
    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY
        QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)
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

# Install other files
set(OTHER_FILES
    ${CMAKE_SOURCE_DIR}/License.md
    ${CMAKE_SOURCE_DIR}/Authors.md
    ${CMAKE_SOURCE_DIR}/ChangeLog.md
    )

INSTALL_FILE(SOURCES ${OTHER_FILES}
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
        COMPONENT Runtime)
