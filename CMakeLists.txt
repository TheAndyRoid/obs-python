project(obs-python)




set(Python_ADDITIONAL_VERSIONS 3.4)
find_package(PythonLibs 3.4 REQUIRED)

find_package(SWIG 2 REQUIRED)
include(${SWIG_USE_FILE})


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
install_obs_plugin_with_data(obs-python data)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/swig/_obspython.so" DESTINATION "data/obs-plugins/${PROJECT_NAME}/scripts")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/swig/obspython.py" DESTINATION "data/obs-plugins/${PROJECT_NAME}/scripts")

