#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "investidor.h"


int menu_investidor(investidor *inv){
    
    double cotacao_bitcoin = 300000.00;
    double cotacao_ethereum = 15000.00;
    double cotacao_ripple = 3.50;

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
                case 5:{
            char senha_digitada[7];
            printf(" Digite sua Senha: ");
            scanf("%s", senha_digitada);

            if (strcmp(senha_digitada, inv->senha) == 0){

                double cotacoes[3] = {cotacao_bitcoin, cotacao_ethereum, cotacao_ripple};
                double taxas[3] = {0.02, 0.01, 0.01};
                double *saldos[3] = {&inv->saldo_Bitcoin, &inv->saldo_Ethereum, &inv->saldo_Ripple};
                const char *siglas[3] = {"BTC", "ETH", "XRP"};
                int moeda = 0;
                double valor = 0;

                printf("\n Cotacoes atuais:\n");
                printf("  [1] Bitcoin:  R$ %.2f (taxa de compra: 2%%)\n", cotacao_bitcoin);
                printf("  [2] Ethereum: R$ %.2f (taxa de compra: 1%%)\n", cotacao_ethereum);
                printf("  [3] Ripple:   R$ %.2f (taxa de compra: 1%%)\n", cotacao_ripple);
                printf("\n Saldo disponivel: R$ %.2f\n", inv->saldo);

                printf("\n Qual criptomoeda deseja comprar? ");
                scanf("%d", &moeda);
                if (moeda < 1 || moeda > 3){
                    printf(" Opcao invalida!");
                    break;
                }
                moeda--;

                printf(" Quanto deseja comprar (em reais)? R$ ");
                scanf("%lf", &valor);
                if (valor <= 0){
                    printf(" Valor invalido!");
                    break;
                }


                double custo = valor * (1 + taxas[moeda]);
                if (custo > inv->saldo){
                    printf(" Saldo insuficiente! Compra + taxa = R$ %.2f e seu saldo e R$ %.2f", custo, inv->saldo);
                    break;
                }

                inv->saldo -= custo;
                *saldos[moeda] += valor / cotacoes[moeda];

                time_t tempo_atual = time(NULL);
                struct tm *relogio = localtime(&tempo_atual);

                int dia = relogio->tm_mday;
                int mes = relogio->tm_mon + 1;
                int ano = relogio->tm_year + 1900;
                int hora = relogio->tm_hour;
                int minuto = relogio->tm_min;

                FILE *extrato = fopen("extrato.txt", "a");

                if (extrato == NULL){
                    printf(" Ouve um erro ao efetuar a compra: ");
                    return 1;
                }

                fprintf(extrato, "%02d-%02d-%d %02d:%02d + %.2f %s CT: %.2f TX: %.2f REAL: %.2f BTC: %.8f ETH: %.8f XRP: %.8f\n", dia, mes, ano, hora, minuto, valor, siglas[moeda], cotacoes[moeda], taxas[moeda], inv->saldo, inv->saldo_Bitcoin, inv->saldo_Ethereum, inv->saldo_Ripple);
                fclose(extrato);

                FILE *fp = fopen("dados.txt", "w");

                if (fp == NULL){
                    printf(" Ouve um erro ao efetuar a compra: ");
                    return 1;
                }

                fprintf(fp, "%s\n", inv->cpf);
                fprintf(fp, "%s\n", inv->senha);
                fprintf(fp, "%s", inv->nome);
                fprintf(fp, "%.2f\n", inv->saldo);
                fprintf(fp, "%.8f\n", inv->saldo_Bitcoin);
                fprintf(fp, "%.8f\n", inv->saldo_Ethereum);
                fprintf(fp, "%.8f\n", inv->saldo_Ripple);
                fclose(fp);

                printf("\n Compra realizada! %.8f %s por R$ %.2f + taxa de R$ %.2f\n", valor / cotacoes[moeda], siglas[moeda], valor, custo - valor);
                printf(" Saldo atual: R$ %.2f\n", inv->saldo);
            } else {
                printf("Senha incorreta!");
            }
            break;
        }
        case 6:{
            char senha_digitada[7];
            printf(" Digite sua Senha: ");
            scanf("%s", senha_digitada);

            if (strcmp(senha_digitada, inv->senha) == 0){

                double cotacoes[3] = {cotacao_bitcoin, cotacao_ethereum, cotacao_ripple};
                double taxas[3] = {0.03, 0.02, 0.01};
                double *saldos[3] = {&inv->saldo_Bitcoin, &inv->saldo_Ethereum, &inv->saldo_Ripple};
                const char *siglas[3] = {"BTC", "ETH", "XRP"};
                int moeda = 0;
                double valor = 0;

                printf("\n Cotacoes atuais:\n");
                printf("  [1] Bitcoin:  R$ %.2f (taxa de venda: 3%%)\n", cotacao_bitcoin);
                printf("  [2] Ethereum: R$ %.2f (taxa de venda: 2%%)\n", cotacao_ethereum);
                printf("  [3] Ripple:   R$ %.2f (taxa de venda: 1%%)\n", cotacao_ripple);
                printf("\n Seus saldos: Bitcoin %.8f | Ethereum %.8f | Ripple %.8f\n", inv->saldo_Bitcoin, inv->saldo_Ethereum, inv->saldo_Ripple);

                printf("\n Qual criptomoeda deseja vender? ");
                scanf("%d", &moeda);
                if (moeda < 1 || moeda > 3){
                    printf(" Opcao invalida!");
                    break;
                }
                moeda--;

                printf(" Quanto deseja vender (em reais)? R$ ");
                scanf("%lf", &valor);
                if (valor <= 0){
                    printf(" Valor invalido!");
                    break;
                }

                double quantidade = valor / cotacoes[moeda];

                if (quantidade > *saldos[moeda] && valor - *saldos[moeda] * cotacoes[moeda] < 0.01){
                    quantidade = *saldos[moeda];
                    valor = quantidade * cotacoes[moeda];
                }
                if (quantidade > *saldos[moeda]){
                    printf(" Saldo de %s insuficiente! Voce tem %.8f %s (R$ %.2f)", siglas[moeda], *saldos[moeda], siglas[moeda], *saldos[moeda] * cotacoes[moeda]);
                    break;
                }

                double recebido = valor * (1 - taxas[moeda]);

                *saldos[moeda] -= quantidade;
                inv->saldo += recebido;

                time_t tempo_atual = time(NULL);
                struct tm *relogio = localtime(&tempo_atual);

                int dia = relogio->tm_mday;
                int mes = relogio->tm_mon + 1;
                int ano = relogio->tm_year + 1900;
                int hora = relogio->tm_hour;
                int minuto = relogio->tm_min;

                FILE *extrato = fopen("extrato.txt", "a");

                if (extrato == NULL){
                    printf(" Ouve um erro ao efetuar a venda: ");
                    return 1;
                }

                fprintf(extrato, "%02d-%02d-%d %02d:%02d - %.2f %s CT: %.2f TX: %.2f REAL: %.2f BTC: %.8f ETH: %.8f XRP: %.8f\n", dia, mes, ano, hora, minuto, valor, siglas[moeda], cotacoes[moeda], taxas[moeda], inv->saldo, inv->saldo_Bitcoin, inv->saldo_Ethereum, inv->saldo_Ripple);
                fclose(extrato);

                FILE *fp = fopen("dados.txt", "w");

                if (fp == NULL){
                    printf(" Ouve um erro ao efetuar a venda: ");
                    return 1;
                }

                fprintf(fp, "%s\n", inv->cpf);
                fprintf(fp, "%s\n", inv->senha);
                fprintf(fp, "%s", inv->nome);
                fprintf(fp, "%.2f\n", inv->saldo);
                fprintf(fp, "%.8f\n", inv->saldo_Bitcoin);
                fprintf(fp, "%.8f\n", inv->saldo_Ethereum);
                fprintf(fp, "%.8f\n", inv->saldo_Ripple);
                fclose(fp);

                printf("\n Venda realizada! %.8f %s por R$ %.2f - taxa de R$ %.2f\n", quantidade, siglas[moeda], valor, valor - recebido);
                printf(" Saldo atual: R$ %.2f\n", inv->saldo);
            } else {
                printf("Senha incorreta!");
            }
            break;
        }
        case 7: {

            double var_btc = ((double)rand() / RAND_MAX) * 0.10 - 0.05;
            double var_eth = ((double)rand() / RAND_MAX) * 0.10 - 0.05;
            double var_xrp = ((double)rand() / RAND_MAX) * 0.10 - 0.05;

            cotacao_bitcoin += cotacao_bitcoin * var_btc;
            cotacao_ethereum += cotacao_ethereum * var_eth;
            cotacao_ripple += cotacao_ripple * var_xrp;


            printf(" Cotacoes atualizadas com sucesso!\n");
            printf(" Bitcoin: R$ %.2f\n", cotacao_bitcoin);
            printf(" Ethereum: R$ %.2f\n", cotacao_ethereum);
            printf("  Ripple: R$ %.2f\n", cotacao_ripple);
            break;
        }
        case 8:
            return 0;
        default:
            break;
        }
    }
}