#include <stdio.h>

void main()
{
    printf("\nfuncao recursiva!");

    printf("\nresultado %i", decremneta(3));

}

int decremneta(int x){

    if ( x <= 0) {
        return 1;
    }else{
        decremneta(x-1);
    }
}