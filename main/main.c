#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "../Utilis/Utilis.c"
#include "../GestaoFuncionarios/GestaoFuncionarios.c"
#include "../GestaoConsultas/GestaoConsultas.c"
#include "../GestaoClinicas/GestaoClinicas.c"


// Função: Gerir o pessoal de unidades clinicas.
// Autor: André Cerqueira
// Data de inicio: 04/01/2021
// Data de ultima atualização: 12/01/2021

/*
 *		Este é o script principal do programa. O programa está dividido em outras 3 bibliotecas: 
 *		"GestaoFuncionarios.c", "GestaoConsultas.c", "GestaoClinicas.c". As mesmas possuem procedimentos
 *		e funções usadas ao longo do programa. Também é usado outra biblioteca "Utilis.c", com procedimentos 
 *		e funções essenciais, usadas várias vezes por todas as bibliotecas.
*/


// Assinaturas
void MenuInicial(int *op);
void CarregarDadosHardCode(Clinica *clinicas, int *n);
	
	
int main(int argc, char *argv[]) 
{
	// Variaveis
	Clinica clinicas[20];
	int op = -1, idAtivo = -1, idInativo = -1, totalClinicas = 0;
	
	// Configurações Iniciais
   	setlocale(LC_ALL, "Portuguese");
   	CarregarDadosHardCode(clinicas, &totalClinicas);
   	
	// O utilizador só sai quando escolher a opção 0- Sair
	while (op != 0)
	{
		// Escolher a opção do menu inicial
		MenuInicial(&op);
	
		// Executar a opção selecionada
		switch (op)
		{
			// Criar Clínica
			case 1:
				AddClinica(clinicas, &totalClinicas);
			break;
			
			// Selecionar Clínica
			case 2:
				
				// Verificação de Erros
				if (totalClinicas == 0)
				{
					puts("> ERRO: Ainda não existe nenhuma Clinica.");
					getch();
				}
				else
				{	
					// Mostrar Tabela com todas as Clinicas
					ListarClinicas(clinicas, totalClinicas);

					// Selecionar ID da clinica
					idAtivo = SelecionarPorID(totalClinicas);
				
					// Condição de Saida
					if (idAtivo < 0 || clinicas[idAtivo].ativo == 0)
						continue;
					
					// Entrar no Menu com o id selecionado
					// O utilizador só sai quando escolher a opção 0- Sair
					while (op != 0)
					{
						// Escolher a opção do menu de clinicas
						MenuClinica(&op, clinicas[idAtivo].nome);
						
						// Executar a opção selecionada
						switch (op)
						{
							// Adicionar Funcionarios
							case 1:
								AddFuncionario(clinicas[idAtivo].funcionarios, &clinicas[idAtivo].totalFuncionarios);
							break;
							// Editar Funcionarios
							case 2:
								EditarFuncionario(clinicas[idAtivo].funcionarios, clinicas[idAtivo].totalFuncionarios);
							break;
							// Remover Funcionarios
							case 3:
								idInativo = RemoverFuncionario(clinicas[idAtivo].funcionarios, clinicas[idAtivo].totalFuncionarios);

								// Inativar todas as consultas de um funcionario, caso o mesmo tenha sido inativado
								if (idInativo != -1)
									InativarTodasConsultasPorFuncionario(clinicas[idAtivo].consultas, clinicas[idAtivo].totalConsultas, idInativo);
							break;
							// Lista de Funcionarios
							case 4:
								ListarFuncionarios(clinicas[idAtivo].funcionarios, clinicas[idAtivo].totalFuncionarios);
								getch();
							break;
							// Marcar uma Consulta
							case 5:
								AddConsulta(clinicas[idAtivo].consultas, &clinicas[idAtivo].totalConsultas, clinicas[idAtivo].funcionarios, clinicas[idAtivo].totalFuncionarios);
							break;
							// Remarcar uma Consulta
							case 6:
								RemarcarConsulta(clinicas[idAtivo].consultas, clinicas[idAtivo].totalConsultas);
							break;
							// Apagar uma Consulta
							case 7:
								RemoverConsulta(clinicas[idAtivo].consultas, clinicas[idAtivo].totalConsultas);
							break;
							// Consultar a Agenda
							case 8:
								Agenda(clinicas[idAtivo].consultas, clinicas[idAtivo].totalConsultas, clinicas[idAtivo].funcionarios, clinicas[idAtivo].totalFuncionarios);
							break;
							// Consultar uma lista com todas as consultas
							case 9:
								ListarConsultas(clinicas[idAtivo].consultas, clinicas[idAtivo].totalConsultas);
								getch();
							break;
							// Informações da Clinica
							case 10:
								ClinicaInfo(clinicas[idAtivo]);
							break;
						}
					}
					// Resetar Opção
					op = -1;
				}
			break;
			
			// Remover Clínica
			case 3:
				RemoverClinica(clinicas, totalClinicas);
			break;
			
			// Listar todos os Médicos
			case 4:
				ListarTodosMedicos(clinicas, totalClinicas);
			break;
		}
	}	
}


