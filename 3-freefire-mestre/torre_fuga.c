/*
 * =====================================================================
 * FREE FIRE SURVIVAL - NIVEL MESTRE
 * Torre de Fuga: Algoritmos de Ordenacao e Analise de Desempenho
 * =====================================================================
 * Descricao: Sistema completo de montagem da torre de fuga com
 * implementacao de Bubble Sort, Insertion Sort e Selection Sort.
 * Inclui medicao de tempo e contador de comparacoes.
 * 
 * Autora: Daniela Chiavenato Marzagao
 * Data: Novembro/2025
 * Disciplina: Analise e Desenvolvimento de Sistemas
 * =====================================================================
 */

// ==================== BIBLIOTECAS ====================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==================== CONSTANTES ====================
#define MAX_COMPONENTES 20
#define TAM_NOME 30
#define TAM_TIPO 20

// ==================== ESTRUTURA DE DADOS ====================
/*
 * Struct Componente:
 * Representa um componente necessario para montar a torre de fuga
 */
typedef struct {
    char nome[TAM_NOME];      // Nome do componente (ex: "Chip Central")
    char tipo[TAM_TIPO];      // Tipo (controle, suporte, propulsao)
    int prioridade;           // Prioridade de 1 a 10
} Componente;

// ==================== VARIAVEIS GLOBAIS ====================
Componente torre[MAX_COMPONENTES];
int totalComponentes = 0;
int comparacoes = 0;

// ==================== PROTOTIPOS DAS FUNCOES ====================
void exibirMenu();
void cadastrarComponente();
void listarComponentes();
void bubbleSortNome();
void insertionSortTipo();
void selectionSortPrioridade();
void buscarBinariaNome();
void montarTorre();
void limparBuffer();
void pausar();

// ==================== FUNCAO PRINCIPAL ====================
int main() {
    int opcao;
    
    printf("=====================================================\n");
    printf("    FREE FIRE SURVIVAL - TORRE DE FUGA (MESTRE)\n");
    printf("=====================================================\n");
    printf("  Monte a torre estrategicamente para escapar!\n");
    printf("=====================================================\n\n");
    
    printf(">>> MODO: Montagem da Torre de Resgate\n");
    printf(">>> OBJETIVO: Organizar componentes e ativar a torre\n\n");
    
    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        printf("\n");
        
        switch (opcao) {
            case 1:
                cadastrarComponente();
                break;
            case 2:
                listarComponentes();
                break;
            case 3:
                bubbleSortNome();
                break;
            case 4:
                insertionSortTipo();
                break;
            case 5:
                selectionSortPrioridade();
                break;
            case 6:
                buscarBinariaNome();
                break;
            case 7:
                montarTorre();
                break;
            case 0:
                printf(">>> Saindo do sistema...\n");
                break;
            default:
                printf(">>> ERRO: Opcao invalida!\n");
        }
        
        if (opcao != 0) {
            pausar();
        }
        
    } while (opcao != 0);
    
    printf("\n=====================================================\n");
    printf("Sistema finalizado!\n");
    printf("=====================================================\n\n");
    
    return 0;
}

// ==================== IMPLEMENTACAO DAS FUNCOES ====================

/*
 * exibirMenu()
 * Exibe o menu principal com todas as opcoes
 */
void exibirMenu() {
    printf("\n=====================================================\n");
    printf("              MENU - TORRE DE FUGA\n");
    printf("=====================================================\n");
    printf("1 - Cadastrar componente\n");
    printf("2 - Listar componentes\n");
    printf("3 - Ordenar por NOME (Bubble Sort)\n");
    printf("4 - Ordenar por TIPO (Insertion Sort)\n");
    printf("5 - Ordenar por PRIORIDADE (Selection Sort)\n");
    printf("6 - Buscar componente-chave (Busca Binaria)\n");
    printf("7 - MONTAR TORRE (Verificacao Final)\n");
    printf("0 - Sair\n");
    printf("=====================================================\n");
    printf("Componentes cadastrados: %d/%d\n", totalComponentes, MAX_COMPONENTES);
    printf("=====================================================\n");
}

