#include <stdbool.h>

struct servico{
    int codigo;
    char nome[50];
    float valorCobrado;
    float valorCusto;
};

typedef struct servico Servico;

extern Servico* servicos;
extern int qServicos;

bool inicializarServicos();
bool encerrarServicos();
bool salvarServico(Servico s);
int quantServicos();
Servico* listarServicos(int* totalServicos);
Servico* pesquisarServicoPeloCodigo(int codigo);
bool atualizarServico(Servico s);
bool excluirServicoPeloCodigo(int codigo);

