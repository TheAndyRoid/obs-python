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
#include "utils.h"
#include "obs-python-module.h"


/*Object Data*/
typedef struct {
    PyObject_HEAD
    PyObject* id;
    PyObject* type;
    PyObject* flags;
    PyObject* name;
    PyObject* create;
    PyObject* destroy;
    PyObject* get_width;
    PyObject* get_height;
    PyObject* get_defaults;
    PyObject* get_properties;
    PyObject* update;
    PyObject* activate;
    PyObject* deactivate;
    PyObject* show;
    PyObject* hide;
    PyObject* video_tick;
    PyObject* video_render;
    PyObject* filter_video;
    PyObject* filter_audio;
    PyObject* enum_sources;
    PyObject* save;
    PyObject* load;
    PyObject* mouse_click;
    PyObject* mouse_move;
    PyObject* mouse_wheel;
    PyObject* focus;
    PyObject* key_click;
    PyObject* data;
    struct obs_source_info* py_source_info;
} py_source;



//The regestired types
struct python_source {
    py_source* source;
    struct python_source* next;
    struct python_source* prev;
};


struct python_data_pair {
    py_source* source;
    PyObject* data;
};


py_source* list_remove_source(const char* id,py_source* self);
struct python_source* list_find_source(const char* id);
void list_add_source(py_source* src);





