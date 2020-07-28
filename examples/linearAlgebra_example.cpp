//
// Created by Mokhairy on 7/26/2020.
//
#include <iostream>

#include "zsim.h"

using namespace zsim;

int main(int argcm, char** argv){

    zsInfo << "Zsim uses Eigen v"<< EIGEN_WORLD_VERSION<<"."
           <<EIGEN_MAJOR_VERSION<<"."<<EIGEN_MINOR_VERSION
           <<" for matrix computations.\n";

    // A matrix with entries of type real_t, and allocated size 3x3
    zsMatrix<real_t> A (3,3);
    // The comman initializer lets us fill the matrix. Note that the
    // matrix must have the correct size for this to work
    A << 2,2,3,  4,5,6,  7,8,10;
    A(0,0) -= 1 ;

    // If the type of the entries of the matrix is not given, the
    // default type is real_t (e.g. double)
    zsMatrix<> E (3,1);
    zsVector<> c (3);
    E << 2,2,3 ;

    // Even if two matrices do not have the same size we can assign one
    // to the other and the result will be two identical matrices
    c = E ;
    // Similary we can assign a column or any other expression to a
    // matrix variable
    c = A.col(1) ;

    // The two extra arguments are the number of rows and columns,
    // statically known at compile time
    zsMatrix<real_t,2,2> F ;
    F << 2,2,3, 4 ;
    zsVector<> w (2);
    w= F.row(1);

    zsInfo << "vector c:\n" << c <<"\n"<< E << "\n";

    zsInfo << "vector as diagonal:\n" << zsMatrix<>( c.asDiagonal() ) << "\n";

    zsInfo << "E.sum():\n" << E.sum() << "\n";

    zsInfo << "dyn: " << Dynamic << "\n";

    zsVector<> b (3);
    b << 3, 3, 4;

    zsInfo << "Here is the matrix A:\n" << A << "\n";
    zsInfo << "Here is the vector b:\n" << b << "\n";


    zsInfo << "Size of A: " << A.rows() << " x " << A.cols()  << "\n";
    zsInfo << "Determinant of A: "<< A.determinant()  << "\n";
    zsInfo << "Transpose of A:\n"<< A.transpose()  << "\n";

    // Note that A.transpose() does not alter A, but only returns an
    // expression of its transpose.
    // We can transpose A in place as follows:
    A.transposeInPlace();
    A.transposeInPlace();//second transposition results in the original A matrix

    // Note that A.inverse() does not alter A. To save the inverse in place of A use
    // A.inverseInPlace()
    zsInfo << "Inverse of A:\n"<< A.inverse()  << "\n";

    // We can initialize a matrix using other matrices by "<<"
    // Note that AAA must have the right size!
    zsMatrix<> AAA(3,12);
    AAA << A, A.transpose(), A.adjoint().eval(), A;
    zsInfo << "A block matrix containing [A, A.tranpose(), A.adjugate(), A] :\n"<< AAA  << "\n";
    AAA.blockTransposeInPlace(3);
    zsInfo << "Block-wise transposition of the above:\n"<< AAA  << "\n";
    AAA.blockTransposeInPlace(6);
    zsInfo << "Block-wise transposition of the above seen as 3x6 blocks:\n"<< AAA  << "\n";

    zsVector<index_t> perm(3);
    perm << 2,1,0;
    zsInfo << "Here is the row permutation ("<<perm.transpose()<<") of matrix A:\n"
           << perm.asPermutation() * A << "\n";
    zsInfo << "Here is the column permutation ("<<perm.transpose()<<") of matrix A:\n"
           <<  A * perm.asPermutation() << "\n";

    zsInfo << "Here is the matrix A:\n" << A << "\n";

    zsInfo << "Here is the max of perm:\n" << perm.isZero() << "\n";

    zsVector<> x;
    // Computes a factorization (LU,QR) and solves Ax=b for the unknown x using
    // this factorization
    x= A.partialPivLu().solve(b);
    //x= A.fullPivLu().solve(b);
    //x= A.colPivHouseholderQr().solve(b);
    zsInfo << "The solution of Ax=b is:\n" << x << "\n";
    zsInfo << "Verification, A*x is:\n" << A*x << "\n";

    zsInfo << "The dot product x.b is : " <<  x.transpose()* b<< "\n"; //x.dot(b)
    zsInfo << "The dot product x.b is : " <<  x.dot( b )<< "\n"; //x.dot(b)

    zsInfo << "The product x*bt is : \n" << x *  b.transpose() << "\n";

    zsMatrix<> M  = x *  b.transpose() ;

    zsMatrix<real_t,3,3> W;

    W << 2,2,3,  4,5,6,  7,8,10;
    zsMatrix<> R2 = W * W ; //x * b.transpose() ;

    zsInfo << "Block of A of size (2,2), starting at (1,1):\n"<< A.block<2,2>(1,1) << "\n";
    // if the block size is not known at compile time:  A.block(1,1,2,2) << "\n";

    zsInfo << "Reverse matrix:\n"<< A.colwise().reverse() << "\n";

 /*   zsSparseMatrix<> B(3,3);
    B.insert(0,0) = 1 ;
    B.insert(1,1) = 2 ;
    B.insert(2,2) = 3 ;
    B(1,1) += 3 ;

    zsInfo << "Here is a sparse matrix B:\n" << B<< " and B(1,1) is "<< B.coeffRef(1,1) << "\n";
    zsInfo << "Matrix B has "<<B.nonZeros()  << " non-zero elements"<< "\n";
    zsInfo << "Here is the product A*B:\n" << A*B << "\n";

    zsVector3d<> v1;
    v1 << 1,2,3;
    zsVector3d<> v2;
    v2 << 3,2,1;

    zsInfo << " dot product: "<< v1.dot(v2) << "\n";
    zsInfo << " cross product: "<< v1.cross(v2) << "\n";

    zsInfo << " dot product of matrix columns: "<< A.col(0).adjoint() * A.col(1) << "\n";
    zsInfo << " Another way: converts 1x1 matrix to value: "<< (A.col(0).transpose() * A.col(1) ).value() << "\n";

    zsMatrix<> r;
    A.firstMinor(0, 0, r);
    zsInfo << "Here are some minors of A:\n" << r  << "\n";
    A.firstMinor(1, 2, r);
    zsInfo << r  << "\n";
    A.firstMinor(2, 0, r);
    zsInfo << r  << "\n";
    A.firstMinor(2, 2, r);
    zsInfo << r  << "\n";

    r.setZero(2,2);
    zsInfo <<"Set matrix to zero setZero():\n"<< r <<"\n";
    r.setOnes();
    zsInfo <<"Set matrix to all ones setOnes():\n"<< r <<"\n";
    r.setConstant(3);
    zsInfo <<"Set matrix to all a constant setConstant(3):\n"<< r <<"\n";
    r.setRandom(2,2); // SLE_11_SP4
    zsInfo <<"Set matrix to random entires setRandom():\n"<< r <<"\n";

#ifndef GISMO_WITH_MPQ // eigenvalues will not work for rational arithmetic types

    zsInfo << " Eigenvalues of non-symmetric matrix: "<< A.eigenvalues().transpose() << "\n";
    zsInfo << " Eigenvectors of non-symmetric matrix: \n"
           << zsMatrix<>::EigenSolver(A).eigenvectors() << "\n";

    zsInfo << " Eigenvalues of symmetric matrix (A's lower triangular part): "
           << A.selfadjointView<Lower>().eigenvalues().transpose()  << "\n";

    zsInfo << " Eigenvalues of symmetric matrix (A's upper triangular part): "
           << A.selfadjointView<Upper>().eigenvalues().transpose()  << "\n";

#endif*/

    return 0;
}

