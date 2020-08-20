//
// Created by Mokhairy on 7/20/2020.
//
/** @file zsForwardDeclarations.h

    @brief Provides forward declarations of types and structs.

    Author(s): Mohamed Mahmoud
*/

#ifndef ZSIM_ZSFORWARDDECLARATIONS_H
#define ZSIM_ZSFORWARDDECLARATIONS_H
// STD includes
#include <vector>
#include <iterator>
#include <set>
#include <map>
#include <stack>
#include <algorithm>
#include <functional>
#include <limits>

#include <zsCore/zsConfig.h>
#include <zsCore/zsDebug.h>
#include <zsCore/zsExport.h>
#include <zsCore/zsMemory.h>
//#include <zsUtils/zsUtils.h>

namespace zsim
{

    template<class T = real_t, int _Rows=-1, int _Cols=-1,
            int _Options  = 0|((_Rows==1 && _Cols!=1)?0x1:0)> class zsMatrix;
    template<class T = real_t, int _Rows=-1, int _Options = 0> class zsVector;

    template<class T= real_t, int _Rows=-1, int _Cols=-1> class zsAsConstMatrix;
    template<class T= real_t, int _Rows=-1, int _Cols=-1> class zsAsMatrix;

    template<class T= real_t, int _Rows=-1> class zsAsVector;
    template<class T= real_t, int _Rows=-1> class zsAsConstVector;

    template<class T = real_t> class zsVector3d;

    template<typename T=real_t, int _Options=0, typename _Index = index_t>
    class zsSparseMatrix;

    template<typename T=real_t, int _Options=0, typename _Index = index_t>
    class zsSparseVector;

    template <class T=real_t>                class zsSparseEntries;


} // end namespace zsim

#endif //ZSIM_ZSFORWARDDECLARATIONS_H
