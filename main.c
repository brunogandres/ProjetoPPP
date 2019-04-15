#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*o gandres chupa piças*/

typedef struct PdI *LPdI;
typedef struct PdI{
    char nome[50], descricao[200], horario[25];
    LPdI proximo;
}Ponto_Interesse;

typedef struct cidade *Lcidade;
typedef struct cidade{
    char nome_cidade[50], escricao_cidade[50];
    LPdI pontos;
    Lcidade proximo;
}Cidades;

typedef struct User *LUser;
typedef struct User{
    char nome[50], morada[50], data_nascimento[15], telemovel[50];
    LUser next;
}UserData;

typedef struct lnode *List;
typedef struct lnode {
    char *info;
    List next;
} List_node;

/*cabeçalhos*/
void lerficheiro();
void registo();
void ordemalfabetica();
List cria_lista (void);
List destroi_lista (List lista);
void elimina_lista (List lista, char *it);
void insere_lista (List lista, char *it);
void imprime_lista (List lista);
int lista_vazia(List lista);
void procura_lista (List lista, char *chave, List *ant, List *actual);
List pesquisa_lista (List lista, char *it);

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



    userdados = fopen("C:\\Users\\Bruno Gandres\\Desktop\\Projeto\\Dados.txt", "a");
    fprintf(userdados, "%s|", user1.nome);
    fprintf(userdados, "%s|", user1.morada);
    fprintf(userdados, "%s|", user1.data_nascimento);
    fprintf(userdados, "%s", user1.telemovel);
    fprintf(userdados, "\n");

    fclose(userdados);
}
void ordemalfabetica() {
    List lista;
    FILE *cidades = fopen("C:\\Users\\Bruno Gandres\\Desktop\\Projeto\\Cidades.txt", "r");
    int i, len;
    char leitura[50];
    lista = cria_lista();
    for (i = 0; fgets(leitura, 256, cidades); i++) {
        if(leitura[0] == '*'){
            insere_lista(lista, leitura);
        }
    }
    fclose(cidades);
    imprime_lista(lista);
}



/*CRIAR LISTA LIGADA*/
List cria_lista (void){
    List aux;
    aux = (List) malloc (sizeof (List_node));
    if (aux != NULL) {
        aux->info = 0;
        aux->next = NULL;
    }
    return aux;
}
List destroi_lista (List lista){
    List temp_ptr;
    while (lista_vazia (lista) == 0) {
        temp_ptr = lista;
        lista= lista->next;
        free (temp_ptr);
    }
    free(lista);
    return NULL;
}
void elimina_lista (List lista, char *it){
    List ant;
    List actual;
    procura_lista (lista, it, &ant, &actual);
    if (actual != NULL) {
        ant->next = actual->next;
        free (actual);
    }
}
void insere_lista (List lista, char *it){
    List no;
    List ant, inutil;
    no = (List) malloc (sizeof (List_node));
    if (no != NULL) {
        no->info = (char *) malloc (sizeof(char) * strlen(it));
        strcpy(no -> info, it);
        procura_lista (lista, it, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}
void imprime_lista (List lista){
    List l = lista->next; /* Salta o header */
    while (l){
        printf("%s ", l->info);
        l=l->next;
    }
}
int lista_vazia(List lista){
    return (lista->next == NULL ? 1 : 0);
}
void procura_lista (List lista, char *chave, List *ant, List *actual){
    *ant = lista; *actual = lista->next;
    while (((*actual) != NULL && strcmp((*actual)->info, chave)) == -1){
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && strcmp((*actual)->info, chave) != 0)
        actual = NULL; /* Se elemento não encontrado*/
}
List pesquisa_lista (List lista, char *it){
    List ant;
    List actual;
    procura_lista (lista, it, &ant, &actual);
    return (actual);
}
