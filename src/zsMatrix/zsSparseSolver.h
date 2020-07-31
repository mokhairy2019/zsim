/**
 * @file zsSparseSolver.h
 * @brief abstract interfaces for solvers and wrapper around Eigen solvers
 * Author Mohamed Mahmoud
 */


#ifndef ZSIM_ZSSPARSESOLVER_H
#define ZSIM_ZSSPARSESOLVER_H

//TODO: Move this to the zsUtil.h file
#define STRINGIFY(x) #x

namespace zsim {
    // forward declarations
    template<typename T> class zsEigenCGIdentity;
    template<typename T> class zsEigenCGDiagonal;
    template<typename T> class zsEigenBiCGSTABIdentity;
    template<typename T> class zsEigenBiCGSTABDiagonal;
    template<typename T> class zsEigenBiCGSTABILUT;
    template<typename T> class zsEigenSparseLU;
    template<typename T> class zsEigenSparseQR;
    template<typename T> class zsEigenSimplicialLDLT;

    template<typename T> class zsEigenSuperLU;
    template<typename T> class zsEigenPardisoLDLT;
    template<typename T> class zsEigenPardisoLLT;
    template<typename T> class zsEigenPardisoLU;

    template<typename T> class zsEigenMINRES;
    template<typename T> class zsEigenGMRES;
    template<typename T> class zsEigenDGMRES;

    /** @brief Abstract class for solvers.
    The solver interface is base on 3 methods:
    -compute set the system matrix (possibly compute the factorization or preconditioners)
    -solve solves for a given right hand side
    -succeed returns true if solving succeded according to solver dependent criteria
    (usually tolerance based)
    So in order to solve \f$ A x = b \f$ with a solver \a s two functions must be called:
    s.compute(A) and s.solve(b). The calls can be chained as in  s.compute(A).solve(b).


    Moreover, a collection of available sparse solvers is given as typedefs
    Example of usage:
    \code
    zsSparseMatrix<real_t> M; // sparse system matrix
    zsMatrix<real_t> b; // right-hand side
    zsSparseSolver<real_t>::CGDiagonal solver;
    solver.compute(M);
    zsMatrix<> x = solver.solve(b);
    \endcode

    See also
    http://eigen.tuxfamily.org/dox/group__TopicSparseSystems.html
    and
    http://eigen.tuxfamily.org/dox/classEigen_1_1IterativeSolverBase.html

    \ingroup Matrix
*/

    template<typename T = real_t>
    class zsSparseSolver
    {
    public:
        /// all types of possible solvers in Eigen
        typedef zsEigenCGIdentity<T>           CGIdentity;
        typedef zsEigenCGDiagonal<T>           CGDiagonal;
        typedef zsEigenBiCGSTABDiagonal<T>     BiCGSTABDiagonal;
        typedef zsEigenBiCGSTABIdentity<T>     BiCGSTABIdentity;
        typedef zsEigenBiCGSTABILUT<T>         BiCGSTABILUT;
        typedef zsEigenSparseLU<T>             LU;
        typedef zsEigenSparseQR<T>             QR;
        typedef zsEigenSimplicialLDLT<T>       SimplicialLDLT;

        // optionals
        typedef zsEigenSuperLU<T>              SuperLU;
        typedef zsEigenPardisoLDLT<T>          PardisoLDLT;
        typedef zsEigenPardisoLLT<T>           PardisoLLT;
        typedef zsEigenPardisoLU<T>            PardisoLU;

        typedef zsEigenMINRES<T>               MINRES;
        typedef zsEigenGMRES<T>                GMRES;
        typedef zsEigenDGMRES<T>               DGMRES;

    public:
        typedef zsSparseMatrix<T> MatrixT;
        typedef zsMatrix<T>       VectorT;

    public:
        virtual ~zsSparseSolver(){ }

        virtual zsSparseSolver& compute (const MatrixT &matrix) = 0;

        virtual VectorT solve (const VectorT& rhs) const = 0 ;

        virtual bool succed()                       const = 0 ;

        /// Prints the object as a string.
        virtual std::ostream &print(std::ostream &os) const
        {
            os << "gsSparseSolver\n";
            return os;
        }

