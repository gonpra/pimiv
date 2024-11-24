cmake_minimum_required(VERSION 3.20)
project(PIM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER gcc)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(GLIB2 REQUIRED IMPORTED_TARGET glib-2.0)
pkg_check_modules(Xlsxwriter REQUIRED IMPORTED_TARGET xlsxwriter)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_definitions(${GTK4_CFLAGS_OTHER})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -export-dynamic")

add_executable(${PROJECT_NAME} src/main.c
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
        src/components/table-company.c
        src/components/table-company.h
        src/usecase.c
        src/include/usecase.h
        src/components/table-company-array.h
        src/usecase.c
)

set(UI_FILES
    src/layout/home.ui
    src/layout/login-user.ui
    src/layout/register-company.ui
    src/layout/register-user.ui
    src/layout/report.ui
)

set(TABLE_FILES
        ${CMAKE_BINARY_DIR}/db/reports.txt
        ${CMAKE_BINARY_DIR}/db/companies.txt
        ${CMAKE_BINARY_DIR}/db/users.txt
)

configure_file(src/style.css ${CMAKE_BINARY_DIR})
set(TXT)

foreach(UI_FILE ${UI_FILES})
    get_filename_component(UI_FILE_NAME ${UI_FILE} NAME)
    configure_file(${UI_FILE} ${CMAKE_BINARY_DIR}/layout/${UI_FILE_NAME})
endforeach ()

foreach (TABLE_FILE ${TABLE_FILES})
    if (NOT EXISTS "${TABLE_FILE}")
        file(WRITE ${TABLE_FILE} "")
    endif ()
endforeach ()

target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::Xlsxwriter PkgConfig::GLIB2 ${GTK4_LIBRARIES} -lcrypto)