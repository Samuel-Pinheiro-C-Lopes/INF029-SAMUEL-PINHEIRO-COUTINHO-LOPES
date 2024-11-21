#include "q8.h"
#include <stdio.h>

int main ()
{
    
    system("clear");
    
    if (NUM_COLUNAS != NUM_LINHAS)
    {
        printf("\nO PROGRAMA FOI INICIADO COM UM FORMATO INCOMPATÍVEL COM O DE JOGO BATALHA NAVAL, SUAS FUNÇÕES PODEM NÃO FUNCIONAR CORRETAMENTE...");
        printf("Número de linhas: %d;\nNúmero de colunas: %d.", NUM_LINHAS, NUM_COLUNAS);
        printf("\n\nAperte enter para continuar, ou 0 e enter para encerrar... ");
        if (getchar() == '0')
            return 0;
    }
    else 
    {
        printf("Número de linhas e colunas: %d", NUM_LINHAS);
        printf("\nAperte enter para continuar... ");
        getchar();
    }
    
    system("clear");
    
    int numero_navios;
    printf("Entre com o número de navios do jogo [mínimo 5]: ");
    ext_ler_int_f(&numero_navios, 10);
    
    if (numero_navios < 5)
    {
        printf("\nNúmero inválida...\n");
        getchar();
        return 0;
   }
    
    int jogo_rodando = 1;
    
    Tabuleiro* tabuleiro_1 = inicializar_tabuleiro(JOGADOR_1);
    Tabuleiro* tabuleiro_2 = inicializar_tabuleiro(JOGADOR_2);

    int count = 0;

    system("clear");
    printf("Inserção do jogador 1!\nAperte enter para prosseguir...");
    getchar();
    while (count < numero_navios)
        interface_insercao (tabuleiro_1, &count);

    count = 0;
    
    printf("Inserção do jogador 2!\nAperte enter para prosseguir...");
    getchar();

    while (count < numero_navios)
        interface_insercao(tabuleiro_2, &count);
    
    while (jogo_rodando)
    {
        switch (checar_navios(tabuleiro_1)) 
        {
            case (NENHUM):
            {
                break;
            }
            case (JOGADOR_2):
            {
                printf("JOGADOR 2 VENCEU!!!\n");
                getchar();
                jogo_rodando = 0;
                break;
            }
        }
        switch (checar_navios(tabuleiro_2)) 
        {
            case (NENHUM):
            {
                break;
            }
            case (JOGADOR_1):
            {
                printf("JOGADOR 1 VENCEU!!!\n");
                getchar();
                jogo_rodando = 0;
                break;
            }
        
        }
        switch (menu_atirar_tabuleiro(tabuleiro_2, JOGADOR_1)) 
        {
            case (ACERTOU):
            {
                printf("ACERTOU UM NAVIO DO ADVERSARIO");
                break;
            }
            case (ERROU):
            {
                printf("ERROU O ALVO");
                break;
            }
            case (OPCAO_INVALIDA):
            {
                printf("OPÇÃO INSERIDA É INVÁLIDA");
                break;
            }
        }
        switch (menu_atirar_tabuleiro(tabuleiro_1, JOGADOR_2)) 
        {
            case (ACERTOU):
            {
                printf("ACERTOU UM NAVIO DO ADVERSÁRIO");
                break;
            }
            case (ERROU):
            {
                printf("ERROU O ALVO");
                break;
            }
            case (OPCAO_INVALIDA):
            {
                printf("OPÇÃO INSERIDA É INVÁLIDA");
                break;
            }
        
        }

    }

    mostrar_tabuleiro(tabuleiro_1, tabuleiro_1->jogador);
    getchar();
    mostrar_tabuleiro(tabuleiro_2, tabuleiro_2->jogador);
    getchar();

    tabuleiro_1 = liberar_tabuleiro(tabuleiro_1);
    tabuleiro_2 = liberar_tabuleiro(tabuleiro_2);

    return 1;
}

int menu_atirar_tabuleiro (Tabuleiro* tabuleiro, int jogador)
{
    char opcao[4];
    int retorno;

    mostrar_tabuleiro(tabuleiro, jogador);
    printf("JOGADOR: %d;", jogador);
    printf("Entre com a opção a tentar acertar: ");
    ler_string_f(opcao, 4);
    int coluna;
    ext_string_para_int(&coluna, &opcao[1]);
    coluna -= 1;
    int linha = opcao[0] - 65;

    if (coluna > NUM_COLUNAS - 1 || linha > NUM_LINHAS - 1 || coluna < 0 || linha < 0) // verifica valor válido   
    {
        retorno = OPCAO_INVALIDA;
        return retorno;
    }
    else 
    {
        if (tabuleiro->linhas_tabuleiro[linha].colunas_linha[coluna].valor == N)
            tabuleiro->linhas_tabuleiro[linha].colunas_linha[coluna].valor = O;
        else
            tabuleiro->linhas_tabuleiro[linha].colunas_linha[coluna].valor = X;
    }

    return TIRO_REALIZADO;
}

