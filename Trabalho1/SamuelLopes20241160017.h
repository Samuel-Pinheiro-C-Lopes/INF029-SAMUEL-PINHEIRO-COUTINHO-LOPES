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
// Última atualização: 07/05/2021

// #################################################
#ifndef TRABALHO1_PRIMEIROULTIMONOMEMATRICULA_H
#define TRABALHO1_PRIMEIROULTIMONOMEMATRICULA_H

typedef struct DQ
{
    int iDia; 
    int iMes;
    int iAno;
    int valido; // 0 se inválido, e 1 se válido 

} DataQuebrada;

typedef struct Qtd
{
    int qtdDias;
    int qtdMeses;
    int qtdAnos;
    int retorno;

} DiasMesesAnos;

int somar(int x, int y); //função utilizada para testes
int fatorial(int x); //função utilizada para testes
int q1(char data[]);
DiasMesesAnos q2(char datainicial[], char datafinal[]);
int q3(char *texto, char c, int isCaseSensitive);
int q4(char *strTexto, char *strBusca, int posicoes[30]);
int q5(int num);
int q6(int numerobase, int numerobusca);
DataQuebrada quebraData(char data[]);

// funções SAMUEL
void qnt_algarismos_int (int* qnt, int num);
int validar_data_ano(int ano);
int validar_data_mes (int mes);
int validar_data_dia (int dia, int mes, int ano);
void string_para_int (int* num, char** string);
void ext_string_para_int (int* num, char** string);
int tamanho_string (char* string);
int validar_data (char* data);
void proximo_valido (char** string);
char* int_para_string (int num);


void caixa_alta_c (char* c);
void caixa_alta_s (char* string);
void buscar_c_string (char* string, char c, int* qnt);
void alternar_caixa_c(char* c);
#endif  // TRABALHO1_PRIMEIROULTIMONOMEMATRICULA_H
