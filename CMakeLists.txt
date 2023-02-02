cmake_minimum_required(VERSION 3.16)
project(curses)

option(SDL "Build the program for SDL" ON)
include_directories("${PROJECT_SOURCE_DIR}/lib/PDCurses")
message("Build with SDL=OFF for console support")

if(SDL)
    # Checks to see if git is present
    find_package(Git REQUIRED)

    # Initialize the submodule if not already done so
    if(NOT EXISTS "${PROJECT_SOURCE_DIR}/lib/PDCurses/curses.h")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive -- ${dir}
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                COMMAND_ERROR_IS_FATAL ANY)
    endif()

    # Import SDL2 library
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    find_package(SDL2_ttf REQUIRED)
    include_directories(${SDL2_TTF_INCLUDE_DIRS})


    # Import PDCurses library
    execute_process(COMMAND "${CMAKE_MAKE_PROGRAM}" WIDE=Y UTF8=Y "SFLAGS=-I${SDL2_INCLUDE_DIR}" "CFLAGS=-DPDC_FONT_PATH=${PROJECT_SOURCE_DIR}/res/Ac437_IBM_BIOS.ttf"
                WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/lib/PDCurses/sdl2"
                COMMAND_ERROR_IS_FATAL ANY)

    set(LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/lib/PDCurses/sdl2/pdcurses.a" SDL2::SDL2 SDL2_ttf::SDL2_ttf)    
else()
    if(WIN32)
        # Checks to see if git is present
        find_package(Git REQUIRED)

        # Initialize the submodule if not already done so
        if(NOT EXISTS "${PROJECT_SOURCE_DIR}/lib/PDCurses/curses.h")
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive -- ${dir}
                    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                    COMMAND_ERROR_IS_FATAL ANY)
        endif()

        # Import PDCurses library
        execute_process(COMMAND "${CMAKE_MAKE_PROGRAM}"
                WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/lib/PDCurses/wincon"
                COMMAND_ERROR_IS_FATAL ANY)

        
        set(LIBRARIES "${PROJECT_SOURCE_DIR}/lib/PDCurses/wincon/pdcurses.a")
    else()
        set(LIBRARIES ncurses)
    endif(WIN32)
endif(SDL)

file(GLOB PROJECT_HEADERS src/*.h)
file(GLOB PROJECT_SOURCES src/*.cpp)


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})