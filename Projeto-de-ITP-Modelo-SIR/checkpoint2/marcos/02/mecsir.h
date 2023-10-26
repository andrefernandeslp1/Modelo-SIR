#include <stdio.h>

//STRUCT PARA ARMAZENAR AS VARIÁVEIS UTILIZADAS NO MODELO
typedef struct {
    float S, I, R, h, t, mortes;
    float b, k, N_b, T_b, T_b2, S_b, I_b, m_k, n_k, T_k, T_k2, tempoT_b2, tempoT_k2, periodo;
} cenarios;

void calcula_b_k(cenarios *v, int i);

void calcula_sir(cenarios *v, int i);

void le_arquivo(cenarios *v, FILE *f, int *x);

void imprime_cabecalho(FILE *f, cenarios *v, int i);

void imprime_dados(FILE *f, cenarios *v, int i);
