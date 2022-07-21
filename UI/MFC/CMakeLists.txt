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
    VERSION ${ChineseChessControl_VERSION})

if(ChineseChessControl_VERSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DChineseChessControl_VERSION="${ChineseChessControl_VERSION}")
endif()

set(CMAKE_MFC_FLAG 2) # 1：用 MFC 静态库 2： 用 MFC DLL  "_AFXDLL"
target_compile_definitions(${PROJECT_NAME} PRIVATE "_AFXDLL" "_AFXEXT"
    "_UNICODE" "UNICODE"
    $<$<CONFIG:Debug>:_DEBUG DEBUG>
    )
target_compile_definitions(${PROJECT_NAME} PUBLIC "CHINESE_CHESS_USE_PNG")
target_link_libraries(${PROJECT_NAME} PUBLIC ChineseChess)
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

# 安装中国象棋控件
INSTALL(TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}Targets
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	    COMPONENT Runtime
    LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Runtime
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT Development
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ChineseChessControl
        COMPONENT Development
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
export(TARGETS ${PROJECT_NAME}
    NAMESPACE ChineseChessControl::
    APPEND FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake
)
# Install cmake configure files
install(EXPORT ${PROJECT_NAME}Targets
    NAMESPACE ChineseChessControl::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ChineseChessControl"
    )
# 因为编译树中已有 export(${PROJECT_NAME}Config.cmake)
configure_package_config_file(
      ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
      ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake.in
      INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ChineseChessControl"
      )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake.in
      DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ChineseChessControl
          COMPONENT Development
      RENAME ${PROJECT_NAME}Config.cmake)

write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${ChineseChessControl_VERSION}
    COMPATIBILITY AnyNewerVersion)
install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ChineseChessControl"
        COMPONENT Development)
