#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GestaoClinicas.h"

/*
 *		"GestaoClinicas.c" � uma biblioteca composta por todas as fun��es 
 *		e procedimentos, relacionados com as clinicas e a sua gest�o.
 *		Primeiramente consultar "GestaoClinicas.h"
 */
 
 
/*
	Este procedimento apresenta o Menu da Clinica e retorna atrav�s de um ponteiro uma op��o selecionada no menu.
	@op = op��o selecionada no menu
	@nome = nome da clinica selecionada
*/
void MenuClinica(int *op, char *nome)
{
	// Resetar Op��o
	*op = -1;

	// Menu
	system("cls");
	puts("+-------------------------------+");
	printf("|\t   Cl�nica %-13s|\n", nome);
	puts("+-------------------------------+");
	puts("|\t\t\t\t|");
	puts("| 1- Adicionar Funcion�rio\t|");
	puts("|\t\t\t\t|");
	puts("| 2- Editar Funcion�rio\t\t|");
	puts("|\t\t\t\t|");
	puts("| 3- Remover Funcion�rio\t|");
	puts("|\t\t\t\t|");
	puts("| 4- Lista de Funcion�rios\t|");
	puts("|\t\t\t\t|");
	puts("+-------------------------------+");
	puts("|\t\t\t\t|");
	puts("| 5- Marcar Consulta\t\t|");
	puts("|\t\t\t\t|");
	puts("| 6- Remarcar Consulta\t\t|");
	puts("|\t\t\t\t|");
	puts("| 7- Apagar Consulta\t\t|");
	puts("|\t\t\t\t|");
	puts("| 8- Consultar Agendas\t\t|");
	puts("|\t\t\t\t|");
	puts("| 9- Todas as Consultas\t\t|");
	puts("|\t\t\t\t|");
	puts("+-------------------------------+");
	puts("|\t\t\t\t|");
	puts("| 10- Informa��es da Clinica\t|");
	puts("|\t\t\t\t|");
	puts("| 0- Voltar\t\t\t|");
	puts("|\t\t\t\t|");
	puts("+-------------------------------+");
	
	// Selecionar uma op��o
	printf("Selecione uma op��o: ");
	scanf("%d", op);
}


/*
	Este procedimento � responsavel por listar todas as clinicas. E possui 2 par�metros de entrada.
	@clinicas = lista de clinicas
	@n = quantidade total de clinicas
*/
void ListarClinicas(Clinica *clinicas, int n)
{
	// Variaveis
	int i;
	
	// Mostrar os dados da clinica
	system("cls");
	puts("+----------------------------------------+");
	puts("|            Lista de Cl�nicas           |");
	puts("+----------------------------------------+");
	puts("|  ID  |       Nome       |  Quantidade  |");
	puts("|      |                  | Funcion�rios |");
	puts("+----------------------------------------+");
	for (i = 0; i < n; i++)
	{
		if (clinicas[i].ativo == 1)
			printf("| %*d  | %-16s | %*d |\n", -3, i, clinicas[i].nome, -12, clinicas[i].totalFuncionarios);
	}
	puts("+----------------------------------------+");
}


/*
	Este procedimento � responsavel pela cria��o de uma clinica. E possui 2 par�metros de entrada.
	@clinicas = lista de clinicas
	@n = quantidade total de clinicas
*/
void AddClinica(Clinica *clinicas, int *n)
{
	// Variaveis
	char nome[50];
	
	// Inserir os dados da clinica
	system("cls");
	puts("+-------------------------------+");
	printf("|\tCriar Cl�nica\t\t|\n");
	puts("+-------------------------------+");
	printf("Insira o nome da clinica: ");
	scanf("%s", nome);
	fflush(stdin);
	
	// Confirmar ou cancelar a respetiva opera��o.
	if (Confirmar() == 2)
		return;
	
	// Atribui��o de dados
	strcpy(clinicas[*n].nome, nome);
	clinicas[*n].totalFuncionarios = 0;
	clinicas[*n].totalConsultas = 0;
	clinicas[*n].ativo = 1;
	clinicas[*n].id = *n;
	*n += 1;
}


/*
	Este procedimento � responsavel pela remo��o de uma clinica. E possui 2 par�metros de entrada.
	@clinicas = lista de clinicas
	@n = quantidade total de clinicas
*/
void RemoverClinica(Clinica *clinicas, int n)
{
	// Variaveis
	int id;
		
	// Mostrar Tabela com todas as Clinicas
	ListarClinicas(clinicas, n);
	
	puts("+-------------------------------+");
	printf("|\tRemover Cl�nica\t\t|\n");
	puts("+-------------------------------+");
	
	// Selecionar ID da clinica
	id = SelecionarPorID(n);
	
	// Confirmar ou cancelar a respetiva opera��o.
	if (id < 0 || clinicas[id].ativo == 0 || Confirmar() == 2)
		return;
	
	// Desativar / Remover Clinica 
	clinicas[id].ativo = 0;
}


