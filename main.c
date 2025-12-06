#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    int opcao;
    double a, b, resultado;
    long long ai, bi; // para módulo com inteiros

    do {
        printf("\n=== Calculadora em C ===\n");
        printf("1) Soma (a + b)\n");
        printf("2) Subtracao (a - b)\n");
        printf("3) Multiplicacao (a * b)\n");
        printf("4) Divisao (a / b)\n");
        printf("5) Potencia (a ^ b)\n");
        printf("6) Modulo (a %% b) - inteiros\n");
        printf("0) Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            limpar_buffer();
            continue;
        }

        switch (opcao) {
            case 0:
                printf("Saindo... Obrigado!\n");
                break;

            case 1:
                printf("Digite dois numeros (a b): ");
                if (scanf("%lf %lf", &a, &b) != 2) { printf("Entrada invalida.\n"); limpar_buffer(); break; }
                resultado = a + b;
                printf("Resultado: %.10g\n", resultado);
                break;

            case 2:
                printf("Digite dois numeros (a b): ");
                if (scanf("%lf %lf", &a, &b) != 2) { printf("Entrada invalida.\n"); limpar_buffer(); break; }
                resultado = a - b;
                printf("Resultado: %.10g\n", resultado);
                break;

            case 3:
                printf("Digite dois numeros (a b): ");
                if (scanf("%lf %lf", &a, &b) != 2) { printf("Entrada invalida.\n"); limpar_buffer(); break; }
                resultado = a * b;
                printf("Resultado: %.10g\n", resultado);
                break;

            case 4:
                printf("Digite dois numeros (a b): ");
                if (scanf("%lf %lf", &a, &b) != 2) { printf("Entrada invalida.\n"); limpar_buffer(); break; }
                if (b == 0.0) {
                    printf("Erro: divisao por zero nao permitida.\n");
                } else {
                    resultado = a / b;
                    printf("Resultado: %.10g\n", resultado);
                }
                break;

            case 5:
                printf("Digite a (base) e b (expoente): ");
                if (scanf("%lf %lf", &a, &b) != 2) { printf("Entrada invalida.\n"); limpar_buffer(); break; }
                resultado = pow(a, b);
                printf("Resultado: %.10g\n", resultado);
                break;

            case 6:
                printf("Modulo (apenas inteiros): digite dois inteiros (a b): ");
                if (scanf("%lld %lld", &ai, &bi) != 2) { printf("Entrada invalida.\n"); limpar_buffer(); break; }
                if (bi == 0) {
                    printf("Erro: modulo por zero nao permitido.\n");
                } else {
                    long long mod = ai % bi;
                    printf("Resultado: %lld\n", mod);
                }
                break;

            default:
                printf("Opcao invalida. Escolha novamente.\n");
                break;
        }

        limpar_buffer(); // remove restos da linha
    } while (opcao != 0);

    return 0;
}
