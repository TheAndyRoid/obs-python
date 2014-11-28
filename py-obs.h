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
#include "graphics/py-graphics.h"




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
    GS_FUNCTIONS
    { NULL, NULL, 0, NULL }
};


struct module_state {
    PyObject* error;
};


#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))


static PyObject*
error_out(PyObject* m)
{
    struct module_state* st = GETSTATE(m);
    PyErr_SetString(st->error, "something bad happened");
    return NULL;
}




static int myextension_traverse(PyObject* m, visitproc visit, void* arg)
{
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int myextension_clear(PyObject* m)
{
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}


static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "OBS",
    NULL,
    sizeof(struct module_state),
    py_obs_methods,
    NULL,
    myextension_traverse,
    myextension_clear,
    NULL
};

#define INITERROR return NULL

PyMODINIT_FUNC
py_obs_init(void)
{


    PyObject* m = PyModule_Create(&moduledef);

    if (m == NULL)
        INITERROR;

    if (PyType_Ready(&py_source_type) < 0) {
        INITERROR;
    }
    Py_INCREF(&py_source_type);
    PyModule_AddObject(m, "Source", (PyObject*)&py_source_type);

    return m;

}
