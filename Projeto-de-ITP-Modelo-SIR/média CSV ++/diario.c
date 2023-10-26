#include "diario.h"

/*
Função para calcular a média de um boletim, armazenar o valor obtido no campo 'media' e registrar o status de aprovação no campo 'status'.
*/
void calculaMedia (boletim *b) {

    b->media = (b->n1 + b->n2 + b->n3)/3;
    float media = b->media;
    if(media>=5 && media<7) b->status = "aprovado por nota";
    else if(media>=7) b->status = "aprovado por média";
    else if(media>=3 && media<5) b->status = "recuperação";
    else b->status = "reprovado";

}
