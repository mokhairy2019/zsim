/** @file linearSolvers_example.cpp

    @brief Example on how the solve a system of linear equations with
    ZSIM's own iterative solvers and Eigen's direct and iterative
    solvers.

    Author(s): Mohamed Mahmoud
*/

#include <iostream>

#include "zsim.h"


using namespace zsim;

//Create a tri-diagonal matrix with -1 of the off diagonals and 2 in the diagonal.
//This matrix is equivalent to discretizing the 1D Poisson equation with homogenius
//Dirichlet boundary condition using a finite difference method. It is a SPD matrix.
//The solution is sin(pi*x);
void poissonDiscretization(zsSparseMatrix<> &mat, zsMatrix<> &rhs, index_t N)
{
rhs.setZero(N,1);

mat.resize(N,N);
mat.setZero();
real_t meshSize = 1./(N+1);
real_t pi = EIGEN_PI;

//Reserving space in the sparse matrix (Speeds up the assemble time of the matrix)
mat.reservePerColumn( 3 ); //Reserve 3 non-zero entry per column

mat(0,0) = 2;
mat(0,1) = -1;
mat(N-1, N-1) = 2;
mat(N-1, N-2) = -1;
for (index_t k = 1; k < N-1; ++k)
{
mat(k,k) = 2;
mat(k,k-1) = -1;
mat(k,k+1) = -1;
}
for (index_t k = 0; k < N; ++k)
rhs(k,0) = pi*pi*meshSize*meshSize*math::cos(meshSize*(1+k)*pi);

//Compress the matrix
mat.makeCompressed();
}

//Print out information of the iterative solver
template<typename SolverType>
void zsIterativeSolverInfo(const SolverType &method,
real_t error, double time, bool& succeeded )
{
zsInfo << method.detail();
zsInfo << " Computed res. error  : " << error << "\n";
zsInfo << " Time to solve:       : " << time << "\n";
if ( method.error() <= method.tolerance() && error <= method.tolerance() )
{
zsInfo <<" Test passed.\n";
}
else
{
zsInfo <<" TEST FAILED!\n";
succeeded = false;
}
}

int main(int argc, char *argv[])
{
    bool succeeded = true;

    index_t N = 100;
    //Tolerance
    real_t tol = std::pow(10.0, - REAL_DIG * 0.75);

    zsSparseMatrix<> mat;
    zsMatrix<> rhs;

    //Assembly of 1D poission equaiton
    poissonDiscretization(mat, rhs, N);

    //The minimal residual implementation requires a preconditioner.
    //We initialize an identity preconditioner (does nothing).
    //TODO implament the linear operatoer later in zsSolvers
    //zsLinearOperator<>::Ptr preConMat = zsIdentityOp<>::make(N);

    zsStopwatch clock;
    zsMatrix<> x0;

#ifndef GISMO_WITH_MPQ
    //Maximum number of iterations
    index_t maxIters = 3*N;
    ///----------------------EIGEN-ITERATIVE-SOLVERS----------------------///
    zsInfo << "\nTesting Eigen's interative solvers:\n";

    zsSparseSolver<>::CGIdentity EigenCGIsolver;
    EigenCGIsolver.setMaxIterations(maxIters);
    EigenCGIsolver.setTolerance(tol);
    zsInfo << "\nEigen's CG + identity prec.: Started solving... ";
    clock.restart();
    EigenCGIsolver.compute(mat);
    x0 = EigenCGIsolver.solve(rhs);
    zsInfo << "done.\n";
    zsIterativeSolverInfo(EigenCGIsolver, (mat*x0-rhs).norm()/rhs.norm(), clock.stop(), succeeded);

    zsSparseSolver<>::CGDiagonal EigenCGDsolver;
    EigenCGDsolver.setMaxIterations(maxIters);
    EigenCGDsolver.setTolerance(tol);
    zsInfo << "\nEigen's CG + diagonal prec.: Started solving... ";
    clock.restart();
    EigenCGDsolver.compute(mat);
    x0 = EigenCGDsolver.solve(rhs);
    zsInfo << "done.\n";
    zsIterativeSolverInfo(EigenCGDsolver, (mat*x0-rhs).norm()/rhs.norm(), clock.stop(), succeeded);

    zsSparseSolver<>::BiCGSTABIdentity EigenBCGIsolver;
    EigenBCGIsolver.setMaxIterations(maxIters);
    EigenBCGIsolver.setTolerance(tol);
    zsInfo << "\nEigen's bi conjugate gradient stabilized + identity prec.: Started solving... ";
    clock.restart();
    EigenBCGIsolver.compute(mat);
    x0 = EigenBCGIsolver.solve(rhs);
    zsInfo << "done.\n";
    zsIterativeSolverInfo(EigenBCGIsolver, (mat*x0-rhs).norm()/rhs.norm(), clock.stop(), succeeded);

    zsSparseSolver<>::BiCGSTABDiagonal EigenBCGDsolver;
    EigenBCGDsolver.setMaxIterations(maxIters);
    EigenBCGDsolver.setTolerance(tol);
    zsInfo << "\nEigen's bi conjugate gradient stabilized solver + diagonal prec.: Started solving... ";
    clock.restart();
    EigenBCGDsolver.compute(mat);
    x0 = EigenBCGDsolver.solve(rhs);
    zsInfo << "done.\n";
    zsIterativeSolverInfo(EigenBCGDsolver, (mat*x0-rhs).norm()/rhs.norm(), clock.stop(), succeeded);

    zsSparseSolver<>::BiCGSTABILUT EigenBCGILUsolver;
    //EigenBCGILUsolver.preconditioner().setFillfactor(1);
    EigenBCGILUsolver.setMaxIterations(maxIters);
    EigenBCGILUsolver.setTolerance(tol);
    zsInfo << "\nEigen's bi conjugate gradient stabilized solver + ILU prec.: Started solving... ";
    clock.restart();
    EigenBCGILUsolver.compute(mat);
    x0 = EigenBCGILUsolver.solve(rhs);
    zsInfo << "done.\n";
    zsIterativeSolverInfo(EigenBCGILUsolver, (mat*x0-rhs).norm()/rhs.norm(), clock.stop(), succeeded);

    ///----------------------EIGEN-DIRECT-SOLVERS----------------------///
    zsSparseSolver<>::SimplicialLDLT EigenSLDLTsolver;
    zsInfo << "\nEigen's Simplicial LDLT: Started solving... ";
    clock.restart();
    EigenSLDLTsolver.compute(mat);
    x0 = EigenSLDLTsolver.solve(rhs);
    zsInfo << "done.\n";
    zsInfo << "Eigen's Simplicial LDLT: Time to solve       : " << clock.stop() << "\n";

    zsSparseSolver<>::QR solverQR;
    zsInfo << "\nEigen's QR: Started solving... ";
    clock.restart();
    solverQR.compute(mat);
    x0 = solverQR.solve(rhs);
    zsInfo << "done.\n";
    zsInfo << "Eigen's QR: Time to solve       : " << clock.stop() << "\n";

#endif

    zsSparseSolver<>::LU solverLU;
    zsInfo << "\nEigen's LU: Started solving... ";
    clock.restart();
    solverLU.compute(mat);
    x0 = solverLU.solve(rhs);
    zsInfo << "done.\n";
    zsInfo << "Eigen's LU: Time to solve       : " << clock.stop() << "\n";
    return succeeded ? EXIT_SUCCESS : EXIT_FAILURE;
}



