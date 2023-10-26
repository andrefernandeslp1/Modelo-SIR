#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

typedef struct {
    float S, I, R, h, t, mortes;
    float b, k, N_b, T_b, T_b2, S_b, I_b, m_k, n_k, T_k, T_k2, tempoT_b2, tempoT_k2, periodo;
} cenarios;

void calcula_b_k(cenarios *v, int i){

    v[i].b = v[i].N_b/(v[i].T_b*v[i].S_b*v[i].I_b);
    v[i].k = v[i].m_k/(v[i].n_k*v[i].T_k);

}

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

    v[i].mortes = v[i].R*0.02;

}

void le_arquivo(cenarios *v, FILE *f){
    char aux[10];

    while(!feof(f)){

        fscanf(f,"%[^,],",aux);
        if (strcmp(aux,"S")==0) fscanf(f,"%f\n",&v[0].S);
        else if (strcmp(aux,"I")==0) fscanf(f,"%f\n",&v[0].I);
        else if (strcmp(aux,"R")==0) fscanf(f,"%f\n",&v[0].R);
        else if (strcmp(aux,"h")==0) fscanf(f,"%f\n",&v[0].h);
        else if (strcmp(aux,"N_b")==0) fscanf(f,"%f\n",&v[0].N_b);
        else if (strcmp(aux,"T_b")==0) fscanf(f,"%f\n",&v[0].T_b);
        else if (strcmp(aux,"T_b2")==0) fscanf(f,"%f\n",&v[0].T_b2);
        else if (strcmp(aux,"tempoT_b2")==0) fscanf(f,"%f\n",&v[0].tempoT_b2);
        else if (strcmp(aux,"S_b")==0) fscanf(f,"%f\n",&v[0].S_b);
        else if (strcmp(aux,"I_b")==0) fscanf(f,"%f\n",&v[0].I_b);
        else if (strcmp(aux,"m_k")==0) fscanf(f,"%f\n",&v[0].m_k);
        else if (strcmp(aux,"n_k")==0) fscanf(f,"%f\n",&v[0].n_k);
        else if (strcmp(aux,"T_k")==0)fscanf(f,"%f\n",&v[0].T_k);
        else if (strcmp(aux,"T_k2")==0)fscanf(f,"%f\n",&v[0].T_k2);
        else if (strcmp(aux,"tempoT_k2")==0)fscanf(f,"%f\n",&v[0].tempoT_k2);
        else if (strcmp(aux,"periodo")==0)fscanf(f,"%f\n",&v[0].periodo);
        else fscanf(f,"\n");
    }

    calcula_b_k(v, 0);
    v[0].t=0;
    v[0].mortes=0;
    v[1] = v[2] = v[0];

}

void imprime_cabecalho(FILE *f, cenarios *v, int i){

    fprintf(f,"S,I,R,mortes,tempo\n");
    fprintf(f,"%.0f,%.0f,%.0f,%.0f,%.0f\n",v[i].S,v[i].I,v[i].R,v[i].mortes,v[i].t);
    printf("Cen%crio %d (Padr%co)\n",160,i,198);
    printf("S,I,R,mortes,tempo\n");
    printf("%.0f,%.0f,%.0f,%.0f,%.0f\n",v[i].S,v[i].I,v[i].R,v[i].mortes,v[i].t);

}

void imprime_dados(FILE *f, cenarios *v, int i){

    calcula_sir(v, i);

    fprintf(f,"%.4f,%.4f,%.4f,%.4f,%.1f\n",v[i].S,v[i].I,v[i].R,v[i].mortes,v[i].t);
    printf("%.4f,%.4f,%.4f,%.4f,%.1f\n",v[i].S,v[i].I,v[i].R,v[i].mortes,v[i].t);

}

int main(int argc,char *argv[]){

    //setlocale(LC_ALL, "Portuguese");

    FILE *f_in, *f_out;

    cenarios *c;

    c = malloc(3*sizeof(cenarios));

    if(argc<3){
        printf("\nComando incorreto!\n");
        printf("Formato correto: ./main cen%crio arquivo_de_entrada\n",160);
        printf("*cen%cios: 0 (Padr%co),\n",160,198);
        printf("          1 (Distanciamento/uso de m%cscaras),\n",160);
        printf("          2 (Melhoria nos protocolos de atendimento),\n");
        printf("          3 (Todos os cen%crios)\n",160);
        return 1;
    }

    //ABERTURA DO ARQUIVO DE ENTRADA
    f_in = fopen(argv[2],"r");

    if(f_in == NULL){
        printf("ERRO de abertura do arquivo");
        return 1;
    }

    //LEITURA DO ARQUIVO
    le_arquivo(c, f_in);

    fclose(f_in);

    //CENÁRIO 0
    if(*argv[1]=='0' || *argv[1]=='3'){

        f_out = fopen("cenario_0.csv","w");

        imprime_cabecalho(f_out, c, 0);

        while (c[0].t < c[0].periodo)
            imprime_dados(f_out, c, 0);

        fclose(f_out);
    }

    //CENÁRIO 1
    if(*argv[1]=='1' || *argv[1]=='3'){

        f_out = fopen("cenario_1.csv","w");

        imprime_cabecalho(f_out, c, 1);

        while (c[1].t < c[1].periodo){

            imprime_dados(f_out, c, 1);

            if(c[1].t > c[1].tempoT_b2) break;
        }

        c[1].T_b = c[1].T_b2;

        calcula_b_k(c, 1);

        while (c[1].t < c[1].periodo)
            imprime_dados(f_out, c, 1);

        fclose(f_out);
    }

    //CENÁRIO 2
    if(*argv[1]=='2' || *argv[1]=='3'){

        f_out = fopen("cenario_2.csv","w");

        imprime_cabecalho(f_out, c, 2);

        while (c[2].t < c[2].periodo){

            imprime_dados(f_out, c, 2);

            if(c[2].t > c[2].tempoT_b2) break;
        }

        c[2].T_k = c[2].T_k2;

        calcula_b_k(c, 2);

        while (c[2].t < c[2].periodo)
            imprime_dados(f_out, c, 2);

        fclose(f_out);
    }

    return 0;
}
