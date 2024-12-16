#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Cliente.h"
#define TAMANHO_BASE 5

static FILE* arquivoCliente = NULL;
int quantClientes = 0;
int tamanhoAtual = TAMANHO_BASE;

bool inicializarClientes() {
    arquivoCliente = fopen("clientes.txt", "r+");
    if (arquivoCliente == NULL) {
        arquivoCliente = fopen("clientes.txt", "w+");
        if (arquivoCliente == NULL) {
            return false;
        }
    }
    quantClientes = 0;
    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, arquivoCliente)) {
        quantClientes++;
    }
    fseek(arquivoCliente, 0, SEEK_END); // Posiciona o ponteiro no final do arquivo
    return true;
}

bool encerraClientes() {
    fclose(arquivoCliente);
    arquivoCliente = NULL;
    return true;
}

bool salvarCliente(Cliente c) {
    if (arquivoCliente == NULL) {
        return false;
    }

    fseek(arquivoCliente, 0, SEEK_END); // Move o ponteiro do arquivo para o final
    if (fwrite(&c, sizeof(Cliente), 1, arquivoCliente) != 1) {
        return false;
    }
    quantClientes++;
    return true;
}

int getQuantClientes() {
    return quantClientes;
}

Cliente* listarClientes(int* totalClientes) {
    if (arquivoCliente == NULL) {
        return NULL;
    }

    *totalClientes = quantClientes;
    if (quantClientes == 0) {
        return NULL;
    }

    Cliente* listaCli = (Cliente*)malloc(quantClientes * sizeof(Cliente));
    if (listaCli == NULL) {
        return NULL;
    }

    fseek(arquivoCliente, 0, SEEK_SET);  // Volta ao início do arquivo
    int i = 0;
    while (fread(&listaCli[i], sizeof(Cliente), 1, arquivoCliente)) {
        i++;
    }

    return listaCli;
}

Cliente* pesquisarClientePeloNome(char* nome) {
    if (arquivoCliente == NULL) {
        return NULL;
    }

    fseek(arquivoCliente, 0, SEEK_SET); // Move para o início do arquivo
    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, arquivoCliente)) {
        if (strcmp(cliente.nome, nome) == 0) {
            Cliente* cli = (Cliente*)malloc(sizeof(Cliente));
            if (cli != NULL) {
                *cli = cliente;
            }
            return cli;
        }
    }
    return NULL;
}

Cliente* pesquisarClientePeloCodigo(int codigo) {
    if (arquivoCliente == NULL) {
        return NULL;
    }

    fseek(arquivoCliente, 0, SEEK_SET);
    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, arquivoCliente)) {
        if (cliente.codigo == codigo) {
            Cliente* cli = (Cliente*)malloc(sizeof(Cliente));
            if (cli != NULL) {
                *cli = cliente;
            }
            return cli;
        }
    }
    return NULL;
}

bool atualizarCliente(Cliente c) {
    if (arquivoCliente == NULL) {
        return false;
    }

    fseek(arquivoCliente, 0, SEEK_SET);
    Cliente cliente;
    long posicao = 0;
    while (fread(&cliente, sizeof(Cliente), 1, arquivoCliente)) {
        if (cliente.codigo == c.codigo) {
            fseek(arquivoCliente, posicao, SEEK_SET);  // Vai para a posição do cliente encontrado
            fwrite(&c, sizeof(Cliente), 1, arquivoCliente);  // Substitui o cliente
            return true;
        }
        posicao = ftell(arquivoCliente);
    }
    return false;
}

bool excluirClientePeloCodigo(int codigo) {
    if (arquivoCliente == NULL) {
        return false;
    }

    // Cria o arquivo temporário
    FILE* tempFile = fopen("temp_cliente.dat", "w+");
    if (tempFile == NULL) {
        return false;
    }

    Cliente cliente;
    bool excluiu = false;

    // Percorre o arquivo original
    while (fread(&cliente, sizeof(Cliente), 1, arquivoCliente)) {
        if (cliente.codigo != codigo) {
            // Se o código não for o do cliente a excluir, grava no arquivo temporário
            fwrite(&cliente, sizeof(Cliente), 1, tempFile);
        } else {
            excluiu = true;  // Marca que excluiu o cliente
        }
    }

    // Fechar ambos os arquivos
    fclose(arquivoCliente);
    fclose(tempFile);

    // Exclui o arquivo original e renomeia o temporário para o nome original
    remove("clientes.txt");
    rename("temp_cliente.dat", "clientes.txt");

    // Reabre o arquivo de clientes
    arquivoCliente = fopen("clientes.txt", "r+");
    return excluiu;  // Retorna true se o cliente foi excluído
}



bool excluirClientePeloNome(char* nome) {
    if (arquivoCliente == NULL) {
        return false;
    }

    FILE* tempFile = fopen("temp_cliente.dat", "w+");
    if (tempFile == NULL) {
        return false;
    }

    fseek(arquivoCliente, 0, SEEK_SET);
    Cliente cliente;
    bool excluiu = false;

    while (fread(&cliente, sizeof(Cliente), 1, arquivoCliente)) {
        if (strcmp(cliente.nome, nome) != 0) {
            fwrite(&cliente, sizeof(Cliente), 1, tempFile);
        } else {
            excluiu = true;
        }
    }

    fclose(arquivoCliente);
    fclose(tempFile);
    remove("clientes.txt");
    rename("temp_cliente.dat", "clientes.txt");

    arquivoCliente = fopen("clientes.txt", "r+");
    return excluiu;
}

