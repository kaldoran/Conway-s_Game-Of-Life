#ifndef OPT
#define OPT

#include <stdbool.h>
#include "option_struct.h"

#define OPT_LIST_DEFAULT "hf:t:n" // FILE

#if defined(PARA_G) || defined(PARA_F)
	#define OPT_LIST OPT_LIST_DEFAULT  "p:"
#else
	#define OPT_LIST OPT_LIST_DEFAULT
#endif

void usage(char* name);

Option getOption(int argc, char** argv);

#endif
