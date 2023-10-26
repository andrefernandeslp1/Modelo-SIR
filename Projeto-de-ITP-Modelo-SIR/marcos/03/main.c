#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

typedef struct {
    float S, I, R, h, t, mortes;
    float b, k, N_b, T_b, T_b2, S_b, I_b, m_k, n_k, T_k, T_k2;
} *parametros;

parametros *criav_p1(parametros *p1){

}

parametros *cria_p2(parametros *p2){

}

parametros *calcula_b_k(parametros *p1){

}

parametros *calcula_sir(parametros *p2){

}

int main(int argc,char *argv[]){

    //setlocale(LC_ALL, "Portuguese");

    parametros *p1, *p2;
    float S, I, R, h, N_b, T_b, T_b2, tempoT_b2, S_b, I_b, m_k, n_k, T_k, T_k2, tempoT_k2;
    float So, Io, Ro, b, k, t, to, mortes, periodo;
    char cabecalho[50], aux[10];
    FILE *f_in, *f_out;

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
    //fscanf(f_in,"%[^\n]\n",cabecalho);
    //fscanf(f_in,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",&S,&I,&R,&h,&N_b,&T_b,&S_b,&I_b,&m_k,&n_k,&T_k);
    while(!feof(f_in)){

        fscanf(f_in,"%[^,],",aux);
        if (strcmp(aux,"S")==0) fscanf(f_in,"%f\n",&S);
        else if (strcmp(aux,"I")==0) fscanf(f_in,"%f\n",&I);
        else if (strcmp(aux,"R")==0) fscanf(f_in,"%f\n",&R);
        else if (strcmp(aux,"h")==0) fscanf(f_in,"%f\n",&h);
        else if (strcmp(aux,"N_b")==0) fscanf(f_in,"%f\n",&N_b);
        else if (strcmp(aux,"T_b")==0) fscanf(f_in,"%f\n",&T_b);
        else if (strcmp(aux,"T_b2")==0) fscanf(f_in,"%f\n",&T_b2);
        else if (strcmp(aux,"tempoT_b2")==0) fscanf(f_in,"%f\n",&tempoT_b2);
        else if (strcmp(aux,"S_b")==0) fscanf(f_in,"%f\n",&S_b);
        else if (strcmp(aux,"I_b")==0) fscanf(f_in,"%f\n",&I_b);
        else if (strcmp(aux,"m_k")==0) fscanf(f_in,"%f\n",&m_k);
        else if (strcmp(aux,"n_k")==0) fscanf(f_in,"%f\n",&n_k);
        else if (strcmp(aux,"T_k")==0)fscanf(f_in,"%f\n",&T_k);
        else if (strcmp(aux,"T_k2")==0)fscanf(f_in,"%f\n",&T_k2);
        else if (strcmp(aux,"tempoT_k2")==0)fscanf(f_in,"%f\n",&tempoT_k2);
        else fscanf(f_in,"\n");
    }
    b = N_b/(T_b*S_b*I_b);
    k = m_k/(n_k*T_k);

    //CENÁRIO 0
    if(*argv[1]=='0'){
        t=0;
        mortes=0;

        f_out = fopen("cenario_0.csv","w");

        fprintf(f_out,"S,I,R,mortes,tempo\n");
        fprintf(f_out,"%.0f,%.0f,%.0f,%.0f,%.0f\n",S,I,R,mortes,t);
        printf("Cen%crio 0 (Padr%co)\n",160,198);
        printf("S,I,R,mortes,tempo\n");
        printf("%.0f,%.0f,%.0f,%.0f,%.0f\n",S,I,R,mortes,t);

        while (t<periodo){

            So = S;
            Io = I;
            Ro = R;
            to = t;

            S = So - h*b*So*Io;
            I = Io + h*(b*So*Io - k*Io);
            R = Ro + h*k*Io;
            t = to + h;

            mortes = R*0.02;

            fprintf(f_out,"%.4f,%.4f,%.4f,%.4f,%.1f\n",S,I,R,mortes,t);
            printf("%.4f,%.4f,%.4f,%.4f,%.1f\n",S,I,R,mortes,t);

        }

        fclose(f_in);
        fclose(f_out);
        return 0;
    }
}