        /// Prints the object as a string with extended details.
        virtual std::string detail() const
        {
            std::ostringstream os;
            print(os);
            return os.str();
        }
    };

    /// \brief Print (as string) operator for sparse solvers
    template<class T>
    std::ostream &operator<<(std::ostream &os, const zsSparseSolver<T>& b)
    {return b.print(os); }

#define ZSIM_EIGEN_SPARSE_SOLVER(zsname, eigenName)                    \
    template<typename T>                                                \
    class zsname : public zsSparseSolver<T>, public zsEigenAdaptor<T>::eigenName \
    {                                                                   \
        typedef typename zsSparseSolver<T>::MatrixT MatrixT;            \
        typedef typename zsSparseSolver<T>::VectorT VectorT;            \
    protected:                                                          \
        index_t m_rows;                                                 \
        index_t m_cols;                                                 \
    public:                                                             \
        zsname()                                                        \
            : m_rows(0),m_cols(0)                                       \
        {}                                                              \
        zsname(const MatrixT &matrix)                                   \
            : zsEigenAdaptor<T>::eigenName(matrix), m_rows(matrix.rows()),m_cols(matrix.cols()) \
        {}                                                              \
        zsname& compute   (const MatrixT &matrix)                       \
        {                                                               \
            m_rows=matrix.rows();                                       \
            m_cols=matrix.cols();                                       \
            zsEigenAdaptor<T>::eigenName::compute(matrix);              \
            return *this;                                               \
        }                                                               \
        VectorT solve  (const VectorT &rhs) const                       \
        {                                                               \
            return zsEigenAdaptor<T>::eigenName::solve(rhs);            \
        }                                                               \
        bool succeed() const                                            \
        {                                                               \
            return zsEigenAdaptor<T>::eigenName::info()==Eigen::Success;\
        }                                                               \
        index_t rows() const {return m_rows;}                           \
        index_t cols() const {return m_cols;}                           \
        std::ostream &print(std::ostream &os) const                     \
        {                                                               \
            os <<STRINGIFY(zsname)<<"\n";                               \
            return os;                                                  \
        }                                                               \
    };

    ZSIM_EIGEN_SPARSE_SOLVER (zsEigenCGIdentity,     CGIdentity)
    ZSIM_EIGEN_SPARSE_SOLVER (zsEigenCGDiagonal,     CGDiagonal)
    ZSIM_EIGEN_SPARSE_SOLVER (zsEigenBiCGSTABIdentity, BiCGSTABIdentity)
    ZSIM_EIGEN_SPARSE_SOLVER (zsEigenBiCGSTABDiagonal, BiCGSTABDiagonal)
    ZSIM_EIGEN_SPARSE_SOLVER (zsEigenBiCGSTABILUT,     BiCGSTABILUT)
    ZSIM_EIGEN_SPARSE_SOLVER (zsEigenSparseLU,       SparseLU)
    ZSIM_EIGEN_SPARSE_SOLVER (zsEigenSparseQR,       SparseQR)
    ZSIM_EIGEN_SPARSE_SOLVER (zsEigenSimplicialLDLT, SimplicialLDLT)

#ifdef ZSIM_WITH_SUPERLU
    ZSIM_EIGEN_SPARSE_SOLVER (zsEigenSuperLU, SuperLU)
#endif

#ifdef ZSIM_WITH_PARDISO
    ZSIM_EIGEN_SPARSE_SOLVER (zsEigenPardisoLDLT, PardisoLDLT)
    ZSIM_EIGEN_SPARSE_SOLVER (zsEigenPardisoLLT, PardisoLLT)
    ZSIM_EIGEN_SPARSE_SOLVER (zsEigenPardisoLU, PardisoLU)
#endif

//ZSIM_EIGEN_SPARSE_SOLVER (zsEigenMINRES, MINRES)
//ZSIM_EIGEN_SPARSE_SOLVER (zsEigenGMRES,  GMRES)
//ZSIM_EIGEN_SPARSE_SOLVER (zsEigenDGMRES, DGMRES)


#undef ZSIM_EIGEN_SPARSE_SOLVER


}
#endif //ZSIM_ZSSPARSESOLVER_H
