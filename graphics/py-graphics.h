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
#include <graphics/graphics.h>


//Function table for OBS module
#define GS_FUNCTIONS\
  {"gs_texture_create",py_gs_texture_create,METH_VARARGS,"Creates a texture."}, \
  {"gs_texture_destroy",py_gs_texture_destroy,METH_VARARGS,"Destroys a texture."}, \
  {"obs_leave_graphics",py_obs_leave_graphics,METH_VARARGS,"Helper function for leaving the OBS graphics context"},\
  {"obs_enter_graphics",py_obs_enter_graphics,METH_VARARGS,"Helper function for entering the OBS graphics context"},\
  {"gs_draw_sprite",py_gs_draw_sprite,METH_VARARGS,"Creates a texture."}, \
  {"gs_reset_blend_state",py_gs_reset_blend_state,METH_VARARGS,""}, \
  {"gs_effect_set_texture",py_gs_effect_set_texture,METH_VARARGS,""}, \
  {"gs_texture_set_image",py_gs_texture_set_image,METH_VARARGS,""}, \
  {"gs_effect_get_param_by_name", py_gs_effect_get_param_by_name,METH_VARARGS,""}, \
 




static PyObject*
py_gs_texture_set_image(PyObject* self, PyObject* args)
{
  

  long linesize,p_tex,invert;
  PyObject *byte_array;

  if (!PyArg_ParseTuple(args, "lOlp", &p_tex,&byte_array,&linesize,&invert)) {
        return NULL;
    }

    char *addr = PyByteArray_AsString(byte_array);
    gs_texture_t* tex = (gs_texture_t*)p_tex;
    
    gs_texture_set_image(tex,addr,linesize,invert);

    Py_RETURN_NONE;
}


static PyObject*
py_gs_effect_set_texture(PyObject* self, PyObject* args)
{
  

    long p_param,p_tex;

    if (!PyArg_ParseTuple(args, "ll", &p_param,&p_tex)) {
        return NULL;
    }


    gs_texture_t* tex = (gs_texture_t*)p_tex;
    gs_eparam_t* param = (gs_effect_t*)p_param;
    gs_effect_set_texture(param,tex);

    Py_RETURN_NONE;
}




static PyObject*
py_gs_effect_get_param_by_name(PyObject* self, PyObject* args)
{

    long p_effect;
    PyObject *py_name;
    if (!PyArg_ParseTuple(args, "lU", &p_effect,&py_name)) {
        return NULL;
    }

    gs_effect_t* effect = (gs_effect_t*)p_effect;
    long p_param = (long)gs_effect_get_param_by_name(effect,PyUnicode_AsUTF8(py_name));
    PyObject *ret = PyLong_FromLong(p_param);
    return ret;

}



static PyObject*
py_gs_reset_blend_state(PyObject* self, PyObject* args)
{

  gs_reset_blend_state();
    Py_RETURN_NONE;
}






static PyObject*
py_gs_draw_sprite(PyObject* self, PyObject* args)
{

    long addr,flip,width,height;

    if (!PyArg_ParseTuple(args, "llll", &addr,&flip,&width,&height)) {
        return NULL;
    }

    //convert to a correct pointer

    gs_texture_t* tex = (gs_texture_t*)addr;


    gs_draw_sprite(tex,flip,width,height);


    Py_RETURN_NONE;
}



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
    if(!PyByteArray_Check(byte_array)) {
        PyErr_SetString(PyExc_TypeError, "Object is not a ByteArray");
        return NULL;
    }

    //get the size
    long size = PyByteArray_Size(byte_array);
    if(cx*cy*4 > size) {
        PyErr_SetString(PyExc_TypeError, "ByteArray is to small");
        return NULL;
    }

    char* addr = PyByteArray_AsString(byte_array);


    gs_texture_t* tex = gs_texture_create(cx,cy,color_format,levels,(const uint8_t**)&addr,flags);

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

    gs_texture_t* tex = (gs_texture_t*)addr;


    gs_texture_destroy(tex);

    Py_RETURN_NONE;
}



static void py_gs_setup_defines(PyObject *module){

   blog(LOG_INFO,"%l",2);


  PyModule_AddIntConstant(module,"GS_DEVICE_OPENGL",GS_DEVICE_OPENGL);
  PyModule_AddIntConstant(module,"GS_DEVICE_DIRECT3D_11",GS_DEVICE_DIRECT3D_11);

 
  PyModule_AddIntConstant(module,"GS_BUILD_MIPMAPS",GS_BUILD_MIPMAPS );
  PyModule_AddIntConstant(module,"GS_DYNAMIC", GS_DYNAMIC );
  PyModule_AddIntConstant(module,"GS_RENDER_TARGET",GS_RENDER_TARGET );
  PyModule_AddIntConstant(module,"GS_GL_DUMMYTEX",GS_GL_DUMMYTEX);
  PyModule_AddIntConstant(module,"GS_FLIP_U",GS_FLIP_U);
  PyModule_AddIntConstant(module,"GS_FLIP_V",GS_FLIP_V);

  PyModule_AddIntConstant(module,"GS_CLEAR_COLOR",GS_CLEAR_COLOR);
  PyModule_AddIntConstant(module,"GS_CLEAR_DEPTH",GS_CLEAR_DEPTH);
  PyModule_AddIntConstant(module,"GS_CLEAR_STENCIL",GS_CLEAR_STENCIL);

}






  
