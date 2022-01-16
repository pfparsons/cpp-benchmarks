#ifndef CPP_BENCHMARKS_MEMORY_BLOCK_H
#define CPP_BENCHMARKS_MEMORY_BLOCK_H

#include <cstddef>
#include <cstdint>

namespace mg::memory {

    class MemoryBlock {
    private:

    /**
     * @brief Pointer to the start of this block
     * of memory
     */
    uintptr_t* _address;

    /**
     * @brief Size of this memory block
     */
     std::size_t _size;

   public:

     MemoryBlock(uintptr_t* address, size_t size) noexcept : _address{address}, _size{size} {}

     inline explicit operator std::byte* () const {
        return reinterpret_cast<std::byte*>(_address);
     }

     //static const MemoryBlock null_block{ nullptr, 0ul };

    };
} // namespace mg::memory

#endif //CPP_BENCHMARKS_MEMORY_BLOCK_H
