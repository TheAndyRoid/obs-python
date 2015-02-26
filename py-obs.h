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

#include <Python.h>
#include "py-source.h"




static PyObject*
py_obs_log(PyObject* self, PyObject* args)
{
    long argLength = PyTuple_Size(args);
    if (argLength != 1) {
        PyErr_SetString(PyExc_TypeError, "Wrong number of arguments");
        return NULL;
    }

    PyUnicodeObject* str;

    if (!PyArg_ParseTuple(args, "U", &str)) {
        return NULL;
    }

    char* cstr =PyUnicode_AsUTF8(str);

    blog(LOG_INFO,"%s",cstr);

    Py_RETURN_NONE;
}

static PyObject*
py_obs_register_source(PyObject* self, PyObject* args)
{
    long argLength = PyTuple_Size(args);
    if (argLength != 1) {
        PyErr_SetString(PyExc_TypeError, "Wrong number of arguments");
        return NULL;
    }

    PyObject* obj;

    if (!PyArg_ParseTuple(args, "O", &obj)) {
        return NULL;
    }

    if (!PyObject_TypeCheck(obj,&py_source_type)) {
        PyErr_SetString(PyExc_TypeError, "Object is not OBS.Source or subclass of OBS.Source");
        return NULL;
    }

    py_source* py_src = (py_source*)obj;

    py_to_obs_source_info(py_src);

    obs_register_source(py_src->py_source_info);
    Py_INCREF(py_src);

    list_add_source(py_src);

    Py_RETURN_NONE;
}



static PyMethodDef py_obs_methods[] = {
    {"log",py_obs_log,METH_VARARGS,"Writes to the obs log"},
    {"obs_register_source",py_obs_register_source,METH_VARARGS,"Registers a new source with obs."},
    { NULL, NULL, 0, NULL }
};




void add_functions_to_py_module(PyObject* module,PyMethodDef* method_list)
{

    PyObject* dict = PyModule_GetDict(module);
    PyObject* name = PyModule_GetNameObject(module);
    if(dict == NULL || name == NULL) {
        return;
    }
    for(PyMethodDef* ml = method_list; ml->ml_name != NULL; ml++) {
        PyObject* func = PyCFunction_NewEx(ml,module,name);
        if(func == NULL) {
            continue;
        }
        PyDict_SetItemString(dict, ml->ml_name, func);
        Py_DECREF(func);
    }
    Py_DECREF(name);
}


#define INITERROR return NULL
void extend_swig_libobs(PyObject* py_swig_libobs)
{


    if (PyType_Ready(&py_source_type) < 0) {
        INITERROR;
    }
    Py_INCREF(&py_source_type);
    PyModule_AddObject(py_swig_libobs , "Source", (PyObject*)&py_source_type);


    add_functions_to_py_module(py_swig_libobs,py_obs_methods);


}

