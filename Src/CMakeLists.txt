set(SOURCES_FILES
    ${SOURCES_FILES}
    ChineseChessCtr.cpp
    Common.cpp
	GoRule.cpp
	Stdafx.cpp
	XQCtl.cpp
	XQPpg.cpp
    )

set(INSTALLHEADER_FILES
    )

set(HEADER_FILES
    ${HEADER_FILES}
    ${INSTALLHEADER_FILES}
	ChineseChessCtr.h
	Common.h
	EnumAndStructAndConst.h
	GoRule.h
	Stdafx.h
	XQCtl.h
	XQPpg.h
    )

SET(RCC_FILES
    ${TRANSLATIONS_RESOURCE_FILES}
	ChineseChessCtr.rc
	)

find_package(IDL)
if(IDL_FOUND)
	add_idl(ChineseChessCtrIDL ChineseChessCtr.odl)
	set(LIBS ${LIBS} ChineseChessCtrIDL)
endif()

if(MSVC)
	set(LIBS_DEFINES ${LIBS_DEFINES} _AFXDLL)
endif()

add_library(${PROJECT_NAME} ${SOURCES_FILES} ${HEADER_FILES} ${RCC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    PUBLIC_HEADER "${INSTALLHEADER_FILES}" # Install head files
    VERSION ${BUILD_VERSION})

if(MSVC)
	set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .ocx)
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC ${LIBS_DEFINES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${QT_LIBRARIES} ${LIBS})
target_include_directories(${PROJECT_NAME}
    PRIVATE ${RabbitCommon_DIR}/Src
    ${CMAKE_BINARY_DIR}
    ${INCLUDE_DIRS})

if(BUILD_VERSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DBUILD_VERSION="${BUILD_VERSION}")
    #set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${BUILD_VERSION})
endif()

# 注册中国象棋控件
#add_custom_command(
#	TARGET ${PROJECT_NAME} POST_BUILD
#	COMMAND regsvr32.exe /s /c "$<TARGET_FILE:${PROJECT_NAME}>"
#	COMMENT "Registering ActiveX Control ......"
#)
