project(ChineseChessMfcApp)

set(SOURCES_FILES
    CDChineseChessControl.cpp
	CDChineseChessControlEvents.cpp
	ChineseChessApp.cpp
	ChineseChessDlg.cpp
	stdafx.cpp
    )

set(INSTALLHEADER_FILES
    )

set(HEADER_FILES
    ${INSTALLHEADER_FILES}
	CDChineseChessControl.h
	CDChineseChessControlEvents.h
	ChineseChessApp.h
	ChineseChessDlg.h
	resource.h
	stdafx.h
	targetver.h
    )

SET(RCC_FILES
    ${TRANSLATIONS_RESOURCE_FILES}
	ChineseChess.rc
	res/ChineseChess.rc2
	)

if(MSVC)
	set(CMAKE_MFC_FLAG 2) # 1：用 MFC 静态库 2： 用 MFC DLL 
    set(LIBS_DEFINES ${LIBS_DEFINES} "_AFXDLL" "_UNICODE" "UNICODE")
endif()

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
     #target_compile_options(${PROJECT_NAME} PRIVATE "/nologo")
endif()

if(BUILD_VERSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DBUILD_VERSION="${BUILD_VERSION}")
    #set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${BUILD_VERSION})
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC ${LIBS_DEFINES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${QT_LIBRARIES} ${LIBS})

# 安装中国象棋
INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Runtime
    LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Runtime
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )
