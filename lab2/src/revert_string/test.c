#include <stdio.h>

int main(void)
{
    printf("hello, world\n");
    int a=0;
    switch(a){
     case 1: a=8;
     case 2: a=3;
     case 0: a++;
     case 5: a++;
    }
    return a;
}