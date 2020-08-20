//
// Created by Mokhairy on 8/11/2020.
//

#ifndef ZSIM_ZSCONTEXTMODE_H
#define ZSIM_ZSCONTEXTMODE_H

namespace zsim {
/**
 * Context mode (mask), defining the type of information written/read to/from context
 */
//typedef unsigned long ContextMode;
    typedef long zsContextMode;
/* Mask selecting status */
#define CM_None         0
#define CM_State        ( 1L << 1 )
#define CM_Definition   ( 1L << 2 )
#define CM_DefinitionGlobal ( 1L << 3 )
#define CM_UnknownDictState ( 1L << 4 )
}
#endif //ZSIM_ZSCONTEXTMODE_H
