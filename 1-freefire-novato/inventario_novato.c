/*
 * =====================================================================
 * FREE FIRE SURVIVAL - NIVEL NOVATO
 * Sistema de Inventario com Vetores e Structs
 * =====================================================================
 * Descricao: Sistema de mochila de loot que permite cadastrar, remover,
 * listar e buscar itens usando estruturas de dados compostas (structs)
 * e listas sequenciais (vetores).
 * 
 * Autora: Daniela Chiavenato Marzagao
 * Data: Novembro/2025
 * Disciplina: Analise e Desenvolvimento de Sistemas
 * =====================================================================
 */

// ==================== BIBLIOTECAS ====================
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ==================== CONSTANTES ====================
#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

// ==================== ESTRUTURA DE DADOS ====================
/*
 * Struct Item:
 * Representa um item do inventario com suas propriedades
 */
typedef struct {
    char nome[TAM_NOME];      // Nome do item (ex: "AK47", "Kit Medico")
    char tipo[TAM_TIPO];      // Tipo do item (arma, municao, cura, ferramenta)
    int quantidade;           // Quantidade no inventario
} Item;

// ==================== VARIAVEIS GLOBAIS ====================
Item mochila[MAX_ITENS];     // Vetor que armazena os itens
int totalItens = 0;          // Contador de itens cadastrados

// ==================== PROTOTIPOS DAS FUNCOES ====================
void exibirMenu();
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void limparBuffer();
void pausar();

// ==================== FUNCAO PRINCIPAL ====================
int main() {
    int opcao;
    
    // Cabecalho do jogo
    printf("=====================================================\n");
    printf("     FREE FIRE SURVIVAL - SISTEMA DE INVENTARIO\n");
    printf("=====================================================\n");
    printf("    Organize sua mochila e sobreviva na ilha!\n");
    printf("=====================================================\n\n");
    
    // Loop principal do menu
    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        printf("\n");
        
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf(">>> Saindo do sistema de inventario...\n");
                printf(">>> Boa sorte na ilha, sobrevivente!\n");
                break;
            default:
                printf(">>> ERRO: Opcao invalida! Tente novamente.\n");
        }
        
        if (opcao != 0) {
            pausar();
        }
        
    } while (opcao != 0);
    
    printf("\n=====================================================\n");
    printf("Sistema finalizado com sucesso!\n");
    printf("=====================================================\n\n");
    
    return 0;
}

// ==================== IMPLEMENTACAO DAS FUNCOES ====================

/*
 * exibirMenu()
 * Exibe o menu principal de opcoes do sistema
 */
void exibirMenu() {
    printf("\n=====================================================\n");
    printf("                  MENU PRINCIPAL\n");
    printf("=====================================================\n");
    printf("1 - Cadastrar novo item na mochila\n");
    printf("2 - Remover item da mochila\n");
    printf("3 - Listar todos os itens\n");
    printf("4 - Buscar item especifico\n");
    printf("0 - Sair do sistema\n");
    printf("=====================================================\n");
    printf("Itens na mochila: %d/%d\n", totalItens, MAX_ITENS);
    printf("=====================================================\n");
}

/*
 * inserirItem()
 * Adiciona um novo item ao inventario
 * Valida se ha espaco disponivel e se os dados sao validos
 */
