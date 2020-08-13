/** @file zsim.h

    @brief Main header to be included by clients using the zsim library.

*/

#ifndef ZSIM_ZSIM_H
#define ZSIM_ZSIM_H

/** @namespace zsim

    @brief
    The \zsim namespace, containing all definitions for the library.
*/
namespace zsim
{
    /** @namespace zsim::internal

    @brief
    This namespace contains functionalities that is internal to the library.
*/
    namespace internal
    { }
}

/*---------- core ----------------*/
#include "zsCore/zsForwardDeclarations.h"
#include "zsCore/zsLinearAlgebra.h"
#include "zsCore/zsEngngModel.h"


#endif //ZSIM_ZSIM_H
