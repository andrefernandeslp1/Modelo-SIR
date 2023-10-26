#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ler.h"
#include "imprimir.h"
#include "calcular.h"

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

    calcula_b_k(v, i);

    while (v[i].t < v[i].periodo){
        calcula_sir(v, i);
        fprintf(f,"%.4f,%.4f,%.4f,%.4f,%.1f\n",v[i].S,v[i].I,v[i].R,v[i].mortes,v[i].t);
        printf("%.4f,%.4f,%.4f,%.4f,%.1f\n",v[i].S,v[i].I,v[i].R,v[i].mortes,v[i].t);

        if(i==1) if(v[i].t > v[i].tempoT_b2) break;
        if(i==2) if(v[i].t > v[i].tempoT_k2) break;
    }
    //CENÁRIO 1 - TRANSIÇÃO PARA NOVO PARÂMETRO DE T_b.
    if(i==1){
        v[i].T_b = v[i].T_b2;
        calcula_b_k(v, i);
        while (v[i].t < v[i].periodo){
            calcula_sir(v, i);
            fprintf(f,"%.4f,%.4f,%.4f,%.4f,%.1f\n",v[i].S,v[i].I,v[i].R,v[i].mortes,v[i].t);
            printf("%.4f,%.4f,%.4f,%.4f,%.1f\n",v[i].S,v[i].I,v[i].R,v[i].mortes,v[i].t);
        }
    }
    //CENÁRIO 2 - TRANSIÇÃO PARA NOVO PARÂMETRO DE T_K.
    if(i==2){
        v[i].T_k = v[i].T_k2;
        calcula_b_k(v, i);
        while (v[i].t < v[i].periodo){
            calcula_sir(v, i);
            fprintf(f,"%.4f,%.4f,%.4f,%.4f,%.1f\n",v[i].S,v[i].I,v[i].R,v[i].mortes,v[i].t);
            printf("%.4f,%.4f,%.4f,%.4f,%.1f\n",v[i].S,v[i].I,v[i].R,v[i].mortes,v[i].t);
        }
    }
}

//LIBERA PONTEIRO ALOCADO DINAMICAMENTE
void libera_c(cenarios **c){
    int i;
    for(i=0; i<3; i++) free(c[i]);
    free(*c);
    *c = NULL;
}
