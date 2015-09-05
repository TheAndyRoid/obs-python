%module(threads="1") obspython
%nothread;
%{
#define SWIG_FILE_WITH_INIT
#include "libobs/graphics/graphics.h"
#include "libobs/obs.h"
#include "libobs/obs-source.h"
#include "libobs/obs-data.h"
#include "libobs/obs-properties.h"
%}

#define EXPORT 
%include "stdint.i"

%typemap(in) uint8_t *data{
  if(!PyByteArray_Check($input))
  {
    SWIG_exception_fail(SWIG_TypeError, "Expected a bytearray");
  }
 $1 = PyByteArray_AsString($input); 
}


%typemap(in) uint8_t **data (uint8_t *tmp){
  if(!PyByteArray_Check($input))
  {
    SWIG_exception_fail(SWIG_TypeError, "Expected a bytearray");
  }
  tmp  = PyByteArray_AsString($input); 
  $1 = &tmp;
 }


%ignore obs_source_info;


%ignore obs_register_source_s(const struct obs_source_info *info, size_t size);
%ignore obs_output_set_video(obs_output_t *output, video_t *video);
%ignore obs_output_video(const obs_output_t *output);

%include "libobs/graphics/graphics.h"
%include "libobs/obs-data.h"
%include "libobs/obs-source.h"
%include "libobs/obs-properties.h"

 /*declare these manually because mutex + GIL = deadlocks*/
%thread;
void obs_enter_graphics(void); //Should only block on entering mutex
%nothread;
%include "libobs/obs.h"


