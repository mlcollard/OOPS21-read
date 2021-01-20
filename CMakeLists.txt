# @file CMakeLists.txt
# 
# CMake files for read experiments

cmake_minimum_required(VERSION 3.10)

# project info
project(Read)

# Force release build since used for timing
set(CMAKE_BUILD_TYPE Release)

# C++17
set(CMAKE_CXX_STANDARD 17)

# Turn on warnings
if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # standard warnings
    add_compile_options(-Wall)
endif()

# Assume each .cpp file is a separate application
file(GLOB APPLICATIONS "*.cpp")

# Generate executable for each .cpp file
foreach(APP ${APPLICATIONS})

    # Use basename (no path, no extension) of .cpp file for application name
    get_filename_component(APPBASENAME "${APP}" NAME_WLE)

    # Application is based on .cpp file only
    add_executable(${APPBASENAME} ${APPBASENAME}.cpp)

endforeach()

# Extract the large example data file
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_SOURCE_DIR}/large.dat.zip
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Setup a timerun command that times all applications, i.e., make timerun
add_custom_target(timerun DEPENDS timerun-cmd)
add_custom_command(OUTPUT timerun-cmd COMMAND date)
set_source_files_properties(timerun-cmd PROPERTIES SYMBOLIC "true")

# Add each application to the timerun command
foreach(APP ${APPLICATIONS})
    get_filename_component(APPBASENAME "${APP}" NAME_WLE)
    add_custom_command(OUTPUT timerun-cmd APPEND
        # applications called with file both on stdin and command line
        COMMAND echo ${APPBASENAME}
        COMMAND time ./${APPBASENAME} large.dat < large.dat
    )
endforeach()

# Setup a timerun command for each application, i.e., make timerun-readcin
foreach(APP ${APPLICATIONS})
    get_filename_component(APPBASENAME "${APP}" NAME_WLE)
    add_custom_target(timerun-${APPBASENAME} DEPENDS timerun-cmd-${APPBASENAME})
    add_custom_command(OUTPUT timerun-cmd-${APPBASENAME} 
            COMMAND echo ${APPBASENAME}
            # Pass data through stdin and as an argv parameter filename as both are used
            COMMAND time ./${APPBASENAME} large.dat < large.dat
        )
    set_source_files_properties(timerun-cmd-${APPBASENAME} PROPERTIES SYMBOLIC "true")
endforeach()
