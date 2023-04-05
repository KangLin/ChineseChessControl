project(ChineseChessMfcApp)
message(STATUS "== Build chinese chess mfc application")

set(SOURCES_FILES
	ChineseChessMFC.cpp
	ChineseChessMFCDlg.cpp
	stdafx.cpp
    )

set(HEADER_FILES
	ChineseChessMFC.h
	ChineseChessMFCDlg.h
	resource.h
	stdafx.h
	targetver.h
    )

SET(RCC_FILES
	ChineseChessMFC.rc
	res/ChineseChessMFC.rc2
	)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES_FILES} ${HEADER_FILES} ${RCC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    PUBLIC_HEADER "${INSTALLHEADER_FILES}" # Install head files
    VERSION ${ChineseChessControl_VERSION})

target_compile_definitions(${PROJECT_NAME} PRIVATE
    -DChineseChessControl_VERSION="${ChineseChessControl_VERSION}"
    )
set(CMAKE_MFC_FLAG 2) # 1：用 MFC 静态库 2： 用 MFC DLL  "_AFXDLL"
target_compile_definitions(${PROJECT_NAME} PRIVATE "_AFXDLL"
    "_UNICODE" "UNICODE"
    $<$<CONFIG:Debug>:_DEBUG DEBUG>
    )
target_link_libraries(${PROJECT_NAME} PRIVATE ChineseChessView)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/Src
	${CMAKE_SOURCE_DIR}/Src/MFC)

# 安装系统运行库
set(CMAKE_INSTALL_MFC_LIBRARIES TRUE)
if("debug" STREQUAL CHINESE_CHESS_CONTROL_BUILD_TYPE)
    set(CMAKE_INSTALL_DEBUG_LIBRARIES TRUE)
endif()
include(InstallRequiredSystemLibraries)

# 安装中国象棋
INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Application
    LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Application
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )
