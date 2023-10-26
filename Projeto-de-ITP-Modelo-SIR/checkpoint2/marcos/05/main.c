#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mecsir.h"

//FUNÇÃO PRINCIPAL
int main(int argc,char *argv[]){
    int i, cont = 0;
    char string0[20]={"cenario_0.csv"}, string1[20]={"cenario_1.csv"}, string2[20]={"cenario_2.csv"};
    FILE *f_in, *f_out;
    cenarios *c;

    c = malloc(3*sizeof(cenarios));

    if(argc<3){
        printf("\nComandos incorretos!\n");
        printf("Formato correto: ./nome_do_programa comandos_1 comandos_2 ... comandos_n\n");
        printf("Comandos: -i arquivo_de_entrada (passagem do arquivo com os parametros de entrada);\n");
        printf("          -o0 arquivo_de_saida (fornece o nome do arquivo de saida para cenario 0);\n");
        printf("          -o1 arquivo_de_saida (fornece o nome do arquivo de saida para cenario 1);\n");
        printf("          -o2 arquivo_de_saida (fornece o nome do arquivo de saida para cenario 2);\n");
        printf("OBS: caso nao sejam fornecidos os nomes dos arquivos de saida, nomes padroes lhes serão atribuidos.\n");
        return 1;
    }

    //LEITURA DOS COMANDOS PASSADOS NO TERMINAL
    for(i=1; i<argc; i++){
        if(argv[i][0]=='-') {
            //ABERTURA DO ARQUIVO DE ENTRADA
            if(argv[i][1]=='i'){
                f_in = fopen(argv[i+1],"r");
                if(f_in == NULL){
                    printf("ERRO de abertura do arquivo");
                    return 1;
                }
            }
            //NOMEIA ARQUIVOS DE SAÍDA. CASO NÃO TENHAM SIDO PASSADOS NA LINHA DE COMANDO, NOMES PADRÕES SERÃO ATRIBUÍDOS.
            if(argv[i][1]=='o'){
                if(argv[i][2]=='0') strcpy(string0, argv[i+1]);
                if(argv[i][2]=='1') strcpy(string1, argv[i+1]);
                if(argv[i][2]=='2') strcpy(string2, argv[i+1]);
            }
        }
    }

    //CHAMA A FUNÇÃO DE LEITURA DO ARQUIVO DE ENTRADA E VERIFICA SUFICIÊNCIA DE PARÂMETROS
    le_arquivo(c, f_in, &cont);
    if(cont<16) {
        printf("Problema no arquivo de entrada! Revise os par%cmetros.",131);
        return 1;
    }
    fclose(f_in);

    //CENÁRIO 0
    f_out = fopen(string0,"w");

    imprime_cabecalho(f_out, c, 0);

    while (c[0].t < c[0].periodo)
        imprime_dados(f_out, c, 0);

    fclose(f_out);

    //CENÁRIO 1
    f_out = fopen(string1,"w");

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

    //CENÁRIO 2
    f_out = fopen(string2,"w");

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

    //LIBERA PONTEIRO ALOCADO DINAMICAMENTE
    libera_c(&c);

    return 0;
}
