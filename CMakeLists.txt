cmake_minimum_required(VERSION 3.20)
project(PIM)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_definitions(${GTK4_CFLAGS_OTHER})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -export-dynamic")

add_executable(PIM src/main.c
        src/ui.c
        src/callbacks.c
        src/structs.c
        src/util.c
        src/db.c
        src/include/ui.h
        src/include/callbacks.h
        src/include/structs.h
        src/include/util.h
        src/include/db.h
)

target_link_libraries(PIM ${GTK4_LIBRARIES} -lcrypt)