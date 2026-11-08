/* Bloco de inclusão das bibliotecas e número máximo de simulações*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 1000

//Protótipos das Funções
int carregarLeituras(const char nomeArquivo[], int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int max);
int carregarUnidades(const char nomeArquivo[], int unidadeIds[], char descricoes[][50], int max);
int buscaLinear(int ids[], int n, int idProcurado);
int buscaBinaria(int ids[], int n, int idProcurado);
void bubbleSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int n);
void insertionSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int n); 
void selectionSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int n); 
void quickSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int inicio, int fim);
void mergeSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int inicio, int fim); 
float calcularConsumoUnidade(int unidadeIds[], float consumos[], int n, int unidadeId);
float calcularConsumoPeriodo(int meses[], int anos[], float consumos[], int n, int mesInicial, int anoInicial, int mesFinal, int anoFinal); 
int encontrarUnidadeMaiorConsumo(int unidadeIds[], float consumos[], int n);

// funções leo:
void trocar(int v[], int a, int b) {
    int temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

void floattrocar(float v[], int a, int b) {
    float temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

int buscalinear(int ids[], int n, int idProcurado) {
    for (int i = 0; i < n; i++) {
        if (ids[i] == idProcurado) {
            return i;
        }
    }
    return -1;
}

void bubbleSortLeituraPorId(int ids[], int unidadesId[], int meses[], int anos[], float consumos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (ids[j] > ids[j + 1]) {
                trocar(ids, j, j + 1);
                trocar(unidadesId, j, j + 1);
                trocar(meses, j, j + 1);
                trocar(anos, j, j + 1);
                floattrocar(consumos, j, j + 1);
            }
        }
    }
}

void insertionSortLeituraPorId(int ids[], int unidadesId[], int meses[], int anos[], float consumos[], int n) {
    for (int i = 1; i < n; i++) {
        int x = ids[i];
        int x2 = unidadesId[i];
        int x3 = meses[i];
        int x4 = anos[i];
        float x5 = consumos[i];
        int j = i - 1;
        
        while (j >= 0 && ids[j] > x) {
            ids[j + 1] = ids[j];
            unidadesId[j + 1] = unidadesId[j];
            meses[j + 1] = meses[j];
            anos[j + 1] = anos[j];
            consumos[j + 1] = consumos[j];
            j--;
        }
        ids[j + 1] = x;
        unidadesId[j + 1] = x2;
        meses[j + 1] = x3;
        anos[j + 1] = x4;
        consumos[j + 1] = x5;
    }
}

int encontrarUnidadeMaiorConsumo(int unidadeIds[], float consumos[], int n) {
    if (n <= 0) {
        return -1; 
    }
    
    int maiorId = -1;
    float maiorConsumoTotal = -1.0;
    int i, j;

    for (i = 0; i < n; i++) {
        int idAtual = unidadeIds[i];
        
        int jaProcessado = 0;
        for (j = 0; j < i; j++) {
            if (unidadeIds[j] == idAtual) {
                jaProcessado = 1;
                break;
            }
        }
        
        if (jaProcessado) {
            continue;
        }

        // Somamos todas leituras associadas ao id que esta sendo passado nesse momento
        float consumoTotalAtual = 0.0;
        for (j = 0; j < n; j++) {
            if (unidadeIds[j] == idAtual) {
                consumoTotalAtual += consumos[j];
            }
        }

        // o maior consumo é atualizado baseado em:
        // Se o consumo total atual for maior que o registado.
        // Em caso de empate no consumo, escolhe o de menor ID.
        if (maiorId == -1 || consumoTotalAtual > maiorConsumoTotal || (consumoTotalAtual == maiorConsumoTotal && idAtual < maiorId)) {
            maiorConsumoTotal = consumoTotalAtual;
            maiorId = idAtual;
        }
    }

    return maiorId;
}

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
int id_buscado;
int opcao_tipo_busca;


int main() {
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
                        void bubbleSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int n);
                        break;
                    case 2:
                        void insertionSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int n);
                        break;
                    case 3:
                        void selectionSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int n);
                        break;
                    case 4:
                        void quickSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int inicio, int fim);
                        break;
                    case 5: 
                        void mergeSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int inicio, int fim);
                        break;
                    }
                } while(opcao_algoritmo < 1 || opcao_algoritmo > 5); 

            case 2:
                printf("Digite o ID da leitura: \n");
                scanf("%d", &id_buscado);

                printf("Escolha o algoritmo de busca: \n");
                printf("\n1. Busca linear\n");
                printf("2. Busca binaria\n");
                
                printf("\nOpcao:\n");
                scanf("%d", &opcao_tipo_busca);
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
}
