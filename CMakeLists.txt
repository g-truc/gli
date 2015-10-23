cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)

project(gli)
set(GLI_VERSION "0.8.0.0")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

enable_testing()

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(".")

option(GLI_TEST_ENABLE "GLI test" OFF)
if(NOT GLI_TEST_ENABLE)
    message(STATUS "GLI is a header only library, no need to build it. Set the option GLI_TEST_ENABLE with ON to build and run the test bench")
endif()

if(MSVC)
	add_definitions(/Za)
endif()

if(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") OR (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel") AND UNIX))
	set(CMAKE_CXX_FLAGS "-std=c++11")
	add_definitions(-Wall)
endif()

################################
# Add package

macro(addExternalPackageGTC NAME DIRECTORY)
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/external/${DIRECTORY}/util)
	set(${NAME}_PACKAGE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/${DIRECTORY})

	find_package(${NAME})
	if(NOT ${NAME}_FOUND)
		message("ERROR: ${NAME} not found")
	endif(NOT ${NAME}_FOUND)
endmacro(addExternalPackageGTC)

################################
# Add GLM 

set(GLM_DIRECTORY glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLM_DIRECTORY})

################################
# Add subdirectory

add_subdirectory(gli)
add_subdirectory(test)
#add_subdirectory(doc)

set(GLI_INSTALL_CONFIGDIR "${CMAKE_INSTALL_LIBDIR}/cmake/gli")
install(DIRECTORY gli DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/gliVersion.cmake"
    VERSION ${GLI_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# build tree package config
configure_file(
    cmake/gliBuildConfig.cmake.in
    gliConfig.cmake
    @ONLY
)

# install tree package config
configure_package_config_file(
    cmake/gliConfig.cmake.in
    ${GLI_INSTALL_CONFIGDIR}/gliConfig.cmake
    INSTALL_DESTINATION ${GLI_INSTALL_CONFIGDIR}
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${GLI_INSTALL_CONFIGDIR}/gliConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/gliVersion.cmake"
    DESTINATION ${GLI_INSTALL_CONFIGDIR}
)

export(PACKAGE gli)