#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *		"Utilis" é uma biblioteca composta por varias funções 
 *		e procedimentos, usados várias vezes no decorrer do programa.
 */


/*
	Esta funçao é responsavel por retornar um valor (1 ou 2). Representando Confirmar ou Cancelar uma operação.
*/
int Confirmar()
{
	// Variaveis
	int valor = -1;
	
	// Mostrar condição de saída do ciclo
	puts("");
	puts("Operação Concluida! Deseja Confirmar?");
	puts("[1] > Confirmar | [2] > Cancelar");
	printf(" > ");
	
	// Garantir a escolha de uma opção valida
	while (valor != 1 && valor != 2)
		scanf("%d", &valor);
	
	return valor;
}


/*
	Esta função é responsavel por retornar um indice de uma determinada lista, ou um número negativo se pertender Cancelar.
	@n = quantidade total da lista
*/
int SelecionarPorID(int n)
{
	// Variaveis
	int id;

	// Inserir ID, e garantir que é válido
	printf("Para Voltar insira um ID negativo.\n");
	printf("Insira um ID: ");
	do 
		scanf("%d", &id);
	while (id >= n);
	
	return id;
}


/*
	Este procedimento é responsavel por retornar uma data por apontador. Tendo que inserir o Dia, Mês e Ano.
*/
void GetDate(char *data)
{
	// Variaveis
	int dia, mes, ano;
	
    // Inserir Data
	printf("Insira a data:");
	printf("\n   > Dia: ");
	scanf("%d", &dia);
	printf("\n   > Mês: ");
	scanf("%d", &mes);
	printf("\n   > Ano: ");
	scanf("%d", &ano);

	// Atribuir data
	sprintf(data, "%02d/%02d/%04d", dia, mes, ano); 	
}




