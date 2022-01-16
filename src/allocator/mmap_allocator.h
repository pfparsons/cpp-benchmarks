#ifndef MG_MMAP_ALLOCATOR_H
#define MG_MMAP_ALLOCATOR_H
#include "memory_block.h"
#include "util/utils.h"
#include <sys/mman.h>
#ifdef __LINUX
#include <numa.h>
#endif

namespace mg::memory {


class MemoryPool {
public:
  explicit MemoryPool( uint64_t size ) {

    _abs_start = static_cast<uintptr_t*>( mmap( nullptr, size, PROT_READ | PROT_WRITE,
                                                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0 ) );
    uint64_t align_offset = mg::mod<64>( reinterpret_cast<const size_t>( _abs_start ) );
    _start = _abs_start + align_offset;

  }

  
private:
  uintptr_t* _abs_start = nullptr;
  uintptr_t* _start = _abs_start;
};

} // namespace mg::memory

#endif // MG_MMAP_ALLOCATOR_H
