#include <stdbool.h>

struct pet{
    int codigo;
    char nome[50];
    char especie[50];
    int codigoCliente;
};
typedef struct pet Pet;

extern Pet* pets;
extern int qPets;
extern int tamanhoAtualPet;

bool inicializarPets();
bool encerrarPets();
bool salvarPet(Pet p);
int quantPets();
Pet* listarPets(int* totalPets);
Pet* pesquisarPetPeloCodigo(int codigo);
Pet* pesquisarPetPelaEspecie(char* especie, int* totalPets);
bool atualizarPet(Pet p);
bool excluirPetPeloCodigo(int codigo);
bool excluirPetPeloNome(char* nome);
bool clienteTemPets(int codigoCliente);
int buscarCodigoPetPeloNome(char* nomePet);

