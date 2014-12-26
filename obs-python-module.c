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


#include "obs-python-module.h"

#include <obs-module.h>
#include <obs-ui.h>
#include <util/platform.h>

#include "utils.h"
#include "py-obs.h"






void list_add_source(py_source* src)
{
    blog(LOG_INFO, "LIST_ADD_SOURCE");
    if(!py_module.first) {
        py_module.first = bzalloc(sizeof(struct python_source));
        py_module.first->source = src;
        return;
    }

    struct python_source* current = py_module.first;

    while(current->next != NULL) {
        current = current->next;
    }

    current->next = bzalloc(sizeof(struct python_source));
    current->next->prev = current;

    current->next->source = src;

}


struct python_source* list_find_source(const char* id)
{
    if(!py_module.first || !id) {
        return NULL;
    }
    blog(LOG_INFO, "LIST_FIND_SOURCE: %s",id);
    struct python_source* current = py_module.first;
    do {
        blog(LOG_INFO, "LIST_FOUND_SOURCE: %s",current->source->py_source_info->id);
        if(strcmp(current->source->py_source_info->id,id) == 0) {
            return current;
        }
        current = current->next;
    } while(current != NULL);

    return NULL;

}



py_source* list_remove_source(const char* id,py_source *self)
{
    blog(LOG_INFO, "LIST_REMOVE_SOURCE");
    struct python_source* remove = list_find_source(id);
    if(!remove) {
        return NULL;
    }
    if(self != remove->source){
      //can only remove registerd source
      return NULL;
    }
    py_source* tmp = remove->source;

    if(remove->next == NULL && remove->prev == NULL) {
        //Last Item in list
        py_module.first = NULL;
    } else if(remove->next == NULL) {
        //end of the list
        remove->prev->next=NULL;
    } else {
        if(remove->prev == NULL) {
            //front of the list
            remove->next->prev = NULL;
            py_module.first = remove->next;
        } else {
            //mid list
            remove->prev->next = remove->next->next;
            remove->next->prev = remove->prev->prev;
        }
    }

    bfree(remove);
    return tmp;
}



bool obs_module_load()
{
    blog(LOG_INFO, "obs_module_load");
    //Need to init python here


    //Load the OBS Extension
    PyImport_AppendInittab("OBS", py_obs_init);

    //load the swig
    PyImport_AppendInittab("_libobs", PyInit__libobs);

    Py_Initialize();
    PyEval_InitThreads();
 
     

    /*Must set arguments for guis to work*/

    wchar_t* argv[] = { L"OBS", NULL };
    int argc = sizeof(argv) / sizeof(wchar_t*) - 1;
  
    SWIG_init();


    PySys_SetArgv(argc, argv);
   
    //need to add to directory

    PyRun_SimpleString("import os");
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("os.environ['PYTHONUNBUFFERED'] = '1'");
    PyRun_SimpleString("sys.stdout = open('/dev/shm/stdOut.txt','w',1)");
    PyRun_SimpleString("sys.stderr = open('/dev/shm/stdErr.txt','w',1)");
    PyRun_SimpleString("import OBS");
 

   /*Load a file*/
    
    
    PyObject* pName, *pModule, *pFunc,*argList;
    


    pName = PyUnicode_FromString("source");

    char script[] = "/scripts";
    char *data_path = obs_get_module_data_path(obs_current_module());
    char *scripts_path = bzalloc(strlen(data_path)+strlen(script));
    strcpy(scripts_path,data_path);
    strcat(scripts_path,script);


    //Add the path to env
    add_to_python_path(scripts_path);
    bfree(scripts_path);

    /*Import libobs*/
    PyImport_ImportModule("libobs");

    //import the script
    pModule = PyImport_Import(pName);
     pyHasError();
    //get the function by name
    if(pModule != NULL) {
        pFunc = PyObject_GetAttr(pModule, PyUnicode_FromString("register"));
        if(pFunc != NULL) {
	  argList = Py_BuildValue("()");
            PyObject_CallObject(pFunc,argList);
 	     pyHasError();
	    Py_XDECREF(pFunc);
	    Py_XDECREF(argList);
        }
	Py_XDECREF(pModule);
    }
    Py_XDECREF(pName);
    




    /*
    PyRun_SimpleString("print('test')");
    PyRun_SimpleString("import OBS");
    PyRun_SimpleString("a = OBS.Source()");

    if(pyHasError()) {
        return false;
    }
    
    PyRun_SimpleString("OBS.log(str(type(a)))");
    PyRun_SimpleString("OBS.log(a.id)");
    PyRun_SimpleString("OBS.log('Module Load')");
    PyRun_SimpleString("OBS.obs_register_source(a)");
    */


    //Not implemented yet?
    //obs_register_modal_ui(&myui);

    //Register this base class here
    obs_register_source(&python_source_info);
    


    //Release the thread gill
    PyThreadState* pts = PyGILState_GetThisThreadState();
    PyEval_ReleaseThread(pts);




    return true;
}

