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




bool obs_module_load()
{
    blog(LOG_INFO, "obs_module_load");


    Py_Initialize();
    PyEval_InitThreads();
 

    /*Must set arguments for guis to work*/
    wchar_t* argv[] = { L"", NULL };
    int argc = sizeof(argv) / sizeof(wchar_t*) - 1;
  

    PySys_SetArgv(argc, argv);

    /* Setup logs to a safe place can be changed by user in OBSPythonManager.py register function*/
    PyRun_SimpleString("import os");
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("os.environ['PYTHONUNBUFFERED'] = '1'");
    /* TODO  change to non platform specific */
    PyRun_SimpleString("sys.stdout = open('/dev/shm/stdOut.txt','w',1)");
    PyRun_SimpleString("sys.stderr = open('/dev/shm/stdErr.txt','w',1)");
    PyRun_SimpleString("print(sys.version)");

    
    /*Load manager from file*/    
    PyObject* pName = NULL;
    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyObject* argList = NULL;

    bool ret = false;

    char script[] = "/scripts";
    const char *data_path = obs_get_module_data_path(obs_current_module());
    char *scripts_path = bzalloc(strlen(data_path)+strlen(script));
    strcpy(scripts_path,data_path);
    strcat(scripts_path,script);


    //Add the scripts path to env
    add_to_python_path(scripts_path);


    /* load the obspython library and extend with manually written functions/objects  */
    PyObject *py_libobs = PyImport_ImportModule("obspython");
    ret = pyHasError();
    if (ret){
      blog(LOG_INFO,
	   "%s:l%i \"Error importing '%s/obspython.py' unloading obs-python\"",
	   __func__,
	   __LINE__,
	   scripts_path
	   );
      goto out;
    }

    extend_swig_libobs(py_libobs);


    //Import the manager script
    pName = PyUnicode_FromString("OBSPythonManager");
    pModule = PyImport_Import(pName);

    ret = pyHasError();
    if (ret){
      blog(LOG_INFO,
	     "%s:l%i \"Error loading '%s/OBSPythonManager.py' unloading obs-python\"",
	     __func__,
	     __LINE__,
	     scripts_path
	     );
      goto out;
    }
    
    //get the function by name
    if(pModule != NULL) {
      PyModule_AddObject(pModule,"obspython",py_libobs);
      pFunc = PyObject_GetAttr(pModule, PyUnicode_FromString("obs_module_load"));
        if(pFunc != NULL) {
	  argList = Py_BuildValue("()");
            PyObject_CallObject(pFunc,argList);
	    ret = pyHasError();
	    if (ret){
	      blog(LOG_INFO,
		   "%s:l%i \"Error running 'register' function in '%s/OBSPythonManager.py' unloading obs-python\"",
		   __func__,
		   __LINE__,
		   scripts_path
		   );
	      goto out;
	    }
	}else{
	  ret = pyHasError();
	  blog(LOG_INFO,
	       "%s:l%i \"Could not find register function in '%s/OBSPythonManager.py' unloading obs-python\"",
	       __func__,
	       __LINE__,
	       scripts_path
	       );
	}
	goto out;
    }

 out:
    bfree(scripts_path);    
    Py_XDECREF(pFunc);
    Py_XDECREF(argList);
    Py_XDECREF(pModule);
    Py_XDECREF(pName); 
    //Release the thread GIL
    PyThreadState* pts = PyGILState_GetThisThreadState();
    PyEval_ReleaseThread(pts);
    if(!ret){    
       return true;
    }else{    
        obs_module_unload();
        return false;
    }
}

void obs_module_unload()
{
    //Shutdown python and call shutdown functions
    blog(LOG_INFO, "obs_module_unload");

    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    UNUSED_PARAMETER(gstate);

    if (Py_IsInitialized()) {
        Py_Finalize();
    }

}

