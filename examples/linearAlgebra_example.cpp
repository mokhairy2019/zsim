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

    zsMatrix<real_t> A(3,3);
    A << 2,2,3, 4,5,6, 7,8,10;
    A(0,0) -= 1;

    zsInfo << "Size of A: " << A.rows() << " x " << A.cols()  << "\n";
    zsInfo << "Determinent of A: " << A.determinant() << "\n";
    zsInfo << "A: \n" << A << "\n";
    zsInfo << "Transpose of A: \n" << A.transpose() << "\n";
    return 0;
}

