/**
 * @file zsSparseRows.h
 * @brief defines the declarations for the spars rows
 */

#ifndef ZSIM_ZSSPARSEROWS_H
#define ZSIM_ZSSPARSEROWS_H

#include <vector>
#include <stdexcept>

#include <zsCore/zsLinearAlgebra.h>

namespace zsim{
    /**
 * \brief A specialized sparse matrix class which stores each row
 *  as a separate sparse vector.
 *
 *  This allows efficient row resizing and insertion
 *  operations, particularly for knot insertion algorithms.
 */
    template<class T>
    class zsSparseRows
    {
    private:
        std::vector< Row* > m_rows;

        /// Change the number of rows without allocating newly added rows
        void resizeRows(index_t newRows)
        {
            // delete rows which will be removed from the array
            // (does nothing if newRows >= rows())
            for (index_t i = newRows; i < rows(); ++i)
                delete m_rows[i];

            m_rows.resize(newRows);
        }
    public:
        typedef Eigen::SparseVector<T> Row;

        struct RowBlockXpr;

    public:
        zsSparseRows()
        { }

        zsSparseRows(index_t rows, index_t cols)
                : m_rows(rows)
        {
            for (index_t i = 0; i < rows; ++i)
                m_rows[i] = new Row(cols);
        }

        zsSparseRows(const zsSparseRows& other)
                : m_rows(other.rows())
        {
            for (int i = 0; i < rows(); ++i)
                m_rows[i] = new Row( *other.m_rows[i] );
        }

        zsSparseRows(const RowBlockXpr& rowxpr)
                : m_rows(rowxpr.num)
        {
            for (index_t i = 0; i < rowxpr.num; ++i)
                m_rows[i] = new Row( *rowxpr.mat.m_rows[rowxpr.start + i] );
        }

        ~zsSparseRows()
        {
            clear();
        }

        zsSparseRows& operator= (const zsSparseRows other)
        {
            this->swap( other );
            return *this;
        }

        zsSparseRows& operator= (const RowBlockXpr& rowxpr)
        {
            zsSparseRows temp(rowxpr);
            this->swap( temp );
            return *this;
        }

        index_t rows() const { return m_rows.size(); }
        index_t cols() const { return (m_rows.size() > 0) ? m_rows[0]->size() : 0; }

        Row& row(index_t i)             { return *m_rows[i]; }
        const Row& row(index_t i) const { return *m_rows[i]; }

        void clear()
        {
            for (int i = 0; i < rows(); ++i)
                delete m_rows[i];
            m_rows.clear();
        }

        void swap(zsSparseRows& other)
        {
            m_rows.swap( other.m_rows );
        }

        void setIdentity(index_t n)
        {
            assert( n >= 0 );

            resize(n, n);

            for (index_t i = 0; i < n; ++i)
                m_rows[i]->insert(i) = T(1.0);
        }

        void resize(index_t rows, index_t cols)
        {
            assert( rows >= 0 && cols >= 0 );

            clear();
            m_rows.resize(rows);
            for (index_t i = 0; i < rows; ++i)
                m_rows[i] = new Row(cols);
        }

        void conservativeResize(index_t newRows, index_t newCols)
        {
            if (rows() > 0 && cols() != newCols)
                throw std::runtime_error("cannot resize columns -- not implemented");

            const index_t oldRows = rows();
            resizeRows(newRows);

            // allocate newly added rows, if any
            for (index_t i = oldRows; i < newRows; ++i)
                m_rows[i] = new Row(newCols);
        }

        void duplicateRow(index_t k)
        {
            assert ( 0 <= k && k < rows() );

            // add one new row
            resizeRows( rows() + 1 );

            // shift rows [k+1,...) down to [k+2,...)
            for (index_t i = rows() - 1; i > k + 1; --i)
                m_rows[i] = m_rows[i-1];

            // allocate new row
            m_rows[k+1] = new Row( row(k) );
        }

        // row expressions

        RowBlockXpr topRows(index_t num)       { return RowBlockXpr(*this, 0, num); }
        const RowBlockXpr topRows(index_t num) const { return RowBlockXpr(*this, 0, num); }

        RowBlockXpr bottomRows(index_t num)       { return RowBlockXpr(*this, rows() - num, num); }
        const RowBlockXpr bottomRows(index_t num) const { return RowBlockXpr(*this, rows() - num, num); }

        RowBlockXpr middleRows(index_t start, index_t num)        { return RowBlockXpr(*this, start, num); }
        const RowBlockXpr middleRows(index_t start, index_t num) const  { return RowBlockXpr(*this, start, num); }

        index_t nonZeros() const
        {
            index_t nnz = 0;
            for (index_t i = 0; i < rows(); ++i)
                nnz += m_rows[i]->nonZeros();
            return nnz;
        }

        template <class Derived>
        void toSparseMatrix(Eigen::SparseMatrixBase<Derived>& m) const
        {
            m.derived().resize( rows(), cols() );
            m.derived().reserve( nonZeros() );
            for (index_t i = 0; i < rows(); ++i)
            {
                for (typename Row::InnerIterator it(*m_rows[i]); it; ++it)
                    m.derived().insert(i, it.index()) = it.value();
            }
            m.derived().makeCompressed();
        }

        struct RowBlockXpr
        {
            RowBlockXpr(const zsSparseRows& _mat, index_t _start, index_t _num)
                    : mat(const_cast<zsSparseRows&>(_mat)), start(_start), num(_num)
            {
                // HACK: We cast away the constness of the matrix, otherwise we would need two versions of
                // this expression class.
                // It's still safe because the row block methods in zsSparseRows above return the proper constness.
                assert( 0 <= num && 0 <= start );
                assert( start < mat.rows() );
                assert( start + num <= mat.rows() );
            }

            zsSparseRows & mat;
            index_t start, num;

            RowBlockXpr& operator= (const RowBlockXpr& other)
            {
                assert(num == other.num);
                for (index_t i = 0; i < num; ++i)
                    mat.row(start + i) = other.mat.row(other.start + i);
                return *this;
            }

            RowBlockXpr& operator= (const zsSparseRows& other)
            {
                assert(num == other.rows());
                for (index_t i = 0; i < num; ++i)
                    mat.row(start + i) = other.row(i);
                return *this;
            }
        };



    };
}
#endif //ZSIM_ZSSPARSEROWS_H
