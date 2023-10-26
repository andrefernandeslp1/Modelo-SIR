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
        //printf("string: %s\n", string);
        sscanf(string,"%[^,],%f", aux, &valor);
        //printf("aux: %s, valor: %.1f\n", aux, valor);
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

        /*
        fscanf(f,"%[^,],",aux);
        //printf("aux: %s\n", aux);
        if (strcmp(aux,"S")==0 || strcmp(aux,"\nS")==0) {fscanf(f,"%f\n",&v[0].S); *x += 1;}
        else if (strcmp(aux,"I")==0 || strcmp(aux,"\nI")==0) {fscanf(f,"%f\n",&v[0].I); *x += 1;}
        else if (strcmp(aux,"R")==0 || strcmp(aux,"\nR")==0) {fscanf(f,"%f\n",&v[0].R); *x += 1;}
        else if (strcmp(aux,"h")==0 || strcmp(aux,"\nh")==0) {fscanf(f,"%f\n",&v[0].h); *x += 1;}
        else if (strcmp(aux,"N_b")==0 || strcmp(aux,"\nN_b")==0) {fscanf(f,"%f\n",&v[0].N_b); *x += 1;}
        else if (strcmp(aux,"T_b")==0 || strcmp(aux,"\nT_b")==0) {fscanf(f,"%f\n",&v[0].T_b); *x += 1;}
        else if (strcmp(aux,"T_b2")==0 || strcmp(aux,"\nT_b2")==0) {fscanf(f,"%f\n",&v[0].T_b2); *x += 1;}
        else if (strcmp(aux,"tempoT_b2")==0 || strcmp(aux,"\ntempoT_b2")==0) {fscanf(f,"%f\n",&v[0].tempoT_b2); *x += 1;}
        else if (strcmp(aux,"S_b")==0 || strcmp(aux,"\nS_b")==0) {fscanf(f,"%f\n",&v[0].S_b); *x += 1;}
        else if (strcmp(aux,"I_b")==0 || strcmp(aux,"\nI_b")==0) {fscanf(f,"%f\n",&v[0].I_b); *x += 1;}
        else if (strcmp(aux,"m_k")==0 || strcmp(aux,"\nm_k")==0) {fscanf(f,"%f\n",&v[0].m_k); *x += 1;}
        else if (strcmp(aux,"n_k")==0 || strcmp(aux,"\nn_k")==0) {fscanf(f,"%f\n",&v[0].n_k); *x += 1;}
        else if (strcmp(aux,"T_k")==0 || strcmp(aux,"\nT_k")==0) {fscanf(f,"%f\n",&v[0].T_k); *x += 1;}
        else if (strcmp(aux,"T_k2")==0 || strcmp(aux,"\nT_k2")==0) {fscanf(f,"%f\n",&v[0].T_k2); *x += 1;}
        else if (strcmp(aux,"tempoT_k2")==0 || strcmp(aux,"\ntempoT_k2")==0) {fscanf(f,"%f\n",&v[0].tempoT_k2); *x += 1;}
        else if (strcmp(aux,"periodo")==0 || strcmp(aux,"\nperiodo")==0) {fscanf(f,"%f\n",&v[0].periodo); *x += 1;}
        else fscanf(f,"\n");
        */
    }

    calcula_b_k(v, 0);
    v[0].periodo *= 24;
    v[0].t=0;
    v[0].mortes=0;
    v[1] = v[2] = v[0];

}

//IMPRIME CABEÇALHO DA TABELA DE SAÍDA
void imprime_cabecalho(FILE *f, cenarios *v, int i){

    fprintf(f,"S,I,R,mortes,tempo\n");
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

void libera_c(cenarios **c){
    int i;
    for(i=0; i<3; i++) free(c[i]);
    free(*c);
    *c = NULL;
}
