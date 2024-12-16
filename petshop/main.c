#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>
#include "cliente.h"
#include "pet.h"
#include "servico.h"
#include "servico_prestado.h"


void limparBuffer(){
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF); 
}

void cadastroCliente(){
	Cliente c;
	int cod;
	
	printf("\nDigite o codigo do cliente: ");
	cod = scanf("%d", &c.codigo);
	if (cod != 1){
		printf("\nCodigo invalido! tente novamente. \n");
		limparBuffer();
		return;
	}
	if (pesquisarClientePeloCodigo(c.codigo) != NULL){
		printf("\nCodigo indisponivel, use outro.\n");
		return;
	}
	printf("\nDigite o nome do cliente: ");
		limparBuffer();
		scanf("%[^\n]s", c.nome); // le numeros com espaco
		if (strlen(c.nome) == 0){ //verifica se string ta vazia
		printf("\nNao eh possivel encontrar um nome vazio!");	
		return;
	}
	printf("\nDigite o cpf do cliente: ");
	scanf("%s", c.cpf);
	printf("\nDigite o telefone do cliente: ");
	scanf("%s", c.telefone);
	
	if(salvarCliente(c)){
		printf("\nCliente cadastrado!");
	}else {
		printf("ERRO! nao foi possivel cadastrar o cliente, tente novamente.");
	}
}


void exibirClientes(){
	int totalClientes = 0;
	
	Cliente* listaC = listarClientes(&totalClientes);
	if (listaC == NULL || totalClientes == 0){
		printf("\nNao tem clientes cadastrados!\n");
		if (listaC != NULL){
			free(listaC);
		}
		return;
	}
	printf("\n -- LISTA DE CLIENTES --\n\n");
	int i;
	for(i = 0; i < totalClientes; i++){
		printf("%d - Codigo: %d, Nome: %s, CPF: %s, Telefone: %s\n", i+1, listaC[i].codigo, listaC[i].nome, listaC[i].cpf, listaC[i].telefone);
	}
	free(listaC);
}

void buscarClientePeloCodigo(){
	int codigo;
	
	printf("\nDigite o codigo do cliente que desejas buscar: ");
	scanf("%d", &codigo);
	Cliente* cliente = pesquisarClientePeloCodigo(codigo);
	if(cliente != NULL){
		printf("\nCliente:\n Codigo: %d, Nome: %s, CPF: %s, Telefone: %s\n", cliente->codigo, cliente->nome, cliente->cpf, cliente->telefone);
		free(cliente);
	}else{
		printf("Nao encontramos esse codigo na lista de clientes :(\n");
	}
}

void buscarClientePeloNome(){
	char nome[50];
	
	printf("\nDigite o nome do cliente que desejas buscar: ");
	limparBuffer();
	scanf("%[^\n]s", nome);
	Cliente* cliente = pesquisarClientePeloNome(nome);
	if(cliente != NULL){
		printf("\nCliente:\n Codigo: %d, Nome: %s, CPF: %s, Telefone: %s\n", cliente->codigo, cliente->nome, cliente->cpf, cliente->telefone);
		free(cliente);
	}else{
		printf("Nao encontramos esse nome na lista de clientes :(\n");
	}
}

void updateCliente(){
	exibirClientes();
	int codigo;
	
	printf("\nDigite o codigo do cliente que desejas atualizar:\n Codigo: ");
	scanf("%d", &codigo);
	Cliente* clienteCadastrado = pesquisarClientePeloCodigo(codigo);
	if(clienteCadastrado == NULL){
		printf("\nNao encontramos nenhum cliente com este codigo, tente novamente.\n");
		return;
	}
	printf("\nCliente:\n Codigo: %d, Nome: %s, CPF: %s, Telefone: %s\n", clienteCadastrado->codigo, clienteCadastrado->nome, clienteCadastrado->cpf, clienteCadastrado->telefone);
	Cliente clienteAtt = *clienteCadastrado;
	free(clienteCadastrado);
	clienteAtt.codigo = codigo;
	printf("\nNovo nome: ");
	limparBuffer();
	scanf("%[^\n]s", clienteAtt.nome); 
	printf("\nNovo CPF: ");
    scanf("%s", clienteAtt.cpf);
    printf("Novo telefone: ");
    scanf("%s", clienteAtt.telefone);
    if (atualizarCliente(clienteAtt)){
        printf("\nCliente atualizado com sucesso!\n");
    }else{
        printf("\nNao foi possivel atualizar o cliente, tente novamente!\n");
    }
}

