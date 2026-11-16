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
void intercalarLeituras(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int inicio, int meio, int fim);

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

//Função de carregar dados
int carregarLeituras(const char nomeArquivo[],
                     int ids[],
                     int unidadeIds[],
                     int meses[],
                     int anos[],
                     float consumos[],
                     int max)
{
    FILE *arq = fopen(nomeArquivo, "r");
    if (arq == NULL) {
        return -1;
    }
    int n = 0;
    while (n < max &&
           fscanf(arq, "%d %d %d %d %f",
                  &ids[n], &unidadeIds[n], &meses[n],
                  &anos[n], &consumos[n]) == 5) {
        n++;
    }
    fclose(arq);
    return n;
}
//Função de carregar unidades
int carregarUnidades(const char nomeArquivo[],
                     int unidadeIds[],
                     char descricoes[][50],
                     int max)
{
    FILE *arq = fopen(nomeArquivo, "r");
    if (arq == NULL) {
        return -1;
    }
    char linha[256];
    int n = 0;
    while (n < max && fgets(linha, sizeof(linha), arq) != NULL) {
        int id;
        char desc[50];
        if (sscanf(linha, "%d;%49[^\r\n]", &id, desc) == 2) {
            unidadeIds[n] = id;
            sprintf(descricoes[n], "%s", desc);
            n++;
        }
    }
    fclose(arq);
    return n;
}

void intercalarLeituras(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int inicio, int meio, int fim) {
    int auxIds[MAX];
    int auxUnidadeIds[MAX];
    int auxMeses[MAX];
    int auxAnos[MAX];
    float auxConsumos[MAX];
 
    int i = inicio;     // percorre a metade esquerda
    int j = meio + 1;   // percorre a metade direita
    int k = 0;          // posicao nos arrays auxiliares
 
    while (i <= meio && j <= fim) {
        // mantem a ordem original em caso de IDs iguais (merge sort estavel)
        if (ids[i] <= ids[j]) {
            auxIds[k] = ids[i];
            auxUnidadeIds[k] = unidadeIds[i];
            auxMeses[k] = meses[i];
            auxAnos[k] = anos[i];
            auxConsumos[k] = consumos[i];
            i++;
        } else {
            auxIds[k] = ids[j];
            auxUnidadeIds[k] = unidadeIds[j];
            auxMeses[k] = meses[j];
            auxAnos[k] = anos[j];
            auxConsumos[k] = consumos[j];
            j++;
        }
        k++;
    }
 
    // Copia o que sobrou da metade esquerda
    while (i <= meio) {
        auxIds[k] = ids[i];
        auxUnidadeIds[k] = unidadeIds[i];
        auxMeses[k] = meses[i];
        auxAnos[k] = anos[i];
        auxConsumos[k] = consumos[i];
        i++;
        k++;
    }
 
    // Copia o que sobrou da metade direita
    while (j <= fim) {
        auxIds[k] = ids[j];
        auxUnidadeIds[k] = unidadeIds[j];
        auxMeses[k] = meses[j];
        auxAnos[k] = anos[j];
        auxConsumos[k] = consumos[j];
        j++;
        k++;
    }
 
    // Devolve o resultado intercalado para os arrays originais
    for (k = 0; k < fim - inicio + 1; k++) {
        ids[inicio + k] = auxIds[k];
        unidadeIds[inicio + k] = auxUnidadeIds[k];
        meses[inicio + k] = auxMeses[k];
        anos[inicio + k] = auxAnos[k];
        consumos[inicio + k] = auxConsumos[k];
    }
}

// Trocar Posições inteiros
void trocar(int v[], int a, int b) {
    int temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}
// Trocar Posições float
void floatTrocar(float v[], int a, int b) {
    float temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}
