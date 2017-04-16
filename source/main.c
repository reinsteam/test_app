
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

    return 0;
}