void apagarClientePeloCodigo(){
	exibirClientes();
    int codigo;
    
    printf("\nDigite o código do cliente para excluir: ");
    scanf("%d", &codigo);
    Cliente* cliente = pesquisarClientePeloCodigo(codigo);
    if (cliente == NULL) {
        printf("\nNao encontramos um cliente com esse codigo.\n");
        return;
    }
    if (clienteTemPets(codigo)){
        printf("\nErro ao excluir este cliente, pois ele possui pets.\n");
        free(cliente);
        return;
    }
    if (excluirClientePeloCodigo(codigo)){
        printf("\nCliente excluido com sucesso.\n");
    } else{
        printf("\nErro ao excluir cliente, tente novamente.\n");
    }
    free(cliente);
}


void apagarClientePeloNome(){
	exibirClientes();
    char nome[50];
    
    printf("\nDigite o nome do cliente que desejas excluir: ");
    limparBuffer();
    scanf("%[^\n]s", nome);
    Cliente* cliente = pesquisarClientePeloNome(nome);
    if (cliente == NULL) {
        printf("\nNao encontramos um cliente com esse nome.\n");
        return;
    }
    if (clienteTemPets(cliente->codigo)){
        printf("\nErro ao excluir este cliente, pois ele possui pets\n");
        free(cliente);
        return;
    }
    if (excluirClientePeloNome(nome)){
        printf("\nCliente excluido com sucesso.\n");
    } else{
        printf("\nErro ao excluir cliente, tente novamente\n");
    }
    free(cliente);
}


void cadastroPet(){
    Pet p;
    int cod;
    
	printf("\nDigite o codigo do pet que desejas cadastrar: ");
    cod = scanf("%d", &p.codigo);
    if (cod != 1){
        printf("\nCodigo invalido! Tente novamente.\n");
        limparBuffer();
        return;
    }
    if (pesquisarPetPeloCodigo(p.codigo) != false){
        printf("\ncodigo ja utilizado por outro pet! escolha outro codigo!.\n");
        return;
    }
    printf("Digite o nome do pet: ");
    limparBuffer();
    scanf("%[^\n]s", p.nome);
    if (strlen(p.nome) == 0){
        printf("\nVoce nao pode deixar o nome do pet vazio!\n");
        return;
    }
    printf("Digite a especie do pet: ");
    limparBuffer();
    scanf("%[^\n]s", p.especie);
    printf("Digite o codigo do dono do pet: ");
    scanf("%d", &p.codigoCliente);
   
    Cliente* cliente = pesquisarClientePeloCodigo(p.codigoCliente);
    if (cliente == NULL){
        printf("\nNao existe cliente cadastrado com esse codigo. tente novamente.\n", p.codigoCliente);
        free(cliente);
		return;
    }
    free(cliente);
    if (salvarPet(p)){
        printf("\nPet cadastrado com sucesso.\n");
    }else{
        printf("\nErro ao cadastrar o pet, tente novamente! \n");
    }
}

void exibirPets(){
    int totalPets = 0;
    
    Pet* listaP = listarPets(&totalPets);
    if (listaP == NULL || totalPets == 0){
        printf("\nNao existe pets cadastrados.\n");
        if (listaP != NULL){
        	free(listaP);
		}
        return;
    }
    printf("\n-- Lista de Pets --\n\n");
    int i;
    for (i = 0; i < totalPets; i++){
        Cliente* cliente = pesquisarClientePeloCodigo(listaP[i].codigoCliente);
        printf("%d - Codigo: %d, Nome: %s, Especie: %s, Codigo do Cliente: %d, Nome do Cliente: %s\n", i+1, listaP[i].codigo, listaP[i].nome, listaP[i].especie, listaP[i].codigoCliente, cliente->nome);
        free(cliente); 
    }
    free(listaP); 
}

void buscarPetPeloCodigo(){
    int codigo;
    
    printf("\nDigite o codigo do pet que deseja pesquisar: ");
    scanf("%d", &codigo);
    Pet* pet = NULL;
	pet = pesquisarPetPeloCodigo(codigo);
    if (pet != NULL){
        printf("\nPet: \n. Codigo: %d, Nome: %s, Especie: %s, Codigo do Cliente: %d\n", pet->codigo, pet->nome, pet->especie, pet->codigoCliente);
    	free(pet);
	} else{
        printf("\nNao encontramos nenhum pet com esse codigo, tente novamente. \n");
    }
}
 
