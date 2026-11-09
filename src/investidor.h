#ifndef INVESTIDOR_H
#define INVESTIDOR_H

typedef struct {
    char cpf[12];
    char senha[7];
    char nome[50];
    double saldo;
    double saldo_Bitcoin;
    double saldo_Ethereum;
    double saldo_Ripple;
} investidor;

#endif