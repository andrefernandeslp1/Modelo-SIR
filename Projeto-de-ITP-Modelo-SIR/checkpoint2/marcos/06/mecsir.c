#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mecsir.h"

#define TAXA_MORTALIDADE 0.02

//FUNÇÃO PARA CALCULAR b E k
void calcula_b_k(cenarios *v, int i){

    v[i].b = v[i].N_b/(v[i].T_b*v[i].S_b*v[i].I_b);
    v[i].k = v[i].m_k/(v[i].n_k*v[i].T_k);
}

//FUNÇÃO P/ CALCULAR MODELO S.I.R.
void calcula_sir(cenarios *v, int i){
    float So, Io, Ro, to;

    So = v[i].S;
    Io = v[i].I;
    Ro = v[i].R;
    to = v[i].t;

    v[i].S = So - v[i].h*v[i].b*So*Io;
    v[i].I = Io + v[i].h*(v[i].b*So*Io - v[i].k*Io);
    v[i].R = Ro + v[i].h*v[i].k*Io;
    v[i].t = to + v[i].h;

    v[i].mortes = v[i].R*TAXA_MORTALIDADE;
}

//FUÇÃO QUE FAZ A LEITURA DO ARQUIVO DE ENTRADA DE DADOS
void le_arquivo(cenarios *v, FILE *f, int *x){
    char aux[20], string[20];
    float valor;

    while(!feof(f)){

        fscanf(f,"%[^\n]\n",string);
        sscanf(string,"%[^,],%f", aux, &valor);
        if (strcmp(aux,"S")==0) {v[0].S = valor; *x += 1;}
        else if (strcmp(aux,"I")==0) {v[0].I = valor; *x += 1;}
        else if (strcmp(aux,"R")==0) {v[0].R = valor; *x += 1;}
        else if (strcmp(aux,"h")==0) {v[0].h = valor; *x += 1;}
        else if (strcmp(aux,"N_b")==0) {v[0].N_b = valor; *x += 1;}
        else if (strcmp(aux,"T_b")==0) {v[0].T_b = valor; *x += 1;}
        else if (strcmp(aux,"T_b2")==0) {v[0].T_b2 = valor; *x += 1;}
        else if (strcmp(aux,"tempoT_b2")==0) {v[0].tempoT_b2 = valor; *x += 1;}
        else if (strcmp(aux,"S_b")==0) {v[0].S_b = valor; *x += 1;}
        else if (strcmp(aux,"I_b")==0) {v[0].I_b = valor; *x += 1;}
        else if (strcmp(aux,"m_k")==0) {v[0].m_k = valor; *x += 1;}
        else if (strcmp(aux,"n_k")==0) {v[0].n_k = valor; *x += 1;}
        else if (strcmp(aux,"T_k")==0) {v[0].T_k = valor; *x += 1;}
        else if (strcmp(aux,"T_k2")==0) {v[0].T_k2 = valor; *x += 1;}
        else if (strcmp(aux,"tempoT_k2")==0) {v[0].tempoT_k2 = valor; *x += 1;}
        else if (strcmp(aux,"periodo")==0) {v[0].periodo = valor; *x += 1;}
        else fscanf(f,"\n");
    }
}

//LÊ PARÂMETROS PASSADOS NA LINHA DE COMANDO
void le_parametros_comando(cenarios *v, char *parametro, int *x, int *x2){
    char aux[20];
    float valor;

    sscanf(parametro,"%[^,],%f", aux, &valor);
    if (strcmp(aux,"S")==0) {v[0].S = valor; *x += 1;}
    else if (strcmp(aux,"I")==0) {v[0].I = valor; *x += 1;}
    else if (strcmp(aux,"R")==0) {v[0].R = valor; *x += 1;}
    else if (strcmp(aux,"h")==0) {v[0].h = valor; *x += 1;}
    else if (strcmp(aux,"N_b")==0) {v[0].N_b = valor; *x += 1;}
    else if (strcmp(aux,"T_b")==0) {v[0].T_b = valor; *x += 1;}
    else if (strcmp(aux,"T_b2")==0) {v[0].T_b2 = valor; *x += 1;}
    else if (strcmp(aux,"tempoT_b2")==0) {v[0].tempoT_b2 = valor; *x += 1;}
    else if (strcmp(aux,"S_b")==0) {v[0].S_b = valor; *x += 1;}
    else if (strcmp(aux,"I_b")==0) {v[0].I_b = valor; *x += 1;}
    else if (strcmp(aux,"m_k")==0) {v[0].m_k = valor; *x += 1;}
    else if (strcmp(aux,"n_k")==0) {v[0].n_k = valor; *x += 1;}
    else if (strcmp(aux,"T_k")==0) {v[0].T_k = valor; *x += 1;}
    else if (strcmp(aux,"T_k2")==0) {v[0].T_k2 = valor; *x += 1;}
    else if (strcmp(aux,"tempoT_k2")==0) {v[0].tempoT_k2 = valor; *x += 1;}
    else if (strcmp(aux,"periodo")==0) {v[0].periodo = valor; *x += 1;}
    else {printf("\nParametro \"%s,%.2f\" nao reconhecido. Verifique codigos dos parametros.\n", aux, valor); *x2 += 1;}
}

