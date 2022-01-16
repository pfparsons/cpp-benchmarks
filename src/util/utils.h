#ifndef MG_UTILS_H
#define MG_UTILS_H
#include "macros.h"
#include <cstddef>

namespace mg {

template <size_t N>
REALLY_INLINE size_t mod( const size_t div ) {
  static_assert( !( N % 2 ), "Template parameter N must be a power of two." );
  return div & N - 1;
}

} // namespace mg

#endif // MG_UTILS_H
