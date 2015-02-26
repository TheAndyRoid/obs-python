%module(threads="1") libobs
%nothread;
%{
#define SWIG_FILE_WITH_INIT




#include "../../../libobs/graphics/graphics.h"
#include "../../../libobs/obs.h"
#include "../../../libobs/obs-data.h"


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


%include "../../../libobs/graphics/graphics.h"
%include "../../../libobs/obs-data.h"




 /*declare these manually because mutex + GIL = deadlocks*/
%thread;
void obs_enter_graphics(void); //Should only block on entering mutex
%nothread;
%include "../../../libobs/obs.h"