//IMPRIME CABEÇALHO DA TABELA DE SAÍDA
void imprime_cabecalho(FILE *f, cenarios *v, int i){

    fprintf(f,"S(t),I(t),R(t),mortes(t),tempo\n");
    fprintf(f,"%.0f,%.0f,%.0f,%.0f,%.0f\n",v[i].S,v[i].I,v[i].R,v[i].mortes,v[i].t);
    printf("Cen%crio %d (Padr%co)\n",160,i,198);
    printf("S,I,R,mortes,tempo\n");
    printf("%.0f,%.0f,%.0f,%.0f,%.0f\n",v[i].S,v[i].I,v[i].R,v[i].mortes,v[i].t);
}

//CHAMA A FUNÇÃO QUE FAZ OS CÁLCULOS E IMPRIME OS RESULTADOS
void imprime_dados(FILE *f, cenarios *v, int i){

    calcula_sir(v, i);

    fprintf(f,"%.4f,%.4f,%.4f,%.4f,%.1f\n",v[i].S,v[i].I,v[i].R,v[i].mortes,v[i].t);
    printf("%.4f,%.4f,%.4f,%.4f,%.1f\n",v[i].S,v[i].I,v[i].R,v[i].mortes,v[i].t);
}

//LIBERA PONTEIRO ALOCADO DINAMICAMENTE
void libera_c(cenarios **c){
    int i;
    for(i=0; i<3; i++) free(c[i]);
    free(*c);
    *c = NULL;
}

//LISTA DOS CÓDIGOS DOS PARÂMETROS DE ENTRADA
void lista_parametros(){
    printf("Codigos dos Parametros:\n");
    printf("S: numero de individuos suscetiveis (que ainda nao estao contaminados);\n");
    printf("I: numero de individuos infectados (capazes de infectar individuos S);\n");
    printf("R: numero de individuos removidos (que se recuperaram, tornaram-se imunes ou faleceram);\n");
    printf("h: pequeno intervalo de tempo entre calculos da projecao (em horas);\n");
    printf("N_b: numero de pessoas suscetiveis que se infectaram em uma observacao b (comportamento de contagio) de um periodo ja decorrido;\n");
    printf("T_b: intervalo de tempo da observacao b (em horas);\n");
    printf("T_b2: intervalo de tempo 2 da observacao b (em horas);\n");
    printf("tempoT_b2: tempo transcorrido ate implementacao de T_b2 (em horas);\n");
    printf("S_b: numero de pessoas suscetiveis no inicio da observacao b;\n");
    printf("I_b: numero de pessoas infectadas no inicio da observacao b;\n");
    printf("T_k: intervalo de tempo de observacao k (comportamento de recuperacao) de um periodo ja decorrido (em horas);\n");
    printf("T_k2: intervalo de tempo 2 da observacao k (comportamento de recuperacao) de um periodo ja decorrido (em horas);\n");
    printf("tempoT_k2: tempo transcorrido ata implementacao de T_k2 (em horas);\n");
    printf("n_k: individuos infectados em um intervalo de tempo T_k;\n");
    printf("m_k: individuos recuperados de um total n_k apos intervalo de tempo t_k;\n");
    printf("periodo: intervalo de tempo da modelagem (em dias).\n");
}
