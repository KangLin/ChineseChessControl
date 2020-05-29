project(ChineseChessQt)

message(STATUS "== Build chinese chess qt dll")

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
if("Debug" STREQUAL CMAKE_BUILD_TYPE)
    LIST(APPEND RCC_FILES
        ${TRANSLATIONS_QRC_FILES}
        )
endif()

add_library(${PROJECT_NAME} ${SOURCES_FILES} ${HEADER_FILES} ${RCC_FILES} ${SOURCE_UI_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    PUBLIC_HEADER "${INSTALLHEADER_FILES}" # Install head files
    VERSION ${BUILD_VERSION})

if(BUILD_VERSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DBUILD_VERSION="${BUILD_VERSION}")
endif()
target_compile_definitions(${PROJECT_NAME} PUBLIC ${LIBS_DEFINES})

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ChineseChess RabbitCommon ${QT_LIBRARIES})
target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${RabbitCommon_DIR}/Src
    )

GENERATE_EXPORT_HEADER(${PROJECT_NAME})
string(TOLOWER ${PROJECT_NAME} LOWER_PROJECT_NAME)
set(INSTALLHEADER_FILES ${INSTALLHEADER_FILES} 
    ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h)
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h
    DESTINATION ${CMAKE_BINARY_DIR})

SET(INSTALL_LIBRARY "${CMAKE_INSTALL_LIBDIR}")
if(WIN32)
	SET(INSTALL_LIBRARY "${CMAKE_INSTALL_BINDIR}")
endif()

# 安装中国象棋控件
INSTALL(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Config
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Runtime
    LIBRARY DESTINATION "${INSTALL_LIBRARY}"
        COMPONENT Runtime
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ChineseChess
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

export(TARGETS ${PROJECT_NAME}
    APPEND FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    )
# Install cmake configure files
install(EXPORT ${PROJECT_NAME}Config
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ChineseChess"
    )
write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${BUILD_VERSION}
    COMPATIBILITY AnyNewerVersion)
install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ChineseChess")

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
