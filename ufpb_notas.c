#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define N_MIN 7.0
#define N_FINAL 5.0
#define M_FINAL 4.0
#define SOMA_OK 21.0
#define MAX 100
#define FLAG_REP -1.0
#define FLAG_IMP -2.0
#define MAX_NOME 50

float media3(float x, float y, float z) {
    return (x + y + z) / 3.0f;
}

float calc_cra(float n[], int h[], int q, char nomes[][MAX_NOME]) {
    float sp = 0.0f;
    int st = 0;
    
    printf("\n--- Disciplinas Cadastradas ---\n");
    for (int i = 0; i < q; i++) {
        printf("%d) Disciplina\t\t\t Nome = %s [Carga Horária: %d h, Média: %.2f]\n", i+1, nomes[i], h[i], n[i]);
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

    if (m >= N_MIN) {
        printf("Aluno já aprovado por média (média >= 7.0).\n");
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

void limpar_buffer() {
    while (getchar() != '\n');
}

void salvar_cra_arquivo(int num_periodos, float cra_geral, char nomes[][MAX_NOME], float notas[], int cargas_horarias[], int qtd_disciplinas) {
    FILE *arquivo = fopen("dados-CRA.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo!\n");
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    fprintf(arquivo, "\n\n=== Dados do CRA - %02d/%02d/%04d %02d:%02d ===\n", 
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
    
    fprintf(arquivo, "\n--- Disciplinas Cadastradas ---\n");
    for (int i = 0; i < qtd_disciplinas; i++) {
        fprintf(arquivo, "%d) %s [CH: %d h, Média: %.2f]\n", 
                i+1, nomes[i], cargas_horarias[i], notas[i]);
    }
    
    fprintf(arquivo, "\n--- Resultados ---\n");
    fprintf(arquivo, "Número de períodos: %d\n", num_periodos);
    fprintf(arquivo, "CRA calculado: %.2f\n", cra_geral);
    
    fclose(arquivo);
    printf("\nDados salvos com sucesso em 'dados-CRA.txt'\n");
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
            limpar_buffer();
            continue;
        }

        switch (op) {
            case 1: {
                float x, y, z;
                printf("Digite as três notas: ");
                if (scanf("%f %f %f", &x, &y, &z) != 3) {
                    printf("Entrada inválida.\n");
                    limpar_buffer();
                    break;
                }
                if (x < 0 || x > 10 || y < 0 || y > 10 || z < 0 || z > 10) {
                    printf("Notas inválidas. Devem estar entre 0 e 10.\n");
                    break;
                }
                printf("Média: %.2f\n", media3(x, y, z));
                break;
            }
            case 2: {
                int qtd_periodos = 0;
                float cra_total = 0.0f;
                int ch_total = 0;
                char nomes[MAX][MAX_NOME];
                float notas[MAX];
                int cargas_horarias[MAX];
                int total_disciplinas = 0;
                
                printf("\n--- Cálculo do CRA ---\n");
                printf("Quantos períodos deseja calcular? ");
                int num_periodos;
                if (scanf("%d", &num_periodos) != 1 || num_periodos <= 0) {
                    printf("Número inválido de períodos.\n");
                    limpar_buffer();
                    break;
                }
                
                for (int p = 1; p <= num_periodos; p++) {
                    printf("\n--- Período %d ---\n", p);
                    
                    char resp;
                    do {
                        printf("Você tem todas as notas do período %d? (S/N): ", p);
                        scanf(" %c", &resp);
                        resp = toupper(resp);
                        limpar_buffer();
                    } while (resp != 'S' && resp != 'N');
                    
                    if (resp == 'N') {
                        printf("Pulando período %d...\n", p);
                        continue;
                    }
                    
                    int qtd_disciplinas;
                    printf("Quantas disciplinas no período %d? ", p);
                    if (scanf("%d", &qtd_disciplinas) != 1 || qtd_disciplinas <= 0 || qtd_disciplinas > MAX) {
                        printf("Quantidade inválida. Deve ser entre 1 e %d.\n", MAX);
                        limpar_buffer();
                        p--; // Repete o período
                        continue;
                    }
                    
                    for (int i = 0; i < qtd_disciplinas; i++) {
                        printf("\nDisciplina %d:\n", i+1);
                        printf("Nome: ");
                        limpar_buffer();
                        fgets(nomes[total_disciplinas], MAX_NOME, stdin);
                        nomes[total_disciplinas][strcspn(nomes[total_disciplinas], "\n")] = '\0';
                        
                        printf("Média final: ");
                        while (scanf("%f", &notas[total_disciplinas]) != 1 || notas[total_disciplinas] < 0 || notas[total_disciplinas] > 10) {
                            printf("Média inválida! Digite novamente (0-10): ");
                            limpar_buffer();
                        }
                        
                        printf("Carga horária (h): ");
                        while (scanf("%d", &cargas_horarias[total_disciplinas]) != 1 || cargas_horarias[total_disciplinas] <= 0) {
                            printf("Carga horária inválida! Digite novamente: ");
                            limpar_buffer();
                        }
                        
                        total_disciplinas++;
                    }
                    
                    float cra_periodo = calc_cra(notas + (total_disciplinas - qtd_disciplinas), 
                          cargas_horarias + (total_disciplinas - qtd_disciplinas), 
                          qtd_disciplinas, 
                          nomes + (total_disciplinas - qtd_disciplinas));
                    printf("\nCRA do período %d: %.2f\n", p, cra_periodo);
                    
                    for (int i = total_disciplinas - qtd_disciplinas; i < total_disciplinas; i++) {
                        cra_total += notas[i] * cargas_horarias[i];
                        ch_total += cargas_horarias[i];
                    }
                    qtd_periodos++;
                }
                
                if (qtd_periodos > 0) {
                    float cra_geral = cra_total / ch_total;
                    printf("\n--- CRA Geral ---\n");
                    printf("CRA calculado: %.2f\n", cra_geral);
                    
                    char opcao;
                    printf("\nDeseja salvar esses dados? (S/N): ");
                    scanf(" %c", &opcao);
                    if (toupper(opcao) == 'S') {
                        salvar_cra_arquivo(qtd_periodos, cra_geral, nomes, notas, cargas_horarias, total_disciplinas);
                    }
                } else {
                    printf("\nNenhum período válido foi informado.\n");
                }
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

// //Aluno: Eduardo de Araújo Galvão
