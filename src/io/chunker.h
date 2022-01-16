#ifndef CPP_BENCHMARKS_CHUNKER_H
#define CPP_BENCHMARKS_CHUNKER_H
#include "util/macros.h"
namespace mg {

template <size_t N>
REALLY_INLINE size_t constexpr mod( const size_t div ) {
  static_assert( !( N % 2 ), "Template parameter N must be a power of two." );
  return div & N - 1;
}


class AllocationUnit {
  using id_t = uint32_t;
  const id_t _id;
  const uintptr_t _start;
  const std::ptrdiff_t _length;

public:
  AllocationUnit( const id_t id, const uintptr_t start, const ptrdiff_t length )
      : _id( id ), _start( start ), _length( length ) {}
  [[nodiscard]] id_t Id() const;
  [[nodiscard]] uintptr_t Start() const;
  [[nodiscard]] ptrdiff_t Length() const;
};

id_t AllocationUnit::Id() const { return _id; }
uintptr_t AllocationUnit::Start() const { return _start; }
ptrdiff_t AllocationUnit::Length() const { return _length; }



} // namespace mg
#endif
