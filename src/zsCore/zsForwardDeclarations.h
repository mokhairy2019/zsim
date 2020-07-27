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
//#include <zsCore/zsExport.h>  // included by zsMemory.h
#include <zsCore/zsMemory.h>
//#include <zsUtils/zsUtils.h>

namespace zsim
{
    // Engineering models objects
    class zsEngngModelContext;
    class zsDomain;
    class zsTimeStep;
    class zsDof;
    class zsDofManager;
    class zsDataReader;
    class zsDataStream;
    class zsErrorEstimator;
    class zsMetaStep;
    class zsMaterialInterface;
    class zsSparseMtrx;
    class zsNumericalMethod;
    class zsFloatMatrix;
    class zsFloatArray;
    class zsLoadBalancer;
    class zsLoadBalancerMonitor;
    class zsGraphicContext;
    class zsProblemCommunicator;
    class zsProcessCommunicatorBuff;
    class zsCommunicatorBuff;
    class zsProcessCommunicator;
    class zsUnknownNumberingScheme;


    template<class T = real_t, int _Rows=-1, int _Cols=-1,
            int _Options  = 0|((_Rows==1 && _Cols!=1)?0x1:0)> class zsMatrix;
    template<class T = real_t, int _Rows=-1, int _Options = 0> class zsVector;

} // end namespace zsim

#endif //ZSIM_ZSFORWARDDECLARATIONS_H
