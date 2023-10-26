#include <stdio.h>

int main(int argc, char *argv[]) {
    int mat;
    float n1, n2, n3, media;
    char c1[20], c2[20], c3[20], c4[20], c5[20];

    FILE *f1, *f2;

    if(argc<4) {
        printf("\ncomando incorreto!\n\nformatos de entrada possíveis:\n./programa -i arquivo_de_entrada -o arquivo_de_saida\nou\n./programa -o arquivo_de_saida -i arquivo_de_entrada\n\n");
        return 1;
    }
    if(argv[1][1]=='i' && argv[3][1]=='o'){
        f1 = fopen(argv[2],"r");
        f2 = fopen(argv[4],"w");
    }
    else if(argv[1][1]=='o' && argv[3][1]=='i'){
        f1 = fopen(argv[4],"r");
        f2 = fopen(argv[2],"w");
    }
    else {
        printf("\ncomando incorreto!\n\nformatos de entrada possíveis:\n./programa -i arquivo_de_entrada -o arquivo_de_saida\nou\n./programa -o arquivo_de_saida -i arquivo_de_entrada\n\n");
        return 1;
    }
    if(f1==NULL || f2==NULL){
        printf("ERRO de abertura dos arquivos");
        return 1;
    }

    //CABEÇALHO
    fscanf(f1,"%[^,],%[^,],%[^,],%[^,],%[^\n]", c1, c2, c3, c4, c5);
    fprintf(f2,"matrícula,%s,média,status\n", c2);

    //DADOS
    while(!feof(f1)){
        fscanf(f1,"%d,%[^,],%f,%f,%f\n", &mat, c2, &n1, &n2, &n3);
        media = (n1+n2+n3)/3;
        fprintf(f2,"%d,%s,%.1f,", mat, c2, media);
        if(media>=5 && media<7) fprintf(f2,"aprovado por nota\n");
        else if(media>=7) fprintf(f2,"aprovado por média\n");
        else if(media>=3 && media<5) fprintf(f2,"recuperação\n");
        else fprintf(f2,"reprovado\n");
    }

    fclose(f1);
    fclose(f2);
    return 0;
}
