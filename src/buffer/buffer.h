#ifndef CPP_BENCHMARKS_BUFFER_H
#define CPP_BENCHMARKS_BUFFER_H

#include <cstddef>
#include <type_traits>
#include "util/macros.h"

namespace mg {

    template<typename PtrType, typename BufType>
    class Buffer {
    public:
      using pointer = PtrType;

      constexpr Buffer() noexcept = default;

      constexpr Buffer(pointer p, std::size_t size) noexcept : _data{p}, _size{size} {}

      [[nodiscard]] constexpr pointer Pointer() const noexcept { return _data; }

      [[nodiscard]] constexpr std::size_t Size() const noexcept { return _size; }

      [[nodiscard]] constexpr bool IsEmpty() const noexcept { return Size() == 0; }


    private:
      pointer _data = nullptr;
      std::size_t _size = 0;
    };

}  // namespace mg

#endif // CPP_BENCHMARKS_BUFFER_H