int checar_navios (Tabuleiro* tabuleiro)
{
    int retorno = JOGADOR_1;
    int i, j;

    for (i = 0; i < NUM_LINHAS; i++)
    {
        for (j = 0; j < NUM_COLUNAS; j++)
        {
            if (tabuleiro->linhas_tabuleiro[i].colunas_linha[j].valor == N)
                retorno = NENHUM;
            break;
        }
        if (retorno == NENHUM)
            break;
    }
    
    if (retorno != NENHUM)
    {
        if (tabuleiro->jogador == JOGADOR_1)
            return JOGADOR_2;
        else
            return JOGADOR_1;
   }
   else 
       return NENHUM;
}

void interface_insercao(Tabuleiro* tabuleiro, int* count)
{

    system("clear");

    int tam;
    
    if (*count == 0)
        tam = 4;
    else if (*count == 1)
        tam = 3;
    else if (*count < 5)
        tam = 1;
    else
        tam = 2;

    printf("Tamanho do navio atual: %d;\nAperte enter para prosseguir...", tam);
    getchar();
    system("clear");
    switch(interface_menu_inserir_navios(tabuleiro, tam))
    {
        case (NAVIO_JA_INSERIDO):
        {
            printf("O caminho especificado já está ocupado por um navio!\nAperte enter para continuar...");
            getchar();
            break;
        }
        case (OPCAO_INVALIDA):
        {
            printf("Opção inserida não corresponde a nenhuma posição de célula presente no tabuleiros.\nAperte enter para continuar...");
            getchar();
            break;
        }
        case (SENTIDO_INVALIDO):
        {
            printf("Sentido inserido inválido.\nAperte enter para continuar...");
            getchar();
            break;
        }
        case (INSERCAO_NAVIO_SUCESSO):
        {
            *count += 1;
            printf("Inserção realizada com sucesso!\nAperte enter para continuar...");
            getchar();
            break;
        }
    }
}


Tabuleiro* inicializar_tabuleiro (int jogador)
{
    int i;
    int j;

    Tabuleiro* tabuleiro = (Tabuleiro*) malloc(sizeof(Tabuleiro)); // alocar tabuleiro

    tabuleiro->nome_tabuleiro = "BATALHA NAVAL";
    tabuleiro->jogador = jogador;
                                                                   
    tabuleiro->linhas_tabuleiro = (Linha*) malloc(sizeof(Linha) * NUM_LINHAS); // alocar linhas
                                                                        
    for (i = 0; i < NUM_LINHAS; i++)
    {
        tabuleiro->linhas_tabuleiro[i].nome_linha = 65 + i;
        tabuleiro->linhas_tabuleiro[i].colunas_linha = (Coluna*) malloc(sizeof(Coluna) * NUM_COLUNAS);

        for (j = 0; j < NUM_COLUNAS; j++)
        {
            tabuleiro->linhas_tabuleiro[i].colunas_linha[j].nome_coluna = 1 + j;
            tabuleiro->linhas_tabuleiro[i].colunas_linha[j].valor = VAZIO;
        }
    }

    return tabuleiro; // retornar ponteiro do tabuleiro inicializado
};

Tabuleiro* liberar_tabuleiro(Tabuleiro* tabuleiro)
{
    int i; 

    for (i = 0; i < NUM_LINHAS; i++)
        free(tabuleiro->linhas_tabuleiro[i].colunas_linha); // desaloca colunas

    free(tabuleiro->linhas_tabuleiro); // desaloca linhas
    
    free(tabuleiro); // desaloca tabuleiro
    
    return NULL;
}

void mostrar_tabuleiro(Tabuleiro* tabuleiro, int jogador)
{
    int i;
    int j;

    system("clear");
    
    printf("%s\n", tabuleiro->nome_tabuleiro);
    printf("     ");
    for (i = 0; i < NUM_COLUNAS; i++)
        printf("%d      ", tabuleiro->linhas_tabuleiro[0].colunas_linha[i].nome_coluna);
    
    printf("\n");

    for (i = 0; i < NUM_LINHAS; i++)
    {
        printf("%c:   ", tabuleiro->linhas_tabuleiro[i].nome_linha); 
        for (j = 0; j < NUM_COLUNAS; j++)
        {
            if (tabuleiro->jogador != jogador)
            {
                if (tabuleiro->linhas_tabuleiro[i].colunas_linha[j].valor == N)
                    printf("%c   ", ' ');
                else
                    printf("%c   ", tabuleiro->linhas_tabuleiro[i].colunas_linha[j].valor);
            }
            else 
                printf("%c   ", tabuleiro->linhas_tabuleiro[i].colunas_linha[j].valor);

            if (j + 1 < NUM_COLUNAS)    
                printf("|  ");
        }
        printf("\n");
    }
    
    printf("\n");
}

int interface_menu_inserir_navios (Tabuleiro* tabuleiro, int tam)
{ 
    char sentido[2];
    char opcao[4];
    mostrar_tabuleiro(tabuleiro, tabuleiro->jogador);
    printf("JOGADOR: %d;", tabuleiro->jogador);
    printf("\nEntre com o sentido de inserção do navio ['H' para horizontal e 'V' para vertical]: ");
    ler_string_f(sentido, 2);
    printf("Entre com a posição [formato: LINHA/COLUNA]: ");
    ler_string_f(opcao, 4);
    system("clear");
    return menu_inserir_navios(tabuleiro, opcao, sentido[0], tam);
}

