#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GestaoConsultas.h"

/*
 *		"GestaoConsultas.c" é uma biblioteca composta por todas as funções 
 *		e procedimentos, relacionados com as consultas e a sua gestão.
 *		Primeiramente consultar "GestaoConsultas.h"
 */
 

/*
	Este procedimento é responsavel por listar todas as consultas. E possui 2 parâmetros de entrada.
	@consultas = lista de consultas
	@n = quantidade total de consultas
*/
void ListarConsultas(Consulta *consultas, int n)
{
	// Variaveis
	int i;
	
	// Mostrar lista de consultas
	system("cls");
	puts("+------------------------------------------------------------+");
	puts("|                     Lista de Consultas                     |");
	puts("+------------------------------------------------------------+");
	puts("|  ID  |    Data    | Funcionario | Nome Utente | SNS Utente |");
	puts("+------------------------------------------------------------+");
	for (i = 0; i < n; i++)
	{
		if (consultas[i].ativo == 1)
			printf("| %*d | %-10s | %-11s | %-11s | %-10s |\n"
			, -4, i, consultas[i].data, consultas[i].funcionario.nome, consultas[i].utente.nome, consultas[i].utente.numeroSns);
	}
	puts("+------------------------------------------------------------+");
	
}


/*
	Este procedimento é responsavel por listar todas as consultas de um determinado funcionario. E possui 4 parâmetros de entrada.
	@consultas = lista de consultas
	@nC = quantidade total de consultas
	@funcionarios = lista de funcionarios
	@nF = quantidade total de funcionarios
*/
void Agenda(Consulta *consultas, int nC, Funcionario *funcionarios, int nF)
{
	// Variaveis
	int i, id;
	
	// Mostrar Lista de Funcionarios
	ListarFuncionarios(funcionarios, nF);
	
	puts("+-------------------------------+");
	printf("|\tSelecionar Agenda\t|\n");
	puts("+-------------------------------+");
	
	// Selecionar o funcionario
	id = SelecionarPorID(nF);
	
	// Condição de Saida e Deteção de erros
	if (id < 0 || funcionarios[id].ativo == 0 || VerificarFuncionario(funcionarios[id]) == 0)
		return;

	// Mostrar a agenda do respetivo funcionario
	system("cls");
	puts("+----------------------------------------------+");
	printf("|              Agenda de %-22s|\n", funcionarios[id].nome);
	puts("+----------------------------------------------+");
	puts("|  ID  |    Data    | Nome Utente | SNS Utente |");
	puts("+----------------------------------------------+");
	for (i = 0; i < nC; i++)
	{
		// Filtrar apenas o funcionario pretendido
		if (consultas[i].funcionario.id == id)
			printf("| %*d | %-10s | %-11s | %-10s |\n", -4, i, consultas[i].data, consultas[i].utente.nome, consultas[i].utente.numeroSns);
	}
	puts("+----------------------------------------------+");
	
	// Pausa
	getch();
}


/*
	Este procedimento é responsavel pela marcação de uma consulta. E possui 4 parâmetros de entrada.
	@consultas = lista de consultas
	@nC = quantidade total de consultas
	@funcionarios = lista de funcionarios
	@nF = quantidade total de funcionarios
*/
void AddConsulta(Consulta *consultas, int *nC, Funcionario *funcionarios, int nF)
{
	// Variaveis
	int i, id;
	
	// Mostrar Lista de Funcionarios
	ListarFuncionarios(funcionarios, nF);
	
	puts("+-------------------------------+");
	printf("|\tMarcar Consulta\t\t|\n");
	puts("+-------------------------------+");
	
	// Inserir Funcionario
	id = SelecionarPorID(nF);
	
	// Condição de Saida e Deteção de erros
	if (id < 0 || VerificarFuncionario(funcionarios[id]) == 0)
		return;
		
	// Inserir Utente
	printf("Insira o utente: ");
	printf("\n   > Nome: ");
	scanf("%s", consultas[*nC].utente.nome);
	fflush(stdin);
	printf("\n   > Número SNS: ");
	scanf("%s", consultas[*nC].utente.numeroSns);
	fflush(stdin);
	
	// Inserir Data
	GetDate(consultas[*nC].data);
	
	// Atribuir Dados
	consultas[*nC].funcionario = funcionarios[id];
	consultas[*nC].ativo = 1;
	consultas[*nC].id = *nC;
	*nC += 1;
}


