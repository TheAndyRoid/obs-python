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
#include <obs-module.h>
#include <obs-ui.h>

/*SWIG GENERATED FILES*/
#include "swig/libobs_wrap.c"

#include "py-source.h"


struct shutdown_func {
    char* name;
    PyObject* func;
    struct shutdown_func* next;
};







struct python_module {
    //struct shutdown_func* first;
    struct python_source* first;
    struct python_source* last;
};



//Need to use a global somewhere to store data
struct python_module py_module ;




static void* python_source_create(obs_data_t* settings, obs_source_t* source);
static void python_source_destroy(void* data);
static void python_source_update(void* data, obs_data_t* settings);
static void python_source_render(void* data, gs_effect_t* effect);
static void python_video_tick(void* data, float seconds);
static uint32_t python_source_get_width(void* data);
static uint32_t python_source_get_height(void* data);
static obs_properties_t* python_source_properties(void* unused);
static const char* python_source_get_name(void);



OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs-python", "en-US")
OBS_MODULE_AUTHOR("Andrew Skinner")
                                 




static struct obs_source_info python_source_info = {
    .id = "python_manager",
    .type = OBS_SOURCE_TYPE_INPUT,
    .output_flags = OBS_SOURCE_VIDEO,
    .get_name = python_source_get_name,
    .create = python_source_create,
    .destroy = python_source_destroy,
    .update = python_source_update,
    .get_width = python_source_get_width,
    .get_height = python_source_get_height,
    .video_render = python_source_render,
    .video_tick = python_video_tick,
    .get_properties = python_source_properties,
};