void buscarPetPelaEspecie(){
    char especie[50];
    
    printf("\nDigite a especie do pet que deseja pesquisar: ");
    limparBuffer();
    scanf("%[^\n]s", especie);
    int totalPets = 0;
    Pet* listaP = pesquisarPetPelaEspecie(especie, &totalPets);
    if (listaP != NULL && totalPets > 0){
        printf("\n-- Lista de especie %s --\n\n", especie);
        int i;
        for (i = 0; i < totalPets; i++){
            printf("Codigo: %d, Nome: %s, Especie: %s, Codigo do Cliente: %d\n", listaP[i].codigo, listaP[i].nome, listaP[i].especie, listaP[i].codigoCliente);
        }
        free(listaP); 
    } else{
        printf("\nNao encontramos pets dessa especie.\n");
    }
}

void updatePet(){ 
	exibirPets();
	int codigo;
    
	printf("\nDigite o codigo do pet que deseja atualizar: ");
    scanf("%d", &codigo);
    Pet* pet = pesquisarPetPeloCodigo(codigo);
    if (pet == NULL){
        printf("\nNao existe nenhum pet com esse codigo :(\n");
        return;
    }
    printf("\nPet:\n Codigo: %d, Nome: %s, Especie: %s, Codigo do Cliente: %d\n", pet->codigo, pet->nome, pet->especie, pet->codigoCliente);
    Pet petAtt = *pet;
    free(pet);
    petAtt.codigo = codigo;
    printf("\nNovo nome do pet: ");
    limparBuffer();
    scanf("%[^\n]s", petAtt.nome);
    printf("Nova especie do pet: ");
    limparBuffer();
    scanf("%[^\n]s", petAtt.especie);
    if (atualizarPet(petAtt)){
        printf("\nPet atualizado com sucesso.\n");
    } else{
        printf("\nERRO! nao foi possivel atualizar o pet, tente novamente.\n");
    }
}

void apagarPetPeloCodigo(){
	exibirPets();
    int codigo;
    
    printf("\nDigite o codigo do pet que desejas excluir: ");
    scanf("%d", &codigo);
    
    Pet* pet = pesquisarPetPeloCodigo(codigo);
    if (pet == NULL){
        printf("\nNao existe um pet com esse codigo. \n");
        return;
    }
    
    if (petTemServicoPrestado(codigo)) {
        printf("\nErro ao excluir pet, nao eh possivel apagar pet com servicos prestados.\n");
        free(pet);
		return;
    }
    
    if (excluirPetPeloCodigo(codigo)){
        printf("\nPet excluido com sucesso!\n");
    } else {
        printf("\nERRO ao excluir pet, tente novamente.\n");
    }
}

void apagarPetPeloNome(){
	exibirPets();
    char nome[50];
    
    
    printf("\nDigite o nome do pet que desejas excluir: ");
    limparBuffer();
    scanf("%[^\n]s", nome);
    
    int codigo = buscarCodigoPetPeloNome(nome); 
    Pet* pet = pesquisarPetPeloCodigo(codigo);
    if (pet == NULL){
        printf("\nNao existe um pet com esse nome cadastrado!tente novamente\n");
        return;
    }

    if (petTemServicoPrestado(codigo)) {
        printf("\nERRO, nao eh possivel apagar pet que possui serviços prestados.\n");
        free(pet);
		return;
    }
    
    if (excluirPetPeloNome(nome)){
        printf("\nPet excluido com sucesso.\n");
    } else {
        printf("\nERRO ao excluir pet, tente novamente.\n");
    }
}

void cadastroServico(){
    Servico s;
    int cod;
    printf("\nDigite o codigo do servico: ");
    cod = scanf("%d", &s.codigo);
    if (cod != 1){
        printf("\nCodigo invalido! Tente novamente.\n");
        limparBuffer();
        return;
    }
    if (pesquisarServicoPeloCodigo(s.codigo) != false){
        printf("\nERRO! codigo ja em uso, tente novamente.\n");
        return;
    }
    printf("Digite o nome do servico: ");
    limparBuffer();
    scanf("%[^\n]s", s.nome);
    if (strlen(s.nome) == 0){
        printf("\nO nome do servico nao pode ficar em branco!.\n");
        return;
    } 
    printf("Digite o valor cobrado pelo servico: ");
    scanf("%f", &s.valorCobrado);
    printf("Digite o valor de custo do servico: ");
    scanf("%f", &s.valorCusto);
    if (salvarServico(s)){
        printf("\nServico cadastrado com sucesso.\n");
    } else {
        printf("\nERRO ao cadastrar servico, tente novamente!.\n");
    }
}