static void
py_source_dealloc(py_source* self)
{
    Py_XDECREF(self->id);
    Py_XDECREF(self->data);
    Py_XDECREF(self->type);
    Py_XDECREF(self->flags);
    Py_XDECREF(self->name);
    Py_XDECREF(self->create);
    Py_XDECREF(self->destroy);
    Py_XDECREF(self->get_width);
    Py_XDECREF(self->get_height);
    Py_XDECREF(self->get_defaults);
    Py_XDECREF(self->get_properties);
    Py_XDECREF(self->update);
    Py_XDECREF(self->activate);
    Py_XDECREF(self->deactivate);
    Py_XDECREF(self->show);
    Py_XDECREF(self->hide);
    Py_XDECREF(self->video_tick);
    Py_XDECREF(self->video_render);
    Py_XDECREF(self->filter_video);
    Py_XDECREF(self->filter_audio);
    Py_XDECREF(self->enum_sources);
    Py_XDECREF(self->save);
    Py_XDECREF(self->load);
    Py_XDECREF(self->mouse_click);
    Py_XDECREF(self->mouse_move);
    Py_XDECREF(self->mouse_wheel);
    Py_XDECREF(self->focus);
    Py_XDECREF(self->key_click);

    list_remove_source(self->py_source_info->id,self);
    bfree(self->py_source_info);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* py_source_new(PyTypeObject* type, PyObject* args,
                               PyObject* kwds)
{

    UNUSED_PARAMETER(args);
    UNUSED_PARAMETER(kwds);
    py_source* self;


    self = (py_source*)type->tp_alloc(type, 0);

    if (self != NULL) {

        self->id = PyUnicode_FromString("python_default");
        if (self->id == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->type = PyLong_FromLong(OBS_SOURCE_TYPE_INPUT);
        if (self->type == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->flags = PyLong_FromLong(OBS_SOURCE_VIDEO);
        if (self->flags == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->name = PyUnicode_FromString("Python-Default");
        if (self->id == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->create = Py_BuildValue("");
        if (self->create == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->destroy = Py_BuildValue("");
        if (self->destroy == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->data = Py_BuildValue("");
        if (self->data == NULL) {
            Py_DECREF(self);
            return NULL;
        }

        self->get_width = Py_BuildValue("");
        if (self->get_width == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->get_height = Py_BuildValue("");
        if (self->get_height == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->get_defaults = Py_BuildValue("");
        if (self->get_defaults == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->get_properties = Py_BuildValue("");
        if (self->get_properties == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->update = Py_BuildValue("");
        if (self->update == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->activate = Py_BuildValue("");
        if (self->activate == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->deactivate = Py_BuildValue("");
        if (self->deactivate == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->show = Py_BuildValue("");
        if (self->show == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->hide = Py_BuildValue("");
        if (self->hide == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->video_tick = Py_BuildValue("");
        if (self->video_tick == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->video_render = Py_BuildValue("");
        if (self->video_render == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->filter_video = Py_BuildValue("");
        if (self->filter_video == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->filter_audio = Py_BuildValue("");
        if (self->filter_audio == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->enum_sources = Py_BuildValue("");
        if (self->enum_sources == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->save = Py_BuildValue("");
        if (self->save == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->load = Py_BuildValue("");
        if (self->load == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->mouse_click = Py_BuildValue("");
        if (self->mouse_click == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->mouse_move = Py_BuildValue("");
        if (self->mouse_move == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->mouse_wheel = Py_BuildValue("");
        if (self->mouse_wheel == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->focus = Py_BuildValue("");
        if (self->focus == NULL) {
            Py_DECREF(self);
            return NULL;
        }
        self->key_click = Py_BuildValue("");
        if (self->key_click == NULL) {
            Py_DECREF(self);
            return NULL;
        }


    }

    self->py_source_info = bzalloc(sizeof(struct obs_source_info));
    return (PyObject*)self;

}


static int
py_source_init(py_source* self, PyObject* args, PyObject* kwds)
{
    UNUSED_PARAMETER(self);
    UNUSED_PARAMETER(args);
    UNUSED_PARAMETER(kwds);
    /*Do nothing for now*/
    return 0;
}



/*Method Table*/
static PyMethodDef py_source_methods[] = {
    { NULL }  /* Sentinel */
};

/*Member table*/
static PyMemberDef py_source_members[] = {
    {"id",T_OBJECT_EX, offsetof(py_source, id), 0,"id" },
    {"type",T_OBJECT_EX, offsetof(py_source, type), 0,"type" },
    {"flags",T_OBJECT_EX, offsetof(py_source, flags), 0,"flags" },
    {"create",T_OBJECT_EX, offsetof(py_source, create), 0,"create" },
    {"destroy",T_OBJECT_EX, offsetof(py_source, destroy), 0,"destroy" },
    {"get_width",T_OBJECT_EX, offsetof(py_source, get_width), 0,"get_width" },
    {"get_height",T_OBJECT_EX, offsetof(py_source, get_height), 0,"get_height" },
    {"get_defaults",T_OBJECT_EX, offsetof(py_source, get_defaults), 0,"get_defaults" },
    {"get_properties",T_OBJECT_EX, offsetof(py_source, get_properties), 0,"get_properties" },
    {"update",T_OBJECT_EX, offsetof(py_source, update), 0,"update" },
    {"activate",T_OBJECT_EX, offsetof(py_source, activate), 0,"activate" },
    {"deactivate",T_OBJECT_EX, offsetof(py_source, deactivate), 0,"deactivate" },
    {"show",T_OBJECT_EX, offsetof(py_source, show), 0,"show" },
    {"hide",T_OBJECT_EX, offsetof(py_source, hide), 0,"hide" },
    {"video_tick",T_OBJECT_EX, offsetof(py_source, video_tick), 0,"video_tick" },
    {"video_render",T_OBJECT_EX, offsetof(py_source, video_render), 0,"video_render" },
    {"filter_video",T_OBJECT_EX, offsetof(py_source, filter_video), 0,"filter video" },
    {"filter_audio",T_OBJECT_EX, offsetof(py_source, filter_audio), 0,"filter video" },
    {"enum_sources",T_OBJECT_EX, offsetof(py_source, enum_sources), 0,"enum_sources" },
    {"save",T_OBJECT_EX, offsetof(py_source, save), 0,"save" },
    {"load",T_OBJECT_EX, offsetof(py_source, load), 0,"load" },
    {"mouse_click",T_OBJECT_EX, offsetof(py_source, mouse_click), 0,"mouse_click" },
    {"mouse_move",T_OBJECT_EX, offsetof(py_source, mouse_move), 0,"mouse_move" },
    {"mouse_wheel",T_OBJECT_EX, offsetof(py_source, mouse_wheel), 0,"mouse_wheel" },
    {"focus",T_OBJECT_EX, offsetof(py_source, focus), 0,"focus" },
    {"key_click",T_OBJECT_EX, offsetof(py_source, key_click), 0,"key_click" },
    { NULL }  /* Sentinel */
};


/*Python Type Object */
static PyTypeObject py_source_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "obspython.obs_source_info",         /*tp_name*/
    sizeof(py_source),     /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)py_source_dealloc, /*tp_dealloc*/
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
    "pylibobs Source",           /* tp_doc */
    0,               /* tp_traverse */
    0,               /* tp_clear */
    0,               /* tp_richcompare */
    0,               /* tp_weaklistoffset */
    0,               /* tp_iter */
    0,               /* tp_iternext */
    py_source_methods,             /* tp_methods */
    py_source_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)py_source_init,      /* tp_init */
    0,                         /* tp_alloc */
    py_source_new,                 /* tp_new */
};



static void* py_source_create(obs_data_t* settings, obs_source_t* source)
{

    const char* id  = source->info.id ;
    struct python_data_pair* py_data = NULL;
    
    int SWIG_result = SWIG_OK;

    //Swig types
    const char* SWIG_str_obs_data_t = "obs_data_t *";
    const char* SWIG_str_obs_source_t = "obs_source_t *";

    //Python
    PyObject* argList = NULL;
    PyObject* data = NULL;
    PyObject* py_swig_settings = NULL;
    PyObject* py_swig_source = NULL;

    struct python_source* pythonsource = list_find_source(id);
    if( !pythonsource) {
        goto failNOGIL;
    }
    py_source* py_src = pythonsource->source;


    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //check python function.
    if(!PyCallable_Check(py_src->create)) {
        blog(LOG_INFO, "None Callable Create: %s",id);
        goto fail;
    }

    SWIG_result =  libobs_to_py_swig(SWIG_str_obs_data_t,settings,0,&py_swig_settings);

    if (!SWIG_IsOK(SWIG_result)) {
        blog(LOG_INFO,
             "%s:l%i \"SWIG Failed to make required python object: '%s' for '%s'\"",
             __func__,
             __LINE__,
             SWIG_str_obs_data_t,
             id);
        goto fail;
    }

    SWIG_result = libobs_to_py_swig(SWIG_str_obs_source_t,source,0,&py_swig_source);

    if (!SWIG_IsOK(SWIG_result)) {
        blog(LOG_INFO,
             "%s:l%i \"SWIG Failed to make required python object: '%s' for '%s'\"",
             __func__,
             __LINE__,
             SWIG_str_obs_source_t,
             id);
        goto fail;
    }

    blog(LOG_INFO, "Source Create");
    argList = Py_BuildValue("(OO)",py_swig_settings,py_swig_source);
    data = PyObject_CallObject(py_src->create,argList);

    if(pyHasError()) {
        goto fail;
    }

    py_data = bzalloc(sizeof(struct python_data_pair));
    py_data->data = data;
    py_data->source = py_src;
    blog(LOG_INFO, "Python Create: %s",id);

fail:
    Py_XDECREF(argList);
    Py_XDECREF(py_swig_settings);
    Py_XDECREF(py_swig_source);
    PyGILState_Release(gstate);
failNOGIL:
    return py_data;
}






static void py_source_destroy(void* data)
{
    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    


    PyObject* argList = NULL;
    PyObject* py_data = NULL;

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //check python function.
    if(!PyCallable_Check(py_src->destroy)) {
        blog(LOG_INFO, "None Callable destroy: %s",py_src->py_source_info->id);
	goto fail;
    }

    py_data = py_pair->data;
    argList = Py_BuildValue("(O)",py_data);
    PyObject_CallObject(py_src->destroy,argList);
    if(pyHasError()){
         blog(LOG_INFO, "Error destroying python object cleanly");
    }

 fail:

    Py_XDECREF(argList);
    Py_XDECREF(py_data);


    PyGILState_Release(gstate);

    bfree(data);

}
static uint32_t py_source_get_width(void* data)
{

    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;
    long width = 0;

    //Python
    PyObject* argList = NULL;
    PyObject* ret = NULL;

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //check python function.
    if(!PyCallable_Check(py_src->get_width)) {
        blog(LOG_INFO, "None Callable get_width: %s",py_src->py_source_info->id);
	goto fail;
      
    }

    argList = Py_BuildValue("(O)",py_data);
    ret = PyObject_CallObject(py_src->get_width,argList);
    if(pyHasError()){
      goto fail;
    }
    if(PyLong_Check(ret)) {
        width = PyLong_AsLong(ret);
    }

 fail:
    Py_XDECREF(argList);
    Py_XDECREF(ret);
    PyGILState_Release(gstate);

    return width;
}
static const char*  py_source_get_name(void)
{
    return "CustomPython";
}
static uint32_t py_source_get_height(void* data)
{

    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;
    long height = 0 ;

    //Python
    PyObject* argList = NULL;
    PyObject* ret = NULL;


    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //check python function.
    if(!PyCallable_Check(py_src->get_height)) {
        blog(LOG_INFO, "None Callable get_height: %s",py_src->py_source_info->id);
	goto fail;
    }

    argList = Py_BuildValue("(O)",py_data);
    ret = PyObject_CallObject(py_src->get_height,argList);
    
    if(pyHasError()){
      goto fail;
    }
    if(PyLong_Check(ret)) {
        height = PyLong_AsLong(ret);
    }

 fail:
    Py_XDECREF(argList);
    Py_XDECREF(ret);
    PyGILState_Release(gstate);

    return height;
}
static obs_properties_t* py_source_properties(void* data)
{
    
    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;
    obs_properties_t* obs_properties = NULL;
    int SWIG_result = SWIG_OK;

    //SWIG
    const char* SWIG_str_obs_properties_t = "obs_properties_t *";

    //Python
    PyObject* py_result = NULL;
    PyObject* argList = NULL;

    
    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();


    //Check python function
    if(!PyCallable_Check(py_src->get_properties)) {
        blog(LOG_INFO, "None Callable get_properties: %s",py_src->py_source_info->id);
	goto fail;
    }

    argList = Py_BuildValue("(O)",py_data);
    py_result = PyObject_CallObject(py_src->get_properties, argList);

    if(pyHasError()){
	goto fail;
    }
    
    SWIG_result = py_swig_to_libobs(SWIG_str_obs_properties_t, py_result, &obs_properties);
    if(!SWIG_IsOK(SWIG_result)){
      obs_properties = NULL;
    }

  fail:
    if( obs_properties == NULL){
        obs_properties = obs_properties_create();
    }
    Py_XDECREF(argList);
    Py_XDECREF(py_result);
    PyGILState_Release(gstate);
    return obs_properties;
}

static void py_source_get_defaults(obs_data_t* settings) {
  UNUSED_PARAMETER(settings);

}
static void py_source_update(void* data, obs_data_t* settings)
{

    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;

    //SWIG
    const char* SWIG_str_obs_data_t = "obs_data_t *";
    int SWIG_result = SWIG_OK;

    //Python
    PyObject* argList = NULL;
    PyObject* py_swig_settings = NULL;

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->update)) {
        blog(LOG_INFO, "None Callable update: %s",py_src->py_source_info->id);
	goto fail;
    }

    SWIG_result = libobs_to_py_swig(SWIG_str_obs_data_t,settings,0,&py_swig_settings);

    if (!SWIG_IsOK(SWIG_result)) {
        blog(LOG_INFO,
             "%s:l%i \"SWIG Failed to make required python object: '%s' for '%s'\"",
             __func__,
             __LINE__,
             SWIG_str_obs_data_t,
             py_src->py_source_info->id);
        goto fail;
    }

    argList = Py_BuildValue("(OO)",py_data,py_swig_settings);
    PyObject_CallObject(py_src->update,argList);
    if(pyHasError()){
      goto fail;
    }

 fail:
    Py_XDECREF(py_swig_settings);
    Py_XDECREF(argList);
    PyGILState_Release(gstate);
}

static void py_source_activate(void* data)
{

    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;
    
    //Python
    PyObject* argList = NULL;

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->activate)) {
        blog(LOG_INFO, "None Callable activate: %s",py_src->py_source_info->id);
	goto fail;
    }

    argList = Py_BuildValue("(O)",py_data);
    PyObject_CallObject(py_src->activate,argList);
    if(pyHasError()){
      goto fail;
    }

 fail:
    Py_XDECREF(argList);
    PyGILState_Release(gstate);
}

static void py_source_deactivate(void* data)
{

    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;

    //Python
    PyObject* argList = NULL;

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->deactivate)) {
        blog(LOG_INFO, "None Callable deactivate: %s",py_src->py_source_info->id);
	goto fail;
    }

    argList = Py_BuildValue("(O)",py_data);
    PyObject_CallObject(py_src->deactivate,argList);
    if(pyHasError()){
      goto fail;
    }

 fail:
    Py_XDECREF(argList);
    PyGILState_Release(gstate);
}
static void py_source_show(void* data)
{

    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;

    //Python
    PyObject* argList = NULL;

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->show)) {
        blog(LOG_INFO, "None Callable show: %s",py_src->py_source_info->id);
        goto fail;
    }

    argList = Py_BuildValue("(O)",py_data);
    PyObject_CallObject(py_src->show,argList);
    if(pyHasError()) {
        goto fail;
    }

fail:
    Py_XDECREF(argList);
    PyGILState_Release(gstate);
}

static void py_source_hide(void* data)
{

    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;

    //Python
    PyObject* argList = NULL;

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->hide)) {
        blog(LOG_INFO, "None Callable hide: %s",py_src->py_source_info->id);
	goto fail;
    }

    argList = Py_BuildValue("(O)",py_data);
    PyObject_CallObject(py_src->hide,argList);

    if(pyHasError()){
      goto fail;
    }

 fail:
    Py_XDECREF(argList);
    PyGILState_Release(gstate);
}
static void py_source_video_tick(void* data, float seconds)
{
    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;
    
    //Python
    PyObject* argList = NULL;

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->video_tick)) {
        blog(LOG_INFO, "None Callable video_tick: %s",py_src->py_source_info->id);
	goto fail;
    }

    argList = Py_BuildValue("(Of)",py_data,seconds);
    PyObject_CallObject(py_src->video_tick,argList);

 fail:
    pyHasError();
    Py_XDECREF(argList);
    PyGILState_Release(gstate);
}
static void py_source_video_render(void* data, gs_effect_t* effect)
{

    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;

    //SWIG
    int SWIG_result = SWIG_OK;
    const char *SWIG_str_gs_effect_t = "gs_effect_t *";

    //Python
    PyObject* py_swig_effect = NULL;
    PyObject* argList = NULL;

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->video_render)) {
        blog(LOG_INFO, "None Callable video_render: %s",py_src->py_source_info->id);
        PyGILState_Release(gstate);
        return ;
    }

    /*Create SWIG effect object*/
    SWIG_result = libobs_to_py_swig(SWIG_str_gs_effect_t,effect,0,&py_swig_effect);
    if(!SWIG_IsOK(SWIG_result)){
      goto fail;
    }

    argList = Py_BuildValue("(OO)",py_data,py_swig_effect);
    PyObject_CallObject(py_src->video_render,argList);
    if(pyHasError()){
      goto fail;
    }

 fail:
    Py_XDECREF(argList);
    Py_XDECREF(py_swig_effect);
    PyGILState_Release(gstate);

}
static struct obs_source_frame* py_source_filter_video(void* data,
                                                       struct obs_source_frame* frame)
{

    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    
    PyObject* py_data = py_pair->data;
    struct obs_source_frame* new_frame = NULL;


    //SWIG
    int SWIG_result = SWIG_OK;
    const char* SWIG_str_obs_source_frame = "obs_source_frame *";

    //Python
    PyObject* argList = NULL;
    PyObject* py_frame = NULL;
    PyObject* py_ret = NULL;

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->filter_video)) {
        blog(LOG_INFO, "None Callable filter_video: %s",py_src->py_source_info->id);
	goto fail;
    }
    
    SWIG_result = libobs_to_py_swig(SWIG_str_obs_source_frame, (void*)frame, 0, &py_frame);

    if (!SWIG_IsOK(SWIG_result)) {
        blog(LOG_INFO,
             "%s:l%i \"SWIG Failed to make required python object: '%s' for '%s'\"",
             __func__,
             __LINE__,
             SWIG_str_obs_source_frame,
             py_src->py_source_info->id);
        goto fail;
    }

    argList = Py_BuildValue("(OO)",py_data,py_frame);
    py_ret = PyObject_CallObject(py_src->filter_video,argList);
    
    if(pyHasError() || py_ret == Py_None ){
      goto fail;
    }
    
    
    SWIG_result = py_swig_to_libobs(SWIG_str_obs_source_frame, py_ret, new_frame);

    if (!SWIG_IsOK(SWIG_result)) {
        blog(LOG_INFO,
             "%s:l%i \"SWIG Failed to convert to libobs object: '%s' for '%s'\"",
             __func__,
             __LINE__,
             SWIG_str_obs_source_frame,
             py_src->py_source_info->id);
        goto fail;
    }

 fail:
    if ( new_frame == NULL ){
      new_frame = (void*)frame;
    }
    Py_XDECREF(py_ret);
    Py_XDECREF(argList);
    Py_XDECREF(py_frame);
    PyGILState_Release(gstate);
    return new_frame;
}
static struct obs_audio_data* py_source_filter_audio(void* data,
                                                      struct obs_audio_data* audio)
{

    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;


    struct obs_audio_data* new_audio = NULL;


    //SWIG
    int SWIG_result = SWIG_OK;
    const char* SWIG_str_obs_audio_data = "obs_audio_data *";

    //Python
    PyObject* argList = NULL;
    PyObject* py_ret = NULL;
    PyObject* py_audio = NULL;


    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->filter_audio)) {
        blog(LOG_INFO, "None Callable filter_audio: %s",py_src->py_source_info->id);
	goto fail;
    }

    SWIG_result = libobs_to_py_swig(SWIG_str_obs_audio_data, (void*)audio, 0, &py_audio);

    if (!SWIG_IsOK(SWIG_result)) {
        blog(LOG_INFO,
             "%s:l%i \"SWIG Failed to make required python object: '%s' for '%s'\"",
             __func__,
             __LINE__,
             SWIG_str_obs_audio_data,
	     py_src->py_source_info->id);
        goto fail;
    }

    argList = Py_BuildValue("(O)",py_data);
    py_ret = PyObject_CallObject(py_src->filter_audio,argList);

    if(pyHasError() || py_ret == Py_None){
      goto fail;
    }

    SWIG_result = py_swig_to_libobs(SWIG_str_obs_audio_data, py_ret, new_audio);

    if (!SWIG_IsOK(SWIG_result)) {
        blog(LOG_INFO,
             "%s:l%i \"SWIG Failed to convert to libobs object: '%s' for '%s'\"",
             __func__,
             __LINE__,
             SWIG_str_obs_audio_data,
	     py_src->py_source_info->id);
        goto fail;
    }


 fail:
    if(new_audio == NULL){
      new_audio = (void*)audio;
    }
    Py_XDECREF(argList);
    PyGILState_Release(gstate);
    return new_audio;
}
static void py_source_enum_sources(void* data,
                                   obs_source_enum_proc_t enum_callback,void* param)
{

    UNUSED_PARAMETER(enum_callback);
    UNUSED_PARAMETER(param);
  
    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;


    PyObject* argList = NULL;

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->enum_sources)) {
        blog(LOG_INFO, "None Callable enum_sources: %s",py_src->py_source_info->id);
	goto fail;
    }

    argList = Py_BuildValue("(O)",py_data);
    PyObject_CallObject(py_src->enum_sources,argList);
    pyHasError();

 fail:
    Py_XDECREF(argList);
    PyGILState_Release(gstate);

}
static void py_source_save(void* data,obs_data_t* settings)
{

    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;

    //SWIG
    int SWIG_result = SWIG_OK;
    const char* SWIG_str_obs_data_t = "obs_data_t *";

    //Python
    PyObject* argList = NULL;
    PyObject* py_swig_settings = NULL;
    

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->save)) {
        blog(LOG_INFO, "None Callable save: %s",py_src->py_source_info->id);
	goto fail;
    }
    
    SWIG_result = libobs_to_py_swig(SWIG_str_obs_data_t, settings, 0, &py_swig_settings);

    if (!SWIG_IsOK(SWIG_result)) {
        blog(LOG_INFO,
             "%s:l%i \"SWIG Failed to make required python object: '%s' for '%s'\"",
             __func__,
             __LINE__,
             SWIG_str_obs_data_t,
             py_src->py_source_info->id);
        goto fail;
    }


    argList = Py_BuildValue("(OO)",py_data);
    PyObject_CallObject(py_src->save,argList);
    if(pyHasError()){
      goto fail;
    }

 fail:
    Py_XDECREF(argList);
    Py_XDECREF(py_swig_settings);
    PyGILState_Release(gstate);
}

static void py_source_load(void* data, obs_data_t* settings)
{
    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;

    //SWIG
    int SWIG_result = SWIG_OK;
    const char* SWIG_str_obs_data_t = "obs_data_t *";

    //Python
    PyObject* argList = NULL;
    PyObject* py_swig_settings = NULL;

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->load)) {
        blog(LOG_INFO, "None Callable load: %s",py_src->py_source_info->id);
	goto fail;
    }

    SWIG_result = libobs_to_py_swig(SWIG_str_obs_data_t, settings, 0, &py_swig_settings);

    if (!SWIG_IsOK(SWIG_result)) {
        blog(LOG_INFO,
             "%s:l%i \"SWIG Failed to make required python object: '%s' for '%s'\"",
             __func__,
             __LINE__,
             SWIG_str_obs_data_t,
             py_src->py_source_info->id);
        goto fail;
    }

    argList = Py_BuildValue("(OO)",py_data,py_swig_settings);
    PyObject_CallObject(py_src->load,argList);
    if(pyHasError()){
      goto fail;
    }

 fail:
    Py_XDECREF(py_swig_settings);
    Py_XDECREF(argList);
    PyGILState_Release(gstate);
}
static void py_source_mouse_click(void* data,
                                  const struct obs_mouse_event* event, 
				  int32_t type,
				  bool mouse_up,
                                  uint32_t click_count)
{
    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;

    //SWIG
    const char* SWIG_str_obs_mouse_event = "obs_mouse_event *";
    int SWIG_result = SWIG_OK;

    //Python
    PyObject* argList = NULL;
    PyObject* py_swig_event = NULL;

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->mouse_click)) {
        blog(LOG_INFO, "None Callable mouuse_click: %s",py_src->py_source_info->id);
	goto fail;
    }

    SWIG_result = libobs_to_py_swig(SWIG_str_obs_mouse_event, (void*)event, 0, &py_swig_event);

    if (!SWIG_IsOK(SWIG_result)) {
        blog(LOG_INFO,
             "%s:l%i \"SWIG Failed to make required python object: '%s' for '%s'\"",
             __func__,
             __LINE__,
             SWIG_str_obs_mouse_event,
             py_src->py_source_info->id);
        goto fail;
    }

    argList = Py_BuildValue("(Oipi)", py_data, type,mouse_up, click_count);
    PyObject_CallObject(py_src->mouse_click,argList);
    if(pyHasError()){
      goto fail;
    }

 fail:
    Py_XDECREF(argList);
    Py_XDECREF(py_swig_event);
    PyGILState_Release(gstate);

}
static void py_source_mouse_move(void* data,
				 const struct obs_mouse_event* event,
                                 bool mouse_leave)
{
    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;

    //SWIG
    const char* SWIG_str_obs_mouse_event = "obs_mouse_event *";
    int SWIG_result = SWIG_OK;

    //Python
    PyObject* argList = NULL;
    PyObject* py_swig_event = NULL;


    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->create)) {
        blog(LOG_INFO, "None Callable mouse_move: %s",py_src->py_source_info->id);
	goto fail;
    }

    SWIG_result = libobs_to_py_swig(SWIG_str_obs_mouse_event, (void*)event, 0, &py_swig_event);

    if (!SWIG_IsOK(SWIG_result)) {
        blog(LOG_INFO,
             "%s:l%i \"SWIG Failed to make required python object: '%s' for '%s'\"",
             __func__,
             __LINE__,
             SWIG_str_obs_mouse_event,
             py_src->py_source_info->id);
        goto fail;
    }

    argList = Py_BuildValue("(OOp)", py_data, py_swig_event, mouse_leave);
    PyObject_CallObject(py_src->create,argList);
    if(pyHasError()){
      goto fail;
    }
 fail:
    Py_XDECREF(py_swig_event);
    Py_XDECREF(argList);
    PyGILState_Release(gstate);

}
static void py_source_mouse_wheel(void* data,
                                  const struct obs_mouse_event* event, 
				  int x_delta,
				  int y_delta)
{
    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;

    //SWIG
    const char* SWIG_str_obs_mouse_event = "obs_mouse_event *";
    int SWIG_result = SWIG_OK;

    //Python
    PyObject* argList = NULL;
    PyObject* py_swig_event = NULL;

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->mouse_wheel)) {
        blog(LOG_INFO, "None Callable mouse_wheel: %s",py_src->py_source_info->id);
	goto fail;
    }

    SWIG_result = libobs_to_py_swig(SWIG_str_obs_mouse_event, (void*)event, 0, &py_swig_event);

    if (!SWIG_IsOK(SWIG_result)) {
        blog(LOG_INFO,
             "%s:l%i \"SWIG Failed to make required python object: '%s' for '%s'\"",
             __func__,
             __LINE__,
             SWIG_str_obs_mouse_event,
             py_src->py_source_info->id);
        goto fail;
    }

    argList = Py_BuildValue("(OOii)", py_data, py_swig_event, x_delta, y_delta);
    PyObject_CallObject(py_src->mouse_wheel,argList);
    if(pyHasError()){
      goto fail;
    }

 fail:
    Py_XDECREF(argList);
    Py_XDECREF(py_swig_event);
    PyGILState_Release(gstate);
}
static void py_source_focus(void* data,bool focus)
{
    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;

    //Python
    PyObject* argList = NULL;

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->focus)) {
        blog(LOG_INFO, "None Callable focus: %s",py_src->py_source_info->id);
	goto fail;
    }

    argList = Py_BuildValue("(Op)",py_data, focus);
    PyObject_CallObject(py_src->focus,argList);
    if(pyHasError()){
      goto fail;
    }

 fail:
    Py_XDECREF(argList);
    PyGILState_Release(gstate);

}
static void py_source_key_click(void* data,
				const struct obs_key_event* event,
                                bool key_up)
{
    struct python_data_pair* py_pair = data;
    py_source* py_src = py_pair->source;
    PyObject* py_data = py_pair->data;

    //SWIG
    const char* SWIG_str_obs_key_event = "obs_key_event *";
    int SWIG_result = SWIG_OK;

    //Python
    PyObject* argList = NULL;
    PyObject* py_swig_event = NULL;


    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Check python function
    if(!PyCallable_Check(py_src->key_click)) {
        blog(LOG_INFO, "None Callable key_click: %s",py_src->py_source_info->id);
	goto fail;
    }


    SWIG_result = libobs_to_py_swig(SWIG_str_obs_key_event, (void*)event, 0, &py_swig_event);

    if (!SWIG_IsOK(SWIG_result)) {
        blog(LOG_INFO,
             "%s:l%i \"SWIG Failed to make required python object: '%s' for '%s'\"",
             __func__,
             __LINE__,
             SWIG_str_obs_key_event,
             py_src->py_source_info->id);
        goto fail;
    }

    argList = Py_BuildValue("(OOp)", py_data, py_swig_event, key_up );
    PyObject_CallObject(py_src->key_click,argList);
    if(pyHasError()){
	goto fail;
    }

 fail:
    Py_XDECREF(argList);
    Py_XDECREF(py_swig_event);
    PyGILState_Release(gstate);
}




