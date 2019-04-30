#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PdI *LPdI;
typedef struct PdI{
    char nome[50], descricao[200], horario[25];
    LPdI next;
}Ponto_Interesse;

typedef struct cidade *Lcidade;
typedef struct cidade{
    char nome_cidade[100], descricao_cidade[50];
    LPdI pontos;
    Lcidade next;
}Cidades;

typedef struct User *LUser;
typedef struct User{
    char nome[50], morada[50], data_nascimento[15], telemovel[50];
    LUser next;
}UserData;


/*cabeçalhos*/
void lerficheiro();
void registo();
void ordemalfabetica();
Lcidade cria_lista_CIDADES(void);
int lista_vazia_CIDADES(Lcidade lista);
void procura_lista_CIDADES(Lcidade lista, char *chave, Lcidade *ant, Lcidade *actual);
Lcidade insere_lista_CIDADES(Lcidade lista, char *it);
void imprime_lista_CIDADES (Lcidade lista);
LPdI cria_lista_PDIS (void);
LPdI destroi_lista_PDIS (LPdI lista);
int lista_vazia_PDIS(LPdI lista);
void procura_lista_PDIS (LPdI lista, char *chave, LPdI *ant, LPdI *actual);
void imprime_lista_PDIS (LPdI lista);
void insere_lista_PDIS (LPdI lista, char *it);



//  Main

int main() {
    Lcidade lista_cidades;
    lista_cidades = cria_lista_CIDADES();

    ordemalfabetica(lista_cidades);

}
/* REGISTO E GUARDA NUM FICHEIRO*/
void registo()
{
    FILE *userdados;
    UserData user1;
    printf("Nome: ");
    gets(user1.nome);
    printf("Morada: ");
    gets(user1.morada);
    printf("Data de Nascimento: ");
    gets(user1.data_nascimento);
    printf("Telemovel: ");
    gets(user1.telemovel);



    userdados = fopen("C:\\Users\\Utilizador\\Desktop\\Projeto\\Dados.txt", "a");
    fprintf(userdados, "%s|", user1.nome);
    fprintf(userdados, "%s|", user1.morada);
    fprintf(userdados, "%s|", user1.data_nascimento);
    fprintf(userdados, "%s", user1.telemovel);
    fprintf(userdados, "\n");

    fclose(userdados);

}
void ordemalfabetica(Lcidade lista) {
    int i;
    char leitura[256];
    FILE *cidades = fopen("C:\\Users\\Utilizador\\Desktop\\Projeto\\Cidades.txt", "r");

    Lcidade noLocal = NULL;//ponteiro para correr cada nó da lista de cidades


    for (i = 0; fgets(leitura, 256, cidades)!=NULL; i++){
        if (leitura[0] == '*') {
            noLocal = insere_lista_CIDADES(lista, leitura + 1);
        }
        else {
            insere_lista_PDIS(noLocal->pontos, leitura+1);
        }
    }
    imprime_lista_CIDADES(lista);
    fclose(cidades);
}




//Lista ligada para as cidades

Lcidade cria_lista_CIDADES (void) {
    Lcidade aux;
    aux = (Lcidade) malloc (sizeof (Cidades));
    if (aux != NULL) {
        strcpy(aux->nome_cidade, "");
        aux->pontos = cria_lista_PDIS();
        aux->next = NULL;
    }
    return aux;
}
Lcidade destroi_lista_CIDADES (Lcidade lista) {
    Lcidade temp_ptr;
    while (lista_vazia_CIDADES(lista) == 0) {
        temp_ptr = lista;
        lista= lista->next; free (temp_ptr);
    }
    free(lista);
    return NULL;
}
int lista_vazia_CIDADES(Lcidade lista) {
    return (lista->next == NULL ? 1 : 0);
}
void procura_lista_CIDADES (Lcidade lista, char chave[], Lcidade *ant, Lcidade *actual) {
    *ant = lista;
    *actual = lista->next;
    while ((*actual) != NULL && strcmp((*actual)->nome_cidade, chave) < 0) {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && strcmp((*actual)->nome_cidade, chave))
        *actual = NULL;
}
Lcidade insere_lista_CIDADES(Lcidade lista, char it[]) {
    Lcidade no;
    Lcidade ant, inutil;
    no = (Lcidade) malloc (sizeof (Cidades));//reserva espaço para o nó
    if (no != NULL) {
        strcpy(no->nome_cidade, it);
        procura_lista_CIDADES (lista, it, &ant, &inutil);
        no->pontos = cria_lista_PDIS();
        no->next = ant->next;
        ant->next = no;
    }
    return no;
}
void imprime_lista_CIDADES (Lcidade lista) {
    Lcidade l = lista->next; /* Salta o header */
    while (l) {
        printf("%s ", l->nome_cidade);
        imprime_lista_PDIS(l->pontos);
        l=l->next;
    }
}


/*LISTA LIGADA PARA OS PONTOS DE INTERESSE*/

LPdI cria_lista_PDIS (void) {
    LPdI aux;
    aux = (LPdI) malloc (sizeof (Ponto_Interesse));
    if (aux != NULL) {
        strcpy(aux->nome, "");
        strcpy(aux->descricao, "");
        strcpy(aux->horario, "");
        aux->next = NULL;
    }
    return aux;
}
LPdI destroi_lista_PDIS (LPdI lista) {
    LPdI temp_ptr;
    while (lista_vazia_PDIS(lista) == 0) {
        temp_ptr = lista;
        lista= lista->next; free (temp_ptr);
    }
    free(lista);
    return NULL;

}
int lista_vazia_PDIS(LPdI lista) {
    return (lista->next == NULL ? 1 : 0);
}
void procura_lista_PDIS (LPdI lista, char chave[], LPdI *ant, LPdI *actual) {
    *ant = lista;
    *actual = lista->next;
    while ((*actual) != NULL && strcmp((*actual)->nome, chave) < 0) {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && strcmp((*actual)->nome, chave))
        *actual = NULL;
}
void insere_lista_PDIS (LPdI lista, char it[]) {
    LPdI no ;
    LPdI ant, inutil;
    no = (LPdI) malloc (sizeof (Ponto_Interesse));
    if (no != NULL) {
        strcpy(no->nome, it);
        procura_lista_PDIS (lista, it, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}
void imprime_lista_PDIS (LPdI lista) {
    LPdI l = lista->next; /* Salta o header */
    while (l) {
        printf("%s ", l->nome);
        l=l->next;
    }
}
