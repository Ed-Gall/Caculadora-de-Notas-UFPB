#include <stdio.h>
#include <math.h>

#define N_MIN 7.0
#define N_FINAL 5.0
#define M_FINAL 4.0
#define SOMA_OK 21.0
#define MAX 100
#define FLAG_REP -1.0
#define FLAG_IMP -2.0

float media3(float x, float y, float z) {
    return (x + y + z) / 3.0f;
}

float calc_cra(float n[], int h[], int q) {
    float sp = 0.0f;
    int st = 0;
    for (int i = 0; i < q; i++) {
        sp += n[i] * h[i];
        st += h[i];
    }
    return (st == 0) ? 0.0f : sp / st;
}

float nota_final(float m) {
    if (m < M_FINAL) return FLAG_REP;
    float nf = (N_FINAL * 2.0f) - m;
    return (nf > 10.0f) ? FLAG_IMP : nf;
}

void precisa_final() {
    float m;
    printf("Média antes da final: ");
    if (scanf("%f", &m) != 1 || m < 0 || m > 10) {
        printf("Entrada inválida.\n");
        while (getchar() != '\n');
        return;
    }

    float nf = nota_final(m);

    if (fabs(nf - FLAG_REP) < 0.001f) {
        printf("Reprovado direto. Média < %.1f\n", M_FINAL);
    } else if (fabs(nf - FLAG_IMP) < 0.001f) {
        printf("Mesmo com 10 na final, não passa.\n");
    } else {
        printf("Tirando %.2f na final, média final será %.2f\n", nf, (m + nf) / 2.0f);
        printf("Com 10 na final, média será %.2f\n", (m + 10.0f) / 2.0f);
    }
}

void precisa_passar() {
    int q;
    printf("Quantas notas já tem (1 ou 2)? ");
    if (scanf("%d", &q) != 1) {
        printf("Entrada inválida.\n");
        while (getchar() != '\n');
        return;
    }

    if (q == 1) {
        float a;
        printf("Nota 1: ");
        if (scanf("%f", &a) != 1 || a < 0 || a > 10) {
            printf("Nota inválida.\n");
            while (getchar() != '\n');
            return;
        }

        float faltam = SOMA_OK - a;
        if (faltam > 20.0f)
            printf("Mesmo com 10 nas duas, não passa.\n");
        else {
            printf("Precisa de soma %.2f nas próximas duas. Ex: duas de %.2f\n", faltam, faltam / 2.0f);
        }

    } else if (q == 2) {
        float a, b;
        printf("Nota 1: ");
        scanf("%f", &a);
        printf("Nota 2: ");
        scanf("%f", &b);

        if (a < 0 || a > 10 || b < 0 || b > 10) {
            printf("Notas devem estar entre 0 e 10.\n");
            return;
        }

        float c = SOMA_OK - (a + b);
        if (c <= 10.0f) {
            printf("Precisa de %.2f na terceira prova.\n", c);
        } else {
            printf("Não dá pra passar só com a terceira prova.\n");

            float men = (a < b) ? a : b;
            float mai = (a > b) ? a : b;
            int tent = 0;

            printf("Testando reposição de %.1f:\n", men);
            for (float nova = men + 0.5f; nova <= 10.0f; nova += 0.5f) {
                float soma = nova + mai;
                float novo_c = SOMA_OK - soma;
                if (novo_c <= 10.0f) {
                    printf("- Repondo %.1f por %.1f e tirando %.1f, passa.\n", men, nova, novo_c);
                    tent++;
                }
                if (tent == 3) break;
            }

            if (tent == 0) {
                printf("Nem com reposição é possível.\n");
                float mp = (a + b) / 2.0f;
                float nf = nota_final(mp);

                if (fabs(nf - FLAG_REP) < 0.001f)
                    printf("Reprovado direto. Média < %.1f\n", M_FINAL);
                else if (fabs(nf - FLAG_IMP) < 0.001f)
                    printf("Mesmo com 10, não passa.\n");
                else
                    printf("Precisa de %.2f na final.\n", nf);
            }
        }

    } else {
        printf("Quantidade inválida. Use 1 ou 2.\n");
    }
}

int main() {
    int op;
    do {
        printf("\n--- UFPB - MENU ---\n");
        printf("1. Calcular média da disciplina\n");
        printf("2. Calcular CRA\n");
        printf("3. Quanto preciso na final\n");
        printf("4. Quanto preciso pra passar por média\n");
        printf("0. Sair\n");
        printf("Opção: ");
        if (scanf("%d", &op) != 1) {
            printf("Entrada inválida.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (op) {
            case 1: {
                float x, y, z;
                printf("Digite as três notas: ");
                scanf("%f %f %f", &x, &y, &z);
                if (x < 0 || x > 10 || y < 0 || y > 10 || z < 0 || z > 10) {
                    printf("Notas inválidas.\n");
                    break;
                }
                printf("Média: %.2f\n", media3(x, y, z));
                break;
            }
            case 2: {
                int q;
                printf("Quantas disciplinas? ");
                scanf("%d", &q);
                if (q <= 0 || q > MAX) {
                    printf("Inválido.\n");
                    break;
                }
                float n[MAX];
                int h[MAX];
                for (int i = 0; i < q; i++) {
                    printf("Média %d: ", i + 1);
                    scanf("%f", &n[i]);
                    printf("Carga horária %d: ", i + 1);
                    scanf("%d", &h[i]);
                }
                printf("CRA: %.2f\n", calc_cra(n, h, q));
                break;
            }
            case 3:
                precisa_final();
                break;
            case 4:
                precisa_passar();
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
