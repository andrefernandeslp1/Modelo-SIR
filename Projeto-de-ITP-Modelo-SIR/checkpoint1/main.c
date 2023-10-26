#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

#define TAXA_MORTALIDADE 0.02

int main(int argc,char *argv[]){

    //setlocale(LC_ALL, "Portuguese");

    float S, So, I, Io, R, Ro, h, N_b, T_b, S_b, I_b, m_k, n_k, T_k, b, k, t=0, to, mortes=0, periodo;
    char aux[3];
    FILE *f_in, *f_out;

    //VERIFICA SE COMANDOS DE EXECUÇÃO DO PROGRAMA FORAM DIGITADOS CORRETAMENTE
    if(argc<3){
        printf("\nComando incorreto!\n");
        printf("Formato correto: ./main cen%crio arquivo_de_entrada\n",160,161);
        printf("*cen%cios: 0 (Padr%co),\n",160,198);
        printf("          1 (Distanciamento/uso de m%cscaras),\n",160);
        printf("          2 (Melhoria nos protocolos de atendimento),\n");
        printf("          3 (Todos os cen%crios)\n",160);
        return 1;
    }

    f_in = fopen(argv[2],"r");

    if(f_in == NULL){
        printf("ERRO de abertura do arquivo");
        return 1;
    }

    //LEITURA DO ARQUIVO
    while(!feof(f_in)){

        fscanf(f_in,"%[^,],",aux);
        if (strcmp(aux,"S")==0) fscanf(f_in,"%f\n",&S);
        else if (strcmp(aux,"I")==0) fscanf(f_in,"%f\n",&I);
        else if (strcmp(aux,"R")==0) fscanf(f_in,"%f\n",&R);
        else if (strcmp(aux,"h")==0) fscanf(f_in,"%f\n",&h);
        else if (strcmp(aux,"N_b")==0) fscanf(f_in,"%f\n",&N_b);
        else if (strcmp(aux,"T_b")==0) fscanf(f_in,"%f\n",&T_b);
        else if (strcmp(aux,"S_b")==0) fscanf(f_in,"%f\n",&S_b);
        else if (strcmp(aux,"I_b")==0) fscanf(f_in,"%f\n",&I_b);
        else if (strcmp(aux,"m_k")==0) fscanf(f_in,"%f\n",&m_k);
        else if (strcmp(aux,"n_k")==0) fscanf(f_in,"%f\n",&n_k);
        else if (strcmp(aux,"T_k")==0) fscanf(f_in,"%f\n",&T_k);
        else if (strcmp(aux,"periodo")==0) fscanf(f_in,"%f\n",&periodo);
        else fscanf(f_in,"\n");
    }
    periodo *= 24;

    b = N_b/(T_b*S_b*I_b);
    k = m_k/(n_k*T_k);

    //CENÁRIO 0
    if(*argv[1] == '0'){

        f_out = fopen("cenario_0.csv","w");

        //IMPRESSÃO DO CABEÇALHO DA TABELA
        fprintf(f_out,"S(t),I(t),R(t),mortes,tempo(t)\n");
        fprintf(f_out,"%.0f,%.0f,%.0f,%.0f,%.0f\n",S,I,R,mortes,t);
        printf("Cen%crio 0 (Padr%co)\n",160,198);
        printf("S(t),I(t),R(t),mortes,tempo(t)\n");
        printf("%.0f,%.0f,%.0f,%.0f,%.0f\n",S,I,R,mortes,t);

        //LAÇO PARA REALIZAÇÃO DOS CÁLCULOS
        while (t<periodo){

            So = S;
            Io = I;
            Ro = R;
            to = t;

            S = So - h*b*So*Io;
            I = Io + h*(b*So*Io - k*Io);
            R = Ro + h*k*Io;
            t = to + h;

            mortes = R*TAXA_MORTALIDADE;

            //IMPRESSÃO DOS DADOS
            fprintf(f_out,"%.4f,%.4f,%.4f,%.4f,%.1f\n",S,I,R,mortes,t);
            printf("%.4f,%.4f,%.4f,%.4f,%.1f\n",S,I,R,mortes,t);

        }

        fclose(f_in);
        fclose(f_out);
        return 0;
    }
}
