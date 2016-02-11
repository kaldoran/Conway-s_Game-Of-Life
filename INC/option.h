#ifndef OPT
#define OPT

#include "option_struct.h"

#define OPT_LIST "hf:t:np:r:c:" // FILE

/** Use the definition defined by David Titarenco
 *  On StackOverFlow http://stackoverflow.com/questions/3437404/min-and-max-in-c
 */
#define MAX(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

void usage(char* name);

Option getOption(int argc, char** argv);

#endif
