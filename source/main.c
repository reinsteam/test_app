#include <stdio.h>

int main()
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