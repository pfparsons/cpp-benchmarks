#ifndef MG_UNITS_H
#define MG_UNITS_H
#include <cstddef>

namespace mg::memory {

uint64_t operator"" _kb( uint64_t size ) { return size * 1000; }

uint64_t operator"" _mb( uint64_t size ) { return size * 1'000'000; }

uint64_t operator"" _gb( uint64_t size ) { return size * 1'000'000'000; }
} // namespace mg::memory

#endif // MG_UNITS_H
