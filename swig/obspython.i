%module(threads="1") obspython
%nothread;
%{
#define SWIG_FILE_WITH_INIT
  //#define SWIG_PYTHON_SAFE_CSTRINGS
#define PDEPRECATED_START 
#define DEPRECATED_END
#include "graphics/graphics.h"
#include "obs.h"
#include "obs-source.h"
#include "obs-data.h"
#include "obs-properties.h"
#include "obs-module.h"
#include "obs-interaction.h"
#include "util/bmem.h"
%}
 
#define DEPRECATED_START 
#define DEPRECATED_END
#define EXPORT 

%include "stdint.i"

%typemap(in) uint8_t *data {
	if(!PyByteArray_Check($input))
	{
		SWIG_exception_fail(SWIG_TypeError, "Expected a bytearray");
	}
	$1 = PyByteArray_AsString($input);
}


%typemap(in) uint8_t **data (uint8_t *tmp)
{
	if(!PyByteArray_Check($input)) {
		SWIG_exception_fail(SWIG_TypeError, "Expected a bytearray");
	}
	tmp  = PyByteArray_AsString($input);
	$1 = &tmp;
}


/*buf and alloc are expected*/
%typemap(in) const char *(Py_ssize_t len, char *buf, PyObject *py_bytes,
                          int alloc)
{
	alloc =  SWIG_OLDOBJ; // We don't want swig to attempt to free this mem
	/*Python 3 Only*/
	if (!PyUnicode_Check($input)) {
		SWIG_exception_fail(SWIG_TypeError, "Expected a string");
	}

	py_bytes = PyUnicode_AsUTF8String($input);
	/* Keep this bytes object around cause fck memory managment for now
	   It would probably be better to use some sort of cache for this,
	   which would need to be global and have fast insert and search
	   or
	   We could force the user to cache the strings themselfs, sit back
	   back and laugh
	 */
	Py_INCREF(py_bytes); //never let go jack

	PyBytes_AsStringAndSize(py_bytes, &buf, &len);
	$1 = buf;
}




%ignore obs_source_info;

 /* Used to free when using %newobject */
%typemap(newfree) char * "bfree($1);";

%ignore obs_module_text;
%ignore obs_source_info;

%ignore obs_register_source_s(const struct obs_source_info *info, size_t size);
%ignore obs_output_set_video(obs_output_t *output, video_t *video);
%ignore obs_output_video(const obs_output_t *output);
%include "graphics/graphics.h"
%include "obs-data.h"
%include "obs-source.h"
%include "obs-properties.h"
%include "obs-interaction.h"


 /* Declare that this returns something to free  */
%newobject obs_module_get_config_path;
%newobject obs_find_module_file;
%ignore obs_current_module;
%include "obs-module.h"


%include "util/bmem.h"

 /*declare these manually because mutex + GIL = deadlocks*/
%thread;
void obs_enter_graphics(void); //Should only block on entering mutex
%nothread;
%include "obs.h"


