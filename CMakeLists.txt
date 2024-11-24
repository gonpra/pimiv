cmake_minimum_required(VERSION 3.20)
project(PIM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER gcc)

add_compile_options(
        -Wno-error=incompatible-pointer-types
        -Wno-error=int-conversion
        -Wno-error=implicit-function-declaration
)

if(WIN32)
	message(STATUS "Configurando para Windows")
	set(LIBRARY_EXT ".dll")
	set(CAIRO_LIB "libcairo.dll.a")
	set(CRYPTO_LIB "libcrypto.dll.a")
	set(GIO_LIB "libgio-2.0.dll.a")
	set(GLIB_LIB "libglib-2.0.dll.a")
	set(GOBJECT_LIB "libgobject-2.0.dll.a")
	set(GTK_LIB "libgtk-4.dll.a")
	set(XLSXWRITER_LIB "libxlsxwriter.dll.a")
	set(LIBRARY_PATH "lib/win")
endif()

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


find_package(PkgConfig REQUIRED)
find_library(CAIRO_LIBRARY NAMES ${CAIRO_LIB} PATHS ${LIBRARY_PATH} REQUIRED)
find_library(CRYPTO_LIBRARY NAMES ${CRYPTO_LIB} PATHS ${LIBRARY_PATH} REQUIRED)
find_library(GIO_LIBRARY NAMES ${GIO_LIB} PATHS ${LIBRARY_PATH} REQUIRED)
find_library(GLIB_LIBRARY NAMES ${GLIB_LIB} PATHS ${LIBRARY_PATH} REQUIRED)
find_library(GOBJECT_LIBRARY NAMES ${GOBJECT_LIB} PATHS ${LIBRARY_PATH} REQUIRED)
find_library(GTK_LIBRARY NAMES ${GTK_LIB} PATHS ${LIBRARY_PATH} REQUIRED)
find_library(XLSXWRITER_LIBRARY NAMES ${XLSXWRITER_LIB} PATHS ${LIBRARY_PATH} REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CAIRO_LIBRARY} ${CRYPTO_LIBRARY} ${GIO_LIBRARY} ${GLIB_LIBRARY} ${GOBJECT_LIBRARY} ${GTK_LIBRARY} ${XLSXWRITER_LIBRARY})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CAIRO_LIBRARY}
		${CRYPTO_LIBRARY}
		${GIO_LIBRARY}
		${GLIB_LIBRARY}
		${GOBJECT_LIBRARY}
		${GTK_LIBRARY}
		${XLSXWRITER_LIBRARY}
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_definitions(${GTK4_CFLAGS_OTHER})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -export-dynamic")

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