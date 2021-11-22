#ifndef GESTAOFUNCIONARIOS_H_
#define GESTAOFUNCIONARIOS_H_
	
	
	// Estruturas
	typedef struct funcionario
	{
		int id;
		char nome[50];
		char genero[10];
		unsigned int idade;
		float vencimento;
		char emprego[15]; // Pode ser Médico, Enfermeiro ou Auxiliar
		char ativo;
	} Funcionario;
	
	
	// Assinaturas
	void AddFuncionario(Funcionario *funcionarios, int *n);
	void ListarFuncionarios(Funcionario *funcionarios, int n);
	void EditarFuncionario(Funcionario *funcionarios, int n);
	int RemoverFuncionario(Funcionario *funcionarios, int n);
	int QuantidadeFuncionariosPorEmprego(Funcionario *funcionarios, int n, char* emprego);
	float MediaIdadesFuncionariosPorEmprego(Funcionario *funcionarios, int n, char *emprego);
	float SomaVencimentosPorGeneroEmprego(Funcionario *funcionarios, int n, char *emprego, char *genero);

#endif

