/**
 * @file zsAsMatrix
 * @brief Wraps pointers as matrix objects
 * Author: Mohamed Mahmoud
 */

#ifndef ZSIM_ZSASMATRIX_H
#define ZSIM_ZSASMATRIX_H
namespace zsim {
    /** \brief Creates a mapped object or data pointer to a matrix without
    copying data.

   This allows for re-indexing the matrix. No copying is taking place
   and the original matrix remains untached.

   \tparam T coefficient type
   \ingroup Matrix
     */
    template<class T, int _Rows, int _Cols>
class zsAsMatrix : public Eigen::Map<Eigen::Matrix<T,_Rows,_Cols> >
{
public:
    typedef Eigen::Map<Eigen::Matrix<T,_Rows,_Cols> > Base;

    /// type of first minor matrix: rows and cols reduced by one
    typedef typename zsMatrix< T, _Rows, _Cols>::FirstMinorMatrixType FirstMinorMatrixType;

    /// type of row minor matrix: rows reduced by one
    typedef typename zsMatrix< T, _Rows, _Cols>::RowMinorMatrixType RowMinorMatrixType;

    /// type of col minor matrix: cols reduced by one
    typedef typename zsMatrix< T, _Rows, _Cols>::ColMinorMatrixType  ColMinorMatrixType;

    /// Type pointing to the transpose of the matrix
    typedef Eigen::Transpose<Base> Tr;

    /// Type pointing to the (const) transpose of the matrix
    typedef const Eigen::Transpose<const Base> constTr;

public:
    zsAsMatrix(std::vector<T> & v, index_t n, index_t m) :Base(v.data(),n,m)
    {
        //ZSIM_ASSERT( v.size() != 0, "Tried to map an empty vector." );
        ZSIM_ASSERT( m*n <= index_t(v.size()), "Not enough coefficients in vector to map." );
    }
    zsAsMatrix( std::vector<T> & v)
    : Base( v.data(), 1, v.size() )
    {
        ZSIM_ASSERT( v.size() != 0, "Tried to map an empty vector." );
    }

    zsAsMatrix(T * pt, unsigned n, unsigned m) : Base (pt, n, m) { }

    zsMatrix<T> move()
    {
        zsMatrix<T> a;
        a.swap(*this);
        return a;
    }

#ifdef _MSC_VER
        template <class EigenExpr>
    zsAsMatrix& operator= (const EigenExpr & other) 
    {
        this->Base::operator=(other);
        return *this;
    }
#else
        using Base::operator=;
#endif

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
        ZSIM_ASSERT( 0 <= i && i <= mrows, "Invalid row." );
        result.resize(mrows, this->cols());
        result.topRows(i)          = this->topRows(i);
        result.bottomRows(mrows-i) = this->bottomRows(mrows-i);
    }

