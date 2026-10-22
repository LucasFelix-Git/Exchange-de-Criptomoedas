#include <stdio.h>
#include "struct/investidor.h"

int carregar_dados(investidor *inv) {
    FILE *fp = fopen("dados.txt", "r");
    
    if (fp == NULL){
        printf("Falha ao abrir o arquivo.");
        return 1;
    }
    fscanf(fp, "%s", inv->cpf);
    fscanf(fp, "%s", inv->senha);
    fgetc(fp);
    fgets(inv->nome, 50, fp);
    fscanf(fp, "%lf", &inv->saldo);
    fscanf(fp, "%lf", &inv->saldo_Bitcoin);
    fscanf(fp, "%lf", &inv->saldo_Ethereum);
    fscanf(fp, "%lf", &inv->saldo_Ripple);
    fclose(fp);

    return 0;
}