/**
 * @file zsPoint.h
 * @brief Provides declaration of Point class.
 * Author Mohamed Mahmoud
 */



#ifndef ZSIM_ZSPOINT_H
#define ZSIM_ZSPOINT_H

namespace zsim {
    /**
* @brief A Point in T^d, with an index number.
* @tparam d
* @tparam T
*/

    template<class T,int d>
    class zsPoint : public zsVector<T,d>
    {
    public:
        typedef zsVector<T,d> Base;

        typedef zsPoint<T,d> Self;

        typedef typename Eigen::aligned_allocator<Self> alloc;

        typedef T Scalar_t;

        zsPoint() : Base(), m_vertexIndex((size_t)0) { }

        zsPoint(T x,T y,size_t index) : Base(), m_vertexIndex(index) {*this << x,y;}

        inline int getVertexIndex() const {return m_vertexIndex;}

    private:
        size_t m_vertexIndex;

    };
 }


#endif //ZSIM_ZSPOINT_H
