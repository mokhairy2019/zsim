//
// Created by Mokhairy on 7/19/2020.
//

#ifndef ZSIM_ZSLINEARALGEBRA_H
#define ZSIM_ZSLINEARALGEBRA_H

#include <zsCore/zsMath.h>

//#define eigen_assert( cond ) GISMO_ASSERT( cond, "" )

// Plugin provides extra members
#define EIGEN_MATRIXBASE_PLUGIN <zsMatrix/zsMatrixAddons.h>
#include <zsMatrix/zsEigenDeclarations.h>

#include <Eigen/Core>

#if defined(GISMO_WITH_MPFR)
#include <unsupported/Eigen/MPRealSupport>
#endif

#if defined(GISMO_WITH_MPQ)
#include <unsupported/Eigen/MPQClassSupport>
#endif

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/StdVector>

// Extra Eigen code
#include <zsMatrix/Adjugate.h>
#include <zsMatrix/BlockDiag.h>
#include <zsMatrix/BlockTranspose.h>
//#include <zsMatrix/RowSelection.h>

#ifdef GISMO_WITH_SUPERLU
#include <Eigen/SuperLUSupport>
#endif

#ifdef GISMO_WITH_PARDISO
#include <Eigen/PardisoSupport>
#endif

#ifdef GISMO_WITH_PASTIX
#include <Eigen/PaStiXSupport>
#endif

// sparsesuite
//#include <Eigen/UmfPackSupport>
//#include <Eigen/SPQRSupport>
//#include <Eigen/CholmodSupport>

// METIS
//#include <Eigen/MetisSupport>

// PaStiX
//#include <Eigen/PaStiXSupport>



namespace zsim{

    using Eigen::internal::cast;
    //TODO: insert the functions related to the linear algebra module

    using Eigen::Dynamic;
    using Eigen::Lower;
    using Eigen::Upper;

    // Values for matrix align options
    using Eigen::RowMajor;//=0
    using Eigen::ColMajor;//=1
    using Eigen::AutoAlign;//=0

    template<class T, int _Rows, int _cols> class zsAsMatrix;
    template<class T, int _Rows, int _cols> class zsAsConstMatrix;

    template<class T, int _Rows> class zsAsVector;
    template<class T, int _Rows> class zsAsConstVector;


    // helper template for changing the dimension of a matrix
    template <int Dim, int Change>
    struct ChangeDim
    {
        enum { D = Change+Dim<0 ? 0 : Dim + Change };
    };
    template <int Change>
    struct ChangeDim<Dynamic, Change>
    {
        enum { D = Dynamic };
    };


}

#include <zsMatrix/zsMatrixBlockView.h>
#include <zsMatrix/zsMatrix.h>
#include <zsMatrix/zsVector.h>
#include <zsMatrix/zsAsMatrix.h>
#include <zsMatrix/zsSparseMatrix.h>
#include <zsMatrix/zsSparseVector.h>
/*#include <zsMatrix/zsSparseSolver.h>
#include <zsMatrix/zsPoint.h>*/

#endif //ZSIM_ZSLINEARALGEBRA_H