void exibirServicos(){
    int totalServicos = 0;
    
    Servico* listaS = listarServicos(&totalServicos);
    if (listaS == NULL || totalServicos == 0){
        printf("\nNao ha servicos cadastrados :(.\n");
        if (listaS != NULL){
            free(listaS);
        }
        return;
    }
    printf("\n-- Lista de Servicos --\n\n");
    int i;
    for (i = 0; i < totalServicos; i++){
        printf("%d - Codigo: %d, Nome: %s, Valor Cobrado: %.2f, Valor Custo: %.2f\n", i + 1, listaS[i].codigo, listaS[i].nome, listaS[i].valorCobrado, listaS[i].valorCusto);
    }
    free(listaS);
}

void buscarServicoPeloCodigo(){
    int codigo;
    printf("\nDigite o codigo do serviço a ser pesquisado: ");
    scanf("%d", &codigo);
    Servico* servico = pesquisarServicoPeloCodigo(codigo);
    if (servico != NULL){
        printf("\nServico: \n Codigo: %d, Nome: %s, Valor Cobrado: %.2f, Valor Custo: %.2f\n", servico->codigo, servico->nome, servico->valorCobrado, servico->valorCusto);
        free(servico);
    } else {
        printf("\nERRO! nao encontramos nenhum servico com esse codigo.\n");
    }
}

void updateServico(){
	exibirServicos();
	
    int codigo;
    printf("\nDigite o codigo do servico que deseja atualizar: ");
    scanf("%d", &codigo);
    
    Servico* servicoCadastrado = pesquisarServicoPeloCodigo(codigo);
    if (servicoCadastrado == NULL){
        printf("\nNao existe servico com esse codigo\n");
        return;
    }
    printf("\nServico: - Codigo: %d, Nome: %s, Valor Cobrado: %.2f, Valor Custo: %.2f\n", servicoCadastrado->codigo, servicoCadastrado->nome, servicoCadastrado->valorCobrado, servicoCadastrado->valorCusto);

    Servico servicoAtt = *servicoCadastrado;
    free(servicoCadastrado);

    printf("Digite o novo nome do serviço: ");
    limparBuffer();
    scanf("%[^\n]s", servicoAtt.nome);
    printf("Digite o novo valor cobrado pelo servico: ");
    scanf("%f", &servicoAtt.valorCobrado);
    printf("Digite o novo valor de custo pelo servico: ");
    scanf("%f", &servicoAtt.valorCusto);

    if (atualizarServico(servicoAtt)){
        printf("\nServico atualizado com sucesso!\n");
    } else{
        printf("\ERRO ao atualizar servico, tente novamente!\n");
    }
}

void apagarServicoPeloCodigo(){
	exibirServicos();
	
    int codigo;
    printf("\nDigite o codigo do servico que desejas excluir: ");
    scanf("%d", &codigo);
    
    Servico* servico = pesquisarServicoPeloCodigo(codigo);
    if (servico == NULL){
        printf("\nNao encontrei nenhum servico com esse codigo :(\n");
        return;
    }
    if (servicoFoiPrestado(codigo)){
        printf("\nERRO! nao eh possivel excluir um servico que ja foi prestado >:(.\n");
        return;
    }
    
    int qServicosPrestados = quantServicosPrestados();
    int totalServicos = 0;
    ServicoPrestado* servicosPr = listarServicosPrestados(&totalServicos);
	int i;
	
    if (excluirServicoPeloCodigo(codigo)){
        printf("\nServico excluido com sucesso.\n");
    } else {
        printf("\nERRO ao excluir cliente, tente novamente.\n");
    }
    free(servico);
}

