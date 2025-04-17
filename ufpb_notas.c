#include <stdio.h>

//valores fixos
#define NOTA_MINIMA_MEDIA 7.0
#define NOTA_MINIMA_FINAL 5.0
#define MEDIA_MINIMA_PARA_FINAL 4.0
#define SOMA_APROVACAO 21.0

float calcular_media(float n1, float n2, float n3) {
    return (n1 + n2 + n3) / 3.0;      //calcular média
}

float calcular_CRA(float notas[], int quant) {
    float soma = 0;        //calcular CRA
    for (int i = 0; i < quant; i++) {
        soma += notas[i];
    }
    return soma / quant;
}

float calcular_nota_necessaria_na_final(float media) {
    if (media < MEDIA_MINIMA_PARA_FINAL) return -1.0;        //Recebe a média atual e calcula quanto falta para atingir média 5.0

    float nota_final = (NOTA_MINIMA_FINAL * 2) - media;

    if (nota_final > 10.0) return -2.0;

    return nota_final;
}

void quanto_precisa_tirar_na_final() {
    float media;          //Cálculo para passar por média (sem final)
    printf("Digite a média das três notas (antes da final): ");
    scanf("%f", &media);

    float nota_necessaria = calcular_nota_necessaria_na_final(media);

    if (nota_necessaria == -1.0) {
        printf("Reprovado direto. Média inferior a %.1f.\n", MEDIA_MINIMA_PARA_FINAL);
    } else if (nota_necessaria == -2.0) {
        printf("Mesmo tirando 10 na final, não é possível ser aprovado.\n");
    } else {
        printf("Simulações:\n");

        float media_minima = (media + nota_necessaria) / 2.0;
        printf("- Tirando %.2f na final, você alcança média %.2f (mínimo para aprovação).\n",
               nota_necessaria, media_minima);

        float media_com_10 = (media + 10.0) / 2.0;
        printf("- Tirando 10.00 na final, sua média final será %.2f.\n", media_com_10);
    }
}

void quanto_precisa_passar_por_media() {
    int qtd;
    printf("Quantas notas você já tem (1 ou 2)? ");
    scanf("%d", &qtd);

    if (qtd == 1) {
        float n1;
        printf("Digite a Nota 1: ");
        scanf("%f", &n1);

        float restante = SOMA_APROVACAO - n1;

        if (restante > 20.0) {
            printf("Mesmo tirando 10 nas próximas duas, não dá para passar por média.\n");
        } else {
            printf("Você precisa de uma soma de %.2f nas próximas duas provas.\n", restante);
            printf("Exemplo: duas notas de %.2f cada bastam.\n", restante / 2.0);
        }
        return;
    }

    if (qtd == 2) {
        float n1, n2;
        printf("Digite a Nota 1: ");
        scanf("%f", &n1);
        printf("Digite a Nota 2: ");
        scanf("%f", &n2);

        if (n1 < 0 || n1 > 10 || n2 < 0 || n2 > 10) {
            printf("Erro: Notas devem estar entre 0 e 10.\n");
            return;
        }

        float n3 = SOMA_APROVACAO - (n1 + n2);
        if (n3 <= 10.0) {
            printf("Você precisa tirar %.2f na terceira prova para passar por média.\n", n3);
            return;
        }

        printf("Impossível passar por média só com a terceira prova.\n");

        float menor = (n1 < n2) ? n1 : n2;
        float maior = (n1 > n2) ? n1 : n2;
        int tentativas = 0;

        printf("Tentando reposição da menor nota (%.1f):\n", menor);
        for (float nova = menor + 0.5; nova <= 10.0; nova += 0.5) {
            float nova_soma = nova + maior;
            float nova_n3 = SOMA_APROVACAO - nova_soma;

            if (nova_n3 <= 10.0) {
                printf("- Repondo %.1f por %.1f e tirando %.1f na terceira prova, você passa por média.\n",
                       menor, nova, nova_n3);
                tentativas++;
            }

            if (tentativas == 3) break;
        }

        if (tentativas == 0) {
            printf("Mesmo com reposição, não é possível passar por média.\n");

            float media_parcial = (n1 + n2) / 2.0;
            float nota_final = calcular_nota_necessaria_na_final(media_parcial);

            if (nota_final == -1.0) {
                printf("Reprovado direto. Média inferior a %.1f.\n", MEDIA_MINIMA_PARA_FINAL);
            } else if (nota_final == -2.0) {
                printf("Mesmo tirando 10 na final, não dá para passar.\n");
            } else {
                printf("Você precisará da final. Precisa tirar pelo menos %.2f na final.\n", nota_final);
            }
        }
    } else {
        printf("Quantidade inválida. Digite 1 ou 2.\n");
    }
}

int main() {
    int opcao;        //menu
    do {
        printf("\n--- SISTEMA UFPB - MENU ---\n");
        printf("1. Calcular média da disciplina\n");
        printf("2. Calcular CRA\n");
        printf("3. Ver quanto preciso tirar na final\n");
        printf("4. Quanto preciso tirar para passar por média\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1: {
            float n1, n2, n3;
            printf("Digite as três notas: ");
            scanf("%f %f %f", &n1, &n2, &n3);
            printf("Média: %.2f\n", calcular_media(n1, n2, n3));
            break;
        }
        case 2: {
            int quant;
            printf("Quantas notas deseja inserir para calcular o CRA? ");
            scanf("%d", &quant);
            if (quant <= 0 || quant > 100) {
                printf("Quantidade inválida.\n");
                break;
            }
            float notas[quant];
            for (int i = 0; i < quant; i++) {
                printf("Nota %d: ", i + 1);
                scanf("%f", &notas[i]);
            }
            printf("CRA: %.2f\n", calcular_CRA(notas, quant));
            break;
        }
        case 3:
            quanto_precisa_tirar_na_final();
            break;
        case 4:
            quanto_precisa_passar_por_media();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida. Digite um número válido.\n");
        }
    } while (opcao != 0);

    return 0;
}

//Aluno: Eduardo de Araújo Galvão.