/*
	Este procedimento é responsavel por remover / inativar uma consulta. E possui 2 parâmetros de entrada.
	@consultas = lista de consultas
	@n = quantidade total de consultas
*/
void RemoverConsulta(Consulta *consultas, int n)
{
	// Variaveis
	int i, id, dia, mes, ano;

	// Consltar lista de consultas
	ListarConsultas(consultas, n);

	puts("+-------------------------------------------------------------+");
	puts("+-------------------------------+");
	printf("|\tApagar Consulta\t\t|\n");
	puts("+-------------------------------+");

	// Selecionar a consulta
	id = SelecionarPorID(n);
	
	// Condição de Saida
	if (id < 0 || consultas[id].ativo == 0 || Confirmar() == 2)
		return;
		
	// Remover Consulta
	consultas[id].ativo = 0;
}


/*
	Este procedimento é responsavel pela remarcação de uma consulta. E possui 2 parâmetros de entrada.
	@consultas = lista de consultas
	@n = quantidade total de consultas
*/
void RemarcarConsulta(Consulta *consultas, int n)
{
	// Variaveis
	int i, id, dia, mes, ano;
	
	// Consltar lista de consultas
	ListarConsultas(consultas, n);

	puts("+-------------------------------------------------------------+");
	puts("+-------------------------------+");
	printf("|\tRemarcar Consulta\t|\n");
	puts("+-------------------------------+");

	// Selecionar a consulta
	id = SelecionarPorID(n);
	
	// Condição de Saida
	if (id < 0 || consultas[id].ativo == 0)
		return;
		
	// Remarcar a Data
	GetDate(consultas[id].data);
}


/*
	Este procedimento é responsavel por inativar todas as consultas de um Funcionario. E possui 3 parâmetros de entrada.
	@consultas = lista de consultas
	@n = quantidade total de consultas
	@id = id do funcionario selecionado
*/
void InativarTodasConsultasPorFuncionario(Consulta *consultas, int n, int id)
{
	// Variaveis
	int i;
	
	// Inativar todas as consultas do funcionario selecionado
	for (i = 0; i < n; i++)
	{
		if (consultas[i].funcionario.id == id)
			consultas[i].ativo = 0;
	}
}


/*
	Este procedimento é responsavel por verificar se o funcionario selecionado pode gerir consultas. E possui 2 parâmetros de entrada.
	@funcionarios = lista de funcionarios
	@id = id selecionado
*/
int VerificarFuncionario(Funcionario funcionario)
{		
	// Deteção de Erros
	if (funcionario.ativo == 0 || strcmp(funcionario.emprego, "Auxiliar") == 0)
	{
		printf("Erro. Insira um ID correto.\n");
		getch();
		return 0;
	}
	
	return 1;
}


/*
	Esta função é responsavel por retornar o total de compromissos/consultas de um funcionário. E possui 3 parâmetros de entrada.
	@funcionario = funcionario pretendido
	@consultas = lista de consultas
	@n = quantidade total de consultas
*/
int TotalConsultasPorFuncionario(Funcionario funcionario, Consulta *consultas, int n)
{
	// Variaveis
	int contador = 0, i;
	
	// Verificações Iniciais
	if (n == 0)
		return 0;
	
	// Ciclo de consultas
	for (i = 0; i < n; i++)
	{
		// Verificar se são o mesmo funcionário
		if (funcionario.ativo == 1 && consultas[i].funcionario.id == funcionario.id)
			contador++;
	}
	
	return contador;
}