void exibirServicosPet(){
	exibirPets();
	
    int cod;
    printf("\nDigite o codigo do pet: ");
    scanf("%d", &cod);

	Pet* pet = pesquisarPetPeloCodigo(cod);
    if (pet == NULL){
        printf("\nNao encontramos pet cadastrado com esse codigo!\n");
        return;
    }

    int totalServicos = 0;
    ServicoPrestado* listaS = listarServicosPet(cod, &totalServicos);
    
	if (listaS == NULL || totalServicos == 0){
        printf("\nEsse pet nao possui servicos prestados!\n");
        return;
	}
	
    printf("\n-- Servicos Prestados [Pet Codigo %d] --\n\n", cod);
    int i;
    for (i = 0; i < totalServicos; i++){
        Servico servico;
        int encontrado = 0;
        int j;
        for (j = 0; j < qServicos; j++){
            if (servicos[j].codigo == listaS[i].codigoServico){
                servico = servicos[j];
                encontrado = 1;
            }
        }
        if (encontrado == 1){
            printf("%d - Codigo: %d, Nome: %s, Valor: %.2f, Data: %s\n", i+1, listaS[i].codigoServico, servico.nome, servico.valorCobrado, listaS[i].data);
        }
    }
    free(pet);
    free(listaS);
}

void exibirServicosCliente(){
	exibirClientes();
	
    int cod;
    printf("\nDigite o codigo do cliente: ");
    scanf("%d", &cod);
    
    Cliente* cliente = pesquisarClientePeloCodigo(cod);
    if (cliente == NULL){
        printf("\nNao encontramos nenhum cliente com esse codigo :(\n");
        return;
    }

    int totalServicos = 0;
    ServicoPrestado* listaS = listarServicosCliente(cod, &totalServicos);

    if (listaS == NULL || totalServicos == 0){
        printf("\nNao encontramos servicos prestados para o cliente de codigo %d.\n", cod);
        free(cliente);
		return;
    }
    
    printf("\n-- Lista Servicos Prestados [cliente de código %d] --\n\n", cod);
    int i, j, k;
    for (i = 0; i < totalServicos; i++){
        Servico servico;
        Pet pet;
        int encontrado = 0;
        for (j = 0; j < qServicos; j++){
            if (servicos[j].codigo == listaS[i].codigoServico){
                servico = servicos[j];
                encontrado = 1;
            }
        }
        for (k = 0; k < qPets; k++){
            if (pets[k].codigo == listaS[i].codigoPet){
                pet = pets[k];
            }
        }
        if (encontrado == 1) {
            printf("%d - Codigo: %d, Pet: %s, Nome: %s, Valor: %.2f, Data: %s\n", i+1, listaS[i].codigoServico, pet.nome, servico.nome, servico.valorCobrado, listaS[i].data);
        }
    }
    free(cliente);
    free(listaS);
}

void realizarServico(){
    ServicoPrestado servicoP;
    
    printf("Digite o codigo do pet: ");
    scanf("%d", &servicoP.codigoPet);

    Pet* pet = pesquisarPetPeloCodigo(servicoP.codigoPet);
    if (pet == NULL){
        printf("\nNao encontramos pet com esse codigo, tente novamente.\n");
        return;
    }
    
    printf("Digite o codigo do servico: ");
    scanf("%d", &servicoP.codigoServico);
 
    Servico* servico = pesquisarServicoPeloCodigo(servicoP.codigoServico);
    if (servico == NULL){
        printf("\nNao encontramos servico com esse codigo, tente novamente!.\n");
        return;
    }
    
    printf("Digite a data do servico (DD/MM/AAAA): ");
    scanf("%s", servicoP.data); 
    
    if (prestarServico(servicoP)){
        printf("\nServico prestado com sucesso!\n");
    } else {
        printf("\nERRO Ao prestar servico, tente novamente.\n");
    }
    free(pet);
    free(servico);
}

void exibirLucroServicos(){
    float lucroT = calcularLucroServicos();
    printf("\n-- Lucro dos Servicos --\n");
    printf("Lucro total: %.2f\n", lucroT);
}

