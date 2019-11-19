#include <stdio.h>

typedef struct Punct{
    int x;
    int y;
    int culoare;
} Punct_t;

int main(){


    Punct_t p={2,3, 17};

    Punct_t* pp=&p;

   // Punct_t aux=*pp;

    int xPunct= *pp.x;

    printf("X_ul punctului este %d\n", xPunct);


return 0;
}
