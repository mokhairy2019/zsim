/**
 * @file zsVector.h
 * @brief provides declaration of the cector calss
 * Author: Mohamed Mahmoud
 */

#ifndef ZSIM_ZSVECTOR_H
#define ZSIM_ZSVECTOR_H
namespace zsim{
    /** @brief
    A vector with arbitrary coefficient type and fixed or dynamic size.

    This class is based on Eigen::Matrix from the Eigen
    linear algebra library. Most operations from Eigen are supported
    on a gsVector. See therefore also the Eigen documentation,
    http://eigen.tuxfamily.org/dox/.

    \tparam T coefficient type
    \tparam _Rows number of rows: an integer or \c Dynamic

    \ingroup Matrix
*/

    template<class T, int _Rows, int _Options>
    class zsVector : public zsMatrix<T, _Rows, 1, _Options>
    {
    public:

        typedef zsMatrix<T,_Rows,1,_Options> zsBase;

        //Base is the single column dense matrix class of Eigen
        typedef typename zsBase::Base Base;

        //self type
        typedef zsVector<T,_Rows,_Options> self;

        typedef typename Eigen::aligned_allocator<self> alloc;

        // Type of the coefficients of the matrix
        typedef T Scalar_T;

        //type pointing to a block of the vector
        typedef typename Eigen::Block<Base> Block;


        typedef zsMatrixBlockView<Base> BlockView;

        /// Unique pointer for zsVector
        typedef memory::unique_ptr< zsVector > uPtr;

        // Type for copying a vector as a permutation matrix
        typedef Eigen::PermutationMatrix<_Rows,Base::SizeAtCompileTime,index_t> Permutation;

        // Type for treating a vector as a permutation matrix
        typedef Eigen::PermutationWrapper<Base> PermutationWrap;

        typedef Eigen::Ref<Base> Ref;

        typedef const Eigen::Ref<const Base> ConstRef;

        // Type for a vector of dimension one less
        typedef zsMatrix< T, ChangeDim<_Rows, -1>::D, ColMajor> Projection_t;

    public:
        // iterator definations
        typedef T * iterator;

        typedef const T * const_iterator;

        T * begin(){
            return this->data();
        }

        const T * begin() const {
            return this->data();
        }

        T * end(){
            return this->data() + this->size();
        }

        const T * end() const{
            return this->data()+this->size();
        }

    public:

        zsVector();

        zsVector(const Base& a);

        explicit zsVector(index_t dimension);

        inline operator Ref () {return Ref (*this);}

        inline operator ConstRef () {return ConstRef (*this);}

        void clear() {this->resize(0);}

        // This constructor allows constructing a zsVector from Eigen expressions
        template<typename OtherDerived>
        zsVector(const Eigen::EigenBase<OtherDerived>& other) : zsBase(other) { }

        // This constructor allows constructing a zsVector from Eigen expressions
        template<typename OtherDerived>
        zsVector(const Eigen::MatrixBase<OtherDerived>& other) : zsBase(other) { }

        // This constructor allows constructing a zsVector from Eigen expressions
        template<typename OtherDerived>
        zsVector(const Eigen::ReturnByValue<OtherDerived>& other) : zsBase(other) { }

        static zsVector<T,2> vec( T x, T y)
        {
            return typename zsVector<T,2>::Base(x, y);
        }

        static zsVector<T,3> vec( T x, T y, T z)
        {
            return typename zsVector<T,3>::Base(x, y, z);
        }

#if !EIGEN_HAS_RVALUE_REFERENCES
        zsVector & operator=(typename Eigen::internal::conditional<
                         -1==_Rows,gsVector, const gsVector &>::type other)
    {
        if (-1==_Rows)
            this->swap(other);
        else
            this->Base::operator=(other);
        return *this;
    }
#endif

        /// \brief Returns the \a i-th element of the vector
        inline T at(index_t i) const { return *(this->data()+i);}

        /// \brief Returns the \a i-th element of the vector
        inline T & at(index_t i)     { return *(this->data()+i);}

