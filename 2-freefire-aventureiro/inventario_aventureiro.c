/*
 * =====================================================================
 * FREE FIRE SURVIVAL - NIVEL AVENTUREIRO
 * Comparacao: Vetor vs Lista Encadeada + Busca Binaria
 * =====================================================================
 * Descricao: Sistema que implementa inventario usando DUAS estruturas
 * diferentes (vetor e lista encadeada) para comparar desempenho.
 * Inclui ordenacao e busca binaria no vetor ordenado.
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
#define MAX_ITENS 20
#define TAM_NOME 30
#define TAM_TIPO 20

// ==================== ESTRUTURAS DE DADOS ====================

// Estrutura basica do item
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Estrutura do no para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ==================== VARIAVEIS GLOBAIS ====================

// VETOR (Lista Sequencial)
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;

// LISTA ENCADEADA
No* inicioLista = NULL;
int totalItensLista = 0;

// Contadores de comparacoes
int comparacoes = 0;

// ==================== PROTOTIPOS - MENU E UTILIDADES ====================
void exibirMenuPrincipal();
void exibirMenuVetor();
void exibirMenuLista();
void limparBuffer();
void pausar();

// ==================== PROTOTIPOS - OPERACOES COM VETOR ====================
void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
void buscarSequencialVetor();
void ordenarVetor();
void buscarBinariaVetor();

// ==================== PROTOTIPOS - OPERACOES COM LISTA ====================
void inserirItemLista();
void removerItemLista();
void listarItensLista();
void buscarSequencialLista();
void liberarLista();

// ==================== FUNCAO PRINCIPAL ====================
int main() {
    int opcao;
    
    printf("=====================================================\n");
    printf("  FREE FIRE SURVIVAL - COMPARACAO DE ESTRUTURAS\n");
    printf("=====================================================\n");
    printf("      Vetor vs Lista Encadeada + Busca Binaria\n");
    printf("=====================================================\n\n");
    
    do {
        exibirMenuPrincipal();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        printf("\n");
        
        switch (opcao) {
            case 1:
                // Submenu do vetor
                {
                    int opcaoVetor;
                    do {
                        exibirMenuVetor();
                        printf("Escolha uma opcao: ");
                        scanf("%d", &opcaoVetor);
                        limparBuffer();
                        printf("\n");
                        
                        switch (opcaoVetor) {
                            case 1: inserirItemVetor(); break;
                            case 2: removerItemVetor(); break;
                            case 3: listarItensVetor(); break;
                            case 4: buscarSequencialVetor(); break;
                            case 5: ordenarVetor(); break;
                            case 6: buscarBinariaVetor(); break;
                            case 0: break;
                            default: printf(">>> Opcao invalida!\n");
                        }
                        
                        if (opcaoVetor != 0) pausar();
                    } while (opcaoVetor != 0);
                }
                break;
                
            case 2:
                // Submenu da lista encadeada
                {
                    int opcaoLista;
                    do {
                        exibirMenuLista();
                        printf("Escolha uma opcao: ");
                        scanf("%d", &opcaoLista);
                        limparBuffer();
                        printf("\n");
                        
                        switch (opcaoLista) {
                            case 1: inserirItemLista(); break;
                            case 2: removerItemLista(); break;
                            case 3: listarItensLista(); break;
                            case 4: buscarSequencialLista(); break;
                            case 0: break;
                            default: printf(">>> Opcao invalida!\n");
                        }
                        
                        if (opcaoLista != 0) pausar();
                    } while (opcaoLista != 0);
                }
                break;
                
            case 0:
                printf(">>> Saindo do sistema...\n");
                break;
                
            default:
                printf(">>> Opcao invalida!\n");
        }
        
    } while (opcao != 0);
    
    // Libera memoria da lista encadeada
    liberarLista();
    
    printf("\n=====================================================\n");
    printf("Sistema finalizado! Memoria liberada com sucesso.\n");
    printf("=====================================================\n\n");
    
    return 0;
}

// ==================== IMPLEMENTACAO - MENUS ====================

void exibirMenuPrincipal() {
    printf("\n=====================================================\n");
    printf("              MENU PRINCIPAL\n");
    printf("=====================================================\n");
    printf("1 - Mochila com VETOR (Lista Sequencial)\n");
    printf("2 - Mochila com LISTA ENCADEADA\n");
    printf("0 - Sair\n");
    printf("=====================================================\n");
}

void exibirMenuVetor() {
    printf("\n=====================================================\n");
    printf("         MOCHILA COM VETOR\n");
    printf("=====================================================\n");
    printf("1 - Inserir item\n");
    printf("2 - Remover item\n");
    printf("3 - Listar itens\n");
    printf("4 - Busca Sequencial\n");
    printf("5 - Ordenar vetor (Bubble Sort)\n");
    printf("6 - Busca Binaria (requer vetor ordenado)\n");
    printf("0 - Voltar\n");
    printf("=====================================================\n");
    printf("Itens no vetor: %d/%d\n", totalItensVetor, MAX_ITENS);
    printf("=====================================================\n");
}

void exibirMenuLista() {
    printf("\n=====================================================\n");
    printf("         MOCHILA COM LISTA ENCADEADA\n");
    printf("=====================================================\n");
    printf("1 - Inserir item\n");
    printf("2 - Remover item\n");
    printf("3 - Listar itens\n");
    printf("4 - Busca Sequencial\n");
    printf("0 - Voltar\n");
    printf("=====================================================\n");
    printf("Itens na lista: %d\n", totalItensLista);
    printf("=====================================================\n");
}

// ==================== OPERACOES COM VETOR ====================

void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf(">>> ERRO: Vetor cheio!\n");
        return;
    }
    
    printf("=== INSERIR ITEM NO VETOR ===\n");
    
    printf("Nome: ");
    fgets(mochilaVetor[totalItensVetor].nome, TAM_NOME, stdin);
    mochilaVetor[totalItensVetor].nome[strcspn(mochilaVetor[totalItensVetor].nome, "\n")] = '\0';
    
    printf("Tipo: ");
    fgets(mochilaVetor[totalItensVetor].tipo, TAM_TIPO, stdin);
    mochilaVetor[totalItensVetor].tipo[strcspn(mochilaVetor[totalItensVetor].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &mochilaVetor[totalItensVetor].quantidade);
    limparBuffer();
    
    totalItensVetor++;
    printf("\n>>> Item inserido no vetor! Total: %d\n", totalItensVetor);
}

void removerItemVetor() {
    char nomeBusca[TAM_NOME];
    int encontrado = 0;
    
    if (totalItensVetor == 0) {
        printf(">>> ERRO: Vetor vazio!\n");
        return;
    }
    
    printf("=== REMOVER ITEM DO VETOR ===\n");
    printf("Nome do item: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            
            // Desloca elementos
            for (int j = i; j < totalItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            
            totalItensVetor--;
            printf("\n>>> Item removido! Total: %d\n", totalItensVetor);
            break;
        }
    }
    
    if (!encontrado) {
        printf("\n>>> Item nao encontrado!\n");
    }
}

void listarItensVetor() {
    printf("=== ITENS NO VETOR ===\n\n");
    
    if (totalItensVetor == 0) {
        printf(">>> Vetor vazio!\n");
        return;
    }
    
    for (int i = 0; i < totalItensVetor; i++) {
        printf("[%d] %s | %s | Qtd: %d\n", 
               i + 1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
    printf("\nTotal: %d itens\n", totalItensVetor);
}

void buscarSequencialVetor() {
    char nomeBusca[TAM_NOME];
    
    if (totalItensVetor == 0) {
        printf(">>> ERRO: Vetor vazio!\n");
        return;
    }
    
    printf("=== BUSCA SEQUENCIAL NO VETOR ===\n");
    printf("Nome do item: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    comparacoes = 0;
    
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoes++;
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            printf("\n>>> ENCONTRADO na posicao %d!\n", i + 1);
            printf("    %s | %s | Qtd: %d\n", 
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("\n>>> Comparacoes: %d\n", comparacoes);
            return;
        }
    }
    
    printf("\n>>> Item nao encontrado!\n");
    printf(">>> Comparacoes: %d\n", comparacoes);
}

void ordenarVetor() {
    if (totalItensVetor == 0) {
        printf(">>> ERRO: Vetor vazio!\n");
        return;
    }
    
    printf("=== ORDENANDO VETOR (Bubble Sort por nome) ===\n");
    
    comparacoes = 0;
    Item temp;
    
    // Bubble Sort
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            comparacoes++;
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                // Troca
                temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    
    printf("\n>>> Vetor ordenado!\n");
    printf(">>> Comparacoes realizadas: %d\n", comparacoes);
    
    listarItensVetor();
}

void buscarBinariaVetor() {
    char nomeBusca[TAM_NOME];
    
    if (totalItensVetor == 0) {
        printf(">>> ERRO: Vetor vazio!\n");
        return;
    }
    
    printf("=== BUSCA BINARIA NO VETOR ===\n");
    printf("ATENCAO: O vetor precisa estar ordenado!\n");
    printf("Nome do item: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    comparacoes = 0;
    int inicio = 0;
    int fim = totalItensVetor - 1;
    
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        
        int cmp = strcmp(mochilaVetor[meio].nome, nomeBusca);
        
        if (cmp == 0) {
            printf("\n>>> ENCONTRADO na posicao %d!\n", meio + 1);
            printf("    %s | %s | Qtd: %d\n",
                   mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            printf("\n>>> Comparacoes: %d\n", comparacoes);
            return;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    printf("\n>>> Item nao encontrado!\n");
    printf(">>> Comparacoes: %d\n", comparacoes);
}

// ==================== OPERACOES COM LISTA ENCADEADA ====================

void inserirItemLista() {
    printf("=== INSERIR ITEM NA LISTA ENCADEADA ===\n");
    
    // Aloca novo no
    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        printf(">>> ERRO: Falha ao alocar memoria!\n");
        return;
    }
    
    printf("Nome: ");
    fgets(novoNo->dados.nome, TAM_NOME, stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = '\0';
    
    printf("Tipo: ");
    fgets(novoNo->dados.tipo, TAM_TIPO, stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    limparBuffer();
    
    // Insere no inicio da lista
    novoNo->proximo = inicioLista;
    inicioLista = novoNo;
    
    totalItensLista++;
    printf("\n>>> Item inserido na lista! Total: %d\n", totalItensLista);
}

void removerItemLista() {
    char nomeBusca[TAM_NOME];
    
    if (inicioLista == NULL) {
        printf(">>> ERRO: Lista vazia!\n");
        return;
    }
    
    printf("=== REMOVER ITEM DA LISTA ===\n");
    printf("Nome do item: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    No* atual = inicioLista;
    No* anterior = NULL;
    
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            if (anterior == NULL) {
                // Remove do inicio
                inicioLista = atual->proximo;
            } else {
                // Remove do meio/fim
                anterior->proximo = atual->proximo;
            }
            
            free(atual);
            totalItensLista--;
            printf("\n>>> Item removido! Total: %d\n", totalItensLista);
            return;
        }
        
        anterior = atual;
        atual = atual->proximo;
    }
    
    printf("\n>>> Item nao encontrado!\n");
}

void listarItensLista() {
    printf("=== ITENS NA LISTA ENCADEADA ===\n\n");
    
    if (inicioLista == NULL) {
        printf(">>> Lista vazia!\n");
        return;
    }
    
    No* atual = inicioLista;
    int posicao = 1;
    
    while (atual != NULL) {
        printf("[%d] %s | %s | Qtd: %d\n",
               posicao, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
        posicao++;
    }
    
    printf("\nTotal: %d itens\n", totalItensLista);
}

void buscarSequencialLista() {
    char nomeBusca[TAM_NOME];
    
    if (inicioLista == NULL) {
        printf(">>> ERRO: Lista vazia!\n");
        return;
    }
    
    printf("=== BUSCA SEQUENCIAL NA LISTA ===\n");
    printf("Nome do item: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    comparacoes = 0;
    No* atual = inicioLista;
    int posicao = 1;
    
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\n>>> ENCONTRADO na posicao %d!\n", posicao);
            printf("    %s | %s | Qtd: %d\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("\n>>> Comparacoes: %d\n", comparacoes);
            return;
        }
        atual = atual->proximo;
        posicao++;
    }
    
    printf("\n>>> Item nao encontrado!\n");
    printf(">>> Comparacoes: %d\n", comparacoes);
}

void liberarLista() {
    No* atual = inicioLista;
    No* proximo;
    
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    inicioLista = NULL;
    totalItensLista = 0;
}

// ==================== UTILIDADES ====================

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

/*
 * =====================================================================
 * COMPARACAO: VETOR vs LISTA ENCADEADA
 * =====================================================================
 * 
 * VETOR (Lista Sequencial):
 * - Acesso direto: O(1)
 * - Insercao no final: O(1)
 * - Remocao: O(n) - precisa deslocar elementos
 * - Busca sequencial: O(n)
 * - Busca binaria (ordenado): O(log n)
 * - Memoria: alocacao contigua, tamanho fixo
 * 
 * LISTA ENCADEADA:
 * - Acesso: O(n) - precisa percorrer
 * - Insercao no inicio: O(1)
 * - Remocao: O(n) - precisa buscar
 * - Busca: sempre O(n)
 * - Memoria: alocacao dinamica, tamanho flexivel
 * 
 * VANTAGENS DO VETOR:
 * + Acesso rapido por indice
 * + Busca binaria possivel (quando ordenado)
 * + Menor overhead de memoria
 * 
 * VANTAGENS DA LISTA:
 * + Tamanho dinamico (cresce conforme necessario)
 * + Insercao/remocao no inicio e rapida
 * + Nao precisa realocar ou deslocar elementos
 * =====================================================================
 */