/*
 * cadastrarComponente()
 * Adiciona um novo componente ao sistema
 */
void cadastrarComponente() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf(">>> ERRO: Limite de componentes atingido!\n");
        return;
    }
    
    printf("=====================================================\n");
    printf("           CADASTRAR COMPONENTE\n");
    printf("=====================================================\n");
    
    printf("Nome do componente: ");
    fgets(torre[totalComponentes].nome, TAM_NOME, stdin);
    torre[totalComponentes].nome[strcspn(torre[totalComponentes].nome, "\n")] = '\0';
    
    if (strlen(torre[totalComponentes].nome) == 0) {
        printf(">>> ERRO: Nome nao pode ser vazio!\n");
        return;
    }
    
    printf("Tipo (controle/suporte/propulsao): ");
    fgets(torre[totalComponentes].tipo, TAM_TIPO, stdin);
    torre[totalComponentes].tipo[strcspn(torre[totalComponentes].tipo, "\n")] = '\0';
    
    if (strlen(torre[totalComponentes].tipo) == 0) {
        printf(">>> ERRO: Tipo nao pode ser vazio!\n");
        return;
    }
    
    printf("Prioridade (1-10): ");
    scanf("%d", &torre[totalComponentes].prioridade);
    limparBuffer();
    
    if (torre[totalComponentes].prioridade < 1 || torre[totalComponentes].prioridade > 10) {
        printf(">>> ERRO: Prioridade deve estar entre 1 e 10!\n");
        return;
    }
    
    totalComponentes++;
    printf("\n>>> Componente cadastrado! Total: %d\n", totalComponentes);
}

/*
 * listarComponentes()
 * Exibe todos os componentes cadastrados
 */
void listarComponentes() {
    printf("=====================================================\n");
    printf("           COMPONENTES DA TORRE\n");
    printf("=====================================================\n\n");
    
    if (totalComponentes == 0) {
        printf(">>> Nenhum componente cadastrado!\n");
        return;
    }
    
    printf("Total: %d componentes\n\n", totalComponentes);
    
    for (int i = 0; i < totalComponentes; i++) {
        printf("[%02d] %-20s | %-12s | Prioridade: %2d\n",
               i + 1, torre[i].nome, torre[i].tipo, torre[i].prioridade);
    }
}

/*
 * bubbleSortNome()
 * Ordena componentes por NOME usando Bubble Sort
 * Mede tempo de execucao e conta comparacoes
 */