        /// \brief Returns the last (bottom) element of the vector
        inline T last() const { return *(this->data()+this->size()-1);}

        /// \brief Returns the last (bottom) element of the vector
        inline T & last() { return *(this->data()+this->size()-1);}

        /// Return a row-block view of the vector with \a rowSizes
        BlockView blockView(const zsVector<index_t> & rowSizes)
        {
            return BlockView(*this, rowSizes);
        }

        PermutationWrap asPermutation() const { return PermutationWrap(*this);}

        /// Removes row \a i from the vector. After the operation the
        /// vector has size one less.
        void removeElement(const index_t i )
        {
            ZSIM_ASSERT( i < this->size(), "Invalid vector element." );
            const T * ce = this->data() + this->size();
            for ( T * c = this->data()+i+1; c!= ce; ++c ) *(c-1) = *c;
            this->conservativeResize(this->size()-1,Eigen::NoChange);
        }

       void findNonZeros(const zsVector<bool> logical)
       {
           int newsize = 0;
           for (int i = 0; i < logical.size(); i++) {
               if ( logical.at(i) ) {
                   ++newsize;
               }
           }
           this->resize(newsize);

           int pos = 0;
           for ( int i = 0; i < logical.size(); ++i ) {
               if ( logical.at(i) ) {
                   this->at(pos++) = i;
               }
           }
       }

    }; // end of class zsVector

    template<class T, int _Rows, int _Options> inline
    zsVector<T, _Rows, _Options>::zsVector() : zsBase() { }

    template<class T, int _Rows, int _Options> inline
    zsVector<T, _Rows, _Options>::zsVector(const zsVector::Base &a):zsBase(a) { }

    template<class T, int _Rows, int _Options> inline
    zsVector<T, _Rows, _Options>::zsVector(index_t dimension):zsBase(dimension,1) { }


/** @brief A fixed-size, statically allocated 3D vector.

    \tparam T coefficient type

    \ingroup Matrix
*/
    template<class T>
    class zsVector3d : public Eigen::Matrix<T,3,1>
    {
    public:
        typedef T scalar_t;
        typedef Eigen::Matrix<T,3,1> Base ;

        /// Shared pointer for gsVector3d
        typedef memory::shared_ptr< zsVector3d > Ptr;

    public:

        zsVector3d();

        zsVector3d(scalar_t x, scalar_t y, scalar_t z = 0 );

        // implcitly declared deleted in C++11
        //gsVector3d(const gsVector3d& a) : Base(a) { }

        zsVector3d(const Base& a) ;

        /// This constructor allows constructing a gsVector3d from Eigen expressions
        template<typename OtherDerived>
        zsVector3d(const Eigen::MatrixBase<OtherDerived>& other) : Base(other) { }

        T angle(const zsVector3d<T> & other)
        {
            return math::acos(this->normalized().dot(other.normalized()));
        }

        // implicitly deleted in C++11
        zsVector3d & operator=(const zsVector3d & other)
        {
            this->Base::operator=(other);
            return *this;
        }

        inline T   at (index_t i) const { return (*this)(i,0); }
        inline T & at (index_t i)       { return (*this)(i,0); }
        inline T   x () const   { return (*this)(0); }
        inline T & x ()         { return (*this)(0); }
        inline T   y () const   { return (*this)(1); }
        inline T & y ()         { return (*this)(1); }
        inline T   z () const   { return (*this)(2); }
        inline T & z ()         { return (*this)(2); }

    }; // class zsVector3d


    template<class T> inline
    zsVector3d<T>::zsVector3d() : Base() { }

    template<class T> inline
    zsVector3d<T>::zsVector3d(scalar_t x, scalar_t y,scalar_t z )
    {
        (*this)(0,0)=x;
        (*this)(1,0)=y;
        (*this)(2,0)=z;
    }

    template<class T> inline
    zsVector3d<T>::zsVector3d(const Base& a): Base(a) { }


}
#endif //ZSIM_ZSVECTOR_H

