#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define LISTA_STOP " \n"
#define STOP_WORD "VEONEER"
#define FILE_PATH "C:\\Users\\iovan\\Desktop\\cuvinte.txt"



void testMalloc(){

    unsigned long long cnt=0;
    char* p;

    do{
        p=malloc(100);
        cnt++;
        if (cnt%10000==0){
            printf("%ul\n", cnt);
        }
    }while (p!=NULL);
    printf("Am reusit sa fac bulca de %llu ori\n", cnt);
}

char* citesteCuvant(FILE* f, char* stopChars){
    if (f==NULL) return NULL;
    int c=fgetc(f);
    ungetc(c,f);
    if (c==EOF){
        return NULL;
    }
    char *p=NULL;
    uint32_t nChar=0;
    do{
        char *q=realloc(p,nChar+1);
        if (q!=NULL){
            c=fgetc(f);
            q[nChar]=c;
            nChar++;
            p=q;
        }
        else{
            return NULL;
        }
    }while (c!=EOF&& strchr(stopChars, c)==NULL);
    p[nChar-1]='\0';
    return p;
}

char** citesteCuvinteDinFisier(FILE* pf){
    char *unCuvant=citesteCuvant(pf,"\n");
    printf("Primul cuv %s\n", unCuvant);
    int cnt=0;
    char** p=NULL;
    while (unCuvant!=NULL){
        cnt++;
        char** q=realloc(p, cnt*sizeof(char*));
        if (q!=NULL){
            q[cnt-1]=unCuvant;
            unCuvant=citesteCuvant(pf, "\n");
//            printf("Cuv este %s\n", unCuvant);
            p=q;
        }
        else{
            return p;
        }
    }
//    printf("AM gasit un total de %d cuvinte \n", cnt);
    return p;
}

int cntCuvEgalPrimul(FILE* f, char *cuvStop){
#ifndef FILE_PATH
    printf("Introduceti datale de la tastatura\n");
#endif // FILE_PATH
    char* primulCuv=citesteCuvant(f,LISTA_STOP);
    if (primulCuv!=NULL){
        if (strcmp(primulCuv, cuvStop)==0)
            return 0;
    }
    int cnt=0;
    char *unCuv=NULL;
    do{
        free(unCuv);
        unCuv=citesteCuvant(f,LISTA_STOP);
        if (unCuv!=NULL){
            if (strcmp(unCuv, primulCuv)==0){
                cnt++;
            }

        }
    }while (unCuv!=NULL && strcmp(unCuv, cuvStop)!=0);
    return cnt;
}

int main(){



#ifdef FILE_PATH
    FILE* pf=fopen(FILE_PATH,"rt");
    if (pf==NULL){
        printf("nu am reusit sa deschid fisierul\n");
        return 0;
    }
#endif
#ifndef FILE_PATH
    FILE* pf=stdin;
#endif // FILE_PATH

    char** pCuv=citesteCuvinteDinFisier(pf);
    for (int i=0; pCuv[i]!=NULL; i++){
        printf("Cuvantul de pe pozitia %d este %s\n", i, pCuv[i]);
    }
    printf("GATA PRIMA CITIRE");

    int nc=cntCuvEgalPrimul(pf, STOP_WORD);
    printf("Am gasit %d cuvinte egale cu primul\n", nc);

   // char* cuv=citesteCuvant(pf, ".,\n");
   // if (cuv!=NULL){
   //     printf("am citit cuvantul: %s\n", cuv);
   // }

#ifdef FILE_PATH
    fclose(pf);
#endif // FILE_PATH
return 0;
}
