project(ChineseChess)

message(STATUS "== Build chinese chess dll")

set(SOURCES_FILES
    ChineseChess.cpp
    ChessGame.cpp
    Piece.cpp
    Common.cpp
    GoRule.cpp
    )

set(HEADER_FILES
    ChineseChess.h
    ChessGame.h
    Piece.h
    Common.h
    GoRule.h
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
    VERSION ${BUILD_VERSION})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR})
if(BUILD_VERSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DBUILD_VERSION="${BUILD_VERSION}")
    #set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${BUILD_VERSION})
endif()
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    target_link_libraries(${PROJECT_NAME} PUBLIC Ws2_32)
elseif(MINGW)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DWIN32 -DMINGW)
    target_link_libraries(${PROJECT_NAME} PUBLIC wsock32)
endif()

# 安装
if(WIN32)
    INSTALL(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Config
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Runtime
        LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Runtime
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ChineseChess
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )
else()
    INSTALL(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Config
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Runtime
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT Runtime
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ChineseChess
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )
endif()

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

# 安装图标
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Res/Picture/Chess.ico
	DESTINATION .
	    COMPONENT Runtime)
