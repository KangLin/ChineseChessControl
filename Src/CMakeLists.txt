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
	ChineseChessCtr.odl)

add_library(${PROJECT_NAME} ${SOURCES_FILES} ${HEADER_FILES} ${RCC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    PUBLIC_HEADER "${INSTALLHEADER_FILES}" # Install head files
    VERSION ${BUILD_VERSION})

# Set flags
if(ANDROID)
    if(ANDROID_ARM_NEON)
        target_compile_options(${PROJECT_NAME} PUBLIC -mfpu=neon-vfpv4)
    endif()
    
    target_compile_options(${PROJECT_NAME} PUBLIC 
        -frtti -fexceptions -funsafe-math-optimizations -ftree-vectorize -ffast-math)
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC RABBITCOMMON ${LIBS_DEFINES})
target_link_libraries(${PROJECT_NAME} PUBLIC RabbitCommon ${QT_LIBRARIES} ${LIBS})
target_include_directories(${PROJECT_NAME}
    PRIVATE ${RabbitCommon_DIR}/Src
    ${CMAKE_BINARY_DIR}
    ${INCLUDE_DIRS})

if(BUILD_VERSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DBUILD_VERSION="${BUILD_VERSION}")
    #set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${BUILD_VERSION})
endif()

GENERATE_EXPORT_HEADER(${PROJECT_NAME})
string(TOLOWER ${PROJECT_NAME} LOWER_PROJECT_NAME)
set(INSTALLHEADER_FILES ${INSTALLHEADER_FILES} 
    ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h)
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h
    DESTINATION ${CMAKE_BINARY_DIR})

if(ANDROID)
    # Install target
    INSTALL(TARGETS ${PROJECT_NAME}
            EXPORT ${PROJECT_NAME}Config
            RUNTIME DESTINATION "libs/${ANDROID_ABI}"
                COMPONENT Runtime
            LIBRARY DESTINATION "libs/${ANDROID_ABI}"
                COMPONENT Runtime
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/FaceReconginzer
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            )
else()
    # Install target
    if(WIN32)
        INSTALL(TARGETS ${PROJECT_NAME}
            EXPORT ${PROJECT_NAME}Config
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
                COMPONENT Runtime
            LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
                COMPONENT Runtime
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/FaceReconginzer
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
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/FaceReconginzer
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            )
    endif()
endif()

export(TARGETS ${PROJECT_NAME}
       APPEND FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake
)
# Install cmake configure files
install(EXPORT ${PROJECT_NAME}Config
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
        )
write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${BUILD_VERSION}
    COMPATIBILITY AnyNewerVersion)
install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake" DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake")
