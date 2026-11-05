/* Bloco de inclusão das bibliotecas e número
máximo de simulações*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 1000

//Protótipos das Funções
void bubbleSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int n);








/* Protótipos das Arrays paralelas */
int ids[MAX];
int unidadesIds[MAX];
int meses[MAX];
int anos[MAX];
float consumos[MAX];
int unidade_Ids_Catalogo[MAX];
char descricoes[MAX][50];
int opcao;
int opcao_algoritmo;


int main(){
    //Laço do Menu Principal
    do {
        printf("===== SISTEMA DE ANALISE DE CONSUMO DE ENERGIA =====\n");
        printf("1. Mostrar leituras ordenadas por ID\n");
        printf("2. Buscar leitura por ID\n");
        printf("3. Calcular consumo de uma unidade\n");
        printf("4. Calcular consumo em um periodo\n");
        printf("5. Identificar unidade com maior consumo\n");
        printf("6. Sair da aplicacao\n");

        printf("Escolha uma opcao: \n");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:
                do {
                    printf("Escolha o Algoritmo de Ordenação:\n");
                    printf("1. Bubble Sort\n");
                    printf("2. Insertion Sort\n");
                    printf("3. Selection Sort\n");
                    printf("4. Quick Sort\n");
                    printf("5. Merge Sort\n");

                    printf("Opcao: \n");
                    scanf("%d", &opcao_algoritmo);

                    switch (opcao_algoritmo)
                    {
                    case 1:
                        
                        break;
                    
                    default:
                        break;
                    }
                } while() {
                break;
            case 2:

                break;

            case 3:

                break;

            case 4:

                break;

            case 5:

                break;

            case 6:
                break;
        }
return 0;
}

