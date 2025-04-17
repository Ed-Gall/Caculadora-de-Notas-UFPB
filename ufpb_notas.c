#include <stdio.h>

#define MIN_FREQ 75
#define MED_PARA_MEDIA 7.0
#define MED_PARA_FINAL 5.0
#define LIMITE_MEDIA 4.0

float media3(float n1, float n2, float n3) {
    return (n1 + n2 + n3) / 3.0;
}

float calc_CRA(float notas[], int qtd) {
    float soma = 0;
    for (int i = 0; i < qtd; i++) soma += notas[i];
    return soma / qtd;
}

// Final
float nota_final(float m) {
    if (m < LIMITE_MEDIA) return -1.0; // Reprovação direta
    float nf = (5 * 10 - 6 * m) / 4.0;
    if (nf > 10.0) return -2.0; // Impossível
    return nf;
}

void final_needed() {
    float m;
    printf("Digite sua média das provas (antes da final): ");
    scanf("%f", &m);

    float nf = nota_final(m);

    if (nf == -1.0) {
        printf("Reprovado direto. Média menor que %.1f.\n", LIMITE_MEDIA);
    } else if (nf == -2.0) {
        printf("Mesmo tirando 10 na final, não é possível ser aprovado.\n");
    } else {
        float media_final = (6 * m + 4 * nf) / 10;
        printf("Você precisa tirar %.2f na final para alcançar média %.2f.\n", nf, media_final);
    }
}

void passar_por_media() {
    int qtd;
    printf("Quantas notas você já tem (1 ou 2)? ");
    scanf("%d", &qtd);

    if (qtd == 1) {
        float n1;
        printf("Nota 1: ");
        scanf("%f", &n1);
        float soma = MED_PARA_MEDIA * 3 - n1;
        if (soma > 20) {
            printf("Mesmo com 10 nas outras, não dá para passar.\n");
        } else {
            printf("Precisa somar %.2f nas próximas duas provas.\n", soma);
        }
    } else if (qtd == 2) {
        float n1, n2;
        printf("Nota 1: "); scanf("%f", &n1);
        printf("Nota 2: "); scanf("%f", &n2);
        float n3 = MED_PARA_MEDIA * 3 - (n1 + n2);
        if (n3 <= 10.0) {
            printf("Precisa tirar %.2f na terceira prova para passar.\n", n3);
        } else {
            printf("Não passa direto. Verificando final...\n");
            float m = (n1 + n2) / 2;
            float nf = nota_final(m);
            if (nf >= 0) {
                printf("Com média %.2f, você precisa de %.2f na final.\n", m, nf);
            } else {
                printf("Não há como passar.\n");
            }
        }
    } else {
        printf("Entrada inválida. Digite 1 ou 2.\n");
    }
}

int main() {
    int op;
    do {
        printf("\n=== SISTEMA UFPB ===\n");
        printf("1. Calcular média da disciplina\n");
        printf("2. Calcular CRA\n");
        printf("3. Ver nota mínima na final\n");
        printf("4. Quanto preciso para passar por média\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1: {
                float a, b, c;
                printf("Digite as 3 notas: ");
                scanf("%f %f %f", &a, &b, &c);
                printf("Média: %.2f\n", media3(a, b, c));
                break;
            }
            case 2: {
                int qtd;
                printf("Quantas disciplinas? ");
                scanf("%d", &qtd);
                float n[qtd];
                for (int i = 0; i < qtd; i++) {
                    printf("Nota %d: ", i + 1);
                    scanf("%f", &n[i]);
                }
                printf("CRA: %.2f\n", calc_CRA(n, qtd));
                break;
            }
            case 3:
                final_needed();
                break;
            case 4:
                passar_por_media();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (op != 0);

    return 0;
}

//Aluno: Eduardo de Araújo Galvão
