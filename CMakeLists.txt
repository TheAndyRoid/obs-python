project(obs-python)

set(Python_ADDITIONAL_VERSIONS 3.4)
find_package(PythonLibs 3.4 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

set(obs-python_SOURCES
	obs-python-module.c
	obs-python-source.c)

add_library(obs-python MODULE
	${obs-python_SOURCES})
target_link_libraries(obs-python
	libobs
	${PYTHON_LIBRARIES})

install_obs_plugin_with_data(obs-python data)
