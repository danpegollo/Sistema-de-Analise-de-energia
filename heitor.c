#define MAX 1000
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
 