    /// Returns the jth column minor, i.e. the matrix after removing row
    /// \a j from the matrix. After the operation the column size of the
    /// matrix is one less.
    void colMinor(index_t j, ColMinorMatrixType & result ) const
    {
        const index_t mcols = this->cols()-1;
        ZSIM_ASSERT( 0 <= j && j <= mcols, "Invalid column." );
        result.resize( this->rows(), mcols);
        result.leftCols(j)        = this->leftCols(j);
        result.rightCols(mcols-j) = this->rightCols(mcols-j);
    }

private:
    zsAsMatrix();

};

    /** \brief Creates a mapped object or data pointer to a const matrix without
    copying data.

   This allows for re-indexing the matrix. No copying is taking place
   and the original matrix remains untached.

   \tparam T coefficient type
   \ingroup Matrix
     */

    template<class T,int _Rows, int _Cols>
    class zsAsConstMatrix : public Eigen::Map <const Eigen::Matrix<T,_Rows,_Cols>>
    {
    public:
        typedef Eigen::Map <const Eigen::Matrix<T,_Rows,_Cols>> Base;
        /// Type pointing to the transpose of the matrix
        typedef Eigen::Transpose<Base> Tr;

        /// Type pointing to the (const) transpose of the matrix
        typedef const Eigen::Transpose<const Base> constTr;

        /// type of first minor matrix: rows and cols reduced by one
        typedef typename zsMatrix< T, _Rows, _Cols>::FirstMinorMatrixType FirstMinorMatrixType;

        /// type of row minor matrix: rows reduced by one
        typedef typename zsMatrix< T, _Rows, _Cols>::RowMinorMatrixType RowMinorMatrixType;

        /// type of col minor matrix: cols reduced by one
        typedef typename zsMatrix< T, _Rows, _Cols>::ColMinorMatrixType  ColMinorMatrixType;

    public:
        zsAsConstMatrix( const std::vector<T> & v, index_t n, index_t m)
                : Base( v.data(), n, m)
        {
            ZSIM_ASSERT( m*n <= index_t(v.size()), "Not enough coefficients in vector to map." );
        }

        zsAsConstMatrix( const std::vector<T> & v)
                : Base( v.data(), 1, v.size() )
        {
            //ZSIM_ASSERT( v.size() != 0, "Tried to map an empty vector." ); 
        }

        zsAsConstMatrix( const T * pt, unsigned n, unsigned m)
                : Base( pt, n, m) {  }

        zsAsConstMatrix(const Eigen::Map< Eigen::Matrix<T,_Rows,_Cols> > & mat)
                : Base( mat.data(), mat.rows(), mat.cols())
        {  }

    public:
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
            ZSIM_ASSERT( 0 <= i && i <= mrows, "Invalid row." );
            result.resize(mrows, this->cols());
            result.topRows(i)          = this->topRows(i);
            result.bottomRows(mrows-i) = this->bottomRows(mrows-i);
        }

        /// Returns the jth column minor, i.e. the matrix after removing row
        /// \a j from the matrix. After the operation the column size of the
        /// matrix is one less.
        void colMinor(index_t j, ColMinorMatrixType & result ) const
        {
            const index_t mcols = this->cols()-1;
            ZSIM_ASSERT( 0 <= j && j <= mcols, "Invalid column." );
            result.resize( this->rows(), mcols);
            result.leftCols(j)        = this->leftCols(j);
            result.rightCols(mcols-j) = this->rightCols(mcols-j);
        }

    private:
        zsAsConstMatrix() { }

    };

    /** \brief Creates a mapped object or data pointer to a vector without
    copying data.

   This allows for re-indexing the matrix. No copying is taking place
   and the original matrix remains untached.

   \tparam T coefficient type
   \ingroup Matrix
 */

    template<class T, int _Rows>
    class zsAsVector : public zsAsMatrix<T,_Rows,1>
    {
    public:
        //typedef zsAsMatrix<T,_Rows,(_Rows==1?1:0)> Base;
        typedef zsAsMatrix<T,_Rows,1> Base;

        // Type for treating a vector as a permutation matrix
        typedef Eigen::PermutationMatrix<_Rows> Permutation;

    public:
        zsAsVector( std::vector<T> & v)
        : Base( v.data(), v.size(), 1 )
        {
            ZSIM_ASSERT( v.size() != 0, "Tried to map an empty vector." );
        }

        zsAsVector( T * pt, unsigned n)
        : Base( pt, n, 1) {  }

#ifdef _MSC_VER
        template <class EigenExpr>
    zsAsVector& operator= (const EigenExpr & other) 
    {
        this->Base::operator=(other);
        return *this;
    }
#else
        using Base::operator=;
#endif

    private:
        zsAsVector() { }

    };

    /** \brief Creates a mapped object or data pointer to a const vector without
    copying data.

   This allows for re-indexing the matrix. No copying is taking place
   and the original matrix remains untached.

   \tparam T coefficient type
   \ingroup Matrix
 */

    template<class T, int _Rows>
    class zsAsConstVector : public zsAsConstMatrix<T, _Rows,1>
    {
    public:
        typedef zsAsConstMatrix<T,_Rows,1> Base;

    public:
        zsAsConstVector( const std::vector<T> & v)
                : Base( v.data(), v.size(), 1)
        {
            ZSIM_ASSERT( v.size() != 0, "Tried to map an empty vector." );
        }

        zsAsConstVector( const T * pt, unsigned n)
                : Base( pt, n, 1) {  }

    private:
        zsAsConstVector() { }
    };

    /// Utility to make a matrix out of an iterator to values
    template<class T, class iterator>
    zsMatrix<T> makeMatrix(iterator it, index_t n, index_t m)
    {
        zsMatrix<T> result(n,m);
        for ( index_t i = 0; i!=n; ++i)
            for ( index_t j = 0; j!=m; ++j)
                result(i,j)= *(it++);
        return result;
    }

}
#endif //ZSIM_ZSASMATRIX_H