int menu_inserir_navios (Tabuleiro* tabuleiro, char opcao[], char sentido, int tam)
{
    int retorno;

    int i;
    int coluna;
    ext_string_para_int(&coluna, &opcao[1]);
    coluna -= 1;
    int linha = opcao[0] - 65;

    if (coluna > NUM_COLUNAS - 1 || linha > NUM_LINHAS - 1 || coluna < 0 || linha < 0) // verifica valor válido   
    {
        retorno = OPCAO_INVALIDA;
        return retorno;
    }


    retorno = checar_tabuleiro(tabuleiro, linha, coluna, sentido, tam); //  verifica lugar válido
    if (retorno != INSERCAO_NAVIO_SUCESSO)
    {
        return retorno;
    }
    
    if (sentido == HORIZONTAL)
    {
        if (coluna + tam > NUM_COLUNAS)
            return OPCAO_INVALIDA;
        
        for (i = 0; i < tam; i++)
            tabuleiro->linhas_tabuleiro[linha].colunas_linha[coluna + i].valor = N;
    }
    
    if (sentido == VERTICAL)
    {
        if (linha - tam < 0)
            return OPCAO_INVALIDA;
        
        for (i = tam; i >= 0; i--)
            tabuleiro->linhas_tabuleiro[linha - i].colunas_linha[coluna].valor = N;
    }

    retorno = INSERCAO_NAVIO_SUCESSO;
    return retorno;
}

int checar_tabuleiro (Tabuleiro* tabuleiro, int linha, int coluna, char sentido, int tam)
{
    int retorno = INSERCAO_NAVIO_SUCESSO;
    int i;

    if (sentido == HORIZONTAL)
    {
        for (i = 0; i < tam; i++)
            if (tabuleiro->linhas_tabuleiro[linha].colunas_linha[coluna + i].valor != VAZIO)
                retorno = NAVIO_JA_INSERIDO;
    }
    else if (sentido == VERTICAL)
    {
        for (i = 0; i < tam; i++)    
            if (tabuleiro->linhas_tabuleiro[linha-i].colunas_linha[coluna].valor != VAZIO)
                retorno = NAVIO_JA_INSERIDO;
    }
    else 
        return retorno = SENTIDO_INVALIDO;
    
    return retorno;
}

// Lê uma string sem poluir o buffer (passar tamanho como 'sizeof(string)' preferencialmente)
void ler_string_f (char* string, int tam)
{
	{
		char entrada = getchar(); // Recebe char

		if (entrada == 10) // entrada é 'enter'
		{
			*string = '\0'; // terminador nulo
			return; // fim recursão
		}
		else if (tam > sizeof(char)) // ainda há caracteres para preencher
		{
			*string = entrada; // caracter atual
			string++; // próximo do ponteiro
			tam -= sizeof(char); // -1 caracter para preencher
		}
	}

	ler_string_f (string, tam);
}

// Lê um inteiro com determinado número de casas específicadas sem poluir o buffer
void ler_int_f (int* int_num, int casas)
{
	{
		int temp_char = getchar(); // recebe caracter
		
		if  (temp_char < 48 || temp_char > 57) // entrada não é um número
		{
			if (temp_char == 10) // entrada foi 'enter'
				return; // fim recursão
			else if (temp_char == '-' && casas > 0) // entrada foi '-' e número ainda é 0
			{
				temp_char = getchar();
				if (temp_char >= 48 && temp_char <= 57) // entrada foi um número
				{
					(*int_num) -= (temp_char - 48); // número recebe próximo algarismo como negativo
					casas--; // -1 casa decimal
				}
				else if (temp_char == 10) // entrada foi 'enter'
					return; // fim recursão
			}
		}
		else if (casas > 0) // char é número e ainda há casas
		{
			(*int_num) *= 10; // move algarismos para a esquerda
			(*int_num) += (*int_num) >= 0 ? (temp_char - 48) : ((temp_char - 48) * -1); // preenche novo digito com base no sinal
			casas--; // -1 casa decimal
		}
	}

	ler_int_f (int_num, casas);
}

// Extensor do ler_int_f para ler inteiro e inicializar apropriadamente (int_num = 0)
void ext_ler_int_f (int* int_num, int casas)
{
	*int_num = 0;
	ler_int_f(int_num, casas);
}


// Transfere o equivalente numérico dos caracteres de uma string para um número (requer que num == 0)
void string_para_int (int* num, char* string)
{
    // caso string esteja no final
    if (*string < 48 || *string > 57)
		return;

	*num *= 10;

	if (*num < 0) // número teve final negativo
		*num -= *(string) - 48;
    else if (*string == '-') // sinal negativo
	{
		string += 1;
        *num -= *(string) - 48;
    }
	else // número é positivo 
		*num += *(string) - 48;

	string_para_int(num, string + 1);
}

void ext_string_para_int (int* num, char* string)
{
	*num = 0;

	string_para_int(num, string);
}
