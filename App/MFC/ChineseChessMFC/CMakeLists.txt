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

set(CMAKE_MFC_FLAG 2) # 1：用 MFC 静态库 2： 用 MFC DLL 

add_executable(${PROJECT_NAME} ${SOURCES_FILES} ${HEADER_FILES} ${RCC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    PUBLIC_HEADER "${INSTALLHEADER_FILES}" # Install head files
    VERSION ${BUILD_VERSION})

if(MINGW)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows")
elseif(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS
	    "/SUBSYSTEM:WINDOWS")
endif()
if(MSVC)
	target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS,5.1")
elseif(MINGW)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _WIN32_WINNT=0x0501)
endif()

if(BUILD_VERSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
	    -DBUILD_VERSION="${BUILD_VERSION}")
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE "_UNICODE" "UNICODE")
target_link_libraries(${PROJECT_NAME} PRIVATE ChineseChessView)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/Src
	${CMAKE_SOURCE_DIR}/Src/MFC)

# 安装中国象棋
INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Runtime
    LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Runtime
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )
