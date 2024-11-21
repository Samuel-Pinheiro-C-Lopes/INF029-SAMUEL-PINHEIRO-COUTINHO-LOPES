#ifndef Q7_HEADER
#define Q7_HEADER

#include<stdlib.h>
#include<stdio.h>

#define NOME_TABULEIRO ("JOGO DA VELHA")
#define NUM_LINHAS (3)
#define NUM_COLUNAS (3)
#define X ('X')
#define O ('O')
#define VAZIO (' ')
#define JOGADOR_1 (1)
#define JOGADOR_2 (2)
#define EMPATE (-3)
#define NENHUM (-99)
#define OPCAO_INVALIDA (-11)
#define JOGADOR_INVALIDO (-12)
#define LOCAL_JA_MARCADO (-21)
#define SUCESSO_MARCACAO (81)

typedef struct tabuleiro Tabuleiro;
typedef struct linha Linha;
typedef struct coluna Coluna;

struct tabuleiro 
{
    char* nome_tabuleiro;
    Linha* linhas_tabuleiro;
};

struct linha 
{
    char nome_linha;
    Coluna* colunas_linha;
};

struct coluna
{
    char nome_coluna;
    int valor;
};

Tabuleiro* inicializar_tabuleiro();
Tabuleiro* liberar_tabuleiro(Tabuleiro* tabuleiro);
void mostrar_tabuleiro(Tabuleiro* tabuleiro);
int checar_vencedor (Tabuleiro* tabuleiro);
int verificar_valor_vencedor (char valor);
int menu_jogo_da_velha (char opcao[], int* jogador, Tabuleiro* tabuleiro);
int interface_menu_jogo_da_velha (char* opcao, int* jogador, Tabuleiro* tabuleiro);
void ext_ler_int_f (int* int_num, int casas);
void ler_int_f (int* int_num, int casas);
void ler_string_f (char* string, int tam);

#endif