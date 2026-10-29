#include <stdio.h>
#include <string.h>
#include "struct/investidor.h"


int menu_investidor(investidor *inv){

    int escolha;

    while(1){
        printf("\n");
        printf("========================================\n");
        printf("             Seja bem vindo %s          \n", inv->nome);
        printf("========================================\n");
        printf("\n");
        printf("  [1] - Consultar Saldo\n");
        printf("  [2] - Consultar Extrato\n");
        printf("  [3] - Depositar\n");
        printf("  [4] - Sacar\n");
        printf("  [5] - Comprar Criptomoeda\n");
        printf("  [6] - Vender Criptomoeda\n");
        printf("  [7] - Atualizar Cotacao\n");
        printf("  [8] - Sair\n");
        printf("\n");
        printf("----------------------------------------\n");
        printf(" Escolha uma opcao: ");

        scanf("%d", &escolha);
        
        switch (escolha) {
        case 1:{
            char senha_digitada[7];
            printf(" Digite sua Senha: ");
            scanf("%s", senha_digitada);

            if (strcmp(senha_digitada, inv->senha) == 0){
                printf("\n Nome: %s", inv->nome);
                printf(" CPF: %s \n", inv->cpf);
                printf("\n");
                printf(" Reais: %.2f \n", inv->saldo);
                printf(" Bitcoin: %.3f \n", inv->saldo_Bitcoin);
                printf(" Ethereum: %.2f \n", inv->saldo_Ethereum);
                printf(" Ripple: %.2f \n", inv->saldo_Ripple);
            } else {
                printf("Senha incorreta!");
            }
            break;
        }
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
        case 5:
            /* code */
        case 6:
            /* code */
            break;
        case 7:
            /* code */
            break;
        case 8:
            /* code */
            break;
        default:
            break;
        }
    }
}