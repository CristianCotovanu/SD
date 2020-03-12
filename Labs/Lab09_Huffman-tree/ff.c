#include <stdio.h>
#include <string.h>

int main(){
    int frec[10] ;
    char *v = "abbac";
    char *c = v;
    int i = 5;
    while (i){
        frec[*v]++;
        printf("%d ", frec[*v]);
        v++;
        i--;
    }
    for (int i = 0; i < 3; i++){
       printf("%d ", frec[c[i]]);
       c++;
    }
}