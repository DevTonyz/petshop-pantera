#include <stdbool.h>

struct cliente{
	int codigo;
	char nome[50];
	char cpf[15];
	char telefone[15];
};
typedef struct cliente Cliente;

bool inicializarClientes();
bool encerrarClientes();
bool salvarCliente(Cliente c);
int quantidadeClientes();
Cliente* listarClientes(int* totalClientes);
Cliente* pesquisarClientePeloCodigo(int codigo);
Cliente* pesquisarClientePeloNome(char* nome);
bool atualizarCliente(Cliente c);
bool excluirClientePeloCodigo(int codigo);
bool excluirClientePeloNome(char* nome);


