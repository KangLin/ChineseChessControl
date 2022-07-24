project(ChineseChess)

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
    VERSION ${ChineseChessControl_VERSION})
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
    )
if(ChineseChessControl_VERSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        -DChineseChessControl_VERSION="${ChineseChessControl_VERSION}")
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
    VERSION ${ChineseChessControl_VERSION}
    COMPATIBILITY AnyNewerVersion)
install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ChineseChessControl"
        COMPONENT Development)

# 安装图标
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Res/Picture/Chess.ico
	DESTINATION .
	    COMPONENT Runtime)
