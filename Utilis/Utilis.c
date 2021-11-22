#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *		"Utilis" � uma biblioteca composta por varias fun��es 
 *		e procedimentos, usados v�rias vezes no decorrer do programa.
 */


/*
	Esta fun�ao � responsavel por retornar um valor (1 ou 2). Representando Confirmar ou Cancelar uma opera��o.
*/
int Confirmar()
{
	// Variaveis
	int valor = -1;
	
	// Mostrar condi��o de sa�da do ciclo
	puts("");
	puts("Opera��o Concluida! Deseja Confirmar?");
	puts("[1] > Confirmar | [2] > Cancelar");
	printf(" > ");
	
	// Garantir a escolha de uma op��o valida
	while (valor != 1 && valor != 2)
		scanf("%d", &valor);
	
	return valor;
}


/*
	Esta fun��o � responsavel por retornar um indice de uma determinada lista, ou um n�mero negativo se pertender Cancelar.
	@n = quantidade total da lista
*/
int SelecionarPorID(int n)
{
	// Variaveis
	int id;

	// Inserir ID, e garantir que � v�lido
	printf("Para Voltar insira um ID negativo.\n");
	printf("Insira um ID: ");
	do 
		scanf("%d", &id);
	while (id >= n);
	
	return id;
}


/*
	Este procedimento � responsavel por retornar uma data por apontador. Tendo que inserir o Dia, M�s e Ano.
*/
void GetDate(char *data)
{
	// Variaveis
	int dia, mes, ano;
	
    // Inserir Data
	printf("Insira a data:");
	printf("\n   > Dia: ");
	scanf("%d", &dia);
	printf("\n   > M�s: ");
	scanf("%d", &mes);
	printf("\n   > Ano: ");
	scanf("%d", &ano);

	// Atribuir data
	sprintf(data, "%02d/%02d/%04d", dia, mes, ano); 	
}




