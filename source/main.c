
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
#include <stdio.h>
RESTORE_WARNINGS_MSVC()


DISABLE_WARNINGS_MSVC(4710)

int main(void)
{
    printf("Test !");

#if defined (_TEST_DEFINE)
    printf("_TEST_DEFINE defined");
#endif

#if defined(TEST_DEFINE_VALUE) && (TEST_DEFINE_VALUE == 1)
    printf("TEST_DEFINE_VALUE==1 defined");
#endif

    return 0;
}