cmake_minimum_required(VERSION 3.3.0)
project(OpMon)

set(EXECUTABLE_NAME OpMon)


set(OPMON_VERSION_MAJOR 0)
set(OPMON_VERSION_MINOR 13)
set(OPMON_VERSION_PATCH 0)
set(OPMON_CONTACT "jlppc <jlppcprog@ntymail.com>")
set(OPMON_DESCRIPTION_SUMMARY "An open source RPG monster fighting game")

set(OPMON_DEBIAN_DEPENDS "libsfml (>= 2.3.2+dfsg-1)")
set(OPMON_DEBIAN_CATEGORY games)

set(OPMON_VERSION "${OPMON_VERSION_MAJOR}.${OPMON_VERSION_MINOR}.${OPMON_VERSION_PATCH}")


# Make SFML_ROOT appear in cmake-gui
set(SFML_ROOT "" CACHE PATH "SFML root directory.")


# Compiler options
set(CMAKE_CXX_STANDARD 11)
if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
endif()
set(CMAKE_DEBUG_POSTFIX "Debug")


# Set the default build mode to "Release"
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
            FORCE)
endif(NOT CMAKE_BUILD_TYPE)


# build config.hpp (insert cmake variables)
configure_file(config.hpp.in config.hpp)
# Set include directory to find the generated "config.hpp" file
include_directories(${PROJECT_BINARY_DIR})



# list all .cpp files in src/
# .hpp are handled automatically.
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

if (WIN32) # set the program icon
    list(APPEND SOURCE_FILES resources.rc)
endif()



# Note: the executable must be declared before adding libraries
add_executable(${EXECUTABLE_NAME} WIN32 ${SOURCE_FILES})
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})


# Set the folder where to find cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Add SFML
find_package(SFML 2.3 COMPONENTS graphics window system audio)
if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found; You should set SFML_ROOT to the SFML path")
endif()
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
include_directories(${SFML_INCLUDE_DIR})


# Install target
if (UNIX)
    install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/OPMon.desktop DESTINATION share/applications)

    # TODO: put resource files in the correct folder
    # Note: trailing slash "bin/" is important.
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION share/OpMon)
else()
    install(TARGETS ${EXECUTABLE_NAME} DESTINATION .)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION .)
    # TODO: copy only usefull DLL
    # Note: trailing slash "bin/" is important.
    install(DIRECTORY ${SFML_ROOT}/bin/ DESTINATION .) # copy SFML DLL
endif()


# CPack packaging
set(CPACK_GENERATOR TGZ DEB) # list of packages type generated

#CPACK_PACKAGE_NAME
#CPACK_PACKAGE_VENDOR
set(CPACK_PACKAGE_VERSION_MAJOR "${OPMON_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${OPMON_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${OPMON_VERSION_PATCH}")
#set(CPACK_PACKAGE_DIRECTORY "packages")
# CPACK_PACKAGE_DESCRIPTION_FILE
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${OPMON_DESCRIPTION_SUMMARY}") # short description
# CPACK_PACKAGE_FILE_NAME
# CPACK_PACKAGE_INSTALL_DIRECTORY
# CPACK_PACKAGE_ICON
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/cmake/LICENSE.txt") # displayed by Windows installer
# CPACK_RESOURCE_FILE_README
# CPACK_RESOURCE_FILE_WELCOME
# CPACK_PACKAGE_EXECUTABLES
#set(CPACK_STRIP_FILES ${EXECUTABLE_NAME})

SET(CPACK_DEBIAN_PACKAGE_DEPENDS "${OPMON_DEBIAN_DEPENDS}")
set(CPACK_PACKAGE_CONTACT ${OPMON_CONTACT})
set(CPACK_DEBIAN_PACKAGE_SECTION ${OPMON_DEBIAN_CATEGORY})

include(CPack)
