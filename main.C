#include <stdio.h>
#include <string.h>
#include "struct/investidor.h"
#include "carregar_dados.h"

int main() {

    int escolha;
    while(1){
        printf("\n");
        printf("========================================\n");
        printf("          SISTEMA DE CRIPTOMOEDAS      \n");
        printf("========================================\n");
        printf("\n");
        printf("  [1] - Login\n");
        printf("  [2] - Cadastro\n");
        printf("  [3] - Sair\n");
        printf("\n");
        printf("----------------------------------------\n");
        printf("  Escolha uma opcao: ");

        scanf("%d", &escolha);

        switch (escolha) {
        case 1: {
            investidor inv;
            carregar_dados(&inv);

            char cpf_digitado[12];
            char senha_digitada[7];

            printf("CPF: ");
            scanf("%s", cpf_digitado);
            printf("SENHA: ");
            scanf("%s", senha_digitada);

            if (strcmp(cpf_digitado, inv.cpf) == 0 && strcmp(senha_digitada, inv.senha) == 0){
                printf("Acesso liberado");
                // menu_investidor()
            } else{
                printf("Senha ou CPF incorretos");
            }
            break;
        }
            
        case 2: {
            investidor inv;

            char cpf_digitado[12];
            char senha_digitada[7];
            char nome_digitado[50];
            double saldo_primario = 0.00;

            printf("CPF: ");
            scanf("%s", cpf_digitado);
            printf("SENHA: ");
            scanf("%s", senha_digitada);
            fgetc(stdin);
            printf("NOME: ");
            fgets(nome_digitado, 50, stdin);
            nome_digitado[strcspn(nome_digitado, "\n")] = '\0';

            FILE *teste = fopen("dados.txt", "r");

            if (teste != NULL){
                printf("Você ja efetuou o cadastro");
        
            } else {
            FILE *fp = fopen("dados.txt", "w");

            if (fp == NULL){
                printf("Falha ao abrir o arquivo.");
                return 1;
            }

            strcpy(inv.cpf, cpf_digitado);
            strcpy(inv.senha, senha_digitada);
            strcpy(inv.nome, nome_digitado);

            fprintf(fp, "%s\n", inv.cpf);
            fprintf(fp, "%s\n", inv.senha);
            fprintf(fp, "%s\n", inv.nome);
            fprintf(fp, "%.2f\n", saldo_primario);
            fprintf(fp, "%.2f\n", saldo_primario);
            fprintf(fp, "%.2f\n", saldo_primario);
            fprintf(fp, "%.2f\n", saldo_primario);
            fclose(fp);
            }
            break;
        } 
            
        default:
            break;
        }
        break;
    }
}