void obs_module_unload()
{
    //Shutdown python and call shutdown functions
    blog(LOG_INFO, "obs_module_unload");


    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //Decrement refrance counter.
    //Garbage collection will sort free
    if(py_module.first != NULL){
      struct python_source* current = py_module.first;
      do
	{
	  Py_XDECREF(current->source);
	  current = current->next;
	} while(current != NULL);
    }   
    


    blog(LOG_INFO, "obs_module_unload");
    UNUSED_PARAMETER(gstate);

    if (Py_IsInitialized()) {
        Py_Finalize();
    }
    blog(LOG_INFO, "obs_module_unload");


}
static const char* python_source_get_name(void)
{
    return obs_module_text("PythonManager" );
}
static void* python_source_create(obs_data_t* settings, obs_source_t* source)
{

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    PyRun_SimpleString("OBS.log('python_source_create with python YAYPyRun_SimpleString')");

    UNUSED_PARAMETER(source);
    //Create the new source here




    obs_data_t* font_obj = obs_data_create();
    obs_data_set_default_string(settings, "text","The lazy.");
    obs_data_release(font_obj);




    /*
        obs_register_source(py_module.tmp->src_info);

        // This creates a new source.
        obs_source_t* source = obs_get_output_source(0); //gets output source?
        obs_scene_t* current_scene = obs_scene_from_source(source);
        char* name = "TESTING";
        source = obs_get_source_by_name(name);
        if(source) {
      //source already exists, just add to scene
            obs_scene_add(current_scene,source);

        } else {
            source = obs_source_create(OBS_SOURCE_TYPE_INPUT,"python_source",name,NULL);
            obs_add_source(source);
            obs_scene_add(current_scene,source);

        }

        obs_source_release(source);
        obs_scene_release(current_scene);

    */
    PyGILState_Release(gstate);
    return &python_source_info;
}
static void python_source_destroy(void* data)
{
    blog(LOG_INFO, "python_source_destroy");
    //Destroy the source here
    UNUSED_PARAMETER(data);
    //bfree(data);

}
static void python_source_update(void* data, obs_data_t* settings)
{
    blog(LOG_INFO, "python_source_update");
    //Update the python source here
    UNUSED_PARAMETER(data);
    UNUSED_PARAMETER(settings);
}
static uint32_t python_source_get_width(void* data)
{
    //blog(LOG_INFO, "python_source_get_width");
    UNUSED_PARAMETER(data);
    return 500;
}
static uint32_t python_source_get_height(void* data)
{
    //blog(LOG_INFO, "python_source_get_height");
    UNUSED_PARAMETER(data);
    return 500;
}
static void python_source_render(void* data ,gs_effect_t* effect)
{
    //Called each frame
    UNUSED_PARAMETER(data);
    UNUSED_PARAMETER(effect);


    //blog(LOG_INFO, "python_source_render");
    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    //PyRun_SimpleString("print('render')");


    PyGILState_Release(gstate);
}
static void python_video_tick(void* data,float seconds)
{
    //blog(LOG_INFO, "python_video_tick");
    UNUSED_PARAMETER(data);
    UNUSED_PARAMETER(seconds);
    //called at a set interval.
}
static obs_properties_t* python_source_properties(void* data)
{

    UNUSED_PARAMETER(data);
    obs_properties_t* props = obs_properties_create();
    obs_properties_add_text(props, "text",obs_module_text("Text"), OBS_TEXT_MULTILINE);

    return props;
}



