#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ler.h"
#include "calcular.h"

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
