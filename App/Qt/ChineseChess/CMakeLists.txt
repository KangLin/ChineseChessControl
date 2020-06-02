project(ChineseChessApp)

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
if("Debug" STREQUAL CMAKE_BUILD_TYPE)
    LIST(APPEND RCC_FILES
        ${TRANSLATIONS_QRC_FILES}
        )
endif()

add_definitions(-DBUILD_VERSION="${BUILD_VERSION}")
add_definitions(-DBUILD_ARCH="${BUILD_ARCH}")
add_definitions(-DBUILD_PLATFORM="${BUILD_PLATFORM}")
if(ANDROID)
    add_library(${PROJECT_NAME} ${SOURCES_FILES} ${HEADER_FILES} ${SOURCE_UI_FILES} ${RCC_FILES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES_FILES} ${HEADER_FILES} ${SOURCE_UI_FILES} ${RCC_FILES})
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE ChineseChessQt ${QT_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    VERSION ${BUILD_VERSION})
if(UNIX AND NOT ANDROID)
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${PROJECT_NAME})
endif()
if(MINGW)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows")
elseif(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS
        "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

if(BUILD_VERSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        -DBUILD_VERSION="${BUILD_VERSION}"
        RABBITCOMMON)
endif()

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_BINARY_DIR}
    ${RabbitCommon_DIR}/Src
    ${CMAKE_SOURCE_DIR}/Src/Qt
    ${CMAKE_SOURCE_DIR}/Src
    )

# Install target
if(ANDROID)
    INSTALL(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "libs/${ANDROID_ABI}"
            COMPONENT Runtime
        LIBRARY DESTINATION "libs/${ANDROID_ABI}"
            COMPONENT Runtime
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        )
elseif(WIN32)
    INSTALL(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            COMPONENT Runtime
        LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
            COMPONENT Runtime
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        )
else()
    INSTALL(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            COMPONENT Runtime
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            COMPONENT Runtime
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        )        
endif()
INSTALL_TARGETS(TARGETS ChineseChessQt ChineseChess)

if(UNIX AND NOT ANDROID)
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/debian/ChineseChess.desktop
        DESTINATION "share/applications"
            COMPONENT Runtime)
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/Src/Qt/Resource/image/b_j.png
        RENAME ChineseChess.png
        DESTINATION "share/pixmaps"
            COMPONENT Runtime)
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

IF( ("Release" STREQUAL CMAKE_BUILD_TYPE)
    OR ("MinSizeRel" STREQUAL CMAKE_BUILD_TYPE)
    AND WIN32 AND BUILD_SHARED_LIBS )
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
        --compiler-runtime
        --verbose 7
        "$<TARGET_FILE:${PROJECT_NAME}>"
        )
    INSTALL(DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
        DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Runtime)
ENDIF()
