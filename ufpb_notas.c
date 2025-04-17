#include <stdio.h>

// Constantes
#define MIN_MED 7.0
#define MIN_FIN 5.0
#define MED_FIN 4.0
#define SOMA_APROV 21.0

float calc_med(float a, float b, float c) {
    return (a + b + c) / 3.0;
}

float calc_CRA(float n[], int q) {
    float s = 0;
    for (int i = 0; i < q; i++) {
        s += n[i];
    }
    return s / q;
}

float calc_nota_final(float m) {
    if (m < MED_FIN) return -1.0;
    
    float nf = (MIN_FIN * 2) - m;
    
    if (nf > 10.0) return -2.0;
    
    return nf;
}

void quanto_final() {
    float m;
    printf("Digite a média antes da final: ");
    scanf("%f", &m);

    float nf = calc_nota_final(m);

    if (nf == -1.0) {
        printf("Reprovado direto. Média < %.1f.\n", MED_FIN);
    } else if (nf == -2.0) {
        printf("Mesmo com 10 na final, não é possível.\n");
    } else {
        printf("Simulações:\n");
        printf("- Tirando %.2f, média %.2f (mínimo).\n", nf, (m + nf)/2);
        printf("- Tirando 10.00, média %.2f.\n", (m + 10)/2);
    }
}

void quanto_media() {
    int q;
    printf("Quantas notas já tem (1 ou 2)? ");
    scanf("%d", &q);

    if (q == 1) {
        float a;
        printf("Nota 1: ");
        scanf("%f", &a);

        float r = SOMA_APROV - a;

        if (r > 20.0) {
            printf("Não dá para passar com mais duas.\n");
        } else {
            printf("Precisa de %.2f nas próximas duas.\n", r);
            printf("Exemplo: duas de %.2f.\n", r / 2);
        }
        return;
    }

    if (q == 2) {
        float a, b;
        printf("Nota 1: ");
        scanf("%f", &a);
        printf("Nota 2: ");
        scanf("%f", &b);

        if (a < 0 || a > 10 || b < 0 || b > 10) {
            printf("Erro: Notas inválidas.\n");
            return;
        }

        float c = SOMA_APROV - (a + b);
        if (c <= 10.0) {
            printf("Precisa de %.2f na terceira.\n", c);
            return;
        }

        printf("Não dá para passar só com a terceira.\n");

        float mn = (a < b) ? a : b;
        float mx = (a > b) ? a : b;
        int t = 0;

        printf("Tentando repor %.1f:\n", mn);
        for (float nr = mn + 0.5; nr <= 10.0; nr += 0.5) {
            float ns = nr + mx;
            float nc = SOMA_APROV - ns;

            if (nc <= 10.0) {
                printf("- Repondo %.1f por %.1f e tirando %.1f\n", mn, nr, nc);
                t++;
            }

            if (t == 3) break;
        }

        if (t == 0) {
            printf("Mesmo com reposição, não dá.\n");

            float mp = (a + b) / 2.0;
            float nf = calc_nota_final(mp);

            if (nf == -1.0) {
                printf("Reprovado. Média < %.1f.\n", MED_FIN);
            } else if (nf == -2.0) {
                printf("Mesmo com 10 na final, não dá.\n");
            } else {
                printf("Precisa de pelo menos %.2f na final.\n", nf);
            }
        }
    } else {
        printf("Quantidade inválida.\n");
    }
}

int main() {
    int op;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Calcular média\n");
        printf("2. Calcular CRA\n");
        printf("3. Quanto na final\n");
        printf("4. Passar por média\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1: {
                float x, y, z;
                printf("Digite 3 notas: ");
                scanf("%f %f %f", &x, &y, &z);
                printf("Média: %.2f\n", calc_med(x, y, z));
                break;
            }
            case 2: {
                int qt;
                printf("Quantas notas? ");
                scanf("%d", &qt);
                if (qt <= 0 || qt > 100) {
                    printf("Inválido.\n");
                    break;
                }
                float nt[qt];
                for (int i = 0; i < qt; i++) {
                    printf("Nota %d: ", i + 1);
                    scanf("%f", &nt[i]);
                }
                printf("CRA: %.2f\n", calc_CRA(nt, qt));
                break;
            }
            case 3:
                quanto_final();
                break;
            case 4:
                quanto_media();
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
