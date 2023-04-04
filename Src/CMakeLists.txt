project(ChineseChess)

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
            OUTPUT_VARIABLE GIT_OUT_VERSION  OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        EXECUTE_PROCESS(
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMAND ${GIT} rev-parse --short HEAD
            OUTPUT_VARIABLE GIT_OUT_REVISION OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        if(NOT GIT_OUT_VERSION)
            set(GIT_OUT_VERSION ${GIT_OUT_REVISION})
        endif()
        SET(${PROJECT_NAME}_VERSION ${GIT_OUT_VERSION})
    ENDIF()
ENDIF()

if(NOT ${PROJECT_NAME}_VERSION)
    SET(${PROJECT_NAME}_VERSION "v2.0.5")
endif()
message("${PROJECT_NAME}_VERSION:${${PROJECT_NAME}_VERSION}")

set(SOURCES_FILES
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

set(HEADER_FILES
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

SET(RCC_FILES
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

add_library(${PROJECT_NAME} ${SOURCES_FILES} ${HEADER_FILES} ${RCC_FILES})

GENERATE_EXPORT_HEADER(${PROJECT_NAME})
string(TOLOWER ${PROJECT_NAME} LOWER_PROJECT_NAME)
LIST(APPEND HEADER_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h)
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h
    DESTINATION ${CMAKE_BINARY_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    PUBLIC_HEADER "${HEADER_FILES}" # Install head files
    VERSION ${${PROJECT_NAME}_VERSION})
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
    )
if(${PROJECT_NAME}_VERSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        -D${PROJECT_NAME}_VERSION="${${PROJECT_NAME}_VERSION}")
endif()
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        "$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    target_compile_options(${PROJECT_NAME} PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    target_link_libraries(${PROJECT_NAME} PRIVATE Ws2_32)
elseif(MINGW)
    target_link_libraries(${PROJECT_NAME} PRIVATE wsock32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MINGW)
endif()

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

# 安装图标
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Res/Picture/Chess.ico
	DESTINATION .
	    COMPONENT Runtime)
