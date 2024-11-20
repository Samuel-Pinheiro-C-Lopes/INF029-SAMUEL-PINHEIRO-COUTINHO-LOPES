// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Samuel Pinheiro Coutinho Lopes
//  email: Samuelpinheiroclopes@gmail.com
//  Matrícula: 20241160017
//  Semestre: 2024.2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "SamuelLopes20241160017.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char* data)
{
  int datavalida = 1;

  //quebrar a string data em strings sDia, sMes, sAno


  //printf("%s\n", data);
  
  datavalida = validar_data(data);

  if (datavalida)
      return 1;
  else
      return 0;
}

int tamanho_string (char* string)
{
	int count = 0;
	for (;*string != '\0'; string += sizeof(char))
		count++;
	return count;
}

void proximo_valido (char** string)
{
	if (*(*string) != '0' && *(*string) != '/')
		return;
	else
	{
		*string += sizeof(char);
		proximo_valido(string);
	}
}

int validar_data (char* data)
{
	int dia, mes, ano;
	ext_string_para_int(&dia, &data);
	data += sizeof(char);
	//printf("\nAtual pós dia: %c", *data);
	ext_string_para_int(&mes, &data);
	data += sizeof(char);
	//printf("\nAtual pós mês %c", *data);

	/*
	int qnt = 0;

	data += sizeof(char);
	while (*data == '0')
	{
		qnt++;
		data += sizeof(char);
	}
	*/

	ext_string_para_int(&ano, &data);
	/*
	printf("\nAtual pós ano %c", *data);
	printf("\nANO: %d,\nMES: %d,\nDIA: %d.\n", ano, mes, dia);	
	*/

	/*
	qnt_algarismos_int(&qnt, ano);

	if (qnt < 3)
		ano += 2000;
	*/

	if (validar_data_dia(dia, mes, ano) == 0)
		return 0;
	else if (validar_data_mes(mes) == 0)
		return 0;
	else if (validar_data_ano(ano) == 0)
		return 0;
	else 
		return 1;
}

// Designa a um inteiro de quantidade a quantidade de algarismos de um número inteiro
void qnt_algarismos_int (int* qnt, int num)
{
	num /= 10;
    *qnt = *qnt + 1;

    if (num == 0)
        return;

    qnt_algarismos_int (qnt, num);
}

int validar_data_ano(int ano)
{
	if (ano < 1)
		return 0;

	return 1;
}

int validar_data_mes (int mes)
{
	if (mes > 12 || mes < 1)
		return 0;
	else 
		return 1;
}

int validar_data_dia (int dia, int mes, int ano)
{
	if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
	{
		if (dia > 31)
			return 0;
	}
	else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
	{
		if (dia > 30)
			return 0;
	}
	else if (ano % 4 == 0 && ano % 100 != 0)
	{
		if (dia > 29)
			return 0;
	}
	else
		if (dia > 28)
			return 0;

	return 1;
}

// Transfere o equivalente numérico dos caracteres de uma string para um número (requer que num == 0)
void string_para_int (int* num, char** string)
{
    // caso string esteja no final
    if (*(*string) < 48 || *(*string) > 57)
		return;

	*num *= 10;

	if (*num < 0) // número teve final negativo
		*num -= *(*(string)) - 48;
    else if (*(*string) == '-') // sinal negativo
	{
		*(string) += 1;
        *num -= *(*(string)) - 48;
    }
	else // número é positivo 
		*num += *(*(string)) - 48;

	*(string) += sizeof(char);
	string_para_int(num, string);
}

