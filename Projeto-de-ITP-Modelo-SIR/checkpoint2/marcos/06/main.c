#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mecsir.h"

//FUN��O PRINCIPAL
int main(int argc,char *argv[]){
    int i, cont = 0, cont2 = 0;
    char string0[20]={"cenario_0.csv"}, string1[20]={"cenario_1.csv"}, string2[20]={"cenario_2.csv"};
    FILE *f_in, *f_out;
    cenarios *c;

    c = malloc(3*sizeof(cenarios));

//INSTRU��ES APRESENTADAS CASO A LINHA DE COMANDO ESTEJA INCORRETA
    if(argc<3){
        printf("\nComandos incorretos!\n");
        printf("Formato correto: ./nome_do_programa comandos_1 comandos_2 ... comandos_n\n");
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
            //NOMEIA ARQUIVOS DE SA�DA. CASO N�O SEJAM PASSADOS NA LINHA DE COMANDO, NOMES PADR�ES SER�O ATRIBU�DOS.
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

//RECEBE PAR�METROS PASSADOS NA LINHA DE COMANDO
    for(i=1; i<argc; i++)
        if(argv[i][0]=='-')
            if(argv[i][1]=='p'){
                le_parametros_comando(c, argv[i+1], &cont, &cont2);
            }

//VERIFICA ERROS DE PASSAGEM DE PAR�METROS DE ENTRADA PELA LINHA DE COMANDO
    if(cont2>0) {
        printf("\n");
        lista_parametros();
        printf("\n");
        return 1;
    }

//VERIFICAR SUFICI�NCIA DE PAR�METROS DE ENTRADA PASSADOS PELO USU�RIO (LINHA DE COMANDO + ARQUIVO DE ENTRADA)
    if(cont<16) {
        printf("Par%cmetros insuficientes!",131);
        return 1;
    }

//CONFIGURA��O DE PAR�METROS PADR�O
    c[0].periodo *= 24;
    c[0].t=0;
    c[0].mortes=0;

//CALCULA b, k
    calcula_b_k(c, 0);

//COPIA PAR�METROS PARA VETORES A SEREM USADOS NOS DEMAIS CEN�RIOS
    c[1] = c[2] = c[0];

//*** CEN�RIO 0 ***
    f_out = fopen(string0,"w");

    imprime_cabecalho(f_out, c, 0);

    while (c[0].t < c[0].periodo)
        imprime_dados(f_out, c, 0);

    fclose(f_out);

//*** CEN�RIO 1 ***
    f_out = fopen(string1,"w");

    imprime_cabecalho(f_out, c, 1);

    while (c[1].t < c[1].periodo){

        imprime_dados(f_out, c, 1);

        if(c[1].t > c[1].tempoT_b2) break;
    }
    //TRANSI��O PARA NOVO PAR�METRO DE T_b.
    c[1].T_b = c[1].T_b2;

    calcula_b_k(c, 1);

    while (c[1].t < c[1].periodo)
        imprime_dados(f_out, c, 1);

    fclose(f_out);

//*** CEN�RIO 2 ***
    f_out = fopen(string2,"w");

    imprime_cabecalho(f_out, c, 2);

    while (c[2].t < c[2].periodo){

        imprime_dados(f_out, c, 2);

        if(c[2].t > c[2].tempoT_b2) break;
    }
    //TRANSI��O PARA NOVO PAR�METRO DE T_k.
    c[2].T_k = c[2].T_k2;

    calcula_b_k(c, 2);

    while (c[2].t < c[2].periodo)
        imprime_dados(f_out, c, 2);

    fclose(f_out);

//LIBERA PONTEIRO ALOCADO DINAMICAMENTE
    libera_c(&c);

    return 0;
}
