#ifndef    _DIARIO_H
#define    _DIARIO_H     1

// Registro para guardar boletim.
typedef struct {
    int matricula;
    char *nome, *status;
    float n1,n2,n3,media;
} boletim;

/*
Registro para guardar um diário de turma com n boletins, armazenados em um vetor alocado dinamicamente e guardado no ponteiro *b.
*/
typedef struct {
    int n;
    boletim *b;
} diario;

void calculaMedia (boletim *b);

#endif