/*
	Este procedimento apresenta o Menu Inicial e retorna através de um ponteiro uma opção selecionada no menu
	@op = opção selecionada no menu
*/
void MenuInicial(int *op)
{
	// Resetar Opção
	*op = -1;
	
	// Menu
	system("cls");
	puts("+-------------------------------+");
	puts("|\t   Menu Inicial   \t|");
	puts("+-------------------------------+");
	puts("|\t\t\t\t|");
	puts("| 1- Criar Clínica\t\t|");
	puts("|\t\t\t\t|");
	puts("| 2- Selecionar Clínica\t\t|");
	puts("|\t\t\t\t|");
	puts("| 3- Remover Clínica\t\t|");
	puts("|\t\t\t\t|");
	puts("| 4- Lista de Médicos\t\t|");
	puts("|\t\t\t\t|");
	puts("| 0- Sair\t\t\t|");
	puts("|\t\t\t\t|");
	puts("+-------------------------------+");
	
	// Selecionar uma opção
	printf("Selecione uma opção: ");
	scanf("%d", op);
	
}


/*
	Procedimento extra para carregar dados por Hardcode para simular dados e testar o programa
	@clinicas = lista de clinicas
	@n = quantidade total de clinicas
*/
void CarregarDadosHardCode(Clinica *clinicas, int *n)
{
	// Variaveis
	int id = 0;
	
	// ---------------------- Criação de Clinicas ----------------------
	strcpy(clinicas[*n].nome, "Andre");
	clinicas[*n].totalFuncionarios = 0;
	clinicas[*n].totalConsultas = 0;
	clinicas[*n].ativo = 1;
	clinicas[*n].id = id;
	id++;
	*n += 1;
	
	strcpy(clinicas[*n].nome, "Barbara");
	clinicas[*n].totalFuncionarios = 0;
	clinicas[*n].totalConsultas = 0;
	clinicas[*n].ativo = 1;
	clinicas[*n].id = id;
	id++;
	*n += 1;
	
	strcpy(clinicas[*n].nome, "Joao");
	clinicas[*n].totalFuncionarios = 0;
	clinicas[*n].totalConsultas = 0;
	clinicas[*n].ativo = 1;
	clinicas[*n].id = id;
	id++;
	*n += 1;
	
	id = 0;
	// ---------------------- Criação de Funcionarios ----------------------
	strcpy(clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].nome, "Antonio");
	strcpy(clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].genero, "Masculino");
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].idade = 23;
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].vencimento = 1200;
	strcpy(clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].emprego, "Médico");
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].ativo = 1;
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].id = id;
	id++;
	clinicas[*n-1].totalFuncionarios += 1;
	
	strcpy(clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].nome, "Joana");
	strcpy(clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].genero, "Feminino");
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].idade = 40;
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].vencimento = 600;
	strcpy(clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].emprego, "Auxiliar");
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].ativo = 1;
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].id = id;
	id++;
	clinicas[*n-1].totalFuncionarios += 1;
	
	strcpy(clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].nome, "Anibal");
	strcpy(clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].genero, "Masculino");
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].idade = 32;
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].vencimento = 900;
	strcpy(clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].emprego, "Enfermeiro");
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].ativo = 1;
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].id = id;
	id++;
	clinicas[*n-1].totalFuncionarios += 1;
	
	strcpy(clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].nome, "Ana");
	strcpy(clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].genero, "Feminino");
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].idade = 18;
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].vencimento = 800;
	strcpy(clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].emprego, "Enfermeiro");
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].ativo = 1;
	clinicas[*n-1].funcionarios[clinicas[*n-1].totalFuncionarios].id = id;
	id++;
	clinicas[*n-1].totalFuncionarios += 1;
	
	id = 0;
	// ---------------------- Criação de Consultas ----------------------
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].funcionario = clinicas[*n-1].funcionarios[0];
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].utente.nome, "Jorge");
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].utente.numeroSns, "165093288");
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].data, "24/02/2021");
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].ativo = 1;
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].id = id;
	id++;
	clinicas[*n-1].totalConsultas += 1;
	
	
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].funcionario = clinicas[*n-1].funcionarios[2];
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].utente.nome, "Tobias");
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].utente.numeroSns, "125343223");
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].data, "12/03/2021");
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].ativo = 1;
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].id = id;
	id++;
	clinicas[*n-1].totalConsultas += 1;
	
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].funcionario = clinicas[*n-1].funcionarios[0];
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].utente.nome, "Antonio");
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].utente.numeroSns, "132420045");
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].data, "01/03/2021");
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].ativo = 1;
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].id = id;
	id++;
	clinicas[*n-1].totalConsultas += 1;
	
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].funcionario = clinicas[*n-1].funcionarios[3];
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].utente.nome, "Miguel");
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].utente.numeroSns, "165093284");
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].data, "12/03/2021");
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].ativo = 1;
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].id = id;
	id++;
	clinicas[*n-1].totalConsultas += 1;
	
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].funcionario = clinicas[*n-1].funcionarios[3];
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].utente.nome, "Pedro");
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].utente.numeroSns, "125343223");
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].data, "24/02/2021");
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].ativo = 1;
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].id = id;
	id++;
	clinicas[*n-1].totalConsultas += 1;
	
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].funcionario = clinicas[*n-1].funcionarios[0];
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].utente.nome, "Marco");
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].utente.numeroSns, "132420045");
	strcpy(clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].data, "11/03/2021");
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].ativo = 1;
	clinicas[*n-1].consultas[clinicas[*n-1].totalConsultas].id = id;
	id++;
	clinicas[*n-1].totalConsultas += 1;
	
	id = 0;
	
}





