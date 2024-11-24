cmake_minimum_required(VERSION 3.20)
project(PIM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER gcc)

add_compile_options(
        -Wno-error=incompatible-pointer-types
        -Wno-error=int-conversion
        -Wno-error=implicit-function-declaration
)

set(LIBRARY_DIR "third_party/lib")
set(BIN_DIR "third_party/bin")
set(INCLUDE_DIR "third_party/include")
if(WIN32)
	message(STATUS "Configurando para Windows")

	file(GLOB PIM_LIBS_A
		"${LIBRARY_DIR}/*.dll.a"
	)

	file(GLOB PIM_LIBS 
		"${BIN_DIR}/*.dll"
	)
elseif(UNIX)
	message(STATUS "Configurando para Linux")

	file(GLOB ALL_LIBS_A
			"${LIBRARY_DIR}/*.a"
	)

	file(GLOB PIM_LIBS
			"${BIN_DIR}/*.so*"
	)

	set(PIM_LIBS_A)
	foreach (LIB_A ${ALL_LIBS_A})
		if(NOT LIB_A MATCHES ".*\\.dll\\.a$")
			list(APPEND PIM_LIBS_A ${LIB_A})
		endif ()
	endforeach ()
endif()

link_directories()
set(INCLUDE_LOCAL_PATH "third_party/include")

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

if(PIM_LIBS_A)
	message(STATUS "Encontrado as bibliotecas estáticas:")
	foreach(LIBRARY_PATH ${PIM_LIBS_A})
		message(STATUS " - ${LIBRARY_PATH}")
	endforeach()
	
	target_link_libraries(PIM PRIVATE ${PIM_LIBS_A})
endif()

if(PIM_LIBS)
	message(STATUS "Encontrado as bibliotecas dinâmicas:")
	foreach(LIB ${PIM_LIBS})
		execute_process(
			COMMAND ${CMAKE_COMMAND} -E copy ${LIB} ${CMAKE_BINARY_DIR}/
		)
		message(STATUS " - ${LIB}")
	endforeach()
endif()

file(GLOB INCLUDE_DIRS RELATIVE ${CMAKE_SOURCE_DIR} "${CMAKE_SOURCE_DIR}/third_party/include/*")
if(INCLUDE_DIRS)
	message(STATUS "Encontrado os cabeçalhos:")
	foreach(DIR ${INCLUDE_DIRS})
		message(STATUS "- ${DIR}")
		include_directories(${CMAKE_SOURCE_DIR}/${DIR})
	endforeach()
endif()

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