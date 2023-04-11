project(ChineseChessActiveX)

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

add_library(${PROJECT_NAME} ${SOURCES_FILES} ${HEADER_FILES} ${RCC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    PUBLIC_HEADER "${INSTALLHEADER_FILES}" # Install head files
    VERSION ${ChineseChessControl_VERSION})

if(ChineseChessControl_VERSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        -DChineseChessControl_VERSION="${ChineseChessControl_VERSION}")
endif()

find_package(MFC REQUIRED)
# 1. DLL分类：
# 1.1. MFC Extension Dll
#      MFC扩展动态库，动态库内部可以使用MFC类，提供的外部接口也可以使用MFC类作为参数。
#      也就是说MFC类可以在调用者与dll间相互传递。 调用者与DLL需使用相同版本MFC动态库。
#
#          _WINDLL,_AFXDLL,_AFXEXT
#
# 1.2. MFC Regual  DLL:
#     MFC标准动态库，动态库内部可以使用MFC类，但其提供的外部接口不能使用MFC类，也就是说MFC类不可再调用者与dll间相互传递。
#
#         _WINDLL,_AFXDLL,_USRDLL
#
# 1.3. Win32 DLL
#
#      Win32动态库，没有任何与MFC相关的dll。
#
#         _USRDLL
#
# 2. 宏
#
#    _WINDLL 表示要做一个用到MFC的DLL
#　　_USRDLL 表示做一个非扩展MFC DLL（相对MFC扩展DLL而言）
#　　_AFXEXT 表示要做一个MFC扩展DLL
#
#    这3个宏搭配可定义以上3种DLL
#
#    _AFXDLL 表示MFC以动态链接库形式提供，Using MFC in a Shared DLL；
#
#                        否则代表MFC以静态方式连接，Using MFC in a static Library；
#参考：https://blog.csdn.net/nsaygl/article/details/39252485
set(CMAKE_MFC_FLAG 2) # 1：用 MFC 静态库 2： 用 MFC DLL  同时需要定义宏 "_AFXDLL"
if(CMAKE_MFC_FLAG EQUAL 2)
    target_compile_definitions(${PROJECT_NAME} PRIVATE "_AFXDLL")
endif()
target_compile_definitions(${PROJECT_NAME} PRIVATE "_AFXEXT" "_WINDLL"
    "_UNICODE" "UNICODE"
    $<$<CONFIG:Debug>:_DEBUG DEBUG>
    )

if(MSVC)
    # 把后缀名改为 ocx
	set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .ocx)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE ${LIBS_DEFINES})
target_link_libraries(${PROJECT_NAME} PRIVATE ChineseChessView ${LIBS})

target_compile_options(${PROJECT_NAME} PRIVATE
    "$<$<C_COMPILER_ID:MSVC>:/utf-8>"
    "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
    )

# 编译完成后向系统注册中国象棋控件
option(REGISTER_ACTIVEX_CONTROL "Registering ActiveX Control" OFF)
if(REGISTER_ACTIVEX_CONTROL)
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND regsvr32.exe /s /c "$<TARGET_FILE:${PROJECT_NAME}>"
		COMMENT "Registering ActiveX Control ......"
		WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
	)
endif()

# 安装中国象棋控件
INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT MFCRuntime
    )
