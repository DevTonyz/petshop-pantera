#include "servico.h"
#include <stdlib.h>
#include <string.h>

#define TAMANHO_BASE 5

Servico* servicos = NULL;
int tamanhoAtualServico = TAMANHO_BASE;
int qServicos = 0;

bool inicializarServicos(){
    servicos = (Servico*)malloc(TAMANHO_BASE * sizeof(Servico));
    if (servicos == NULL){
        return false;
    }
    
    servicos[0].codigo = 111;
    strcpy(servicos[0].nome, "Banho");
    servicos[0].valorCobrado = 40.00;
    servicos[0].valorCusto = 15.00;

    servicos[1].codigo = 222;
    strcpy(servicos[1].nome, "Adestramento");
    servicos[1].valorCobrado = 350.00;
    servicos[1].valorCusto = 50.00;

    servicos[2].codigo = 333;
    strcpy(servicos[2].nome, "Tosa");
    servicos[2].valorCobrado = 50.00;
    servicos[2].valorCusto = 5.00;
    
    qServicos = 3;
    
    return true;
}

bool encerrarServicos(){
    free(servicos);
    servicos = NULL;
    qServicos = 0;
    return true;
}

bool salvarServico(Servico s){
    if (qServicos == tamanhoAtualServico){
        tamanhoAtualServico += 5;
        Servico* se = (Servico*)realloc(servicos, tamanhoAtualServico * sizeof(Servico));
        if (se == NULL){
            return false;
        }
        servicos = se;
    }
    servicos[qServicos++] = s;
    return true;
}

int quantServicos(){
	int seQuantidade = qServicos;
    return seQuantidade;
}

Servico* listarServicos(int* totalServicos){
    *totalServicos = qServicos;
    
    Servico* listaS = (Servico*)malloc(qServicos * sizeof(Servico));

    int i;
    for (i = 0; i < qServicos; i++){
        listaS[i] = servicos[i];
    }
    if (listaS == NULL){
        free(listaS);
        return NULL;
    }
    return listaS;
}

Servico* pesquisarServicoPeloCodigo(int codigo){
	int i;
    for (i = 0; i < qServicos; i++){
        if (servicos[i].codigo == codigo){
            Servico* Se = (Servico*)malloc(sizeof(Servico));
            if (Se != NULL){
                *Se = servicos[i];
            }
            return Se;
        }
    }
    return NULL;
}

bool atualizarServico(Servico s){
	int i;
    for (i = 0; i < qServicos; i++){
        if (servicos[i].codigo == s.codigo){
            servicos[i] = s;
            return true;
        }
    }
    return false;
}

bool excluirServicoPeloCodigo(int codigo){
    int indice = -1;
    int i;
    for (i = 0; i < qServicos; i++){
        if (servicos[i].codigo == codigo){
            indice = i;
            break;
        }
    }
    if (indice == -1){
        return false;
    }
    servicos[indice] = servicos[qServicos - 1];
    qServicos--;
    if (qServicos < tamanhoAtualServico / 2 && tamanhoAtualServico > TAMANHO_BASE){
        int novoTamanho = tamanhoAtualServico / 2;
        if (novoTamanho < TAMANHO_BASE){
            novoTamanho = TAMANHO_BASE;
        }
        Servico* se = (Servico*)realloc(servicos, novoTamanho * sizeof(Servico));
        if (se != NULL){
            servicos = se;
            tamanhoAtualServico = novoTamanho;
        }
    }
    return true;
}
