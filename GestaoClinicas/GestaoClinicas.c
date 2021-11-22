#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GestaoClinicas.h"

/*
 *		"GestaoClinicas.c" é uma biblioteca composta por todas as funções 
 *		e procedimentos, relacionados com as clinicas e a sua gestão.
 *		Primeiramente consultar "GestaoClinicas.h"
 */
 
 
/*
	Este procedimento apresenta o Menu da Clinica e retorna através de um ponteiro uma opção selecionada no menu.
	@op = opção selecionada no menu
	@nome = nome da clinica selecionada
*/
void MenuClinica(int *op, char *nome)
{
	// Resetar Opção
	*op = -1;

	// Menu
	system("cls");
	puts("+-------------------------------+");
	printf("|\t   Clínica %-13s|\n", nome);
	puts("+-------------------------------+");
	puts("|\t\t\t\t|");
	puts("| 1- Adicionar Funcionário\t|");
	puts("|\t\t\t\t|");
	puts("| 2- Editar Funcionário\t\t|");
	puts("|\t\t\t\t|");
	puts("| 3- Remover Funcionário\t|");
	puts("|\t\t\t\t|");
	puts("| 4- Lista de Funcionários\t|");
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
	puts("| 10- Informações da Clinica\t|");
	puts("|\t\t\t\t|");
	puts("| 0- Voltar\t\t\t|");
	puts("|\t\t\t\t|");
	puts("+-------------------------------+");
	
	// Selecionar uma opção
	printf("Selecione uma opção: ");
	scanf("%d", op);
}


/*
	Este procedimento é responsavel por listar todas as clinicas. E possui 2 parâmetros de entrada.
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
	puts("|            Lista de Clínicas           |");
	puts("+----------------------------------------+");
	puts("|  ID  |       Nome       |  Quantidade  |");
	puts("|      |                  | Funcionários |");
	puts("+----------------------------------------+");
	for (i = 0; i < n; i++)
	{
		if (clinicas[i].ativo == 1)
			printf("| %*d  | %-16s | %*d |\n", -3, i, clinicas[i].nome, -12, clinicas[i].totalFuncionarios);
	}
	puts("+----------------------------------------+");
}


/*
	Este procedimento é responsavel pela criação de uma clinica. E possui 2 parâmetros de entrada.
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
	printf("|\tCriar Clínica\t\t|\n");
	puts("+-------------------------------+");
	printf("Insira o nome da clinica: ");
	scanf("%s", nome);
	fflush(stdin);
	
	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == 2)
		return;
	
	// Atribuição de dados
	strcpy(clinicas[*n].nome, nome);
	clinicas[*n].totalFuncionarios = 0;
	clinicas[*n].totalConsultas = 0;
	clinicas[*n].ativo = 1;
	clinicas[*n].id = *n;
	*n += 1;
}


/*
	Este procedimento é responsavel pela remoção de uma clinica. E possui 2 parâmetros de entrada.
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
	printf("|\tRemover Clínica\t\t|\n");
	puts("+-------------------------------+");
	
	// Selecionar ID da clinica
	id = SelecionarPorID(n);
	
	// Confirmar ou cancelar a respetiva operação.
	if (id < 0 || clinicas[id].ativo == 0 || Confirmar() == 2)
		return;
	
	// Desativar / Remover Clinica 
	clinicas[id].ativo = 0;
}


/*
	Procedimento para mostrar as informações da clinica selecionada. E possui 1 parâmetros de entrada.
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
	vencimentos[0][0] = SomaVencimentosPorGeneroEmprego(f, n, "Médico", "Feminino");
	vencimentos[0][1] = SomaVencimentosPorGeneroEmprego(f, n, "Médico", "Masculino");
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
	
	// Informação da Clinica
    system("cls");
    puts("+-----------------------------------------+");
    printf("|\t  [Info] Clínica %-10s \t  |\n", clinica.nome);
    puts("+-----------------------------------------+");
    puts("|                                         |");
    puts("| Quantidade:                             |");
    printf("|    > Médicos:     %-18d    |\n", QuantidadeFuncionariosPorEmprego(f, n, "Médico"));
    printf("|    > Enfermeiros: %-18d    |\n", QuantidadeFuncionariosPorEmprego(f, n, "Enfermeiro"));
    printf("|    > Auxiliares:  %-18d    |\n", QuantidadeFuncionariosPorEmprego(f, n, "Auxiliar"));
    puts("|                                         |");
    puts("| Média de idades:                        |");
    printf("|    > Médicos:     %-18.2f    |\n", MediaIdadesFuncionariosPorEmprego(f, n, "Médico"));
    printf("|    > Enfermeiros: %-18.2f    |\n", MediaIdadesFuncionariosPorEmprego(f, n, "Enfermeiro"));
    printf("|    > Auxiliares:  %-18.2f    |\n", MediaIdadesFuncionariosPorEmprego(f, n, "Auxiliar"));
    puts("|                                         |");
    puts("| Soma de vencimentos:                    |");
    puts("|    > [Médicos]:                         |");
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
	
 	// Ciclo de todos os Funcionários
 	for (i = 0; i < n; i++)
 	{
 		// Verificar se é enfermeiro
 		if(strcmp(f[i].emprego, "Enfermeiro") == 0 && f[i].ativo == 1)
    		printf("| %13s: %-25d|\n", f[i].nome, TotalConsultasPorFuncionario(f[i], clinica.consultas, clinica.totalConsultas));
	}


    puts("|                                         |");
    puts("+-----------------------------------------+");
    
    // Pausa
    getch();
}


/*
	Este procedimento é responsavel por listar todas os médicos de todas as clinicas. E possui 2 parâmetros de entrada.
	@clinicas = lista de clinicas
	@n = quantidade total de clinicas
*/
void ListarTodosMedicos(Clinica *clinicas, int n)
{
	// Variaveis
	int i, j;
	float soma = 0;
	
	// Mostrar lista de médicos
	system("cls");
    puts("+-----------------------------------------+");
    puts("|             Lista de Médicos            |");
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
 			if (strcmp(clinicas[i].funcionarios[j].emprego, "Médico") == 0 && clinicas[i].funcionarios[j].ativo == 1)
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






