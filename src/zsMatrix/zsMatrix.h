//
// Created by Mokhairy on 7/26/2020.
//
/** @file zsMatrix.h

    @brief Provides declaration of Matrix class.

    Author(s): Mohamed Mahmoud
*/

#ifndef ZSIM_ZSMATRIX_H
#define ZSIM_ZSMATRIX_H


namespace zsim
{

/** @brief
    A matrix with arbitrary coefficient type and fixed or dynamic size.

    This class provides an interface to Eigen::Matrix from the Eigen
    linear algebra library. Most operations from Eigen are supported
    on a zsMatrix.

    See therefore also the Eigen documentation for dense matrices,
    http://eigen.tuxfamily.org/dox/group__QuickRefPage.html

    \tparam T coefficient type
    \tparam _Rows number of rows: an integer or \c Dynamic
    \tparam _Cols number of rows: an integer or \c Dynamic
    \tparam _Options further options; see Eigen documentation

    \ingroup Matrix
*/
    template<class T, int _Rows, int _Cols, int _Options>
    class zsMatrix : public Eigen::Matrix<T,_Rows, _Cols, _Options>
//i.e. Eigen::PlainObjectBase<Eigen::Matrix>
//i.e. Eigen::EigenBase<Eigen::Matrix>
    {
    public:
        // Base is the dense matrix class of Eigen
        typedef Eigen::Matrix<T,_Rows, _Cols, _Options> Base;

        // Self type
        typedef zsMatrix<T,_Rows, _Cols, _Options> Self;

        // The type of the coefficients of the matrix
        typedef T Scalar_t;

        typedef typename Eigen::aligned_allocator<Self> aalloc;

        // Type pointing to a block view of the matrix
        typedef zsMatrixBlockView<Base> BlockView;

        // Type pointing to a block of the matrix
        typedef Eigen::Block<Base> Block;

        // Type pointing to a (const) block of the matrix
        typedef Eigen::Block<const Base> constBlock;

        // Type pointing to a row of the matrix
        typedef Eigen::Block<Base, 1, _Cols, false> Row;

        // Type pointing to a (const) row of the matrix
        typedef Eigen::Block<const Base, 1, _Cols, false> constRow;

        // Type pointing to a set of successive rows of the matrix
        typedef Eigen::Block<Base, Dynamic, _Cols, false> Rows;

        // Type pointing to a a set of successive (const) rows of the matrix
        typedef Eigen::Block<const Base, Dynamic, _Cols, false> constRows;

        // Type pointing to a column of the matrix
        typedef Eigen::Block<Base, _Rows, 1, true > Column;

        // Type pointing to a (const) column of the matrix
        typedef Eigen::Block<const Base, _Rows, 1, true > constColumn;

        // Type pointing to a set of successive columns of the matrix
        typedef Eigen::Block<Base, _Rows, Dynamic, true > Columns;

        // Type pointing to a set of successive (const) columns of the matrix
        typedef Eigen::Block<const Base, _Rows, Dynamic, true > constColumns;

        // Type pointing to the transpose of the matrix
        typedef Eigen::Transpose<Base> Tr;

        // Type pointing to the (const) transpose of the matrix
        typedef const Eigen::Transpose<const Base> constTr;

        // Type refering to any possible Eigen type that can be copied
        // into a zsMatrix
        typedef Eigen::Ref<Base> Ref;

        // Type refering to any (const) possible Eigen types that can be
        // copied into a zsMatrix
        typedef const Eigen::Ref<const Base> constRef;

        /// Shared pointer for zsMatrix
        typedef memory::shared_ptr<zsMatrix> Ptr;

        /// Unique pointer for zsMatrix
        typedef memory::unique_ptr<zsMatrix> uPtr;

        // type of first minor matrix: rows and cols reduced by one
        typedef zsMatrix< T, ChangeDim<_Rows, -1>::D, ChangeDim<_Cols, -1>::D>
                FirstMinorMatrixType;

        // type of row minor matrix: rows reduced by one
        typedef zsMatrix< T, ChangeDim<_Rows, -1>::D, _Cols>
                RowMinorMatrixType;

        // type of col minor matrix: cols reduced by one
        typedef zsMatrix< T, _Rows, ChangeDim<_Cols, -1>::D>
                ColMinorMatrixType;

    public:  // Solvers related to zsMatrix
        typedef typename Eigen::EigenSolver<Base> EigenSolver;

        typedef typename Eigen::SelfAdjointEigenSolver<Base> SelfAdjEigenSolver;

        typedef typename Eigen::GeneralizedSelfAdjointEigenSolver<Base> GenSelfAdjEigenSolver;

        // Jacobi SVD using ColPivHouseholderQRPreconditioner
        typedef typename Eigen::JacobiSVD<Base> JacobiSVD;

        // Bidiagonal Divide and Conquer SVD
        //typedef typename Eigen::BDCSVD<Base> BDCSVD;

        //typedef typename Eigen::CompleteOrthogonalDecomposition CODecomposition;

    public:

        zsMatrix() { }

        zsMatrix(const Base& a) ;

        // implicitly deleted in C++11
        //zsMatrix(const zsMatrix& a) : Base(a) { }

        zsMatrix(int rows, int cols) ;

        /// This constructor allows constructing a zsMatrix from Eigen expressions
        template<typename OtherDerived>
        zsMatrix(const Eigen::EigenBase<OtherDerived>& other) : Base(other) { }

        /// This constructor allows constructing a zsMatrix from Eigen expressions
        template<typename OtherDerived>
        zsMatrix(const Eigen::MatrixBase<OtherDerived>& other) : Base(other) { }

        /// This constructor allows constructing a zsMatrix from Eigen expressions
        template<typename OtherDerived>
        zsMatrix(const Eigen::ReturnByValue<OtherDerived>& other) : Base(other) { }

        inline operator Ref () { return Ref(*this); }

        inline operator const constRef () { return constRef(*this); }

        /**
          \brief This function returns a smart pointer to the
          matrix. After calling it, the matrix object becomes empty, ie
          the size of the matrix is 0
         */
        uPtr moveToPtr()
        {
            uPtr m(new zsMatrix);
            m->swap(*this);
            return m;
            //return uPtr(new zsMatrix<T>(give(*this)));
        }

        void clear() { this->resize(0,0); }
/*
    // Using the assignment operators of Eigen
    // Note: using Base::operator=; is ambiguous in MSVC
#ifdef _MSC_VER // && !__INTEL_COMPILER
    template <class EigenExpr>
    zsMatrix& operator= (const EigenExpr & other)
    {
        this->Base::operator=(other);
        return *this;
    }
#else
    using Base::operator=;
#endif
*/

#if !EIGEN_HAS_RVALUE_REFERENCES
        // swap assignment operator
        zsMatrix & operator=(typename Eigen::internal::conditional<
                -1==_Rows,zsMatrix, const zsMatrix &>::type other)
        {
            if (-1==_Rows)
                this->swap(other);
            else
                this->Base::operator=(other);
            return *this;
        }
#endif

        std::pair<index_t,index_t> dim() const
        { return std::make_pair(this->rows(), this->cols() ); }

        /// \brief Returns the \a i-th element of the vectorization of the matrix
        T   at (index_t i) const { return *(this->data()+i);}

        /// \brief Returns the \a i-th element of the vectorization of the matrix
        T & at (index_t i)       { return *(this->data()+i);}

        // \brief Returns the last element of the matrix (maximum row and column)
        //T   lastCoeff() { return *(this->data()+this->size()-1);}

        /// \brief Returns the matrix resized to n x m matrix (data is not copied)
        /// This function assumes that the matrix is size n*m, ie. already allocated
        zsAsMatrix<T, Dynamic, Dynamic> reshape(index_t n, index_t m )
        { return zsAsMatrix<T, Dynamic, Dynamic>(this->data(), n, m); }

        /// \brief Returns the matrix resized to n x m matrix (data is not copied)
        /// This function assumes that the matrix is size n*m, ie. already allocated
        zsAsConstMatrix<T, Dynamic, Dynamic> reshape(index_t n, index_t m ) const
        { return zsAsConstMatrix<T, Dynamic, Dynamic>(this->data(), n, m); }

        /// \brief Returns column \a c of the matrix resized to n x m matrix
        /// This function assumes that the matrix is size n*m, ie. already allocated
        zsAsMatrix<T, Dynamic, Dynamic> reshapeCol( index_t c, index_t n, index_t m )
        { return zsAsMatrix<T, Dynamic, Dynamic>(this->col(c).data(), n, m); }

        /// \brief Returns column \a c of the matrix resized to n x m matrix
        /// This function assumes that the matrix is size n*m, ie. already allocated
        zsAsConstMatrix<T, Dynamic, Dynamic> reshapeCol( index_t c, index_t n, index_t m ) const
        { return zsAsConstMatrix<T, Dynamic, Dynamic>(this->col(c).data(), n, m); }

        /// \brief Returns the entries of the matrix resized to a n*m vector column-wise
        zsAsVector<T, Dynamic> asVector()
        { return zsAsVector<T, Dynamic>(this->data(), this->rows()*this->cols() ); }

        /// \brief Returns the entries of the matrix resized to a (const) n*m vector column-wise
        zsAsConstVector<T, Dynamic> asVector() const
        { return zsAsConstVector<T, Dynamic>(this->data(), this->rows()*this->cols() ); }

        /// Returns the entries of the matrix resized to a 1 x n*m
        /// row-vector column-wise
        zsAsMatrix<T, 1, Dynamic> asRowVector()
        { return zsAsMatrix<T, 1, Dynamic>(this->data(), 1, this->rows()*this->cols() ); }

        /// Returns the entries of the matrix resized to a (const) 1 x n*m
        /// row-vector column-wise
        zsAsConstMatrix<T, 1, Dynamic> asRowVector() const
        { return zsAsConstMatrix<T, 1, Dynamic>(this->data(), 1, this->rows()*this->cols() ); }

        /// Returns a submatrix consisting of the columns indexed by the
        /// vector container \a colInd
        template<class container>
        void submatrixCols(const container & colInd, zsMatrix<T> & result) const
        {
            //ZSIM_ASSERT(colInd.cols() == 1, "Invalid column index vector");
            const index_t nc = colInd.size();
            result.resize(this->rows(), nc );
            for ( index_t i = 0; i!= nc; ++i )
                result.col(i) = this->col( colInd[i] );
        }

        /// Returns a submatrix consisting of the rows indexed by the
        /// vector container \a rowInd
        template<class container>
        void submatrixRows(const container & rowInd, zsMatrix<T> & result) const
        {
            //ZSIM_ASSERT(rowInd.cols() == 1, "Invalid row index vector");
            const index_t nr = rowInd.size();
            result.resize(nr, this->cols() );
            for ( index_t i = 0; i!= nr; ++i )
                result.row(i) = this->row( rowInd[i] );
        }

        /// Returns a submatrix consisting of the rows and columns indexed
        /// by the vector containers \a rowInd and \a colInd respectively
        template<class container>
        void submatrix(const container & rowInd,
                       const container & colInd,
                       zsMatrix<T> & result) const
        {
            //ZSIM_ASSERT(rowInd.cols() == 1 && colInd.cols() == 1, "Invalid index vector");
            const index_t nr = rowInd.size();
            const index_t nc = colInd.size();
            result.resize(nr, nc );
            for ( index_t i = 0; i!= nr; ++i )
                for ( index_t j = 0; j!= nc; ++j )
                    result(i,j) = this->coeff(rowInd[i], colInd[j] );
        }

        /// Removes column \a i from the matrix. After the operation the
        /// column size of the matrix is one less.
        void removeCol( index_t i )
        {
            index_t cc= this->cols();
            ZSIM_ASSERT( i < cc, "Invalid column." );
            for ( index_t c = i+1; c!= cc; ++c )
                this->col(c-1) = this->col(c);
            this->conservativeResize(this->rows(), cc-1);
        }

        /// Returns the (i,j)-minor, i.e. the matrix after removing row
        /// \a i and column \a j from the matrix. After the operation the
        /// row and column size of the matrix is one less.
        void firstMinor(index_t i, index_t j, FirstMinorMatrixType & result ) const
        {
            const index_t mrows = this->rows()-1,
                    mcols = this->cols()-1;
            ZSIM_ASSERT( i <= mrows, "Invalid row." );
            ZSIM_ASSERT( j <= mcols, "Invalid column." );
            result.resize(mrows,mcols);
            result.block(0,0,i,j)             = this->block(0,0,i,j);
            result.block(i,0,mrows-i,j)       = this->block(i+1,0,mrows-i,j);
            result.block(0,j,i,mcols-j)       = this->block(0,j+1,i,mcols-j);
            result.block(i,j,mrows-i,mcols-j) = this->block(i+1,j+1,mrows-i,mcols-j);
        }

        /// Returns the ith row minor, i.e. the matrix after removing row
        /// \a i from the matrix. After the operation the row size of the
        /// matrix is one less.
        void rowMinor(index_t i, RowMinorMatrixType & result ) const
        {
            const index_t mrows = this->rows()-1;
            ZSIM_ASSERT( i <= mrows, "Invalid row." );
            result.resize(mrows, this->cols());
            result.topRows(i)          = this->topRows(i);
            result.bottomRows(mrows-i) = this->bottomRows(mrows-i);
        }

        /// Returns the jth column minor, i.e. the matrix after removing column
        /// \a j from the matrix. After the operation the column size of the
        /// matrix is one less.
        void colMinor(index_t j, ColMinorMatrixType & result ) const
        {
            const index_t mcols = this->cols()-1;
            ZSIM_ASSERT( j <= mcols, "Invalid column." );
            result.resize(this->rows(), mcols);
            result.leftCols(j)        = this->leftCols(j);
            result.rightCols(mcols-j) = this->rightCols(mcols-j);
        }

        void duplicateRow( index_t k )
        {
            this->conservativeResize(this->rows() + 1, this->cols());

            /*
            // Test this
            this->bottomRows(this->rows() - k ) =
            this->middleRows(this->rows() - k, k+1 );

            this->row(k+1) = this->row(k);
            return;

            //*/

            for (index_t i = this->rows() - 1; i > k+1 ; --i)
                this->row(i).swap(this->row(i-1));

            this->row(k+1) = this->row(k);
        }

        void removeNoise(const T tol)
        {
            this->noalias() = this->unaryExpr(removeNoise_helper(tol));
        }

        // Clone function. Used to make a copy of the matrix
        //zsMatrix * clone() const;

        /// Return a block view of the matrix with \a rowSizes and \a colSizes
        BlockView blockView(const zsVector<index_t> & rowSizes,
                            const zsVector<index_t> & colSizes)
        {
            return BlockView(*this, rowSizes, colSizes);
        }

        /// Sorts rows of matrix by column \em j.
        void sortByColumn(const index_t j )
        {
            ZSIM_ASSERT( j < this->cols(), "Invalid column.");

            index_t lastSwapDone = this->rows() - 1;
            index_t lastCheckIdx = lastSwapDone;

            bool didSwap;
            zsMatrix<T> tmp(1, this->cols() );
            do{ //caution! A stable sort algorithm is needed here for lexSortColumns function below
                didSwap = false;
                lastCheckIdx = lastSwapDone;

                for( index_t i=0; i < lastCheckIdx; i++)
                    if( this->coeff(i,j) > this->coeff(i+1,j) )
                    {
                        tmp.row(0) = this->row(i);
                        this->row(i) = this->row(i+1);
                        this->row(i+1) = tmp.row(0);

                        didSwap = true;
                        lastSwapDone = i;
                    }
            }while( didSwap );
        }

        /// Sorts rows of matrix by columns in vector \em lorder.
        void lexSortRows(const std::vector<index_t> & lorder)
        {
            ZSIM_ASSERT(lorder.size() == static_cast<size_t>(this->cols()),
                         "Error in dimensions");

            for(std::vector<index_t>::const_reverse_iterator k = lorder.rbegin();
                k != lorder.rend(); ++k) //sort from last to first given column
                this->sortByColumn( *k ); // stable sort wrt column
        }

        /// \brief Transposes in place the matrix block-wise. The matrix is
        //  treated a 1 x (cols()/colBlock) block matrix, and every block
        //  of size rows() x colBlock is transposed in place
        void blockTransposeInPlace(const index_t colBlock)
        {
            const index_t nc = this->cols();
            const index_t nr = this->rows();

            ZSIM_ASSERT( nc % colBlock == 0,
                          "The blocksize is not compatible with number of columns.");

            if (nr == 1 || colBlock == 1)
            {
                this->resize(colBlock, this->size()/colBlock);
            }
            else if ( nr == colBlock )
            {
                for (index_t j = 0; j!= nc; j+=colBlock)
                    this->middleCols(j,colBlock).template triangularView<Eigen::StrictlyUpper>()
                            .swap( this->middleCols(j,colBlock).transpose() );
            }
            else
            {
                Eigen::Map<Base> m(this->data(), nr, nc);
                this->resize(colBlock, this->size()/colBlock);

                index_t i = 0;
                for (index_t j = 0; j!= nc; j+=colBlock, i+=nr)
                    this->middleCols(i,nr) = m.middleCols(j,colBlock).transpose().eval();
            }
        }

        /// Converts the matrix to its Reduced Row Echelon Form (RREF)
        void rrefInPlace() { rref_impl(*this); }

        /// Converts the matrix to its Reduced Column Echelon Form (RCEF)
        void rcefInPlace() { rref_impl(this->transpose()); }

        /// Converts the matrix to a Row Echelon Form (REF)
        void refInPlace() { ref_impl(*this); }

        /// Converts the matrix to a Column Echelon Form (CEF)
        void cefInPlace() { ref_impl(this->transpose()); }

        std::string printSparsity() const
        {
            std::ostringstream os;
            os <<", sparsity: "<< std::fixed << std::setprecision(2)<<"nnz: "<<this->size()
               <<(double)100*(this->array() != 0).count()/this->size() <<'%'<<"\n";
            for (index_t i = 0; i!=this->rows(); ++i)
            {
                for (index_t j = 0; j!=this->cols(); ++j)
                    os<< ( 0 == this->coeff(i,j) ? "\u00B7" : "x");
                os<<"  "<<(this->row(i).array()!=0).count()<<"\n";
            }
            return os.str();
        }

        /// Returns the Kronecker product of \a this with \a other
        template<typename OtherDerived>
        zsMatrix kron(const Eigen::MatrixBase<OtherDerived>& other) const
        {
            const index_t r  = this->rows(), c = this->cols();
            const index_t ro = other.rows(), co = other.cols();
            zsMatrix result(r*ro, c*co);
            for (index_t i = 0; i != r; ++i) // for all rows
                for (index_t j = 0; j != c; ++j) // for all cols
                    result.block(i*ro, j*ro, ro, co) = this->coeff(i,j) * other;
            return result;
        }

        /// Returns the Khatri-Rao product of \a this with \a other
        template<typename OtherDerived>
        zsMatrix khatriRao(const Eigen::MatrixBase<OtherDerived>& other) const
        {
            const index_t r  = this->rows(), c = this->cols();
            const index_t ro = other.rows();
            ZSIM_ASSERT(c==other.cols(), "Column sizes do not match.");
            zsMatrix result(r*ro, c);
            for (index_t j = 0; j != c; ++j) // for all cols
                for (index_t i = 0; i != ro; ++i) // for all rows
                    result.block(i*r, j, r, 1) = this->coeff(i,j) * other.col(j);
            return result;
        }

    private:

        // Implementation of (inplace) Reduced Row Echelon Form computation
        template <typename Derived>
        static void rref_impl(const Eigen::MatrixBase<Derived>& Mat)
        {
            // todo: const T tol = 0
            Eigen::MatrixBase<Derived> & M = const_cast<Eigen::MatrixBase<Derived>& >(Mat);
            index_t i, piv = 0;
            const index_t nr = M.rows();
            const index_t nc = M.cols();
            for (index_t r=0; r!=nr; ++r)
            {
                if (nc <= piv) return;
                i = r;
                while (0 == M(i, piv)) //~
                {
                    ++i;
                    if (nr == i)
                    {
                        i = r;
                        ++piv;
                        if (nc == piv) return;
                    }
                }

                if (i != r) M.row(i).swap(M.row(r));
                const index_t br = nr-r-1;
                const index_t bc = nc-piv-1;

                // pivot row
                M.row(r).tail(bc).array() /= M(r, piv);
                M(r, piv) = T(1);

                // upper block
                M.block(0, piv+1, r, bc).noalias() -=
                        M.col(piv).head(r) * M.row(r).tail(bc);
                M.col(piv).head(r).setZero();

                // lower block
                M.block(r+1, piv+1, br, bc).noalias() -= M.col(piv).tail(br) * M.row(r).tail(bc);
                M.col(piv).tail(br).setZero();

                ++piv;
            }
        }

        // Implementation of (inplace) Row Echelon Form computation
        template <typename Derived>
        static void ref_impl(const Eigen::MatrixBase<Derived>& Mat)
        {
            // todo: const T tol = 0
            Eigen::MatrixBase<Derived> & M = const_cast<Eigen::MatrixBase<Derived>& >(Mat);
            index_t i, piv = 0;
            const index_t nr = M.rows();
            const index_t nc = M.cols();
            for (index_t r=0; r!=nr; ++r)
            {
                if (nc <= piv) return;
                i = r;
                while (0 == M(i, piv)) //~
                {
                    ++i;
                    if (nr == i)
                    {
                        i = r;
                        ++piv;
                        if (nc == piv) return;
                    }
                }

                if (i != r) M.row(i).swap(M.row(r));
                const index_t br = nr-r-1;
                const index_t bc = nc-piv-1;

                // lower block
                M.block(r+1, piv+1, br, bc).noalias() -=
                        M.col(piv).tail(br) * M.row(r).tail(bc) / M(r, piv);
                M.col(piv).tail(br).setZero();

                ++piv;
            }
        }

        struct removeNoise_helper
        {
            removeNoise_helper(const T & tol)
                    : m_tol(tol) { }

            inline const T operator() (const T & val) const
            { return ( math::abs(val) < m_tol ? 0 : val ); }

            const T & m_tol;
        };

    }; // class zsMatrix


/*
template<class T, int _Rows, int _Cols, int _Options> inline
zsMatrix<T,_Rows, _Cols, _Options>::zsMatrix() { }
*/

