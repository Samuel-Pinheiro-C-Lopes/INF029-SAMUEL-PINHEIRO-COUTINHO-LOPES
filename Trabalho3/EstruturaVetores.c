#include <stdio.h>
#include <stdlib.h>
#define TAM 10
#define LINHA_MAX (255)

#include "EstruturaVetores.h"

typedef struct aux 
{
    int idx;
    int tam;
    int vet[];
}Aux;

Aux* vetorPrincipal[TAM];

int convStrInt(char *str);
char* proxOcorrencia(char *idxStr, char *separadores);
char* obterSubstring(char *idxStr, char *separadores);
void copiarString(char *fonte, char *alvo, int tamMax);
void escreverArquivo (void);

/*
int main (void) 
{
    char teste[200];
    copiarString("Ola, teste!", teste, 100);
    printf("\n%s\n", teste);
    char teste2[100];
    copiarString(obterSubstring(teste, "!"), teste2, 12);
    printf("\n%s\n", teste2);
    char * outro = proxOcorrencia(teste, "t");
    printf("\n%s\n", outro);
    
    return EXIT_SUCCESS; 
}
*/
/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    int retorno = 0;

    if (posicao > TAM || posicao < 1)
    // se posição é um valor válido {entre 1 e 10}
        retorno = POSICAO_INVALIDA;
    else if (vetorPrincipal[posicao - 1] != NULL)
    // a posicao pode já existir estrutura auxiliar
        retorno = JA_TEM_ESTRUTURA_AUXILIAR;
    else if (tamanho > 10)
    // o tamanho ser muito grande
        retorno = SEM_ESPACO_DE_MEMORIA;
    // o tamanho nao pode ser menor que 1
    else if (tamanho < 1)
        retorno = TAMANHO_INVALIDO;
    else
    {
    // deu tudo certo, crie
        vetorPrincipal[posicao - 1] = (Aux*) malloc(sizeof(Aux) + (sizeof(int) * tamanho));
        vetorPrincipal[posicao - 1]->tam = tamanho;
        vetorPrincipal[posicao - 1]->idx = 0;

        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;
    
    if (posicao > TAM || posicao < 1)
        posicao_invalida = 1;

    if (vetorPrincipal[posicao - 1] != NULL)
    {
        existeEstruturaAuxiliar = 1;
        if (vetorPrincipal[posicao - 1]->idx < vetorPrincipal[posicao - 1]->tam)
            temEspaco = 1;
    }

    if (posicao_invalida)
        retorno = POSICAO_INVALIDA;
    else
    {
        // testar se existe a estrutura auxiliar
        if (existeEstruturaAuxiliar)
        {
            if (temEspaco)
            {
                //insere
                Aux* atual = vetorPrincipal[posicao - 1]; // para tornar mais legível
                atual->vet[atual->idx] = valor;
                atual->idx++;
                retorno = SUCESSO;
            }
            else
            {
                retorno = SEM_ESPACO;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    int retorno;

    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    
    Aux* atual = vetorPrincipal[posicao - 1];

    if (atual == NULL)
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else if (atual->idx == 0)
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    else
    {
        atual->idx--;
        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int retorno = SUCESSO;

    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    
    Aux* atual = vetorPrincipal[posicao - 1];

    if (atual == NULL)
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else if (atual->idx == 0)
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    else
    {
        for (int i = 0; i < atual->idx; i++)
            if (atual->vet[i] == valor)
            {
                for (int j = i; j <  atual->idx - 1; j++)
                    atual->vet[j] = atual->vet[j + 1];

                atual->idx--;
                
                return SUCESSO;
            }

        retorno = NUMERO_INEXISTENTE;
    }

    return retorno;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{

    int retorno = SUCESSO;
    
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    
    Aux* atual = vetorPrincipal[posicao - 1];

    if (atual == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    for (int i = 0; i < atual->idx; i++)
        vetorAux[i] = atual->vet[i];

    return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{

    int retorno = SUCESSO;
    int i, j, chave;

    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;
    
    Aux* atual = vetorPrincipal[posicao - 1];

    if (atual == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    if (atual->idx == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    for (i = 0; i < atual->idx; i++)
        vetorAux[i] = atual->vet[i];

    // ordena
    for (i = 1; i < atual->idx; i++) 
    {
        chave = vetorAux[i];
        j = i - 1;

        while (j >= 0 && vetorAux[j] > chave) {
            vetorAux[j + 1] = vetorAux[j];
            j = j - 1;
        }

        vetorAux[j + 1] = chave;
    }
    
    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{

    int retorno = SUCESSO;
    int i, j, k;
    Aux* atual;

    for (i = 0; i < TAM; i++)
    {
        atual = vetorPrincipal[i];
        if (atual != NULL)
        {
            if (atual->idx != 0)
            {
                break;
            }
        }
        else if (i == TAM - 1)
            return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

    k = 0;
    for (i = 0; i < TAM; i++)
    {
        atual = vetorPrincipal[i];
        if (atual != NULL)
        {
            for (j = 0; j < atual->idx; j++)
                vetorAux[k++] = atual->vet[j];
        }
    }

    return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{

    int retorno = SUCESSO;
    int i, j, k, chave;
    

    Aux* atual;

    for (i = 0; i < TAM; i++)
    {
        atual = vetorPrincipal[i];
        if (atual != NULL)
        {
            if (atual->idx != 0)
            {
                break;
            }
        }
        else if (i == TAM - 1)
            return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }


    k = 0;
    for (i = 0; i < TAM; i++)
    {
        atual = vetorPrincipal[i];
        if (atual != NULL)
        {
            for (j = 0; j < atual->idx; j++)
                vetorAux[k++] = atual->vet[j];
        }
    }

    // ordena
    for (i = 1; i < k; i++) 
    {
        chave = vetorAux[i];
        j = i - 1;

        while (j >= 0 && vetorAux[j] > chave) {
            vetorAux[j + 1] = vetorAux[j];
            j = j - 1;
        }

        vetorAux[j + 1] = chave;
    }
    
    return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;

    Aux* atual = vetorPrincipal[posicao - 1];

    if (atual == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    if (atual->tam + novoTamanho < 1)
        return NOVO_TAMANHO_INVALIDO;

    atual = realloc(atual, sizeof(Aux) + (sizeof(int) * (atual->tam + novoTamanho)));

    if (atual == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    atual->tam = atual->tam + novoTamanho;
    
    if (atual->idx >= atual->tam)
        atual->idx = atual->tam;

    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{

    int retorno = 0;
    
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;

    Aux* atual = vetorPrincipal[posicao - 1];

    if (atual == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    else if (atual->idx == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    retorno = atual->idx;

    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    No* inicio = NULL;
    No* atualNo;
    
    for (int i = 0; i < TAM; i++)
    {
        Aux* atual = vetorPrincipal[i];
        if (atual != NULL)
        {
            for (int j = 0; j < atual->idx; j++)
            {
                if (inicio == NULL)
                {
                    inicio = (No*) malloc(sizeof(No));
                    inicio->conteudo = atual->vet[j];
                    inicio->prox = NULL;
                }
                else 
                {
                    atualNo = inicio;
                    while (atualNo->prox != NULL)
                        atualNo = atualNo->prox;

                    atualNo->prox = (No*) malloc(sizeof(No));
                    atualNo->prox->conteudo = atual->vet[j];
                    atualNo->prox->prox = NULL;
                }
            }
        }
    }

    return inicio;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    int i = 0;
    while (inicio != NULL)
    {
        vetorAux[i] = inicio->conteudo;
        i++;
        inicio = inicio->prox;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No* atual = *inicio;
    No* temp;

    while (atual != NULL)
    {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    
    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
    for (int i = 0; i < TAM; i++)
        vetorPrincipal[i] = NULL;
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    escreverArquivo();
    for (int i = 0; i < TAM; i++)
        if (vetorPrincipal[i] != NULL)
            free(vetorPrincipal[i]);
}

/*
ARQUIVOS
*/

#define tam_max_substr (255)

// Sumário: copia o conteúdo de uma fonte de caracteres para um alvo até que encontre
// o terminador nulo da fonte ou chegue em um tamanho máximo de caracteres copiados
// (preferivelmente o tamanho máximo da cadeia alvo)
// Parâmetros: <fonte: string fonte>, <alvo: string alvo> e <tamMax: número máximo
// de caracteres a serem copiados, contando com o terminador nulo>
// Retorna: <void>
void copiarString(char *fonte, char *alvo, int tamMax)
{
    for (int i = 0; i < tamMax - 1 && *(fonte) != '\0'; i++)
        *(alvo++) = *(fonte++);
    
    *(alvo) = '\0';
}

// Sumário: função para obter uma substring a partir de string inicial
// e separador para entender o final da substring ('\0' sempre incluso)
// Parâmetros: <string> e <separadores: string com caracteres que finalizarão
// a substring - qualquer um deles finda a substring>
// Retorna: <char *: endereço para substring estática - requer copiar, não atribuir>
char* obterSubstring(char *idxString, char *separadores) 
{
    static char substring[tam_max_substr];
    int i, k;

    for (i = 0; idxString[i] != '\0'; i++)
    {
        for (k = 0; separadores[k] != '\0'; k++)
            if (idxString[i] == separadores[k])
                goto fim;
        
        substring[i] = idxString[i];
    }

    fim: 
    substring[++i] = '\0';
    return substring;
}

// Sumário: avança um indexador até a próxima ocorrência de um ou mais
// caracteres 
// Parâmetros: <idxStr: indexador atual a ser acrescido> e <separadores:
// caracteres que demarcarão o final do avanço>
// Retorna: <char *: idxStr após incrementos que resultem nele indexar
// um dos separadores>
char* proxOcorrencia(char *idxStr, char *separadores)
{
    char *idxSep;

    for (; *(idxStr) != '\0'; idxStr += sizeof(char))
        for (idxSep = separadores; *(idxSep) != '\0'; idxSep += sizeof(char))
            if (*(idxStr) == *(idxSep))
                goto fim;
            
    fim: return idxStr;
}

// Sumário: converte uma string em um inteiro
// Parâmetros: <str>
// Retorna: <int>
int convStrInt(char *str)
{
    int num = 0;
    int negativo = 0;

    if (*(str) == '-')
    {
        str += sizeof(char);
        negativo = 1;
    }

    while (*(str) != '\0')
    {
        num *= 10;
        num += *(str) - 48;
        str += sizeof(char);
    }

    if (negativo)
        num *= -1;
    
    return num;
}


// ESCREVER ARQUIVO

// Sumário: escreve um arquivo "vetorPrincipal.dados" que vai armazenar todos os dados
// de todas as estruturas auxiliares obtidas no vetorPrincipal durante o tempo de 
// execução do programa
// Parâmetros: <void>
// Retorna: <void>
void escreverArquivo (void)
{
    FILE *saida = fopen("vetorPrincipal.dados", "w");
    if (saida == NULL)
    {
        printf("\nERRO AO CRIAR ARQUIVO DE SAÍDA");
        return;
    }

    int i, j, tam;
    for (i = 0; i < TAM; i++)
    {
        if (vetorPrincipal[i] == NULL)
            continue; // sentinela caso não haja estrutura auxiliar na posição designada

        tam = vetorPrincipal[i]->tam;
        fprintf(saida, "%d;%d;%d;", i, tam, vetorPrincipal[i]->idx);
    
        for (j = 0; j < tam; j++)
            fprintf(saida, "%d;", vetorPrincipal[i]->vet[j]);
        
        fprintf(saida, "\n");
    }
    
    fclose(saida);
}