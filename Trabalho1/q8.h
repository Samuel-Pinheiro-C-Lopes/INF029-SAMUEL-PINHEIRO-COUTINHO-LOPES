#ifndef Q8_HEADER

#define Q8_HEADER
#include<stdio.h>
#include<stdlib.h>

#define NOME_TABULEIRO ("JOGO DA VELHA")
#define NUM_LINHAS (10)
#define NUM_COLUNAS (10)
#define X ('X')
#define O ('O')
#define N ('N')
#define VAZIO (' ')
#define JOGADOR_1 (1)
#define JOGADOR_2 (2)
#define OPCAO_INVALIDA (-1)
#define NAVIO_JA_INSERIDO (-2)
#define LOCAL_JA_MARCADO (-3)
#define SENTIDO_INVALIDO (-4)
#define HORIZONTAL ('H')
#define VERTICAL ('V')
#define INSERCAO_NAVIO_SUCESSO (-31)
#define SUCESSO_MARCACAO (-32)
#define TIRO_REALIZADO (-33)
#define NENHUM (-55)
#define ACERTOU (-69)
#define ERROU (-70)

typedef struct tabuleiro Tabuleiro;
typedef struct linha Linha;
typedef struct coluna Coluna;

struct tabuleiro 
{
    char* nome_tabuleiro;
    int jogador;
    Linha* linhas_tabuleiro;
};

struct linha 
{
    char nome_linha;
    Coluna* colunas_linha;
};

struct coluna
{
    int nome_coluna;
    int valor;
};

Tabuleiro* inicializar_tabuleiro(int jogador);
Tabuleiro* liberar_tabuleiro(Tabuleiro* tabuleiro);
void mostrar_tabuleiro(Tabuleiro* tabuleiro, int jogador);
void ext_ler_int_f (int* int_num, int casas);
void ler_int_f (int* int_num, int casas);
void ler_string_f (char* string, int tam);
int checar_tabuleiro (Tabuleiro* tabuleiro, int linha, int coluna, char sentido, int tam);
int menu_inserir_navios (Tabuleiro* tabuleiro, char opcao[], char sentido, int tam);
int interface_menu_inserir_navios (Tabuleiro* tabuleiro, int tam);
void interface_insercao(Tabuleiro* tabuleiro, int* count);
void string_para_int (int* num, char* string);
void ext_string_para_int (int* num, char* string);
int checar_navios (Tabuleiro* tabuleiro);
int menu_atirar_tabuleiro (Tabuleiro* tabuleiro, int jogador);

#endif