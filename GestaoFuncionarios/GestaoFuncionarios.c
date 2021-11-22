#include <stdio.h>
#include <stdlib.h>
#include "GestaoFuncionarios.h"

/*
 *		"GestaoFuncionarios.c" é uma biblioteca composta por todas as funções 
 *		e procedimentos, relacionados com os funcionarios e a sua gestão.
 *		Primeiramente consultar "GestaoFuncionarios.h"
 */
 
 
/*
	Este procedimento é responsavel pela criação de um Funcionario. E possui 2 parâmetros de entrada.
	@funcionarios = lista de funcionarios
	@n = quantidade total de funcionarios
*/
void AddFuncionario(Funcionario *funcionarios, int *n)
{
	// Variaveis
	int emprego, genero;
	
	// Inserir os dados do funcionário
	system("cls");
	puts("+-------------------------------+");
	printf("|\tAdicionar Funcionário\t|\n");
	puts("+-------------------------------+");
	
	// Inserir Nome
	printf("Insira o nome: ");
	scanf("%s", &funcionarios[*n].nome);
	fflush(stdin);
	
	// Inserir Genero
	puts("[1] > Feminino | [2] > Masculino");
	printf("Insira o genero: ");
	do {	
		scanf("%d", &genero);
	} while (genero != 1 && genero != 2);
	
	// Inserir Idade
	printf("Insira a Idade: ");
	scanf("%d", &funcionarios[*n].idade);
	
	// Inserir Vencimento
	printf("Insira o Vencimento: ");
	do {
		scanf("%f", &funcionarios[*n].vencimento);
	} while (funcionarios[*n].vencimento < 0);
	
	// Inserir Emprego
	puts("[1] > Médico | [2] > Enfermeiro | [3] > Auxiliar ");
	printf("Insira o Emprego: ");
	do {
		scanf("%d", &emprego);
	} while (emprego != 1 && emprego != 2 && emprego != 3);
	
	// Atribuir um Genero dependendo do número
	strcpy(funcionarios[*n].genero, (genero == 1) ? "Feminino" : "Masculino");
	
	// Atribuir um Emprego dependendo do número
	switch(emprego)
	{
		case 1: strcpy(funcionarios[*n].emprego, "Médico");
		break;
		case 2: strcpy(funcionarios[*n].emprego, "Enfermeiro");
		break;
		case 3: strcpy(funcionarios[*n].emprego, "Auxiliar");
		break;
	}
	
	// Atribuir outros dados
	funcionarios[*n].ativo = 1;
	funcionarios[*n].id = *n;
	*n += 1;
}


/*
	Este procedimento é responsavel por listar todos os Funcionarios ativos. E possui 2 parâmetros de entrada.
	@funcionarios = lista de funcionarios
	@n = quantidade total de funcionarios
*/
void ListarFuncionarios(Funcionario *funcionarios, int n)
{
	// Variaveis
	int i;
	
	// Mostrar os dados do funcionário
	system("cls");
	puts("+--------------------------------------------------------------------+");
	puts("|                        Lista de Funcionários                       |");
	puts("+--------------------------------------------------------------------+");
	puts("|  ID  |     Nome     |   Genero   | Idade | Vencimento |  Emprego   |");
	puts("+--------------------------------------------------------------------+");
	for(i = 0; i < n; i++)
	{
		if (funcionarios[i].ativo == 1)
			printf("| %*d  | %-12s | %-10s | %*d | %-10.2f | %-10s |\n"
			, -3, i, funcionarios[i].nome, funcionarios[i].genero, -5, funcionarios[i].idade, 
			funcionarios[i].vencimento, funcionarios[i].emprego);
	}
	puts("+--------------------------------------------------------------------+");
}


