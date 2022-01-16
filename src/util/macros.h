#ifndef CPP_BENCHMARKS_MACROS_H
#define CPP_BENCHMARKS_MACROS_H

#include "compiler_macros.h"

/* --------------------------------------------------------------------------------------
    Stringizing
--------------------------------------------------------------------------------------- */
#ifndef STR
#define STR_HELPER( ... ) #__VA_ARGS__
#define STR( ... ) STR_HELPER( __VA_ARGS__ )
#endif

/* --------------------------------------------------------------------------------------
    Force Inline
--------------------------------------------------------------------------------------- */
#if defined( COMPILER_IS_GNU_LIKE )
#define REALLY_INLINE inline __attribute__( ( always_inline ) )
#elif defined( COMPILER_IS_MSVC )
#define REALLY_INLINE __forceinline
#else
#define REALLY_INLINE
#endif

/* --------------------------------------------------------------------------------------
    Branch Predictor
--------------------------------------------------------------------------------------- */
#if defined( COMPILER_IS_GNU_LIKE )
#define PREDICT_FALSE( x ) ( __builtin_expect( !!( x ), 0 ) )
#define PREDICT_TRUE( x ) ( __builtin_expect( !!( x ), 1 ) )
#else
#define PREDICT_FALSE( x ) ( x )
#define PREDICT_TRUE( x ) ( x )
#endif

#endif // CPP_BENCHMARKS_MACROS_H
