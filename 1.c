#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int cmpstr (const void * a, const void * b ) {
    char *pa=*(char **)a;
    char *pb=*(char **)b;
    if (strlen(pa)>strlen(pb)){
        return -1;
    }
    else {
        if (strlen(pa)<strlen(pb)){
            return 1;
        }
        else{
            return strcmp(pa, pb);
        }
    }
}
int main(){
    char* str[] = {"ioan","gogu","ana","gigi","maria"};
    int n = sizeof(str) / sizeof(char *);
    //int n=5;
    qsort(str, n, sizeof(char *), cmpstr);
    for (int i=0; i<n; ++i)
        printf("%d: %s\n", i, str[i]);
}