/*
	Este procedimento é responsavel pela edição de um Funcionario. Só é possivel alterar a idade e o vencimento. 
	E possui 2 parâmetros de entrada.
	@funcionarios = lista de funcionarios
	@n = quantidade total de funcionarios
*/
void EditarFuncionario(Funcionario *funcionarios, int n)
{	
	// Variaveis
	int id;
		
	// Mostrar Lista de Funcionarios
	ListarFuncionarios(funcionarios, n);
	
	puts("+-------------------------------+");
	printf("|\tEditar Funcionário\t|\n");
	puts("+-------------------------------+");
	
	// Selecionar o funcionario
	id = SelecionarPorID(n);
	
	// Condição de Saida
	if (id < 0 || funcionarios[id].ativo == 0)
		return;
	
	// Inserir Idade
	printf("Insira a Idade: ");
	scanf("%d", &funcionarios[id].idade);
	
	// Inserir Vencimento
	printf("Insira o Vencimento: ");
	do {
		scanf("%f", &funcionarios[id].vencimento);
	} while (funcionarios[id].vencimento < 0);

}


/*
	Este procedimento é responsavel por remover / inativar um Funcionario. E possui 2 parâmetros de entrada.
	@funcionarios = lista de funcionarios
	@n = quantidade total de funcionarios
*/
int RemoverFuncionario(Funcionario *funcionarios, int n)
{
	// Variaveis
	int id;
		
	// Mostrar Lista de Funcionarios
	ListarFuncionarios(funcionarios, n);
	
	puts("+-------------------------------+");
	printf("|\tRemover Funcionário\t|\n");
	puts("+-------------------------------+");
	
	// Selecionar o funcionario
	id = SelecionarPorID(n);
	
	// Condição de Saida
	if (id < 0 || funcionarios[id].ativo == 0 || Confirmar() == 2)
		return -1;
		
	// Inativar o funcionario / remover
	funcionarios[id].ativo = 0;
	
	return id;
}


/*
	Função para retornar a quantidade de funcionarios com um determinado emprego dentro de uma clinica. E possui 3 parâmetros de entrada.
	@funcionarios = lista de funcionarios
	@n = quantidade total de funcionarios
	@emprego = emprego o qual prentende a retornar a quantidade de funcionarios
*/
int QuantidadeFuncionariosPorEmprego(Funcionario *funcionarios, int n, char *emprego)
{
	// Variaveis
	int total = 0, i;
	
	// Verificações Iniciais
	if (n == 0)
		return 0;
	
	// Percorrer a lista de funcionarios e somar a quantidade de funcionarios com o emprego pretendido
	for (i = 0; i < n; i++)
	{
		if (strcmp(funcionarios[i].emprego, emprego) == 0 && funcionarios[i].ativo == 1)
			total++;
	}
	
	return total;
}


/*
	Função para retornar a média de idades dos funcionarios de um determinado emprego dentro de uma clinica. E possui 3 parâmetros de entrada.
	@funcionarios = lista de funcionarios
	@n = quantidade total de funcionarios
	@emprego = emprego o qual prentende a retornar a media de idades dos funcionarios
*/
float MediaIdadesFuncionariosPorEmprego(Funcionario *funcionarios, int n, char *emprego)
{
	// Variaveis
	int soma = 0, contador = 0, i;
	
	// Verificações Iniciais
	if (n == 0)
		return 0;
	
	// Percorrer a lista de funcionarios e somar a quantidade de funcionarios com o emprego pretendido
	for (i = 0; i < n; i++)
	{
		if (strcmp(funcionarios[i].emprego, emprego) == 0  && funcionarios[i].ativo == 1)
		{
			soma += funcionarios[i].idade;
			contador++;
		}
	}
	
	return (contador == 0) ? 0 : soma / (float)contador;
}


/*
	Função para retornar a soma de vencimentos dos funcionarios de um determinado emprego e genero dentro de uma clinica. E possui 4 parâmetros de entrada.
	@funcionarios = lista de funcionarios
	@n = quantidade total de funcionarios
	@emprego = emprego pretendido
	@genero = genero pretendido
*/
float SomaVencimentosPorGeneroEmprego(Funcionario *funcionarios, int n, char *emprego, char *genero)
{
	// Variaveis
	int i;
	float soma = 0;
	
	// Verificações Iniciais
	if (n == 0)
		return 0;
	
	// Percorrer a lista de funcionarios e somar a quantidade de funcionarios com o emprego e genero pretendido 
	for (i = 0; i < n; i++)
	{
		if (strcmp(funcionarios[i].genero, genero) == 0 && strcmp(funcionarios[i].emprego, emprego) == 0 && funcionarios[i].ativo == 1)
			soma += funcionarios[i].vencimento;
	}
	
	return soma;
}






