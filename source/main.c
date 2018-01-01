
#ifdef _MSC_VER
#   define DISABLE_WARNINGS_MSVC(x) \
    __pragma(warning(push)) \
    __pragma(warning(disable : 4001 4255 4710 4820))
#   define RESTORE_WARNINGS_MSVC() \
    __pragma(warning(pop))
#else
#   define DISABLE_WARNINGS_MSVC(x)
#   define RESTORE_WARNINGS_MSVC()
#endif


DISABLE_WARNINGS_MSVC(4001 4255 4710 4820)
#include <stdarg.h>
#include <stdio.h>
int printf_custom(const char * format, ...)
{
    int result;
    va_list args;
    va_start(args, format);
    result = vprintf(format, args);
    va_end(args);
    return result;
}
RESTORE_WARNINGS_MSVC()


#if defined(__clang__) || defined(__GNUC__)
#   if defined(__x86_64__) || (defined(__i386__) && defined(__SSE2__))
#       define PRM_GNUC_SSE2_STYLE
#   elif defined(__i386__)
#       define PRM_GNUC_PRE_SSE2_STYLE
#   else
#       error Unknown Arch with Clang / GCC compiler
#   endif
#elif defined(_MSC_VER)
#   if defined(_M_X64) || (defined(_M_IX86_FP) && (_M_IX86_FP > 1))
#       define PRM_MSVC_SSE2_STYLE
#   elif defined(_M_IX86_FP)
#       define PRM_MSVC_PRE_SSE2_STYLE
#   else
#       error Unknown Arch with MSVC compiler
#   endif
#endif

#ifndef PRM_EXTERN_C
#   if defined(__cplusplus)
#       define PRM_EXTERN_C extern "C"
#   else
#       define PRM_EXTERN_C
#   endif
#endif

#if defined(PRM_MSVC_SSE2_STYLE)
    PRM_EXTERN_C void _mm_mfence(void);
    PRM_EXTERN_C void _mm_lfence(void);
    PRM_EXTERN_C void _mm_sfence(void);

    #pragma intrinsic(_mm_mfence)
    #pragma intrinsic(_mm_lfence)
    #pragma intrinsic(_mm_sfence)

    #define prm_hw_mem_barrier_seq_cst() _mm_mfence()
    #define prm_hw_mem_barrier_acquire() _mm_lfence()
    #define prm_hw_mem_barrier_release() _mm_sfence()

#elif defined(PRM_GNUC_SSE2_STYLE)
    #define prm_hw_mem_barrier_seq_cst() __asm__ __volatile__ ("mfence" ::: "memory")
    #define prm_hw_mem_barrier_acquire() __asm__ __volatile__ ("lfence" ::: "memory")
    #define prm_hw_mem_barrier_release() __asm__ __volatile__ ("sfence" ::: "memory")

#elif defined(PRM_MSVC_PRE_SSE2_STYLE)

    PRM_EXTERN_C long _InterlockedExchange(long volatile * mem, long val);
    #pragma intrinsic(_InterlockedExchange)

    #define prm_while_0 \
        __pragma(warning(push)) \
        __pragma(warning(disable : 4127)) \
        while(0) \
        __pragma(warning(pop))

    #define prm_hw_mem_barrier_seq_cst() do { long Dummy; _InterlockedExchange(&Dummy, 0); } prm_while_0

    #undef prm_while_0

#elif defined(PRM_GNUC_PRE_SSE2_STYLE)
    #define prm_hw_mem_barrier_seq_cst() __sync_synchronize()

#endif

#if defined (PRM_MSVC_PRE_SSE2_STYLE) || defined(PRM_GNUC_PRE_SSE2_STYLE)
    #define prm_hw_mem_barrier_acquire() prm_hw_mem_barrier_seq_cst()
    #define prm_hw_mem_barrier_release() prm_hw_mem_barrier_seq_cst()

#endif

#if defined(PRM_MSVC_SSE2_STYLE) || defined(PRM_MSVC_PRE_SSE2_STYLE)
    PRM_EXTERN_C void _ReadWriteBarrier(void);
    PRM_EXTERN_C void _ReadBarrier(void);
    PRM_EXTERN_C void _WriteBarrier(void);

    #pragma intrinsic(_ReadWriteBarrier)
    #pragma intrinsic(_ReadBarrier)
    #pragma intrinsic(_WriteBarrier)

    #define prm_sw_mem_barrier_seq_cst() _ReadWriteBarrier()
    #define prm_sw_mem_barrier_acquire() _ReadBarrier()
    #define prm_sw_mem_barrier_release() _WriteBarrier()

#elif defined(PRM_GNUC_SSE2_STYLE) || defined(PRM_GNUC_PRE_SSE2_STYLE)
    #define prm_sw_mem_barrier_seq_cst() asm volatile("" ::: "memory")
    #define prm_sw_mem_barrier_acquire() prm_sw_mem_barrier_seq_cst()
    #define prm_sw_mem_barrier_release() prm_sw_mem_barrier_seq_cst()

#endif

#undef PRM_EXTERN_C


int main(void)
{
    printf_custom("Test !\n");

#if defined (_TEST_DEFINE)
    printf_custom("_TEST_DEFINE defined\n");
#endif

#if defined(TEST_DEFINE_VALUE) && (TEST_DEFINE_VALUE == 1)
    printf_custom("TEST_DEFINE_VALUE==1 defined\n");
#endif

#ifdef __clang__
    printf_custom("__clang__ defined, __clang_major__ : %d, __clang_minor__ : %d\n", __clang_major__, __clang_minor__);
#endif

#ifdef __GNUC__
    printf_custom("__GNUC__ defined, __GNUC__ : %d, __GNUC_MINOR__ : %d, __GNUC_PATCHLEVEL__ : %d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif

    prm_sw_mem_barrier_acquire();
    prm_sw_mem_barrier_release();
    prm_sw_mem_barrier_seq_cst();

    prm_hw_mem_barrier_acquire();
    prm_hw_mem_barrier_release();
    prm_hw_mem_barrier_seq_cst();

    return 0;
}