// Trocar Leitura
void trocarLeitura(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int a, int b) {
    trocar(ids, a, b);
    trocar(unidadeIds, a, b);
    trocar(meses, a, b);
    trocar(anos, a, b);
    floatTrocar(consumos, a, b);
}
//Busca Linear
int buscaLinear(int ids[], int n, int idProcurado) {
    for (int i = 0; i < n; i++) {
        if (ids[i] == idProcurado){
            return i;
        }
    }
    return -1;
}
//Busca Binária
int buscaBinaria(int ids[], int n, int idProcurado){
    int inicio = 0;
    int fim = n - 1;
    while (inicio <= fim){
        int meio = (inicio + fim) /2;
        if(ids[meio] == idProcurado){
            return meio; //Encontrou o elemento na posição meio
        } else if (idProcurado < ids[meio]){
            fim = meio - 1; //Valor procurado é menor que o meio
        } else {
            inicio = meio + 1;
        }
    }
    return -1; //Não encontrou
}
// Ordenação Bubble
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
//Ordenação Insertion
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
//Ordenação Selection
void selectionSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (ids[j] < ids[min]) min = j;
        }
        if (min != i) trocarLeitura(ids, unidadeIds, meses, anos, consumos, i, min);
    }
}
//Ordenação Quick
int particionarLeituras(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int inicio, int fim) {
    int pivo = ids[fim];
    int i = inicio - 1;
    for (int j = inicio; j < fim; j++) {
        if (ids[j] <= pivo) {
            i++;
            trocarLeitura(ids, unidadeIds, meses, anos, consumos, i, j);
        }
    }
    trocarLeitura(ids, unidadeIds, meses, anos, consumos, i + 1, fim);
    return i + 1;
}

void quickSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int inicio, int fim) {
    if (inicio < fim) {
        int p = particionarLeituras(ids, unidadeIds, meses, anos, consumos, inicio, fim);
        quickSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, inicio, p - 1);
        quickSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, p + 1, fim);
    }
}













// Chamada: mergeSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, 0, qtdLeituras - 1);
void mergeSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
 
        mergeSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, inicio, meio);
        mergeSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, meio + 1, fim);
        intercalarLeituras(ids, unidadeIds, meses, anos, consumos, inicio, meio, fim);
    }
}
// Soma o consumo de todas as leituras associadas ao unidadeId informado
float calcularConsumoUnidade(int unidadeIds[], float consumos[], int n, int unidadeId) {
    float total = 0.0;
 
    for (int i = 0; i < n; i++) {
        if (unidadeIds[i] == unidadeId) {
            total += consumos[i];
        }
    }
 
    return total;
}
/* Soma o consumo de todas as leituras entre o mes/ano inicial e o mes/ano final
   (inclusive). Cada data e convertida em "meses desde o ano 0" (ano * 12 + mes),
   o que permite comparar periodos que atravessam mais de um ano.*/
float calcularConsumoPeriodo(int meses[], int anos[], float consumos[], int n, int mesInicial, int anoInicial, int mesFinal, int anoFinal) {
    float total = 0.0;
    int inicio = anoInicial * 12 + mesInicial;
    int fim = anoFinal * 12 + mesFinal;
 
    for (int i = 0; i < n; i++) {
        int atual = anos[i] * 12 + meses[i];
 
        if (atual >= inicio && atual <= fim) {
            total += consumos[i];
        }
    }
 
    return total;
}
 
