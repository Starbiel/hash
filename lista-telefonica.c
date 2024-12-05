#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 100

typedef struct Contact {
    char name[50];
    char phone[20];
    struct Contact* next;
} Contact;

Contact* hashTable[TABLE_SIZE] = {NULL};

unsigned int hashFunction(char* name) {
    unsigned int hash = 0;
    while (*name) {
        hash += *name++;
    }
    return hash % TABLE_SIZE;
}

void adicionarContato() {
    char name[50];
    char phone[20];

    printf("Nome: ");
    scanf(" %[^\n]", name);
    printf("Telefone: ");
    scanf(" %[^\n]", phone);

    unsigned int index = hashFunction(name);

    Contact* temp = hashTable[index];
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("Contato ja existe. Atualizando o numero de telefone.\n");
            strcpy(temp->phone, phone);
            return;
        }
        temp = temp->next;
    }

    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    if (!newContact) {
        printf("Erro ao alocar memoria.\n");
        return;
    }
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    newContact->next = hashTable[index];
    hashTable[index] = newContact;

    printf("Contato adicionado com sucesso.\n");
}

void buscarContato() {
    char name[50];
    printf("Nome: ");
    scanf(" %[^\n]", name);

    unsigned int index = hashFunction(name);
    Contact* temp = hashTable[index];

    clock_t start = clock();

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            clock_t end = clock();
            double time_spent = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
            printf("Telefone de %s: %s (tempo de busca: %.2f ms)\n", temp->name, temp->phone, time_spent);
            return;
        }
        temp = temp->next;
    }

    clock_t end = clock();
    double time_spent = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("Contato nao encontrado. (tempo de busca: %.2f ms)\n", time_spent);
}

void removerContato() {
    char name[50];
    printf("Nome: ");
    scanf(" %[^\n]", name);

    unsigned int index = hashFunction(name);
    Contact* temp = hashTable[index];
    Contact* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            if (prev == NULL) {
                hashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Contato removido com sucesso.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Contato nao encontrado.\n");
}

void exibirContatos() {
    printf("\nLista de contatos:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Contact* temp = hashTable[i];
        while (temp != NULL) {
            printf("Nome: %s, Telefone: %s\n", temp->name, temp->phone);
            temp = temp->next;
        }
    }
}

int main() {
    int opcao;
    clock_t start, end;
    double totalInsertTime = 0.0;
    int insertCount = 0;

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                start = clock();
                adicionarContato();
                end = clock();
                totalInsertTime += ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
                insertCount++;
                break;
            case 2:
                buscarContato();
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    if (insertCount > 0) {
        printf("Tempo medio de insercao: %.2f ms\n", totalInsertTime / insertCount);
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        Contact* temp = hashTable[i];
        while (temp != NULL) {
            Contact* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }

    return 0;
}
