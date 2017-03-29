

__pragma(warning(push))
__pragma(warning(disable : 4001 4255 4710 4820))
#include <stdio.h>
__pragma(warning(pop))

__pragma(warning(disable : 4710))

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