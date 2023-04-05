project(ChineseChess)

SET(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(GenerateExportHeader)

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
            OUTPUT_VARIABLE ${PROJECT_NAME}_VERSION  OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        EXECUTE_PROCESS(
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMAND ${GIT} rev-parse --short HEAD
            OUTPUT_VARIABLE ${PROJECT_NAME}_REVISION OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        if(NOT ${PROJECT_NAME}_VERSION)
            set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_REVISION})
        endif()
        SET(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION})
    ENDIF()
ENDIF()

if(NOT ${PROJECT_NAME}_VERSION)
    SET(${PROJECT_NAME}_VERSION "v2.0.5")
endif()

if(${PROJECT_NAME}_VERSION)
    list(APPEND CHINESE_CHESS_DEFINITIONS
        ${PROJECT_NAME}_VERSION="${${PROJECT_NAME}_VERSION}")
endif()
if(${PROJECT_NAME}_REVISION)
    list(APPEND CHINESE_CHESS_DEFINITIONS
        ${PROJECT_NAME}_REVISION="${${PROJECT_NAME}_REVISION}")
endif()
message("${PROJECT_NAME}_VERSION:${${PROJECT_NAME}_VERSION};${PROJECT_NAME}_REVISION=${${PROJECT_NAME}_REVISION}")

set(CHINESE_CHESS_SOURCES_FILES
    ChineseChess.cpp
    ChessGame.cpp
    ChessSteps.cpp
    ChessStepsChinese.cpp
    Piece.cpp
    Common.cpp
    GoRule.cpp
    Fen.cpp
    Pgn.cpp
    )

set(CHINESE_CHESS_HEADER_FILES
    ChineseChess.h
    ChessGame.h
    ChessSteps.h
    ChessStepsChinese.h
    Piece.h
    Common.h
    GoRule.h
    Fen.h
    Pgn.h
    )

SET(CHINESE_CHESS_RCC_FILES
    ${TRANSLATIONS_RESOURCE_FILES}
	)

# For debug libs and exes, add "_d" postfix
if(NOT CMAKE_DEBUG_POSTFIX)
    set(CMAKE_DEBUG_POSTFIX "_d")
endif()
if(WIN32)
    option(WITH_LIBRARY_SUFFIX_VERSION "Library suffix plus version number" ON)

    if(WITH_LIBRARY_SUFFIX_VERSION)
        if(CMAKE_BUILD_TYPE)
            string(TOUPPER ${CMAKE_BUILD_TYPE} UPPER_CMAKE_BUILD_TYPE)
            SET(CMAKE_${UPPER_CMAKE_BUILD_TYPE}_POSTFIX "${CMAKE_${UPPER_CMAKE_BUILD_TYPE}_POSTFIX}_${${PROJECT_NAME}_VERSION}")
        elseif(CMAKE_CONFIGURATION_TYPES)
            foreach(PARA_CONFIG ${CMAKE_CONFIGURATION_TYPES})
                string(TOUPPER ${PARA_CONFIG} UPPER_PARA_CONFIG)
                SET(CMAKE_${UPPER_PARA_CONFIG}_POSTFIX "${CMAKE_${UPPER_PARA_CONFIG}_POSTFIX}_${${PROJECT_NAME}_VERSION}")
            endforeach()
        endif()
    endif()
endif()

add_library(${PROJECT_NAME} ${CHINESE_CHESS_SOURCES_FILES} ${CHINESE_CHESS_HEADER_FILES} ${CHINESE_CHESS_RCC_FILES})

GENERATE_EXPORT_HEADER(${PROJECT_NAME})
string(TOLOWER ${PROJECT_NAME} LOWER_PROJECT_NAME)
LIST(APPEND CHINESE_CHESS_HEADER_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h)
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h
    DESTINATION ${CMAKE_BINARY_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    PUBLIC_HEADER "${CHINESE_CHESS_HEADER_FILES}" # Install head files
    VERSION ${${PROJECT_NAME}_VERSION})
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
    )
target_compile_options(${PROJECT_NAME} PRIVATE
    "$<$<C_COMPILER_ID:MSVC>:/utf-8>"
    "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
    $<$<CXX_COMPILER_ID:GNU,Clang>:$<IF:$<CONFIG:Debug>, -g -ggdb, -O3>>
    )
if(MSVC)
    if(NOT DEFINED CMAKE_WINDOWS_VERSION)
        set(CMAKE_WINDOWS_VERSION "WIN7")
    endif()
    # WINDOWS 版本号详见： SDKDDKVer.h
    if(CMAKE_WINDOWS_VERSION STREQUAL "WINXP")
        list(APPEND CHINESE_CHESS_DEFINITIONS 
            WINVER=0x0501 _WIN32_WINNT=0x0501)
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS
            "/SUBSYSTEM:WINDOWS\",5.01\" /ENTRY:mainCRTStartup")
    elseif(CMAKE_WINDOWS_VERSION STREQUAL "WIN7")
        list(APPEND CHINESE_CHESS_DEFINITIONS
            WINVER=0x0601 _WIN32_WINNT=0x0601)
    elseif(CMAKE_WINDOWS_VERSION STREQUAL "WIN8")
        list(APPEND CHINESE_CHESS_DEFINITIONS
            WINVER=0x0602 _WIN32_WINNT=0x0602)
    elseif(CMAKE_WINDOWS_VERSION STREQUAL "WIN10")
        list(APPEND CHINESE_CHESS_DEFINITIONS
            WINVER=0x0A00 _WIN32_WINNT=0x0A00)
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE Ws2_32)
elseif(MINGW)
    target_link_libraries(${PROJECT_NAME} PRIVATE wsock32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MINGW)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:_DEBUG DEBUG>
    )
target_compile_definitions(${PROJECT_NAME} PUBLIC ${CHINESE_CHESS_DEFINITIONS})

# 安装
SET(INSTALL_LIBRARY "${CMAKE_INSTALL_LIBDIR}")
if(WIN32)
	SET(INSTALL_LIBRARY "${CMAKE_INSTALL_BINDIR}")
endif()
INSTALL(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Config
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
# Install cmake configure files
install(EXPORT ${PROJECT_NAME}Config
    NAMESPACE ChineseChessControl::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ChineseChessControl"
    )
# Install cmake configure version file
write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${${PROJECT_NAME}_VERSION}
    COMPATIBILITY AnyNewerVersion)
install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ChineseChessControl"
        COMPONENT Development)

# Install pkg-config file
#if(UNIX OR MINGW)
    foreach(d ${CHINESE_CHESS_DEFINITIONS})
        SET(CHINESE_CHESS_DEFINITIONS_PC "${CHINESE_CHESS_DEFINITIONS_PC} -D${d}")
    endforeach()
    
    # Install pc files
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/${PROJECT_NAME}.pc.in
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc @ONLY)
    install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
        COMPONENT Development)
#endif()

# 安装图标
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Res/Picture/Chess.ico
	DESTINATION .
	    COMPONENT Runtime)
