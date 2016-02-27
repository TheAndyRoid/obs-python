cmake_minimum_required(VERSION 2.8)
project(obs-python)



set(Python_ADDITIONAL_VERSIONS 3.4)
find_package(PythonLibs 3.4 REQUIRED)

find_package(LibObs REQUIRED)
find_package(SWIG 2 REQUIRED)
include(${SWIG_USE_FILE})
include(external/ObsPluginHelpers.cmake)


include_directories(${PYTHON_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})



set(obs-python_SOURCES
    obs-python-module.c
    py-source.h
    py-obs.h)


add_library(obs-python SHARED
           ${obs-python_SOURCES})


target_link_libraries(obs-python
                      libobs
		      ${PYTHON_LIBRARIES})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

add_definitions( -DSWIG_TYPE_TABLE=obspython )
add_subdirectory(swig)

set(SWIG_RUNTIME swig/swigpyrun.h)
add_custom_command(OUTPUT ${SWIG_RUNTIME} 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} 
    COMMAND ${SWIG_EXECUTABLE} -python -external-runtime ${SWIG_RUNTIME} 
)
set_source_files_properties( ${SWIG_RUNTIME} PROPERTIES GENERATED TRUE ) 
add_custom_target(swig-runtime 
  DEPENDS ${SWIG_RUNTIME}
  )
     
add_dependencies(obs-python swig-runtime)



function(install_plugin_with_data target data_loc)
	if(APPLE)
		set(_bit_suffix "")
	elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(_bit_suffix "64bit/")
	else()
		set(_bit_suffix "32bit/")
	endif()

	set_target_properties(${target} PROPERTIES
		PREFIX "")

	add_custom_command(TARGET ${target} POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy
			"$<TARGET_FILE_NAME:${target}>"
			"${EXTERNAL_PLUGIN_OUTPUT_DIR}/$<CONFIGURATION>/obs-plugins/${_bit_suffix}/$<TARGET_FILE_NAME:${target}>"
		VERBATIM)

	add_custom_command(TARGET ${target} POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy_directory
			"${CMAKE_CURRENT_SOURCE_DIR}/${data_loc}"
			"${EXTERNAL_PLUGIN_OUTPUT_DIR}/$<CONFIGURATION>/data/obs-plugins/${target}/"
		VERBATIM)
endfunction()


install_plugin_with_data(obs-python data)


