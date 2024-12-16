#include "pet.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TAMANHO_BASE 5

static FILE* arquivoPet = NULL;
Pet* pets = NULL;
int tamanhoAtualPet = TAMANHO_BASE;
int qPets = 0;

bool inicializarPets() {
    arquivoPet = fopen("pets.txt", "r+");
    if (arquivoPet == NULL) {
        arquivoPet = fopen("pets.txt", "w+");
        if (arquivoPet == NULL) {
            return false;
        }
    }
    qPets = 0;
    Pet pet;
    while (fread(&pet, sizeof(Pet), 1, arquivoPet)) {
        qPets++;
    }
    fseek(arquivoPet, 0, SEEK_END); // Posiciona o ponteiro no final do arquivo
    return true;
}

bool encerrarPets() {
    fclose(arquivoPet);
    arquivoPet = NULL;
    return true;
}

bool salvarPet(Pet p) {
    if (arquivoPet == NULL) {
        return false;
    }
    
    fseek(arquivoPet, 0, SEEK_END);  // Move para o final do arquivo
    if (fwrite(&p, sizeof(Pet), 1, arquivoPet) != 1) {
        return false;
    }
    qPets++;
    return true;
}

int quantPets() {
    return qPets;
}

Pet* listarPets(int* totalPets) {
    if (arquivoPet == NULL) {
        return NULL;
    }

    *totalPets = qPets;
    if (qPets == 0) {
        return NULL;
    }

    Pet* listaP = (Pet*)malloc(qPets * sizeof(Pet));
    if (listaP == NULL) {
        return NULL;
    }

    fseek(arquivoPet, 0, SEEK_SET);  // Volta ao início do arquivo
    int i = 0;
    while (fread(&listaP[i], sizeof(Pet), 1, arquivoPet)) {
        i++;
    }

    return listaP;
}

Pet* pesquisarPetPeloCodigo(int codigo) {
    if (arquivoPet == NULL) {
        return NULL;
    }

    fseek(arquivoPet, 0, SEEK_SET); // Move para o início do arquivo
    Pet pet;
    while (fread(&pet, sizeof(Pet), 1, arquivoPet)) {
        if (pet.codigo == codigo) {
            Pet* pe = (Pet*)malloc(sizeof(Pet));
            if (pe != NULL) {
                *pe = pet;
            }
            return pe;
        }
    }
    return NULL;
}

Pet* pesquisarPetPelaEspecie(char* especie, int* totalPets) {
    *totalPets = 0;
    if (arquivoPet == NULL) {
        return NULL;
    }

    Pet* petsEncontrados = (Pet*)malloc(TAMANHO_BASE * sizeof(Pet));
    if (petsEncontrados == NULL) {
        return NULL;
    }

    fseek(arquivoPet, 0, SEEK_SET);
    Pet pet;
    int i = 0;
    while (fread(&pet, sizeof(Pet), 1, arquivoPet)) {
        if (strcmp(pet.especie, especie) == 0) {
            petsEncontrados[*totalPets] = pet;
            (*totalPets)++;
        }
    }

    if (*totalPets == 0) {
        free(petsEncontrados);
        return NULL;
    }

    return petsEncontrados;
}

bool atualizarPet(Pet p) {
    if (arquivoPet == NULL) {
        return false;
    }

    fseek(arquivoPet, 0, SEEK_SET);
    Pet pet;
    long posicao = 0;
    while (fread(&pet, sizeof(Pet), 1, arquivoPet)) {
        if (pet.codigo == p.codigo) {
            fseek(arquivoPet, posicao, SEEK_SET);  // Vai para a posição do pet encontrado
            fwrite(&p, sizeof(Pet), 1, arquivoPet);  // Substitui o pet
            return true;
        }
        posicao = ftell(arquivoPet);
    }
    return false;
}

bool excluirPetPeloCodigo(int codigo) {
    if (arquivoPet == NULL) {
        return false;
    }

    FILE* tempFile = fopen("temp_pet.dat", "w+");
    if (tempFile == NULL) {
        return false;
    }

    fseek(arquivoPet, 0, SEEK_SET);
    Pet pet;
    bool excluiu = false;

    while (fread(&pet, sizeof(Pet), 1, arquivoPet)) {
        if (pet.codigo != codigo) {
            fwrite(&pet, sizeof(Pet), 1, tempFile);
        } else {
            excluiu = true;
        }
    }

    fclose(arquivoPet);
    fclose(tempFile);
    remove("pets.txt");  // Apaga o arquivo original
    rename("temp_pet.dat", "pets.txt");  // Renomeia o arquivo temporário

    arquivoPet = fopen("pets.txt", "r+");  // Reabre o arquivo original
    return excluiu;
}

bool excluirPetPeloNome(char* nome) {
    if (arquivoPet == NULL) {
        return false;
    }

    FILE* tempFile = fopen("temp_pet.dat", "w+");
    if (tempFile == NULL) {
        return false;
    }

    fseek(arquivoPet, 0, SEEK_SET);
    Pet pet;
    bool excluiu = false;

    while (fread(&pet, sizeof(Pet), 1, arquivoPet)) {
        if (strcmp(pet.nome, nome) != 0) {
            fwrite(&pet, sizeof(Pet), 1, tempFile);
        } else {
            excluiu = true;
        }
    }

    fclose(arquivoPet);
    fclose(tempFile);
    remove("pets.txt");  // Apaga o arquivo original
    rename("temp_pet.dat", "pets.txt");  // Renomeia o arquivo temporário

    arquivoPet = fopen("pets.txt", "r+");  // Reabre o arquivo original
    return excluiu;
}

bool clienteTemPets(int codigoCliente) {
    int totalPets = 0;
    Pet* listaP = listarPets(&totalPets);
    if (listaP == NULL) {
        return false;
    }
	int i;
    for (i = 0; i < totalPets; i++) {
        if (listaP[i].codigoCliente == codigoCliente) {
            free(listaP);
            return true;
        }
    }
    free(listaP);
    return false;
}

int buscarCodigoPetPeloNome(char* nomePet) {
    if (arquivoPet == NULL) {
        return -1;
    }

    fseek(arquivoPet, 0, SEEK_SET);
    Pet pet;
    while (fread(&pet, sizeof(Pet), 1, arquivoPet)) {
        if (strcmp(pet.nome, nomePet) == 0) {
            return pet.codigo;
        }
    }
    return -1;
}

