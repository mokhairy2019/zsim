/**
 * @file zsSparseVector
 * @brief provides declaration of sparseVector class (wrapping eigen)
 * Author: Mohamed Mahmoud
 */

#ifndef ZSIM_ZSSPARSEVECTOR_H
#define ZSIM_ZSSPARSEVECTOR_H

namespace zsim{
    /** @brief
    Sparse vector class, based on Eigen::SparseVector.

    \tparam T coefficient type
    \tparam _Option zero is ColMajor order.
    \tparam _Index index type

    \ingroup Matrix
*/
    template<typename T,int _Options,typename _Index>
    class zsSparseVector : public Eigen::SparseVector<T,_Options,_Index>
    {
    public:
        typedef Eigen::SparseVector<T,_Options,_Index> Base;

        /// Type pointing to a block of the sparse vector
        typedef typename Eigen::Block<Base> Block;

        /// Type pointing to a block view of the sparse vector
        typedef zsMatrixBlockView<Base> BlockView;

        /// Shared pointer for zsSparseVector
        typedef memory::shared_ptr< zsSparseVector > Ptr;

    public:
        zsSparseVector():Base() { }

        zsSparseVector(_Index rows) : Base(rows) { }

        /// This constructor allows constructing a zsSparseVector from
        /// Eigen expressions
        template<typename OtherDerived>
        zsSparseVector(const Eigen::EigenBase<OtherDerived>& other) : Base(other) { }

        /// This constructor allows constructing a zsSparseVector from
        /// another sparse expression
        template<typename OtherDerived>
        zsSparseVector(const Eigen::MatrixBase<OtherDerived> &other) : Base(other) { }

        /// This constructor allows constructing a zsSparseVector from
        /// another sparse expression
        template<typename  OtherDerived>
        zsSparseVector(const Eigen::SparseMatrixBase<OtherDerived> &other) : Base(other) { }

        /// This constructor allows constructing a zsSparseVector from
        /// another sparse expression
        template<typename OtherDerived>
        zsSparseVector(const Eigen::ReturnByValue<OtherDerived>& other)  : Base(other) { }

        ~zsSparseVector() { }
#if !EIGEN_HAS_RVALUE_REFERENCES
        // Using the assignment operators of Eigen
    // Note: using Base::operator=; is ambiguous in MSVC
#ifdef _MSC_VER
    template <class EigenExpr>
    zsSparseVector& operator= (const EigenExpr & other) 
    {
        this->Base::operator=(other);
        return *this;
    }
#else
    using Base::operator=;
#endif

#else

        // Avoid default keyword for MSVC<2013 
        // https://msdn.microsoft.com/en-us/library/hh567368.aspx
        zsSparseVector(const zsSparseVector& other) : Base(other)
        { Base::operator=(other); }

        zsSparseVector& operator= (const zsSparseVector & other)
        { Base::operator=(other); return *this; }

        zsSparseVector(zsSparseVector&& other)
        { operator=(std::forward<zsSparseVector>(other)); }

        zsSparseVector & operator=(zsSparseVector&& other)
        {
            this->swap(other);
            other.clear();
            return *this;
        }

#endif

void clear ()
{
    this->resize(0);
    this->data().squeeze;
}
        inline T   at (_Index i ) const { return this->coeff(i); }
        inline T & at (_Index i ) { return this->coeffRef(i); }

        inline T    operator () (_Index i) const { return this->coeff(i); }
        inline T  & operator () (_Index i) { return this->coeffRef(i); }

        inline T    operator [] (_Index i) const { return this->coeff(i); }
        inline T  & operator [] (_Index i) { return this->coeffRef(i); }

        /// Clone function. Used to make a copy of the matrix
        zsSparseVector * clone() const
        { return new zsSparseVector(*this); }


    }; // End of the class zsSparseVector
}

#endif //ZSIM_ZSSPARSEVECTOR_H
