cmake_minimum_required(VERSION 2.8)
project(obs-python-swig)


find_package(SWIG 2 REQUIRED)
find_package(LibObs)
include(${SWIG_USE_FILE})
include(../external/ObsPluginHelpers.cmake)

set(Python_ADDITIONAL_VERSIONS 3.4)
find_package(PythonLibs 3.4 REQUIRED)

include_directories(${PYTHON_INCLUDE_DIR})
include_directories(${LIBOBS_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


#add_definitions( -DSWIG_TYPE_TABLE=libobs )
SET_SOURCE_FILES_PROPERTIES(obspython.i PROPERTIES SWIG_FLAGS "-modern")
SET_SOURCE_FILES_PROPERTIES(obspython.i PROPERTIES SWIG_FLAGS "-builtin")
SET_SOURCE_FILES_PROPERTIES(obspython.i PROPERTIES SWIG_FLAGS "-modernargs")
SET_SOURCE_FILES_PROPERTIES(obspython.i PROPERTIES SWIG_FLAGS "-includeall")
SET_SOURCE_FILES_PROPERTIES(obspython.i PROPERTIES SWIG_FLAGS "-importall")
SET_SOURCE_FILES_PROPERTIES(obspython.i PROPERTIES SWIG_FLAGS "-py3")



SWIG_ADD_MODULE(obspython python obspython.i)
SWIG_LINK_LIBRARIES(obspython obs-python libobs ${PYTHON_LIBRARIES} )

#if(UNIX)
#  if(APPLE)
#    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/_obspython.dylib" DESTINATION "data/obs-plugins/obs-python/scripts")
#  else(APPLE)
#    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/_obspython.so" DESTINATION "data/obs-plugins/obs-python/scripts")
#  endif(APPLE)
#endif(UNIX)
#
#if(WIN32)
#  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/_obspython.pyd" DESTINATION "data/obs-plugins/obs-python/scripts")
#endif(WIN32)



function(install_plugin_bin_swig target additional_target)
	if(APPLE)
		set(_bit_suffix "")
	elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(_bit_suffix "64bit/")
	else()
		set(_bit_suffix "32bit/")
	endif()

	set_target_properties(${additional_target} PROPERTIES
		PREFIX "")

	add_custom_command(TARGET ${additional_target} POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy
			"${CMAKE_CURRENT_BINARY_DIR}/obspython.py"
			"${EXTERNAL_PLUGIN_OUTPUT_DIR}/$<CONFIGURATION>/data/obs-plugins/${target}/${_bit_suffix}/obspython.py"
		VERBATIM)
	add_custom_command(TARGET ${additional_target} POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy
			"$<TARGET_FILE:${additional_target}>"
			"${EXTERNAL_PLUGIN_OUTPUT_DIR}/$<CONFIGURATION>/data/obs-plugins/${target}/${_bit_suffix}/$<TARGET_FILE_NAME:${additional_target}>"
		VERBATIM)
endfunction()




install_plugin_bin_swig (obs-python _obspython)
#install(FILES "${CMAKE_CURRENT_BINARY_DIR}/obspython.py" DESTINATION "data/obs-plugins/obs-python/scripts")
#install_external_plugin(obs-python obs-python-swig)
