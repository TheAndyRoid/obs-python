project(obs-python-swig)


find_package(SWIG 2 REQUIRED)
include(${SWIG_USE_FILE})


set(Python_ADDITIONAL_VERSIONS 3.4)
find_package(PythonLibs 3.4 REQUIRED)

include_directories(${PYTHON_INCLUDE_DIR})
include_directories("../../../")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


add_definitions( -DSWIG_TYPE_TABLE=libobs )
SET_SOURCE_FILES_PROPERTIES(libobs.i PROPERTIES SWIG_FLAGS "-modern")
SET_SOURCE_FILES_PROPERTIES(libobs.i PROPERTIES SWIG_FLAGS "-builtin")
SET_SOURCE_FILES_PROPERTIES(libobs.i PROPERTIES SWIG_FLAGS "-modernargs")
SET_SOURCE_FILES_PROPERTIES(libobs.i PROPERTIES SWIG_FLAGS "-includeall")
SET_SOURCE_FILES_PROPERTIES(libobs.i PROPERTIES SWIG_FLAGS "-importall")
SET_SOURCE_FILES_PROPERTIES(libobs.i PROPERTIES SWIG_FLAGS "-py3")
SET_SOURCE_FILES_PROPERTIES(libobs.i PROPERTIES SWIG_FLAGS "-DSWIG_TYPE_TABLE=obspython")


SWIG_ADD_MODULE(obspython python obspython.i)
SWIG_LINK_LIBRARIES(obspython obs-python libobs ${PYTHON_LIBRARIES} )


