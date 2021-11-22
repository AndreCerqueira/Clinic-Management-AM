#ifndef GESTAOCLINICAS_H_
#define GESTAOCLINICAS_H_
	
	
	// Estruturas
	typedef struct clinica
	{
		int id;
		char nome[50];
		Funcionario funcionarios[20];
		int totalFuncionarios;
		Consulta consultas[20];
		int totalConsultas;
		char ativo;
	} Clinica;
	
	
	// Assinaturas
	void MenuClinica(int *op, char *nome);
	void ListarClinicas(Clinica *clinicas, int n);
	void AddClinica(Clinica *clinicas, int *n);
	void RemoverClinica(Clinica *clinicas, int n);
	void ClinicaInfo(Clinica clinica);
	void ListarTodosMedicos(Clinica *clinicas, int n);

#endif


