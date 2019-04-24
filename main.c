#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PdI *LPdI;
typedef struct PdI{
    char nome[50], descricao[200], horario[25];
    LPdI proximo;
}Ponto_Interesse;

typedef struct cidade *Lcidade;
typedef struct cidade{
    char nome_cidade[50], escricao_cidade[50];
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
void insere_lista_CIDADES(Lcidade lista, char *it);
void imprime_lista_CIDADES (Lcidade lista);


        int main() {

    ordemalfabetica();
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
void ordemalfabetica() {
    Lcidade lista;
    int i, j, len;
    lista = cria_lista_CIDADES();
    FILE *cidades = fopen("C:\\Users\\Utilizador\\Desktop\\Projeto\\Cidades.txt", "r");

    char leitura[50];

    for (i = 0; fgets(leitura, 256, cidades); i++) {
        if(leitura[0] == '*'){
            insere_lista_CIDADES(lista, leitura + 1);
            }
        }
    fclose(cidades);
    imprime_lista_CIDADES(lista);
}





/*CRIAR LISTA LIGADA*/
Lcidade cria_lista_CIDADES (void) {
    Lcidade aux;
    aux = (Lcidade) malloc (sizeof (Cidades));
    if (aux != NULL) {
        aux->nome_cidade = ' ';
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
void procura_lista_CIDADES (Lcidade lista, char *chave, Lcidade *ant, Lcidade *actual) {
    *ant = lista;
    *actual = lista->next;
    while ((*actual) != NULL && strcmp((*actual)->nome_cidade, chave) < 0) {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && strcmp((*actual)->nome_cidade, chave))
        *actual = NULL;
}
void insere_lista_CIDADES(Lcidade lista, char *it) {
    Lcidade no;
    Lcidade ant, inutil;
    no = (Lcidade) malloc (sizeof (Cidades));
    if (no != NULL) {
        strcpy(no->nome_cidade, it);
        procura_lista_CIDADES (lista, it, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}
void imprime_lista_CIDADES (Lcidade lista) {
    Lcidade l = lista->next; /* Salta o header */
    while (l) {
        printf("%s ", l->nome_cidade);
        l=l->next;
    }
}
