#include <stdio.h>
#include <string.h>
#include <time.h>
#include "struct/investidor.h"


int menu_investidor(investidor *inv){

    int escolha;

    while(1){
        printf("\n");
        printf("========================================\n");
        printf("     Seja bem vindo %s          \n", inv->nome);
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
        case 2:{ 
            char senha_digitada[7];
            char linha[200];
            printf(" Digite sua Senha: ");
            scanf("%s", senha_digitada);
            printf(" Nome: %s", inv->nome);
            printf(" CPF: %s\n\n", inv->cpf);
            if (strcmp(senha_digitada, inv->senha) == 0){
                FILE *fp = fopen("extrato.txt", "r");

                if (fp == NULL){
                    printf("Falha ao abrir o arquivo.");
                    return 1;
                }
                while (fgets(linha, 200, fp) != NULL) {
                    printf(" %s\n", linha);
                }
                fclose(fp);
                break;
            }
            break;
        }
        case 3:{
            double deposito;
            printf(" Valor do deposito: ");
            scanf("%lf", &deposito);

            time_t tempo_atual = time(NULL);
            struct tm *relogio = localtime(&tempo_atual);

            int dia = relogio->tm_mday;
            int mes = relogio->tm_mon + 1;
            int ano = relogio->tm_year + 1900; 
            int hora = relogio->tm_hour;
            int minuto = relogio->tm_min;
            
            inv->saldo += deposito;

            FILE *extrato = fopen("extrato.txt", "a");

            if (extrato == NULL){
                printf("Ouve um erro ao efetuar o deposito: ");
                return 1;
            }

            fprintf(extrato, "%02d-%02d-%d %02d:%02d + %.2f REAL CT: 0.00 TX: 0.00 REAL: %.2f BTC: %.3f ETH: %.4f XRP: %.2f\n", dia, mes, ano, hora, minuto, deposito, inv->saldo, inv->saldo_Bitcoin, inv->saldo_Ethereum, inv->saldo_Ripple);
            fclose(extrato);

            FILE *fp = fopen("dados.txt", "w");
            
            if (fp == NULL){
                printf("Ouve um erro ao efetuar o deposito: ");
                return 1;
            }

            fprintf(fp, "%s\n", inv->cpf);
            fprintf(fp, "%s\n", inv->senha);
            fprintf(fp, "%s", inv->nome);
            fprintf(fp, "%.2f\n", inv->saldo);
            fprintf(fp, "%.2f\n", inv->saldo_Bitcoin);
            fprintf(fp, "%.2f\n", inv->saldo_Ethereum);
            fprintf(fp, "%.2f\n", inv->saldo_Ripple);
            fclose(fp);
            break;
        }

        case 4:{
            double saque;
            printf(" Valor do saque: ");
            scanf("%lf", &saque);

            if (saque > inv->saldo){
                printf(" Saque indisponivel para esse valor, verifique seu saldo");
                break;
            }

            time_t tempo_atual = time(NULL);
            struct tm *relogio = localtime(&tempo_atual);

            int dia = relogio->tm_mday;
            int mes = relogio->tm_mon + 1;
            int ano = relogio->tm_year + 1900; 
            int hora = relogio->tm_hour;
            int minuto = relogio->tm_min;
            
            inv->saldo -= saque;

            FILE *extrato = fopen("extrato.txt", "a");

            if (extrato == NULL){
                printf(" Ouve um erro ao efetuar o saque: ");
                return 1;
            }

            fprintf(extrato, "%02d-%02d-%d %02d:%02d - %.2f REAL CT: 0.00 TX: 0.00 REAL: %.2f BTC: %.3f ETH: %.4f XRP: %.2f\n", dia, mes, ano, hora, minuto, saque, inv->saldo, inv->saldo_Bitcoin, inv->saldo_Ethereum, inv->saldo_Ripple);
            fclose(extrato);

            FILE *fp = fopen("dados.txt", "w");
            
            if (fp == NULL){
                printf(" Ouve um erro ao efetuar o saque: ");
                return 1;
            }

            fprintf(fp, "%s\n", inv->cpf);
            fprintf(fp, "%s\n", inv->senha);
            fprintf(fp, "%s", inv->nome);
            fprintf(fp, "%.2f\n", inv->saldo);
            fprintf(fp, "%.2f\n", inv->saldo_Bitcoin);
            fprintf(fp, "%.2f\n", inv->saldo_Ethereum);
            fprintf(fp, "%.2f\n", inv->saldo_Ripple);
            fclose(fp);
            break;
        }
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