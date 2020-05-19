project(ChineseChessView)

message(STATUS "== Build chinese chess mfc view")

set(SOURCES_FILES
    ${SOURCES_FILES}
    ChineseChessView.cpp
	dllmain.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../ChineseChess.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../ChessGame.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Piece.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../GoRule.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../Common.cpp
    )

set(INSTALLHEADER_FILES
	ChineseChessView.h
	${CMAKE_CURRENT_SOURCE_DIR}/../ChineseChess.h
	${CMAKE_CURRENT_SOURCE_DIR}/../ChessGame.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Piece.h
	${CMAKE_CURRENT_SOURCE_DIR}/../GoRule.h
	${CMAKE_CURRENT_SOURCE_DIR}/../Common.h
    )

set(HEADER_FILES
    ${HEADER_FILES}
    ${INSTALLHEADER_FILES}
	Resource.h
    )

SET(RCC_FILES
    ${TRANSLATIONS_RESOURCE_FILES}
	ChineseChessView.rc
	)

if(MSVC)
	set(CMAKE_MFC_FLAG 2) # 1：用 MFC 静态库 2： 用 MFC DLL 
    set(LIBS_DEFINES ${LIBS_DEFINES} "_AFXDLL" "_UNICODE" "UNICODE")
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

target_compile_definitions(${PROJECT_NAME} PUBLIC ${LIBS_DEFINES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${QT_LIBRARIES} ${LIBS})
target_include_directories(${PROJECT_NAME}
    PRIVATE ${RabbitCommon_DIR}/Src
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..)

GENERATE_EXPORT_HEADER(${PROJECT_NAME})
string(TOLOWER ${PROJECT_NAME} LOWER_PROJECT_NAME)
set(INSTALLHEADER_FILES ${INSTALLHEADER_FILES} 
    ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h)
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h
    DESTINATION ${CMAKE_BINARY_DIR})

# 安装中国象棋控件
INSTALL(TARGETS ${PROJECT_NAME}
            EXPORT ${PROJECT_NAME}Config
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
                COMPONENT Runtime
            LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
                COMPONENT Runtime
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ChineseChessView
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            )

export(TARGETS ${PROJECT_NAME}
       APPEND FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake
)
# Install cmake configure files
install(EXPORT ${PROJECT_NAME}Config
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ChineseChessControl"
        )
write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${BUILD_VERSION}
    COMPATIBILITY AnyNewerVersion)
install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake" DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ChineseChessControl")

# 安装图标
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../Res/Picture/Chess.ICO
	DESTINATION .
	    COMPONENT Runtime)
