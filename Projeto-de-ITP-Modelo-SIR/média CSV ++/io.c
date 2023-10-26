#include <stdio.h>
#include <string.h>
#include "diario.h"
#include "io.h"

/*
Função para fazer a leitura de um arquivo CSV contendo as notas dos alunos de uma turma. Retorna um ponteiro para um diário. Caso ocorra algum erro, retornar NULL. O arquivo deverá ser aberto e fechado no código principal (main).
*/
diario *lerDiarioCSV (FILE **f) {
    int i;
    char cabecalho[50];
    diario *x;
    x = malloc(sizeof(diario));
    x->n = 0;
    x->b = malloc(10*sizeof(boletim));
    fscanf(*f,"%[^\n]\n",cabecalho);

    for(i = 0; !feof(*f); i++){
        x->b[i].nome = malloc(20*sizeof(char*));
        x->b[i].status = malloc(20*sizeof(char*));
        fscanf(*f,"%d,%[^,],%f,%f,%f\n", &x->b[i].matricula, x->b[i].nome, &x->b[i].n1, &x->b[i].n2, &x->b[i].n3);
        x->n +=1;
        if(i>10) x->b = realloc(x->b, i*sizeof(boletim));
    }
    printf("teste");
    if(*f == NULL) return NULL;
    return x;
}

/*
Função para fazer a escrita de um arquivo CSV do diário da turma. Retorna a quantidade de boletins gravados com sucesso. Caso ocorra algum erro, retornar -1. O arquivo deverá ser aberto e fechado no código principal (main)
*/
int escreverBoletimCSV (FILE **f, diario *d) {

    int i = d->n;

    fprintf(*f,"%d,%s,%.1f,%s\n", d->b[i].matricula, d->b[i].nome, d->b[i].media, d->b[i].status);

    d->n += 1;
    if(*f == NULL) return -1;
    return i+1;
}