//Only called in a python function.
static void py_to_obs_source_info(py_source* py_info)
{

    /*Should probably check that no other source already has this id*/
    struct obs_source_info* info = py_info->py_source_info;
    info->id               = PyUnicode_AsUTF8(py_info->id);
    info->type             = PyLong_AsLong(py_info->type);
    info->output_flags     = PyLong_AsLong(py_info->flags);

    //These functions suck.
    info->get_name         = py_source_get_name;
    info->get_defaults     = py_source_get_defaults;

    /*The rest of the function pointers point to generic function that use void *data .*/
    info->create           = py_source_create;
    info->destroy          = py_source_destroy;
    info->get_width        = py_source_get_width;
    info->get_height       = py_source_get_height;
    info->get_properties   = py_source_properties;
    info->update           = py_source_update;
    info->activate         = py_source_activate;
    info->deactivate       = py_source_deactivate;
    info->show             = py_source_show;
    info->hide             = py_source_hide;
    info->video_tick       = py_source_video_tick;
    info->video_render     = py_source_video_render;
    info->filter_video     = py_source_filter_video;
    info->filter_audio     = py_source_filter_audio;
    info->enum_sources     = py_source_enum_sources;
    info->save             = py_source_save;
    info->load             = py_source_load;
    info->mouse_click      = py_source_mouse_click;
    info->mouse_move       = py_source_mouse_move;
    info->mouse_wheel      = py_source_mouse_wheel;
    info->focus            = py_source_focus;
    info->key_click        = py_source_key_click;

};