    template<class T, int _Rows, int _Cols, int _Options> inline
    zsMatrix<T,_Rows, _Cols, _Options>::zsMatrix(const Base& a) : Base(a) { }

    template<class T, int _Rows, int _Cols, int _Options> inline
    zsMatrix<T,_Rows, _Cols, _Options>::zsMatrix(int rows, int cols) : Base(rows,cols) { }

// template<class T, int _Rows, int _Cols, int _Options>
//  template<typename OtherDerived>
// zsMatrix<T,_Rows, _Cols, _Options>::zsMatrix(const Eigen::MatrixBase<OtherDerived>& other) : Base(other) { }

/* Clone function. Used to make a copy of the matrix
template<class T, int _Rows, int _Cols, int _Options> inline
zsMatrix<T,_Rows, _Cols, _Options> * zsMatrix<T,_Rows, _Cols, _Options>::clone() const
{ return new zsMatrix<T,_Rows, _Cols, _Options>(*this); }
*/

} // namespace gismo


namespace Eigen { namespace internal {
        template<class T, int _Rows, int _Cols, int _Options>
        struct traits<zsim::zsMatrix<T,_Rows,_Cols,_Options> > :
                Eigen::internal::traits<Eigen::Matrix<T,_Rows,_Cols,_Options> > { };
    } }

#endif //ZSIM_ZSMATRIX_H
