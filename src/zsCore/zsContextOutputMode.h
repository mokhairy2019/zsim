//
// Created by Mokhairy on 7/20/2020.
//

#ifndef ZSIM_ZSCONTEXTOUTPUTMODE_H
#define ZSIM_ZSCONTEXTOUTPUTMODE_H

namespace zsim {
    enum zsContextOutputMode {
        COM_NoContext,     ///< No context.
        COM_Always,        ///< Enable for post-processing.
        COM_Required,      ///< If required (for backtracking computation).
        COM_UserDefined,   ///< Input attribute of domain (each n-th step).
    };

}


#endif //ZSIM_ZSCONTEXTOUTPUTMODE_H
