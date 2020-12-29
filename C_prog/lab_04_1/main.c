#include "my_strpbrk.h"
#include <stdio.h>
#include <string.h>

#define OK 0


int main()
{                     
    char *ans = my_strpbrk("ddddbbbb", "blabla");

    if (ans == NULL)
    {
        printf("my_strpbrk : NOT FOUND\n");
        printf("strpbrk : NOT FOUND\n");
    }
    else
    {
        printf("find result in %d\n", *my_strpbrk("ddddbbbb", "blabla"));
        printf("find result in %d\n", *strpbrk("ddddbbbb", "blabla"));                         
    }

    char *ans1 = my_strpbrk("pamcaskjcasdkjdfasu", "0987654321");

    if (ans1 == NULL)
    {
        printf("my_strpbrk : NOT FOUND\n");
        printf("strpbrk : NOT FOUND\n");
    }
    else
    {
        printf("find result in %d\n", *my_strpbrk("pamcaskjcasdkjdfasu", "0987654321"));                          
        printf("find result in %d\n", *strpbrk("pamcaskjcasdkjdfasu", "0987654321"));   
    }
    char *ans2 = my_strpbrk(" ", ",.,/,ajsdka");

    if (ans2 == NULL)
    {
        printf("my_strpbrk : NOT FOUND\n");
        printf("strpbrk : NOT FOUND\n");
    }
    else
    {
        printf("find result in %d\n", *my_strpbrk(" ", ",.,/,ajsdka"));                          
        printf("find result in %d\n", *strpbrk(" ", ",.,/,ajsdka"));   
    }

    char *ans3 = my_strpbrk("a", "cba");

    if (ans3 == NULL)
    {
        printf("my_strpbrk : NOT FOUND\n");
        printf("strpbrk : NOT FOUND\n");
    }
    else
    {
        printf("find result in %d\n", *my_strpbrk("a", "cba"));                          
        printf("find result in %d\n", *strpbrk("a", "cba"));   
    }


    return OK;
}