//Encontra a unidade com o maior consumo
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
        /* O maior consumo é atualizado baseado em: se o consumo total atual for maior que o registado.
        Em caso de empate no consumo, escolhe o de menor ID.*/
        if (maiorId == -1 || consumoTotalAtual > maiorConsumoTotal || (consumoTotalAtual == maiorConsumoTotal && idAtual < maiorId)) {
            maiorConsumoTotal = consumoTotalAtual;
            maiorId = idAtual;
        }
    }
    return maiorId;
}
//Função main
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

            case 2: {
                int indice;
                int indiceUnidade;

                printf("Digite o ID da leitura: \n");
                scanf("%d", &id_buscado);

                printf("Escolha o algoritmo de busca: \n");
                printf("\n1. Busca linear\n");
                printf("2. Busca binaria\n");
                printf("\nOpcao:\n");
                scanf("%d", &opcao_tipo_busca);

                if (opcao_tipo_busca == 1) {
                    indice = buscaLinear(ids, qtdLeituras, id_buscado);
                } else if (opcao_tipo_busca == 2) {
                    if (!ordenado) {
                    quickSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, 0, qtdLeituras - 1);
                    ordenado = 1;
                    }
                    indice = buscaBinaria(ids, qtdLeituras, id_buscado);
                } else {
                    printf("Opcao invalida. Tente novamente.\n");
                    break;
                }

                if (indice == -1) {
                    printf("Leitura nao encontrada.\n");
                } else {
                    indiceUnidade = buscaLinear(unidadeIdsCatalogo, qtdUnidades, unidadeIds[indice]);

                printf("Leitura encontrada:\n\n");
                printf("ID Leitura: %d\n", ids[indice]);
                printf("Unidade: %d\n", unidadeIds[indice]);
                printf("Descricao: %s\n", descricoes[indiceUnidade]);
                printf("Mes: %d\n", meses[indice]);
                printf("Ano: %d\n", anos[indice]);
                printf("Consumo: %.2f kWh\n", consumos[indice]);
                }
                break;
            }

            case 3: {
                int idUnidade;
                int indice;
                float total;

                printf("Digite o ID da unidade: \n");
                scanf("%d", &idUnidade);

                indice = buscaLinear(ids, n, idUnidade);

                if (indice == -1) {
                    printf("Unidade nao encontrada.\n");
                } else {
                total = calcularConsumoUnidade(ids, consumos, n, idUnidade);

                printf("Consumo da unidade:\n\n");
                printf("Unidade: %d\n", idUnidade);
                printf("Descricao: %s\n", descricoes[indice]);
                printf("Consumo total: %.2f kWh\n", total);
                }
            break;
            }

            case 4: {
                int mes_inicial, ano_inicial, mes_final, ano_final;
                float total;

                printf("Digite o mes inicial:\n");
                scanf("%d", &mes_inicial);
                printf("Digite o ano inicial:\n");
                scanf("%d", &ano_inicial);
                printf("Digite o mes final:\n");
                scanf("%d", &mes_final);
                printf("Digite o ano final:\n");
                scanf("%d", &ano_final);

                if (mes_inicial < 1 || mes_inicial > 12 ||
                    mes_final < 1 || mes_final > 12 ||
                    (ano_inicial * 12 + mes_inicial) > (ano_final * 12 + mes_final)) {
                    printf("Periodo invalido.\n");
                } else {
                    total = calcularConsumoPeriodo(meses, anos, consumos, qtdLeituras,
                    mes_inicial, ano_inicial, mes_final, ano_final);

                    printf("Consumo no periodo:\n\n");
                    printf("Periodo: %02d/%d ate %02d/%d\n", mes_inicial, ano_inicial, mes_final, ano_final);
                    printf("Consumo total: %.2f kWh\n", total);
                } break;
            }

            case 5: {
                int idMaior;
                int indice;
                float total;

                idMaior = encontrarUnidadeMaiorConsumo(unidadeIds, consumos, qtdLeituras);
                indice = buscaLinear(unidadeIdsCatalogo, qtdUnidades, idMaior);
                total = calcularConsumoUnidade(unidadeIds, consumos, qtdLeituras, idMaior);

                printf("Unidade com maior consumo:\n\n");
                printf("Unidade: %d\n", idMaior);
                printf("Descricao: %s\n", descricoes[indice]);
                printf("Consumo total: %.2f kWh\n", total);
                break;
            }
        case 6:
            printf("Encerrando o programa.\n");
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
return 0;
}
