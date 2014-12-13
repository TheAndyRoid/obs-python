project(obs-python)

set(Python_ADDITIONAL_VERSIONS 3.4)
find_package(PythonLibs 3.4 REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})

find_package(SWIG 2 REQUIRED)

set(obs-python_SOURCES
	obs-python-module.c
	obs-python-source.c
	py-source.h
	py-obs.h)

add_library(obs-python MODULE
	${obs-python_SOURCES})

target_link_libraries(obs-python
	libobs
	${PYTHON_LIBRARIES})



#Pre_build step to generate files.
set(PRE_BUILD_TARGET obs-python-swig)
add_custom_target(obs-python-swig
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/swig
  COMMAND swig -python -modern -py3 libobs.i
  COMMAND mv libobs.py ../data/scripts/libobs.py

)
add_dependencies(${PROJECT_NAME} ${PRE_BUILD_TARGET})

      
install_obs_plugin_with_data(obs-python data)