/*
	Procedimento para mostrar as informa��es da clinica selecionada. E possui 1 par�metros de entrada.
	@clinica = clinica selecionada pelo utilizador
*/
void ClinicaInfo(Clinica clinica)
{
	// Variaveis
	Funcionario *f = clinica.funcionarios;
	int n = clinica.totalFuncionarios;
	int i, j;
	float vencimentos[3][2], totalVencimentos = 0;
	
	// Atribuir Vencimentos
	vencimentos[0][0] = SomaVencimentosPorGeneroEmprego(f, n, "M�dico", "Feminino");
	vencimentos[0][1] = SomaVencimentosPorGeneroEmprego(f, n, "M�dico", "Masculino");
	vencimentos[1][0] = SomaVencimentosPorGeneroEmprego(f, n, "Enfermeiro", "Feminino");
	vencimentos[1][1] = SomaVencimentosPorGeneroEmprego(f, n, "Enfermeiro", "Masculino");
	vencimentos[2][0] = SomaVencimentosPorGeneroEmprego(f, n, "Auxiliar", "Feminino");
	vencimentos[2][1] = SomaVencimentosPorGeneroEmprego(f, n, "Auxiliar", "Masculino");
	
	// Calcular total dos vencimentos
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 2; j++)
			totalVencimentos += vencimentos[i][j];
	}
	
	// Informa��o da Clinica
    system("cls");
    puts("+-----------------------------------------+");
    printf("|\t  [Info] Cl�nica %-10s \t  |\n", clinica.nome);
    puts("+-----------------------------------------+");
    puts("|                                         |");
    puts("| Quantidade:                             |");
    printf("|    > M�dicos:     %-18d    |\n", QuantidadeFuncionariosPorEmprego(f, n, "M�dico"));
    printf("|    > Enfermeiros: %-18d    |\n", QuantidadeFuncionariosPorEmprego(f, n, "Enfermeiro"));
    printf("|    > Auxiliares:  %-18d    |\n", QuantidadeFuncionariosPorEmprego(f, n, "Auxiliar"));
    puts("|                                         |");
    puts("| M�dia de idades:                        |");
    printf("|    > M�dicos:     %-18.2f    |\n", MediaIdadesFuncionariosPorEmprego(f, n, "M�dico"));
    printf("|    > Enfermeiros: %-18.2f    |\n", MediaIdadesFuncionariosPorEmprego(f, n, "Enfermeiro"));
    printf("|    > Auxiliares:  %-18.2f    |\n", MediaIdadesFuncionariosPorEmprego(f, n, "Auxiliar"));
    puts("|                                         |");
    puts("| Soma de vencimentos:                    |");
    puts("|    > [M�dicos]:                         |");
    printf("|       > Feminino:  %-16.2f     |\n", vencimentos[0][0]);
    printf("|       > Masculino: %-16.2f     |\n", vencimentos[0][1]);
    printf("|       = Total:     %-16.2f     |\n", vencimentos[0][0] + vencimentos[0][1]);
    puts("|    > [Enfermeiros]:                     |");
    printf("|       > Feminino:  %-16.2f     |\n", vencimentos[1][0]);
    printf("|      	> Masculino: %-16.2f     |\n", vencimentos[1][1]);
    printf("|       = Total:     %-16.2f     |\n", vencimentos[1][0] + vencimentos[1][1]);
    puts("|    > [Auxiliares]:                      |");
    printf("|       > Feminino:  %-16.2f     |\n", vencimentos[2][0]);
    printf("|       > Masculino: %-16.2f     |\n", vencimentos[2][1]);
    printf("|       = Total:     %-16.2f     |\n", vencimentos[2][0] + vencimentos[2][1]);
    puts("|                                         |");
    printf("|    > [Total]: %-16.2f          |\n", totalVencimentos);
    puts("|                                         |");
    puts("| Quantidade total de Compromissos:       |");
    puts("|    > [Enfermeiros]:                     |");
	
 	// Ciclo de todos os Funcion�rios
 	for (i = 0; i < n; i++)
 	{
 		// Verificar se � enfermeiro
 		if(strcmp(f[i].emprego, "Enfermeiro") == 0 && f[i].ativo == 1)
    		printf("| %13s: %-25d|\n", f[i].nome, TotalConsultasPorFuncionario(f[i], clinica.consultas, clinica.totalConsultas));
	}


    puts("|                                         |");
    puts("+-----------------------------------------+");
    
    // Pausa
    getch();
}


/*
	Este procedimento � responsavel por listar todas os m�dicos de todas as clinicas. E possui 2 par�metros de entrada.
	@clinicas = lista de clinicas
	@n = quantidade total de clinicas
*/
void ListarTodosMedicos(Clinica *clinicas, int n)
{
	// Variaveis
	int i, j;
	float soma = 0;
	
	// Mostrar lista de m�dicos
	system("cls");
    puts("+-----------------------------------------+");
    puts("|             Lista de M�dicos            |");
    puts("+-----------------------------------------+");
    puts("|                                         |");
 	puts("| Lista de Vencimentos:                   |");
 	puts("|                                         |");
 	
 	// Ciclo das Clinicas
 	for (i = 0; i < n; i++)
 	{
    	printf("|    > Clinica %-27s|\n", clinicas[i].nome);
    	
    	// Ciclo dos Funcionarios de cada Clinica
    	for (j = 0; j < clinicas[i].totalFuncionarios; j++)
 		{
 			if (strcmp(clinicas[i].funcionarios[j].emprego, "M�dico") == 0 && clinicas[i].funcionarios[j].ativo == 1)
 			{
 				printf("|%16s: %-23.2f|\n", clinicas[i].funcionarios[j].nome, clinicas[i].funcionarios[j].vencimento);
 				soma += clinicas[i].funcionarios[j].vencimento;
			}
		}
 		
 		puts("|                                         |");
	}
	
	printf("| [Total]: %-31.2f|\n", soma);
	puts("|                                         |");
    puts("+-----------------------------------------+");
    
    // Pausa
    getch();
}






