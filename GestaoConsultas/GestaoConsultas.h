#ifndef GESTAOCONSULTAS_H_
#define GESTAOCONSULTAS_H_
	
	
	// Estruturas
	typedef struct utente
	{
		char nome[50];
		char numeroSns[10];
	} Utente;
	
	typedef struct consulta
	{
		int id;
		char data[15];
		Funcionario funcionario;
		Utente utente;
		char ativo;
	} Consulta;
	
	
	// Assinaturas
	void ListarConsultas(Consulta *consultas, int n);
	void Agenda(Consulta *consultas, int nC, Funcionario *funcionarios, int nF);
	void AddConsulta(Consulta *consultas, int *nC, Funcionario *funcionarios, int nF);
	void RemoverConsulta(Consulta *consultas, int n);
	void RemarcarConsulta(Consulta *consultas, int n);
	void InativarTodasConsultasPorFuncionario(Consulta *consultas, int n, int id);
	int VerificarFuncionario(Funcionario funcionario);
	int TotalConsultasPorFuncionario(Funcionario funcionario, Consulta *consultas, int n);

#endif


