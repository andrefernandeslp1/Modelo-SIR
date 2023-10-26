#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ler.h"
#include "calcular.h"
#include "imprimir.h"

//FUNÇÃO PRINCIPAL
int main(int argc,char *argv[]){
    int i, cont = 0, cont2 = 0;
    char string0[20]={"cenario_0.csv"}, string1[20]={"cenario_1.csv"}, string2[20]={"cenario_2.csv"};
    FILE *f_in, *f_out;
    cenarios *c;

    c = malloc(3*sizeof(cenarios));

//INSTRUÇÕES APRESENTADAS CASO A LINHA DE COMANDO ESTEJA INCORRETA
    if(argc<3){
        printf("\nComando incorreto!\n\n");
        printf("Formato correto de entrada: ./nome_do_programa comandos_1 comandos_2 ... comandos_n\n");
        printf("Comandos: -i arquivo_de_entrada (passagem do arquivo com os parametros de entrada);\n");
        printf("          -o0 arquivo_de_saida (fornece o nome do arquivo de saida para cenario 0);\n");
        printf("          -o1 arquivo_de_saida (fornece o nome do arquivo de saida para cenario 1);\n");
        printf("          -o2 arquivo_de_saida (fornece o nome do arquivo de saida para cenario 2);\n");
        printf("          -p nome_do_parametro,valor (parametro fornecido na linha de comando);\n");
        printf("OBS: caso nao sejam fornecidos os nomes dos arquivos de saida, nomes padroes lhes serao atribuidos.\n\n");
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
            //NOMEIA ARQUIVOS DE SAÍDA. CASO NÃO SEJAM PASSADOS NA LINHA DE COMANDO, NOMES PADRÕES SERÃO ATRIBUÍDOS.
            if(argv[i][1]=='o'){
                if(argv[i][2]=='0') strcpy(string0, argv[i+1]);
                if(argv[i][2]=='1') strcpy(string1, argv[i+1]);
                if(argv[i][2]=='2') strcpy(string2, argv[i+1]);
            }
        }
    }

//LER ARQUIVO DE ENTRADA
    le_arquivo(c, f_in, &cont);
    fclose(f_in);

//RECEBE PARÂMETROS PASSADOS NA LINHA DE COMANDO
    for(i=1; i<argc; i++)
        if(argv[i][0]=='-')
            if(argv[i][1]=='p')
                le_parametros_comando(c, argv[i+1], &cont, &cont2);

//ALERTA SOBRE ERROS NA PASSAGEM DE PARÂMETROS DE ENTRADA PELA LINHA DE COMANDO
    if(cont2>0) {
        printf("\n");
        lista_parametros();
        printf("\n");
        return 1;
    }

//VERIFICAR SUFICIÊNCIA DE PARÂMETROS DE ENTRADA PASSADOS PELO USUÁRIO (LINHA DE COMANDO + ARQUIVO DE ENTRADA)
    if(cont<16) {
        printf("Parametros de entrada insuficientes!");
        return 1;
    }

//CONFIGURAÇÃO DE PARÂMETROS PADRÃO
    c[0].periodo *= 24;
    c[0].t=0;
    c[0].mortes=0;
    c[1] = c[2] = c[0];

//*** CENÁRIO 0 ***
    f_out = fopen(string0,"w");
    imprime_cabecalho(f_out, c, 0);
    imprime_dados(f_out, c, 0);
    fclose(f_out);

//*** CENÁRIO 1 ***
    f_out = fopen(string1,"w");
    imprime_cabecalho(f_out, c, 1);
    imprime_dados(f_out, c, 1);
    fclose(f_out);

//*** CENÁRIO 2 ***
    f_out = fopen(string2,"w");
    imprime_cabecalho(f_out, c, 2);
    imprime_dados(f_out, c, 2);
    fclose(f_out);

//LIBERA PONTEIRO ALOCADO DINAMICAMENTE
    libera_c(&c);

    return 0;
}
