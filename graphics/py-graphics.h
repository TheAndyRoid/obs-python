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
#include "../obs-python-module.h"


//Function table for OBS module
#define GS_FUNCTIONS\
  {"gs_texture_create",py_gs_texture_create,METH_VARARGS,"Creates a texture."}, \
  {"gs_texture_destroy",py_gs_texture_destroy,METH_VARARGS,"Destroys a texture."}, \
  {"obs_leave_graphics",py_obs_leave_graphics,METH_VARARGS,"Helper function for leaving the OBS graphics context"},\
  {"obs_enter_graphics",py_obs_enter_graphics,METH_VARARGS,"Helper function for entering the OBS graphics context"},\
   


static PyObject*
py_obs_enter_graphics(PyObject* self, PyObject* args)
{
  obs_enter_graphics();
  Py_RETURN_NONE;
}
static PyObject*
py_obs_leave_graphics(PyObject* self, PyObject* args)
{
  obs_leave_graphics();
  Py_RETURN_NONE;
}
 


static PyObject*
py_gs_texture_create(PyObject* self, PyObject* args)
{

    PyObject* byte_array;
    long cx,cy,color_format,levels,flags;
   
      
    if (!PyArg_ParseTuple(args, "llllOl", &cx,&cy,&color_format,&levels,&byte_array,&flags)) {
        return NULL;
    }

    //safety check the bytearray
    if(!PyByteArray_Check(byte_array)){
      PyErr_SetString(PyExc_TypeError, "Object is not a ByteArray");
      return NULL;
    }
    
    //get the size
    long size = PyByteArray_Size(byte_array);
    if(cx*cy*4 > size){
      PyErr_SetString(PyExc_TypeError, "ByteArray is to small");  
      return NULL;
    }

    char *addr = PyByteArray_AsString(byte_array);


    gs_texture_t *tex = gs_texture_create(cx,cy,color_format,levels,(const uint8_t**)&addr,flags);

    return PyLong_FromLong((long)tex);
    
}

static PyObject*
py_gs_texture_destroy(PyObject* self, PyObject* args)
{

    long addr;
   
      
    if (!PyArg_ParseTuple(args, "l", &addr)) {
        return NULL;
    }

    //convert to a correct pointer
    
    gs_texture_t *tex = (gs_texture_t*)addr;

    gs_texture_destroy(tex);

    Py_RETURN_NONE;
}








 

