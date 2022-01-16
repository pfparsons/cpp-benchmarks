#define COMPILER_IS_MSVC 0
#define COMPILER_IS_CLANG 0
#define COMPILER_IS_APPLE_CLANG 0
#define COMPILER_IS_LLVM_CLANG 0
#define COMPILER_IS_GNU 0

// clang-format off
#if defined(_MSC_VER)
    #undef COMPILER_IS_MSVC
    #define COMPILER_IS_MSVC 1
#elif defined(__clang__)
    #undef COMPILER_IS_CLANG
    #define COMPILER_IS_CLANG 1
    #if defined(__apple_build_version__)
        #undef COMPILER_IS_APPLE_CLANG
        #define COMPILER_IS_APPLE_CLANG 1
    #else
        #undef COMPILER_IS_LLVM_CLANG
        #define COMPILER_IS_LLVM_CLANG 1
    #endif
#elif defined(__GNUC__)
    #undef COMPILER_IS_GNU
    #define COMPILER_IS_GNU 1
#endif
// clang-format on

#define COMPILER_IS_GNU_LIKE (COMPILER_IS_GNU || COMPILER_IS_CLANG)
