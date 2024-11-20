#include "q7.h"

int main ()
{

    system("clear");
    
    if (NUM_COLUNAS != NUM_LINHAS)
    {
        printf("\nO PROGRAMA FOI INICIADO COM UM FORMATO INCOMPATÍVEL COM O DE UM JOGO DA VELHA, SUAS FUNÇÕES PODEM NÃO FUNCIONAR CORRETAMENTE...");
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

    char opcao[3];
    
    int jogador = JOGADOR_1;
    int jogo_rodando = 1;

    Tabuleiro* tabuleiro = inicializar_tabuleiro();

    while (jogo_rodando) 
    {
        switch (interface_menu_jogo_da_velha(opcao, &jogador, tabuleiro)) 
        {
            case (JOGADOR_INVALIDO):
            {
                printf("\nJOGADOR INVÁLIDO!\nEncerrando jogo...");
                getchar();
                jogo_rodando = 0;
                break;
            }
            case (LOCAL_JA_MARCADO):
            {
                printf("\nLOCAL DESIGNADO JÁ SE ENCONTRA MARCADO...");
                getchar();
                break;
            }
            case (OPCAO_INVALIDA):
            {
                printf("\nA OPCAO INSERIDA NÃO CORRESPONDE A NENHUMA LINHA / COLUNA NO FORMATO: (LETRA/NÚMERO) presente no tabuleiro atual...");
                getchar();
                break;
            }
            case (SUCESSO_MARCACAO):
            {
                system("clear");
                int vencedor = checar_vencedor(tabuleiro);
                switch(vencedor)
                {
                    case (NENHUM):
                    {
                        printf("\nMARCACAO FEITA COM SUCESSO!\nContinuando jogo...");
                        getchar();
                        break;
                    }
                    case (EMPATE):
                    {
                        printf("EMPATE!\nEncerrando o jogo...");
                        getchar();
                        jogo_rodando = 0;
                        break;
                    }
                    default:
                    {
                        printf("\nJOGADOR %d VENCEU!\nEncerrando o jogo...", vencedor);
                        getchar();
                        jogo_rodando = 0;
                        break;
                    }
                }
                break;
            }
        }
    }

    tabuleiro = liberar_tabuleiro(tabuleiro);
    
    return 1;
}

int interface_menu_jogo_da_velha (char* opcao, int* jogador, Tabuleiro* tabuleiro)
{
    mostrar_tabuleiro(tabuleiro);
    printf("JOGADOR: %d;\n", *jogador);
    printf("Entre com a opção: ");
    ler_string_f(opcao, 3);
    return menu_jogo_da_velha(opcao, jogador, tabuleiro);
}

int menu_jogo_da_velha (char opcao[], int* jogador, Tabuleiro* tabuleiro)
{
    char valor;

    // verifica jogador atual
    if (*jogador == JOGADOR_1)
        valor = X;
    else if (*jogador == JOGADOR_2)
        valor = O;
    else
        return JOGADOR_INVALIDO;
    
    // obtém linha e coluna da opção inserida
    int coluna = opcao[1] - 49;
    int linha = opcao[0] - 65;    

    if (coluna > NUM_COLUNAS - 1 || linha > NUM_LINHAS - 1 || coluna < 0 || linha < 0) // verifica valor válido   
        return OPCAO_INVALIDA;

    if (tabuleiro->linhas_tabuleiro[linha].colunas_linha[coluna].valor != ' ') // verifica lugar válido
        return LOCAL_JA_MARCADO;
    
    tabuleiro->linhas_tabuleiro[linha].colunas_linha[coluna].valor = valor; // marca o local
    *jogador = *jogador == JOGADOR_1 ? JOGADOR_2 : JOGADOR_1; // alterna jogador
                                                              
    return SUCESSO_MARCACAO;
}

int verificar_valor_vencedor (char valor)
{
    if (valor == X)
    {
        return JOGADOR_1;
    }
    else if (valor == O)
    {
        return JOGADOR_2;
    }
    else 
        return NENHUM;
}

int checar_vencedor (Tabuleiro* tabuleiro)
{
    int vencedor; 
    int i, j;
    char valor_atual;
    
    // checa por linha
    for (i = 0; i < NUM_LINHAS; i++)
    {
        valor_atual = tabuleiro->linhas_tabuleiro[i].colunas_linha[0].valor;
        for (j = 0; j < NUM_COLUNAS; j++)
        {
            if (valor_atual == tabuleiro->linhas_tabuleiro[i].colunas_linha[j].valor)
                continue;
            else
            {
                valor_atual = ' ';
                break;
            }
        }
        
        if (valor_atual != ' ')
            break;
    }
    
    vencedor = verificar_valor_vencedor(valor_atual);
    if (vencedor != NENHUM)
        return vencedor;

    // checa por coluna
    for (i = 0; i < NUM_COLUNAS; i++)
    {
        valor_atual = tabuleiro->linhas_tabuleiro[0].colunas_linha[i].valor;
        for (j = 0; j < NUM_LINHAS; j++)
        {
            if (valor_atual == tabuleiro->linhas_tabuleiro[j].colunas_linha[i].valor)
                continue;
            else
            {
                valor_atual = ' ';                
                break;
            }
        }
        
        if (valor_atual != ' ')
            break;       
    }
    
    vencedor = verificar_valor_vencedor(valor_atual);
    if (vencedor != NENHUM)
        return vencedor;

   
    // checa por diagonal principal
    valor_atual = tabuleiro->linhas_tabuleiro[0].colunas_linha[0].valor;
    for (i = 0; i < NUM_LINHAS; i++)
    {
        if (valor_atual == tabuleiro->linhas_tabuleiro[i].colunas_linha[i].valor)
            continue;
        else
        {
            valor_atual = ' ';
            break;
        }
    }

    vencedor = verificar_valor_vencedor(valor_atual);
    if (vencedor != NENHUM)
        return vencedor;

    // checa por diagonal secundária
    valor_atual = tabuleiro->linhas_tabuleiro[0].colunas_linha[NUM_COLUNAS - 1].valor;
    j = 0;
    
    for (i = NUM_LINHAS - 1; i >= 0; i--)
    {
            if (valor_atual == tabuleiro->linhas_tabuleiro[j].colunas_linha[i].valor)
            {
                j++;
                continue;
            }
            else
            {
                valor_atual = ' ';
                break;
            }
    }

    vencedor = verificar_valor_vencedor(valor_atual);
    if (vencedor != NENHUM)
        return vencedor;
    
    // checa se o tabuleiro está cheio
    vencedor = EMPATE;
    for (i = 0; i < NUM_LINHAS; i++)
    {
        for (j = 0; j < NUM_COLUNAS; j++)
        {
            if (tabuleiro->linhas_tabuleiro[i].colunas_linha[j].valor == ' ')
            {
                vencedor = NENHUM;
                break;
            }
        }

        if (vencedor == NENHUM)
            break;
    }
    
    return vencedor;
}

Tabuleiro* inicializar_tabuleiro ()
{
    int i;
    int j;

    Tabuleiro* tabuleiro = (Tabuleiro*) malloc(sizeof(Tabuleiro)); // alocar tabuleiro
                                                                   
    tabuleiro->linhas_tabuleiro = (Linha*) malloc(sizeof(Linha) * NUM_LINHAS); // alocar linhas
                                                                        
    for (i = 0; i < NUM_LINHAS; i++)
    {
        tabuleiro->linhas_tabuleiro[i].nome_linha = 65 + i;
        tabuleiro->linhas_tabuleiro[i].colunas_linha = (Coluna*) malloc(sizeof(Coluna) * NUM_COLUNAS);

        for (j = 0; j < NUM_COLUNAS; j++)
        {
            tabuleiro->linhas_tabuleiro[i].colunas_linha[j].nome_coluna = 49 + j;
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

void mostrar_tabuleiro(Tabuleiro* tabuleiro)
{
    int i;
    int j;

    system("clear");
    
    printf("TABULEIRO DO JOGO DA VELHA\n");
    printf("     ");
    for (i = 0; i < NUM_COLUNAS; i++)
        printf("%c      ", tabuleiro->linhas_tabuleiro[0].colunas_linha[i].nome_coluna);
    
    printf("\n");

    for (i = 0; i < NUM_LINHAS; i++)
    {
        printf("%c:   ", tabuleiro->linhas_tabuleiro[i].nome_linha); 
        for (j = 0; j < NUM_COLUNAS; j++)
        {
            printf("%c   ", tabuleiro->linhas_tabuleiro[i].colunas_linha[j].valor);
            if (j + 1 < NUM_COLUNAS)    
                printf("|  ");
        }
        printf("\n");
    }
    
    printf("\n\n");
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
