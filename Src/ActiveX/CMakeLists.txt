project(ChineseChessActiveX)

message(STATUS "== Build chinese chess ActiveX")

set(SOURCES_FILES
    ChineseChessActiveX.cpp
    ChineseChessActiveXPropPage.cpp
    ChineseChessActiveXCtrl.cpp
    stdafx.cpp
    )

set(HEADER_FILES
	ChineseChessActiveX.h
	ChineseChessActiveXPropPage.h
	targetver.h
	ChineseChessActiveXCtrl.h
	Resource.h
	stdafx.h
    )

SET(RCC_FILES
	ChineseChessActiveX.rc
	)

# 编译 IDL 文件
find_package(IDL)
if(IDL_FOUND)
	add_idl(ChineseChessActiveXIDL ChineseChessActiveX.idl)
	SET(LIBS ChineseChessActiveXIDL)
endif()

if(MSVC)
	set(CMAKE_MFC_FLAG 2) # 1：用 MFC 静态库 2： 用 MFC DLL 
	SET(LIBS_DEFINES "_AFXDLL" "_UNICODE" "UNICODE")
	LIST(APPEND RCC_FILES ChineseChessActiveX.def)
endif()

add_library(${PROJECT_NAME} ${SOURCES_FILES} ${HEADER_FILES} ${RCC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    PUBLIC_HEADER "${INSTALLHEADER_FILES}" # Install head files
    VERSION ${BUILD_VERSION})

if(BUILD_VERSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DBUILD_VERSION="${BUILD_VERSION}")
    #set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${BUILD_VERSION})
endif()

if(MSVC)
    # 把后缀名改为 ocx
	set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .ocx)
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC ${LIBS_DEFINES})
target_link_libraries(${PROJECT_NAME} PUBLIC ChineseChessView ${LIBS})
target_include_directories(${PROJECT_NAME}
    PRIVATE ${RabbitCommon_DIR}/Src
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../)

# 编译完成后向系统注册中国象棋控件
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND regsvr32.exe /s /c "$<TARGET_FILE:${PROJECT_NAME}>"
	COMMENT "Registering ActiveX Control ......"
	WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)

# 安装中国象棋控件
INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Runtime
    #LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
    #    COMPONENT Runtime
    #ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )
