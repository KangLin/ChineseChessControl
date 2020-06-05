project(ChineseChessView)

message(STATUS "== Build chinese chess mfc view dll")

set(SOURCES_FILES
    ChineseChessView.cpp
	dllmain.cpp
    )

set(INSTALLHEADER_FILES
	ChineseChessView.h
    )

set(HEADER_FILES
	${INSTALLHEADER_FILES}
	Resource.h
    )

SET(RCC_FILES
	ChineseChessView.rc
	)

add_library(${PROJECT_NAME} ${SOURCES_FILES} ${HEADER_FILES} ${RCC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    PUBLIC_HEADER "${INSTALLHEADER_FILES}" # Install head files
    VERSION ${BUILD_VERSION})

if(BUILD_VERSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DBUILD_VERSION="${BUILD_VERSION}")
endif()

set(CMAKE_MFC_FLAG 2) # 1：用 MFC 静态库 2： 用 MFC DLL  "_AFXDLL"
target_compile_definitions(${PROJECT_NAME} PRIVATE "_AFXEXT" "_UNICODE" "UNICODE")# USE_PNG)

target_link_libraries(${PROJECT_NAME} PUBLIC ChineseChess)
target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..)

# 安装中国象棋控件
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