// Extensor de string_para_int que inicializa o número para o valor esperado
void ext_string_para_int (int* num, char** string)
{
	*num = 0;

	string_para_int(num, string);
}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;

    if (q1(datainicial) == 0)
	{
      dma.retorno = 2;
      return dma;
    }
	else if (q1(datafinal) == 0)
	{
      dma.retorno = 3;
      return dma;
    }
	else
	{
		//verifique se a data final não é menor que a data inicial
		DataQuebrada dt_init; dt_init.valido = 1;
		DataQuebrada dt_fim; dt_fim.valido = 1;

		ext_string_para_int(&dt_init.iDia, &datainicial);
		datainicial += sizeof(char);
		ext_string_para_int(&dt_init.iMes, &datainicial);
		datainicial += sizeof(char);
		ext_string_para_int(&dt_init.iAno, &datainicial);

		ext_string_para_int(&dt_fim.iDia, &datafinal);
		datafinal += sizeof(char);
		ext_string_para_int(&dt_fim.iMes, &datafinal);
		datafinal += sizeof(char);
		ext_string_para_int(&dt_fim.iAno, &datafinal);

		if ((dt_fim.iAno < dt_init.iAno))
			dma.retorno = 4;
		else if (dt_fim.iAno == dt_init.iAno)
		{
			if((dt_fim.iMes < dt_init.iMes))
				dma.retorno = 4;
			else if ((dt_fim.iMes == dt_init.iMes))
				if ((dt_fim.iDia < dt_init.iDia))
					dma.retorno = 4;
		}

		if (dma.retorno == 4)
			return dma;
		
		DiasMesesAnos qtds;
		qtds.qtdDias = 0;
		qtds.qtdMeses = 0;
		qtds.qtdAnos = 0;

		for (int a = dt_init.iAno; a < dt_fim.iAno; a++)
			qtds.qtdAnos++;

		if (dt_fim.iMes < dt_init.iMes)
		{
			qtds.qtdAnos--;
			qtds.qtdMeses += (dt_init.iMes - dt_fim.iMes);
		}
		else 
		{
			qtds.qtdMeses += (dt_fim.iMes - dt_init.iMes);
		}

		if (dt_fim.iDia < dt_init.iDia)
		{
			qtds.qtdMeses--;
			int m = dt_init.iMes;
			if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
				qtds.qtdDias += (31 - dt_init.iDia);
			else if (m != 2)
				qtds.qtdDias += (30 - dt_init.iDia);
			else
			{
				if (dt_fim.iAno % 4 == 0 && dt_fim.iAno % 100 != 0)
					qtds.qtdDias += (29 - dt_init.iDia);
				else 
					qtds.qtdDias += (28 - dt_init.iDia);
			}

			qtds.qtdDias += dt_fim.iDia;
		}
		else 
		{
			qtds.qtdDias += (dt_fim.iDia - dt_init.iDia);
		}

		/*
	else if (ano % 4 == 0 && ano % 100 != 0)
	{
		if (dia > 29)
			return DIA_INVALIDO;
	}
	else
		if (dia > 28)
			*/

		/*
		printf("\n dt_init: %s \n", datainicial);
		printf("\n QNT_DIAS: %d;\n QNT_MESES: %d;\n QNT_ANOS: %d.\n", qtds.qtdDias, qtds.qtdMeses, qtds.qtdAnos);
		*/

		//calcule a distancia entre as datas


		//se tudo der certo
		dma = qtds;
		dma.retorno = 1;
		return dma;

    }
    
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;

	if (isCaseSensitive == 1)
	{
		buscar_c_string(texto, c, &qtdOcorrencias);	
	}
	else
	{
		buscar_c_string(texto, c, &qtdOcorrencias);
		alternar_caixa_c(&c);
		buscar_c_string(texto, c, &qtdOcorrencias);
	}

    return qtdOcorrencias;
}

void alternar_caixa_c (char* c)
{
	if (*c > 96 && *c < 123)
		*c -= 32;
	else if (*c > 64 && *c < 91)
		*c += 32;
}

void caixa_alta_c (char* c)
{
	if (*c > 96 && *c < 123)
		*c -= 32;
}

void caixa_alta_s (char* string)
{
	if (*string == '\0')
		return;
	else if (*string > 96 && *string < 123)
		*string -= 32;

	caixa_alta_s(string + 1);
}

void buscar_c_string (char* string, char c, int* qnt)
{
	if (*string == '\0')
		return;
	else
	{
		if (*string == c)
			*qnt += 1;
		buscar_c_string((string + 1), c, qnt);
	}
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
	/*
	int i, j; int x = -1;
    int qtdOcorrencias = 0;

	for (i = 0; *(strTexto + i) != '\0'; i++)
	{
		if (*(strBusca) == *(strTexto + i))
		{
			for (j = 0; *(strBusca + j) != '\0'; j++)
				if (*(strTexto + i + j) != *(strBusca + j))
					break;

			if (*(strBusca + j) == '\0')
			{
				printf("\nc1: %c", *strBusca);
				printf("\nc2: %c", *strTexto);
				printf("\nJ: %d", j);
				printf("\nI: %d", i);
				*(posicoes + (++x)) = i;
				*(posicoes + (++x)) = i + j;
				qtdOcorrencias++;
				printf(" [ %d ; %d ] \n", *(posicoes + x - 1), *(posicoes + x));
			}
		}
	}

	printf("\nQTD OCORR: %d\n", qtdOcorrencias);
	*/

	int i, j;
	i = 0; j = 0;
	int x = -1;

	int qtdOcorrencias = 0;

	for (i = 0; *(strTexto + i) != '\0'; i++)
	{
		j = 0;
		if (*(strTexto + i) == *(strBusca))
			for (; *(strBusca + j) != '\0'; j++)
			{
				// printf("strBusca: %c  |  strTexto: %c\n", *(strBusca + j), *(strTexto + i + j));
				if (*(strTexto + i + j) != *(strBusca + j))
					break;
			}

		if (*(strBusca + j) == '\0')
		{
			*(posicoes + ++x) = i + 1;
			*(posicoes + ++x) = i + (j);
			// printf("\n [ %d : %d ] \n", *(posicoes + x - 1), *(posicoes + x));
			i += j - 1;
			qtdOcorrencias++;
		}

		printf("\n---\n");
	}

	// printf("\nOcorrências: %d\n", qtdOcorrencias);
    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{

    return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;
    return qtdOcorrencias;
}




DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}

