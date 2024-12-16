#include <stdbool.h>

struct servicoPrestado{
    int codigoPet;
    int codigoServico;
    char data[11]; 
};

typedef struct servicoPrestado ServicoPrestado;

bool inicializarServicosPrestados();
bool encerrarServicosPrestados();
bool prestarServico(ServicoPrestado sp);
int quantServicosPrestados();
ServicoPrestado* listarServicosPet(int codigoPet, int* totalServicos);
ServicoPrestado* listarServicosCliente(int codigoCliente, int* totalServicos);
float calcularLucroServicos();
ServicoPrestado* listarServicosPrestados(int* totalServicos);
bool petTemServicoPrestado(int codigoPet);


