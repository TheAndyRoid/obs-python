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



static bool pyHasError()
{
    bool ret = false;

    if (PyErr_Occurred()) {

        PyErr_Print();
        ret = true;
    }

    return ret;
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

    while(strstr(cstr,"\\") != NULL) {
        char* c = strstr(cstr,"\\") ;
        c = "/";
    }
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


