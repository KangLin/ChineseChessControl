project(ChineseChessQt)

#需要的QT组件
SET(QT_LIBRARIES)
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
endif()
    
LIST(APPEND SOURCES_FILES
    FrmChineseChess.cpp
    )

LIST(APPEND INSTALLHEADER_FILES
    FrmChineseChess.h
    )

IF(NOT ANDROID)
    LIST(APPEND SOURCES_FILES
        FrmChineseChessPlugin.cpp
        )
    
    LIST(APPEND INSTALLHEADER_FILES
        FrmChineseChessPlugin.h
        )
ENDIF()

LIST(APPEND HEADER_FILES
    ${INSTALLHEADER_FILES}
    )

LIST(APPEND SOURCE_UI_FILES
    FrmChineseChess.ui)

SET(RCC_FILES
    ResourceChineseChess.qrc
    )

#翻译
include(${RabbitCommon_DIR}/cmake/Translations.cmake)
GENERATED_QT_TRANSLATIONS(SOURCES ${SOURCES_FILES} ${SOURCE_UI_FILES}
    OUT_QRC TRANSLATIONS_QRC_FILES)
if("debug" STREQUAL CHINESE_CHESS_CONTROL_BUILD_TYPE)
    LIST(APPEND RCC_FILES ${TRANSLATIONS_QRC_FILES})
endif()

add_library(${PROJECT_NAME} ${SOURCES_FILES} ${HEADER_FILES}
    ${RCC_FILES} ${SOURCE_UI_FILES})

GENERATE_EXPORT_HEADER(${PROJECT_NAME})
string(TOLOWER ${PROJECT_NAME} LOWER_PROJECT_NAME)
set(INSTALLHEADER_FILES ${INSTALLHEADER_FILES} 
    ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h)
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h
    DESTINATION ${CMAKE_BINARY_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    PUBLIC_HEADER "${INSTALLHEADER_FILES}" # Install head files
    VERSION ${ChineseChessControl_VERSION})

if(ChineseChessControl_VERSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        -DChineseChessControl_VERSION="${ChineseChessControl_VERSION}")
endif()
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:_DEBUG DEBUG>
    )

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        "$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    target_compile_options(${PROJECT_NAME} PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ChineseChess ${QT_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE RabbitCommon)
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

# 安装中国象棋控件
SET(INSTALL_LIBRARY "${CMAKE_INSTALL_LIBDIR}")
if(WIN32)
	SET(INSTALL_LIBRARY "${CMAKE_INSTALL_BINDIR}")
endif()
INSTALL(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Runtime
    LIBRARY DESTINATION "${INSTALL_LIBRARY}"
        COMPONENT Runtime
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT Development
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ChineseChessControl
        COMPONENT Development
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ChineseChessControl
    )

export(TARGETS ${PROJECT_NAME}
    APPEND FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    NAMESPACE ChineseChessControl::
    )

# 因为编译树中已有 export(ChineseChessQtConfig.cmake)
configure_package_config_file(
      ${CMAKE_SOURCE_DIR}/cmake/ChineseChessQtConfig.cmake.in
      ${CMAKE_CURRENT_BINARY_DIR}/ChineseChessQtConfig.cmake.in
      INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ChineseChessControl"
      )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ChineseChessQtConfig.cmake.in
      DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ChineseChessControl
          COMPONENT Development
      RENAME ChineseChessQtConfig.cmake)

# Install cmake configure files
install(EXPORT ${PROJECT_NAME}Targets
    NAMESPACE ChineseChessControl::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ChineseChessControl"
    )

write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${ChineseChessControl_VERSION}
    COMPATIBILITY AnyNewerVersion)
install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ChineseChessControl"
        COMPONENT Development)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
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
        "$<TARGET_FILE:${PROJECT_NAME}>"
        )
    INSTALL(DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
        DESTINATION "${CMAKE_INSTALL_BINDIR}"
            COMPONENT Runtime)
ENDIF()
