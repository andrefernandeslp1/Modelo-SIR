#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"
#include "diario.h"

int main(int argc, char *argv[]){

    int i, tam;
    FILE *f1, *f2;

    if(argc<4) {
        printf("\ncomando incorreto!\n\nformatos de entrada possíveis:\n./programa -i arquivo_de_entrada -o arquivo_de_saida\nou\n./programa -o arquivo_de_saida -i arquivo_de_entrada\n\n");
        return 1;
    }
    if(argv[1][1]=='i' && argv[3][1]=='o'){
        f1 = fopen(argv[2],"r");
        f2 = fopen(argv[4],"w");
    }
    else if(argv[1][1]=='o' && argv[3][1]=='i'){
        f1 = fopen(argv[4],"r");
        f2 = fopen(argv[2],"w");
    }
    else {
        printf("\ncomando incorreto!\n\nformatos de entrada possíveis:\n./programa -i arquivo_de_entrada -o arquivo_de_saida\nou\n./programa -o arquivo_de_saida -i arquivo_de_entrada\n\n");
        return 1;
    }
    if(f1==NULL || f2==NULL){
        printf("ERRO de abertura dos arquivos");
        return 1;
    }

    diario *x;
    boletim *bol;
    bol = malloc(sizeof(boletim));
    x = lerDiarioCSV(&f1);

    fprintf(f2,"matrícula,nome,média,status\n");

    tam = x->n;
    x->n = 0;
    for(i=0; i<tam; i++){
        bol->n1 = x->b[i].n1;
        bol->n2 = x->b[i].n2;
        bol->n3 = x->b[i].n3;
        calculaMedia(bol);
        x->b[i].media = bol->media;
        x->b[i].status = bol->status;
        escreverBoletimCSV (&f2, x);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}

