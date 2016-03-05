/********************************************************************************
Copyright (C) 2014 Andrew Skinner <obs@theandyroid.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
********************************************************************************/


#pragma once


#include <Python.h>
#include "swig/swigpyrun.h"


static bool pyHasError()
{
    if (PyErr_Occurred()) {
        PyErr_Print();
        return true;
    }
    return false;
}

static bool isPyObjectBaseClass(PyObject* obj, const char* type )
{

    PyObject* tuple = obj->ob_type->tp_bases;
    Py_ssize_t len = PyTuple_Size(tuple);
    for (int i = 0; i < len; i++) {
        PyObject* base = PyTuple_GetItem(tuple, i);
        PyObject* name = PyObject_GetAttrString(base, "__name__");
        pyHasError();
        char* cname = NULL;
        if (name != NULL) {
            cname = PyUnicode_AsUTF8(obj);
        }
        if (cname != NULL ) {
            if (strcmp(cname, type)== 0) {
                return true;
            }
        }
    }
    return false;
}


static void add_to_python_path(char* cstr)
{
    //make sure that sys is imported
    PyRun_SimpleString("import sys");
    PyObject* path = PySys_GetObject("path");
    pyHasError();

    

    blog(LOG_INFO, "PATH: %s",cstr);
    PyList_Append(path, PyUnicode_FromString(cstr));
    pyHasError();

    return;
}


static void add_enum_to_dict(PyObject *tp_dict, char ** names){
  int i = 0;
    while(names[i] != NULL){
      PyDict_SetItemString(tp_dict,names[i],PyLong_FromLong(i));
      i++;
    }

}

//must be used when GIL lock is held
static inline int  py_swig_to_libobs(const char* SWIG_type_str, PyObject* py_in, void* libobs_out){

  swig_type_info* SWIG_type_info = SWIG_TypeQuery(SWIG_type_str);
    
  if (SWIG_type_info == NULL){
    blog(LOG_INFO, "SWIG could not find type : %s",SWIG_type_str);
    return SWIG_ERROR ;
  }
    
  return SWIG_ConvertPtr(py_in, libobs_out, SWIG_type_info, 0);
}

static inline int libobs_to_py_swig(const char* SWIG_type_str, void* libobs_in, int ownership, PyObject** py_out){

  swig_type_info* SWIG_type_info = SWIG_TypeQuery(SWIG_type_str);
  
  if (SWIG_type_info == NULL){
    blog(LOG_INFO, "SWIG could not find type : %s",SWIG_type_str);
    return SWIG_ERROR;
  }

  *py_out = SWIG_NewPointerObj(libobs_in, SWIG_type_info, ownership);

  if(*py_out == Py_None){
    return SWIG_ERROR;
  }
  return SWIG_OK;
}


