/**
 * @file zsMatrixAddons
 * @brief Provides extra member declarations to the Eigen MatrixBase class
 * Author Mohamed Mahmoud
 */

inline const internal::adjugate_impl<Derived> adjugate() const;

inline void adjugateInPlace();

typedef BlockDiag<Derived,Dynamic> BlockDiagReturnType;
inline const BlockDiagReturnType blockDiag(Index rowFactor) const;

typedef BlockTranspose<Derived,Dynamic> BlockTransposeReturnType;
inline const BlockTransposeReturnType blockTranspose(Index rowFactor) const;

template<typename IndicesType>
const RowSelection<Derived,IndicesType> selectRows(const IndicesType & ind) const;


/**
  * \brief Simple (inplace) Gauss elimination without any pivoting
  */


