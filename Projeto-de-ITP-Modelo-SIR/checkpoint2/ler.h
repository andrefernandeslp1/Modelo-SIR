#include<stdio.h>

//STRUCT PARA ARMAZENAR AS VARIÁVEIS UTILIZADAS NO MODELO
typedef struct {
    float S, I, R, h, t, mortes;
    float b, k, N_b, T_b, T_b2, S_b, I_b, m_k, n_k, T_k, T_k2, tempoT_b2, tempoT_k2, periodo;
} cenarios;

void le_arquivo(cenarios *v, FILE *f, int *x);

void le_parametros_comando(cenarios *v, char *parametro, int *x, int *x2);

void lista_parametros();
