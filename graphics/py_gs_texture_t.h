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
#include <structmember.h>
#include <obs-module.h>
#include <obs-internal.h>
#include <graphics/graphics.h>

//pointer object

/*Object Data*/
typedef struct {
    PyObject_HEAD
    gs_texture_t* tex;
} py_gs_texture_t;


static void
py_gs_texture_t_dealloc(py_source* self)
{
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* py_gs_texture_t_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
    py_gs_texture_t* self;
    self = (py_gs_texture_t*)type->tp_alloc(type, 0);
    self->tex = NULL;
    return (PyObject*)self;
}


static int
py_gs_texture_t_init(py_source* self, PyObject* args, PyObject* kwds)
{
    /*Do nothing for now*/
    return 0;
}


static int
py_gs_texture_t_init_type(PyTypeObject* type_object )
{
    return 0;
}


/*Method Table*/
static PyMethodDef py_gs_texture_t_methods[] = {
    { NULL }  /* Sentinel */
};




static PyMemberDef py_gs_texture_t_members[] = {
    { NULL }  /* Sentinel */
};



/*Python Type Object */
static PyTypeObject py_gs_texture_t_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "gs_texture_t",         /*tp_name*/
    sizeof(py_gs_texture_t),     /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)py_gs_texture_t_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "",           /* tp_doc */
    0,               /* tp_traverse */
    0,               /* tp_clear */
    0,               /* tp_richcompare */
    0,               /* tp_weaklistoffset */
    0,               /* tp_iter */
    0,               /* tp_iternext */
    py_gs_texture_t_methods,             /* tp_methods */
    py_gs_texture_t_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)py_gs_texture_t_init,      /* tp_init */
    0,                         /* tp_alloc */
    py_gs_texture_t_new,                 /* tp_new */
};

