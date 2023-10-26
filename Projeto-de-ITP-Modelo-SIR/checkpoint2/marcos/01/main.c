#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mecsir.h"



//FUNÇÃO PRINCIPAL
int main(int argc,char *argv[]){

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

    //CHAMA A FUNÇÃO DE LEITURA DO ARQUIVO
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
