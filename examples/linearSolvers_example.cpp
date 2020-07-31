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
void poissonDiscretization(gsSparseMatrix<> &mat, gsMatrix<> &rhs, index_t N)
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
void gsIterativeSolverInfo(const SolverType &method,
real_t error, double time, bool& succeeded )
{
gsInfo << method.detail();
gsInfo << " Computed res. error  : " << error << "\n";
gsInfo << " Time to solve:       : " << time << "\n";
if ( method.error() <= method.tolerance() && error <= method.tolerance() )
{
gsInfo <<" Test passed.\n";
}
else
{
gsInfo <<" TEST FAILED!\n";
succeeded = false;
}
}

int main(int argc, char *argv[])
{

    return succeeded ? EXIT_SUCCESS : EXIT_FAILURE;
}