void menu(){
	int opcao, opcaoSub;
	printf("\nBem-vindo ao Pantera Negra PetShop!\n");
	
    do{
    	printf("\n---------------------------------------");
        printf("\n\nO que desejas fazer?:\n\n");
        printf("0 - Sair\n");
        printf("1 - Gerenciar Clientes\n");
        printf("2 - Gerenciar Pets\n");
        printf("3 - Gerenciar Servicos\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 0:
                printf("\nSaindo...\n");
                break;
            case 1:
            	do{
            		printf("\n---------------------------------------");
            		printf("\n\nCLIENTES:\n\n");
	            	printf("0 - Voltar \n");
	            	printf("1 - Listar clientes\n");
	        		printf("2 - Cadastrar cliente\n");
	        		printf("3 - Pesquisar cliente por codigo\n");
	        		printf("4 - Pesquisar cliente por nome\n");
	        		printf("5 - Excluir cliente por codigo\n");
	        		printf("6 - Excluir cliente por nome\n");
	        		printf("7 - Atualizar cliente\n");
	        		printf("\n---------------------------------------");
	        		scanf("%d", &opcaoSub);
	        		switch(opcaoSub){
	        			case 0:
	        				break;
	        			case 1:
			                exibirClientes();
			                break;
			            case 2:
			                cadastroCliente();
			                break;
              			case 3:
              				buscarClientePeloCodigo();
              				break;
			            case 4:
			                buscarClientePeloNome();
			                break;
			            case 5:
			                apagarClientePeloCodigo();
			                break;
               			case 6:
               				apagarClientePeloNome();
               				break;
               			case 7:
               				updateCliente();
               				break;
	              		default:
	          				printf("Opcao invalida! Tente novamente.\n");
	                		break;	
					}
				}while(opcaoSub != 0);
            	break;
			case 2:
      			do{
      				printf("\n---------------------------------------");
	      			printf("\n\nPets:\n\n");
	      			printf("0 - Voltar\n");
					printf("1 - Listar pets\n");
	        		printf("2 - Cadastrar pet\n");
	        		printf("3 - Pesquisar pet por codigo\n");
					printf("4 - Pesquisar pet por especie\n");
					printf("5 - Excluir pet por codigo\n");
					printf("6 - Excluir pet por nome\n");
					printf("7 - Atualizar pet\n");
					printf("\n---------------------------------------");
	        		scanf("%d", &opcaoSub);
	        		switch(opcaoSub){
	        			case 0:
	        				break;
	        			case 1:
			                exibirPets();
			                break;
			            case 2:
			                cadastroPet();
			                break;
              			case 3:
              				buscarPetPeloCodigo();
              				break;
			            case 4:
			                buscarPetPelaEspecie();
			                break;
			            case 5:
			                apagarPetPeloCodigo();
			                break;
               			case 6:
               				apagarPetPeloNome();
               				break;
               			case 7:
               				updatePet();
               				break;
	              		default:
	          				printf("Opção invalida! Tente novamente.\n");
	                		break;
					}
				}while(opcaoSub != 0);
				break;
			case 3:
  				do{
  					printf("\n---------------------------------------");
	  				printf("\n\nServicos:\n\n");
	  				printf("0 - Voltar\n");
	  				printf("1 - Listar servicos\n");
			        printf("2 - Cadastrar servico\n");
			        printf("3 - Pesquisar servico\n");
			        printf("4 - Excluir servico\n");
			        printf("5 - Atualizar servico\n");
			        printf("6 - Listar servicos do pet\n");
			        printf("7 - Listar servicos do cliente\n");
			        printf("8 - Prestar servico\n");
			        printf("9 - Ver lucro dos servicos\n");
			        printf("\n---------------------------------------");
	        		scanf("%d", &opcaoSub);
	        		switch(opcaoSub){
	        			case 0:
	        				break;
	        			case 1:
			                exibirServicos();
			                break;
			            case 2:
			                cadastroServico();
			                break;
			            case 3:
			                buscarServicoPeloCodigo();
			                break;
			            case 4:
			                apagarServicoPeloCodigo();
			                break;
			            case 5:
			                updateServico();
			                break;
			            case 6:
			            	exibirServicosPet();
			                break;
			            case 7:
			            	exibirServicosCliente();
			            	break;
			            case 8:
			                realizarServico();
			                break;
			            case 9:
			                exibirLucroServicos();
			                break;
	              		default:
	          				printf("Opcao invalida! Tente novamente.\n");
	                		break;
					}
				}while(opcaoSub != 0);
				break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }	
	}while(opcao != 0);
}

int main(int argc, char *argv[]){
	
	
	
	if(!inicializarClientes()){
		printf("Erro ao inicializar clientes.\n");
		return 1;
	}
	if(!inicializarPets()){
		printf("Erro ao inicializar pets.\n");
		return 1;
	}
	if(!inicializarServicos()){
		printf("Erro ao inicializar servicos.\n");
		return 1;
		
	}
	if(!inicializarServicosPrestados()){
		printf("Erro ao inicializar servicos prestados.\n");
		return 1;
	}
    
	menu();
		
	encerraClientes();
	encerrarPets();
	encerrarServicos();
	encerrarServicosPrestados();
	return 0;
}
