%module(threads="1") libobs
%nothread;
%{
#define SWIG_FILE_WITH_INIT




#include "../../../libobs/graphics/graphics.h"
#include "../../../libobs/obs.h"


%}

#define EXPORT 
%include "stdint.i"

%typemap(in) uint8_t *data{
 $1 = PyByteArray_AsString($input); 
}

%typemap(in) uint8_t **data (uint8_t *tmp){
  tmp = PyByteArray_AsString($input); 
  $1 = &tmp;
}


%include "../../../libobs/graphics/graphics.h"




 /*declare these manually cause mutex + GIL = deadlocks*/
%thread;
void obs_enter_graphics(void);
//void obs_leave_graphics(void);
%nothread;
%include "../../../libobs/obs.h"


