#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

typedef struct {
    float S, I, R, h, t, mortes;
    float b, k, N_b, T_b, T_b2, S_b, I_b, m_k, n_k, T_k, T_k2;
} cenarios;

cenarios *calcula_b_k(cenarios *v, int i){

    v[i].b = v[i].N_b/(v[i].T_b*v[i].S_b*v[i].I_b);
    v[i].k = v[i].m_k/(v[i].n_k*v[i].T_k);

    return v;
}

cenarios *calcula_sir(cenarios *v, int i){
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

    return v;
}

int main(int argc,char *argv[]){

    //setlocale(LC_ALL, "Portuguese");

    int i;
    float periodo, tempoT_b2, tempoT_k2;
    char aux[10];
    FILE *f_in, *f_out;

    cenarios *c;

    c = malloc(3*sizeof(cenarios));

    //for(i=0; i<3; i++) c[i] = malloc(sizeof(cenarios));

    if(argc<4){
        printf("\nComando incorreto!\n");
        printf("Formato correto: ./main cen%crio per%codo arquivo_de_entrada\n",160,161);
        printf("*cen%cios: 0 (Padr%co),\n",160,198);
        printf("          1 (Distanciamento/uso de m%cscaras),\n",160);
        printf("          2 (Melhoria nos protocolos de atendimento),\n");
        printf("          3 (Todos os cen%crios)\n",160);
        printf("*per%codo: per%codo de tempo da proje%c%co (em horas)\n\n",161,161,135,198);
        return 1;
    }

    sscanf(argv[2], "%f", &periodo);

    f_in = fopen(argv[3],"r");

    if(f_in == NULL){
        printf("ERRO de abertura do arquivo");
        return 1;
    }

    while(!feof(f_in)){

        fscanf(f_in,"%[^,],",aux);
        if (strcmp(aux,"S")==0) fscanf(f_in,"%f\n",&c[0].S);
        else if (strcmp(aux,"I")==0) fscanf(f_in,"%f\n",&c[0].I);
        else if (strcmp(aux,"R")==0) fscanf(f_in,"%f\n",&c[0].R);
        else if (strcmp(aux,"h")==0) fscanf(f_in,"%f\n",&c[0].h);
        else if (strcmp(aux,"N_b")==0) fscanf(f_in,"%f\n",&c[0].N_b);
        else if (strcmp(aux,"T_b")==0) fscanf(f_in,"%f\n",&c[0].T_b);
        else if (strcmp(aux,"T_b2")==0) fscanf(f_in,"%f\n",&c[0].T_b2);
        else if (strcmp(aux,"tempoT_b2")==0) fscanf(f_in,"%f\n",&tempoT_b2);
        else if (strcmp(aux,"S_b")==0) fscanf(f_in,"%f\n",&c[0].S_b);
        else if (strcmp(aux,"I_b")==0) fscanf(f_in,"%f\n",&c[0].I_b);
        else if (strcmp(aux,"m_k")==0) fscanf(f_in,"%f\n",&c[0].m_k);
        else if (strcmp(aux,"n_k")==0) fscanf(f_in,"%f\n",&c[0].n_k);
        else if (strcmp(aux,"T_k")==0)fscanf(f_in,"%f\n",&c[0].T_k);
        else if (strcmp(aux,"T_k2")==0)fscanf(f_in,"%f\n",&c[0].T_k2);
        else if (strcmp(aux,"tempoT_k2")==0)fscanf(f_in,"%f\n",&tempoT_k2);
        else fscanf(f_in,"\n");
    }

    fclose(f_in);

    calcula_b_k(c, 0);
    c[0].t=0;
    c[0].mortes=0;

    c[1] = c[2] = c[0];

    //CENÁRIO 0
    if(*argv[1]=='0' || *argv[1]=='3'){

        f_out = fopen("cenario_0.csv","w");

        fprintf(f_out,"S,I,R,mortes,tempo\n");
        fprintf(f_out,"%.0f,%.0f,%.0f,%.0f,%.0f\n",c[0].S,c[0].I,c[0].R,c[0].mortes,c[0].t);
        printf("Cen%crio 0 (Padr%co)\n",160,198);
        printf("S,I,R,mortes,tempo\n");
        printf("%.0f,%.0f,%.0f,%.0f,%.0f\n",c[0].S,c[0].I,c[0].R,c[0].mortes,c[0].t);

        //calcula_b_k(c, 0);

        while (c[0].t<periodo){

            calcula_sir(c, 0);

            fprintf(f_out,"%.4f,%.4f,%.4f,%.4f,%.1f\n",c[0].S,c[0].I,c[0].R,c[0].mortes,c[0].t);
            printf("%.4f,%.4f,%.4f,%.4f,%.1f\n",c[0].S,c[0].I,c[0].R,c[0].mortes,c[0].t);
        }
        fclose(f_out);
    }

    //CENÁRIO 1
    if(*argv[1]=='1' || *argv[1]=='3'){

        f_out = fopen("cenario_1.csv","w");

        fprintf(f_out,"S,I,R,mortes,tempo\n");
        fprintf(f_out,"%.0f,%.0f,%.0f,%.0f,%.0f\n",c[1].S,c[1].I,c[1].R,c[1].mortes,c[1].t);
        printf("Cen%crio 0 (Padr%co)\n",160,198);
        printf("S,I,R,mortes,tempo\n");
        printf("%.0f,%.0f,%.0f,%.0f,%.0f\n",c[1].S,c[1].I,c[1].R,c[1].mortes,c[1].t);

        //calcula_b_k(c, 1);

        while (c[1].t<periodo){

            calcula_sir(c, 1);

            fprintf(f_out,"%.4f,%.4f,%.4f,%.4f,%.1f\n",c[1].S,c[1].I,c[1].R,c[1].mortes,c[1].t);
            printf("%.4f,%.4f,%.4f,%.4f,%.1f\n",c[1].S,c[1].I,c[1].R,c[1].mortes,c[1].t);

            if(c[1].t>tempoT_b2) break;
        }

        c[1].T_b = c[1].T_b2;

        calcula_b_k(c, 1);

        while (c[1].t<periodo){

            calcula_sir(c, 1);

            fprintf(f_out,"%.4f,%.4f,%.4f,%.4f,%.1f\n",c[1].S,c[1].I,c[1].R,c[1].mortes,c[1].t);
            printf("%.4f,%.4f,%.4f,%.4f,%.1f\n",c[1].S,c[1].I,c[1].R,c[1].mortes,c[1].t);

        }

        fclose(f_out);
    }

    //CENÁRIO 2
    if(*argv[1]=='2' || *argv[1]=='3'){

        f_out = fopen("cenario_2.csv","w");

        fprintf(f_out,"S,I,R,mortes,tempo\n");
        fprintf(f_out,"%.0f,%.0f,%.0f,%.0f,%.0f\n",c[2].S,c[2].I,c[2].R,c[2].mortes,c[2].t);
        printf("Cen%crio 0 (Padr%co)\n",160,198);
        printf("S,I,R,mortes,tempo\n");
        printf("%.0f,%.0f,%.0f,%.0f,%.0f\n",c[2].S,c[2].I,c[2].R,c[2].mortes,c[2].t);

        //calcula_b_k(c, 1);

        while (c[2].t<periodo){

            calcula_sir(c, 2);

            fprintf(f_out,"%.4f,%.4f,%.4f,%.4f,%.1f\n",c[2].S,c[2].I,c[2].R,c[2].mortes,c[2].t);
            printf("%.4f,%.4f,%.4f,%.4f,%.1f\n",c[2].S,c[2].I,c[2].R,c[2].mortes,c[2].t);

            if(c[2].t>tempoT_k2) break;
        }

        c[2].T_b = c[2].T_b2;

        calcula_b_k(c, 2);

        while (c[2].t<periodo){

            calcula_sir(c, 2);

            fprintf(f_out,"%.4f,%.4f,%.4f,%.4f,%.1f\n",c[2].S,c[2].I,c[2].R,c[2].mortes,c[2].t);
            printf("%.4f,%.4f,%.4f,%.4f,%.1f\n",c[2].S,c[2].I,c[2].R,c[2].mortes,c[2].t);

        }

        fclose(f_out);
    }

    return 0;
}
