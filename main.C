#include <stdio.h>
#include "struct/investidor.h"

int main() {

    FILE *fp = fopen("dados.txt", "w");

    if (fp == NULL){
        printf("Falha ao abrir o arquivo.");
        return 1;
    }

    investidor inv = {"12345678900", "123456", "Lucas Felix", 580.0, 0.0158, 1.03, 200.35};

    fprintf(fp, "%s\n", inv.cpf);
    fprintf(fp, "%s\n", inv.senha);
    fprintf(fp, "%s\n", inv.nome);
    fprintf(fp, "%.2f\n", inv.saldo);
    fprintf(fp, "%.2f\n",inv.saldo_Bitcoin);
    fprintf(fp, "%.2f\n", inv.saldo_Ethereum);
    fprintf(fp, "%.2f\n", inv.saldo_Ripple);

    fclose(fp);

    return 0;
}