void inserirItem() {
    // Verifica se ha espaco na mochila
    if (totalItens >= MAX_ITENS) {
        printf(">>> ERRO: Mochila cheia! Remova itens antes de adicionar novos.\n");
        return;
    }
    
    printf("=====================================================\n");
    printf("           CADASTRAR NOVO ITEM\n");
    printf("=====================================================\n");
    
    // Leitura do nome do item
    printf("Digite o nome do item: ");
    fgets(mochila[totalItens].nome, TAM_NOME, stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0';
    
    // Verifica se o nome nao esta vazio
    if (strlen(mochila[totalItens].nome) == 0) {
        printf(">>> ERRO: Nome do item nao pode ser vazio!\n");
        return;
    }
    
    // Leitura do tipo do item
    printf("Digite o tipo do item (arma/municao/cura/ferramenta): ");
    fgets(mochila[totalItens].tipo, TAM_TIPO, stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0';
    
    // Verifica se o tipo nao esta vazio
    if (strlen(mochila[totalItens].tipo) == 0) {
        printf(">>> ERRO: Tipo do item nao pode ser vazio!\n");
        return;
    }
    
    // Leitura da quantidade
    printf("Digite a quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    limparBuffer();
    
    // Valida a quantidade
    if (mochila[totalItens].quantidade <= 0) {
        printf(">>> ERRO: Quantidade deve ser maior que zero!\n");
        return;
    }
    
    // Incrementa o contador de itens
    totalItens++;
    
    printf("\n>>> Item cadastrado com sucesso!\n");
    printf(">>> Total de itens na mochila: %d/%d\n", totalItens, MAX_ITENS);
}

/*
 * removerItem()
 * Remove um item do inventario com base no nome
 * Usa busca sequencial para localizar o item
 */
void removerItem() {
    char nomeBusca[TAM_NOME];
    int i, encontrado = 0;
    
    // Verifica se ha itens para remover
    if (totalItens == 0) {
        printf(">>> ERRO: Mochila vazia! Nao ha itens para remover.\n");
        return;
    }
    
    printf("=====================================================\n");
    printf("              REMOVER ITEM\n");
    printf("=====================================================\n");
    
    // Solicita o nome do item a ser removido
    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca sequencial pelo item
    for (i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            
            // Exibe dados do item encontrado
            printf("\n>>> Item encontrado:\n");
            printf("    Nome.......: %s\n", mochila[i].nome);
            printf("    Tipo.......: %s\n", mochila[i].tipo);
            printf("    Quantidade.: %d\n", mochila[i].quantidade);
            
            // Remove o item deslocando os elementos posteriores
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            
            totalItens--;
            printf("\n>>> Item removido com sucesso!\n");
            printf(">>> Total de itens na mochila: %d/%d\n", totalItens, MAX_ITENS);
            break;
        }
    }
    
    if (!encontrado) {
        printf("\n>>> ERRO: Item '%s' nao encontrado na mochila!\n", nomeBusca);
    }
}

/*
 * listarItens()
 * Exibe todos os itens cadastrados no inventario
 * Mostra nome, tipo e quantidade de cada item
 */
void listarItens() {
    int i;
    
    printf("=====================================================\n");
    printf("           INVENTARIO COMPLETO\n");
    printf("=====================================================\n");
    
    // Verifica se ha itens para listar
    if (totalItens == 0) {
        printf(">>> Mochila vazia! Nenhum item cadastrado.\n");
        return;
    }
    
    // Lista todos os itens
    printf("\nTotal de itens: %d/%d\n\n", totalItens, MAX_ITENS);
    
    for (i = 0; i < totalItens; i++) {
        printf("ITEM %d:\n", i + 1);
        printf("  Nome.......: %s\n", mochila[i].nome);
        printf("  Tipo.......: %s\n", mochila[i].tipo);
        printf("  Quantidade.: %d\n", mochila[i].quantidade);
        printf("-----------------------------------------------------\n");
    }
}

/*
 * buscarItem()
 * Realiza busca sequencial por um item especifico
 * Conta e exibe o numero de comparacoes realizadas
 */
void buscarItem() {
    char nomeBusca[TAM_NOME];
    int i, encontrado = 0, comparacoes = 0;
    
    // Verifica se ha itens para buscar
    if (totalItens == 0) {
        printf(">>> ERRO: Mochila vazia! Nao ha itens para buscar.\n");
        return;
    }
    
    printf("=====================================================\n");
    printf("              BUSCAR ITEM\n");
    printf("=====================================================\n");
    
    // Solicita o nome do item a buscar
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    printf("\n>>> Realizando busca sequencial...\n\n");
    
    // Busca sequencial com contador de comparacoes
    for (i = 0; i < totalItens; i++) {
        comparacoes++;
        
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            
            // Exibe o item encontrado
            printf(">>> ITEM ENCONTRADO!\n");
            printf("-----------------------------------------------------\n");
            printf("  Posicao....: %d\n", i + 1);
            printf("  Nome.......: %s\n", mochila[i].nome);
            printf("  Tipo.......: %s\n", mochila[i].tipo);
            printf("  Quantidade.: %d\n", mochila[i].quantidade);
            printf("-----------------------------------------------------\n");
            break;
        }
    }
    
    if (!encontrado) {
        printf(">>> Item '%s' nao encontrado na mochila!\n", nomeBusca);
    }
    
    // Exibe estatisticas da busca
    printf("\n>>> Estatisticas da busca:\n");
    printf("    Comparacoes realizadas: %d\n", comparacoes);
    printf("    Total de itens na mochila: %d\n", totalItens);
}

/*
 * limparBuffer()
 * Limpa o buffer de entrada para evitar problemas com scanf
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * pausar()
 * Pausa a execucao aguardando o usuario pressionar ENTER
 */
void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

/*
 * =====================================================================
 * EXPLICACOES TECNICAS:
 * =====================================================================
 * 
 * 1. STRUCT ITEM:
 *    - Agrupa dados relacionados (nome, tipo, quantidade)
 *    - Facilita organizacao e manipulacao de dados do inventario
 *    - typedef permite uso direto sem a palavra "struct"
 * 
 * 2. VETOR DE STRUCTS (LISTA SEQUENCIAL):
 *    - mochila[MAX_ITENS] = espaco para 10 itens
 *    - Acesso direto por indice: O(1)
 *    - Insercao no final: O(1)
 *    - Remocao com deslocamento: O(n)
 * 
 * 3. BUSCA SEQUENCIAL:
 *    - Percorre item por item ate encontrar
 *    - Complexidade: O(n) no pior caso
 *    - Melhor caso: O(1) se item estiver no inicio
 *    - Contador de comparacoes demonstra o desempenho
 * 
 * 4. OPERACOES IMPLEMENTADAS:
 *    - Insercao: Adiciona no final do vetor
 *    - Remocao: Busca + desloca elementos posteriores
 *    - Listagem: Percorre e exibe todos os itens
 *    - Busca: Localiza item especifico por nome
 * 
 * 5. VALIDACOES:
 *    - Verifica espaco disponivel antes de inserir
 *    - Valida dados de entrada (nao vazios, quantidade > 0)
 *    - Trata casos de mochila vazia
 *    - Feedback claro ao usuario em todas operacoes
 * =====================================================================
 */