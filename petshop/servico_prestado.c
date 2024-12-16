#include "servico_prestado.h"
#include "servico.h"
#include "pet.h"
#include <stdlib.h>
#include <string.h>

#define TAMANHO_BASE 5

ServicoPrestado* servicosPrestados = NULL;
int tamanhoAtualServicosPrestados = TAMANHO_BASE;
int qServicosPrestados = 0;

bool inicializarServicosPrestados(){
    servicosPrestados = (ServicoPrestado*)malloc(TAMANHO_BASE * sizeof(ServicoPrestado));
    if (servicosPrestados == NULL){
        return false;
    }
    
    servicosPrestados[0].codigoPet = 11;
    servicosPrestados[0].codigoServico = 111;
    strcpy(servicosPrestados[0].data, "11/11/2024");

    servicosPrestados[1].codigoPet = 22;
    servicosPrestados[1].codigoServico = 222;
    strcpy(servicosPrestados[1].data, "22/10/2024");

    servicosPrestados[2].codigoPet = 33;
    servicosPrestados[2].codigoServico = 333;
    strcpy(servicosPrestados[2].data, "14/07/2024");

    servicosPrestados[3].codigoPet = 22;
    servicosPrestados[3].codigoServico = 111;
    strcpy(servicosPrestados[3].data, "16/04/2023");
    
    qServicosPrestados = 4;
    
    return true;
}

bool encerrarServicosPrestados(){
    free(servicosPrestados);
    servicosPrestados = NULL;
    qServicosPrestados = 0;
    return true;
}

bool prestarServico(ServicoPrestado sp){
    if (qServicosPrestados == tamanhoAtualServicosPrestados){
        tamanhoAtualServicosPrestados += 5;
        ServicoPrestado* Sep = (ServicoPrestado*)realloc(servicosPrestados, tamanhoAtualServicosPrestados * sizeof(ServicoPrestado));
        if (Sep == NULL){
            return false;
        }
        servicosPrestados = Sep;
    }
    servicosPrestados[qServicosPrestados++] = sp;
    return true;
}

int quantServicosPrestados(){
	int spQuantidade = qServicosPrestados;
    return spQuantidade;
}

ServicoPrestado* listarServicosPet(int codigopet, int* totalServicos){
    *totalServicos = 0;
    int i;
    for (i = 0; i < qServicosPrestados; i++){
        if (servicosPrestados[i].codigoPet == codigopet){
            (*totalServicos)++;
        }
    }
    if (*totalServicos == 0){
    	return NULL;
	}

    ServicoPrestado* listaSp = (ServicoPrestado*)malloc(*totalServicos * sizeof(ServicoPrestado));
    int j = 0;
    for (i = 0; i < qServicosPrestados; i++) {
        if (servicosPrestados[i].codigoPet == codigopet) {
            listaSp[j++] = servicosPrestados[i];
        }
    }
    return listaSp;
}

ServicoPrestado* listarServicosCliente(int codigoCliente, int* totalServicos){
    *totalServicos = 0;

    ServicoPrestado* listaSp = (ServicoPrestado*)malloc(qServicosPrestados * sizeof(ServicoPrestado));
    if (listaSp == NULL){
        return NULL;
    }

	int i, j;
    for (i = 0; i < qServicosPrestados; i++){
        int codigoPetAtual = servicosPrestados[i].codigoPet;

        for (j = 0; j < qPets; j++) {
            if (pets[j].codigo == codigoPetAtual && pets[j].codigoCliente == codigoCliente){
                listaSp[*totalServicos] = servicosPrestados[i];
                (*totalServicos)++;
                break; 
            }
        }
    }

    if (*totalServicos == 0){
        free(listaSp);
        return NULL;
    }

    return listaSp;
}

float calcularLucroServicos(){
    float totalLucro = 0.0;
    int i;
    for (i = 0; i < qServicosPrestados; i++){
        int codigoServico = servicosPrestados[i].codigoServico;
        int j;
        for (j = 0; j < qServicos; j++){
            if (servicos[j].codigo == codigoServico){
                totalLucro += (servicos[j].valorCobrado - servicos[j].valorCusto);
            }
        }
    }
    return totalLucro;
}

ServicoPrestado* listarServicosPrestados(int* totalServicos){
    *totalServicos = 0;
    
    int qServicosPrestados = quantServicosPrestados();
    ServicoPrestado* listaSp = (ServicoPrestado*)malloc(qServicosPrestados * sizeof(ServicoPrestado));

    if (listaSp == NULL){
    	return NULL;  
	}
	int i;
    for (i = 0; i < qServicosPrestados; i++){
        listaSp[i] = servicosPrestados[i];
    }
    
    return listaSp;
}

bool petTemServicoPrestado(int codigopet){
	int i;
    for (i = 0; i < qServicosPrestados; i++){
        if (servicosPrestados[i].codigoPet == codigopet){
            return true;
        }
    }
    return false;
}

bool servicoFoiPrestado(int codigoservico){
	int i;
    for (i = 0; i < qServicosPrestados; i++){
        if (servicosPrestados[i].codigoServico == codigoservico){
            return true;  
        }
    }
    return false;  
}