void bubbleSortNome() {
    if (totalComponentes == 0) {
        printf(">>> ERRO: Nenhum componente para ordenar!\n");
        return;
    }
    
    printf("=====================================================\n");
    printf("     ORDENACAO POR NOME (Bubble Sort)\n");
    printf("=====================================================\n");
    
    clock_t inicio = clock();
    comparacoes = 0;
    
    Componente temp;
    
    // Algoritmo Bubble Sort
    for (int i = 0; i < totalComponentes - 1; i++) {
        for (int j = 0; j < totalComponentes - i - 1; j++) {
            comparacoes++;
            if (strcmp(torre[j].nome, torre[j + 1].nome) > 0) {
                // Troca
                temp = torre[j];
                torre[j] = torre[j + 1];
                torre[j + 1] = temp;
            }
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("\n>>> Componentes ordenados por NOME!\n");
    printf(">>> Comparacoes: %d\n", comparacoes);
    printf(">>> Tempo de execucao: %.4f ms\n", tempo);
    
    printf("\n");
    listarComponentes();
}

/*
 * insertionSortTipo()
 * Ordena componentes por TIPO usando Insertion Sort
 * Mede tempo de execucao e conta comparacoes
 */
void insertionSortTipo() {
    if (totalComponentes == 0) {
        printf(">>> ERRO: Nenhum componente para ordenar!\n");
        return;
    }
    
    printf("=====================================================\n");
    printf("     ORDENACAO POR TIPO (Insertion Sort)\n");
    printf("=====================================================\n");
    
    clock_t inicio = clock();
    comparacoes = 0;
    
    // Algoritmo Insertion Sort
    for (int i = 1; i < totalComponentes; i++) {
        Componente chave = torre[i];
        int j = i - 1;
        
        while (j >= 0) {
            comparacoes++;
            if (strcmp(torre[j].tipo, chave.tipo) > 0) {
                torre[j + 1] = torre[j];
                j--;
            } else {
                break;
            }
        }
        torre[j + 1] = chave;
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("\n>>> Componentes ordenados por TIPO!\n");
    printf(">>> Comparacoes: %d\n", comparacoes);
    printf(">>> Tempo de execucao: %.4f ms\n", tempo);
    
    printf("\n");
    listarComponentes();
}

/*
 * selectionSortPrioridade()
 * Ordena componentes por PRIORIDADE usando Selection Sort
 * Mede tempo de execucao e conta comparacoes
 */
void selectionSortPrioridade() {
    if (totalComponentes == 0) {
        printf(">>> ERRO: Nenhum componente para ordenar!\n");
        return;
    }
    
    printf("=====================================================\n");
    printf("   ORDENACAO POR PRIORIDADE (Selection Sort)\n");
    printf("=====================================================\n");
    
    clock_t inicio = clock();
    comparacoes = 0;
    
    // Algoritmo Selection Sort (ordem decrescente de prioridade)
    for (int i = 0; i < totalComponentes - 1; i++) {
        int indiceMaior = i;
        
        for (int j = i + 1; j < totalComponentes; j++) {
            comparacoes++;
            if (torre[j].prioridade > torre[indiceMaior].prioridade) {
                indiceMaior = j;
            }
        }
        
        if (indiceMaior != i) {
            Componente temp = torre[i];
            torre[i] = torre[indiceMaior];
            torre[indiceMaior] = temp;
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("\n>>> Componentes ordenados por PRIORIDADE (maior primeiro)!\n");
    printf(">>> Comparacoes: %d\n", comparacoes);
    printf(">>> Tempo de execucao: %.4f ms\n", tempo);
    
    printf("\n");
    listarComponentes();
}

/*
 * buscarBinariaNome()
 * Busca o componente-chave usando busca binaria
 * REQUER que o vetor esteja ordenado por nome
 */
void buscarBinariaNome() {
    char nomeBusca[TAM_NOME];
    
    if (totalComponentes == 0) {
        printf(">>> ERRO: Nenhum componente cadastrado!\n");
        return;
    }
    
    printf("=====================================================\n");
    printf("     BUSCAR COMPONENTE-CHAVE (Busca Binaria)\n");
    printf("=====================================================\n");
    printf("ATENCAO: O vetor deve estar ordenado por NOME!\n");
    printf("Use a opcao 3 antes de buscar.\n\n");
    
    printf("Nome do componente-chave: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    comparacoes = 0;
    int inicio = 0;
    int fim = totalComponentes - 1;
    
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        
        int cmp = strcmp(torre[meio].nome, nomeBusca);
        
        if (cmp == 0) {
            printf("\n>>> COMPONENTE-CHAVE ENCONTRADO!\n");
            printf("-----------------------------------------------------\n");
            printf("Posicao........: %d\n", meio + 1);
            printf("Nome...........: %s\n", torre[meio].nome);
            printf("Tipo...........: %s\n", torre[meio].tipo);
            printf("Prioridade.....: %d\n", torre[meio].prioridade);
            printf("-----------------------------------------------------\n");
            printf(">>> Comparacoes: %d\n", comparacoes);
            printf(">>> Torre pronta para ativacao!\n");
            return;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    printf("\n>>> Componente nao encontrado!\n");
    printf(">>> Comparacoes: %d\n", comparacoes);
    printf(">>> ALERTA: Sem o componente-chave, a torre nao pode ser ativada!\n");
}

/*
 * montarTorre()
 * Funcao final que verifica se todos os componentes essenciais estao presentes
 */
void montarTorre() {
    printf("\n");
    printf("*****************************************************\n");
    printf("*                                                   *\n");
    printf("*          INICIANDO MONTAGEM DA TORRE              *\n");
    printf("*                                                   *\n");
    printf("*****************************************************\n\n");
    
    if (totalComponentes == 0) {
        printf(">>> FALHA: Nenhum componente cadastrado!\n");
        printf(">>> A torre nao pode ser montada.\n");
        return;
    }
    
    printf(">>> Verificando componentes...\n\n");
    
    // Verifica se ha componentes de cada tipo
    int temControle = 0, temSuporte = 0, temPropulsao = 0;
    int prioridadeTotal = 0;
    
    for (int i = 0; i < totalComponentes; i++) {
        if (strcmp(torre[i].tipo, "controle") == 0) temControle = 1;
        if (strcmp(torre[i].tipo, "suporte") == 0) temSuporte = 1;
        if (strcmp(torre[i].tipo, "propulsao") == 0) temPropulsao = 1;
        prioridadeTotal += torre[i].prioridade;
    }
    
    printf("Componentes cadastrados: %d\n", totalComponentes);
    printf("Prioridade total.......: %d\n", prioridadeTotal);
    printf("Tem controle...........: %s\n", temControle ? "SIM" : "NAO");
    printf("Tem suporte............: %s\n", temSuporte ? "SIM" : "NAO");
    printf("Tem propulsao..........: %s\n", temPropulsao ? "SIM" : "NAO");
    
    printf("\n");
    
    if (temControle && temSuporte && temPropulsao && totalComponentes >= 5) {
        printf("*****************************************************\n");
        printf("*                                                   *\n");
        printf("*         TORRE MONTADA COM SUCESSO!                *\n");
        printf("*                                                   *\n");
        printf("*         VOCE ESCAPOU DA ILHA!                     *\n");
        printf("*                                                   *\n");
        printf("*****************************************************\n");
    } else {
        printf(">>> FALHA NA MONTAGEM!\n");
        printf(">>> Componentes insuficientes ou tipos faltando.\n");
        printf(">>> Requisitos minimos:\n");
        printf("    - Pelo menos 5 componentes\n");
        printf("    - Pelo menos 1 de cada tipo (controle, suporte, propulsao)\n");
    }
}

/*
 * limparBuffer()
 * Limpa o buffer de entrada
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * pausar()
 * Pausa a execucao aguardando ENTER
 */
void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

/*
 * =====================================================================
 * ANALISE DE ALGORITMOS DE ORDENACAO
 * =====================================================================
 * 
 * BUBBLE SORT:
 * - Complexidade: O(n²) no pior e medio caso, O(n) no melhor
 * - Comparacoes: n(n-1)/2
 * - Estavel: SIM (mantem ordem de elementos iguais)
 * - In-place: SIM (nao usa memoria extra)
 * - Uso: Didatico, bom para dados quase ordenados
 * 
 * INSERTION SORT:
 * - Complexidade: O(n²) no pior e medio caso, O(n) no melhor
 * - Comparacoes: Varia de n-1 ate n(n-1)/2
 * - Estavel: SIM
 * - In-place: SIM
 * - Uso: Eficiente para pequenos conjuntos ou quase ordenados
 * 
 * SELECTION SORT:
 * - Complexidade: O(n²) em todos os casos
 * - Comparacoes: Sempre n(n-1)/2
 * - Estavel: NAO (na implementacao padrao)
 * - In-place: SIM
 * - Uso: Simples, poucas trocas, desempenho previsivel
 * 
 * BUSCA BINARIA:
 * - Complexidade: O(log n)
 * - Pre-requisito: Dados ORDENADOS
 * - Comparacoes: log₂(n) no pior caso
 * - Muito mais rapida que busca sequencial para grandes conjuntos
 * 
 * COMPARACAO PRATICA:
 * Para 20 elementos:
 * - Bubble/Insertion/Selection: ~190 comparacoes (pior caso)
 * - Busca Sequencial: ate 20 comparacoes
 * - Busca Binaria: ate 5 comparacoes (log₂(20) ≈ 4.32)
 * =====================================================================
 */