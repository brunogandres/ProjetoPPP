#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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


typedef struct User2 *LUser2;
typedef struct User2{
    char morada[50], data_nascimento[15], telemovel[50];
    LUser2 next;
}UserData2;

typedef struct User *LUser;
typedef struct User{
    char nome[50], morada[50], data_nascimento[15], telemovel[50];
    LUser2 detalhes;
    LUser next;
}UserData;


/*cabeçalhos*/
void menu();
void registo();
void alterardados();
void ordemalfabetica(Lcidade lista);

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

LUser cria_lista_USERS (void);
LUser destroi_lista_USERS (LUser lista);
int lista_vazia_USERS(LUser lista);
void procura_lista_USERS (LUser lista, char chave[], LUser *ant, LUser *actual);
LUser insere_lista_USERS(LUser lista, char it[]);
void imprime_lista_USERS (LUser lista);


LUser2 cria_lista_USERS2(void);
LUser2 destroi_lista_USERS2 (LUser2 lista);
int lista_vazia_USERS2(LUser2 lista);
void procura_lista_USERS2 (LUser2 lista, char chave[], LUser2 *ant, LUser2 *actual);
void insere_lista_USERS2 (LUser2 lista, char it[]);
void imprime_lista_USERS2 (LUser2 lista);







//  Main

int main() {
    Lcidade lista_cidades;
    lista_cidades = cria_lista_CIDADES();//lista criada aqui caso seja precisa pra outras coisas
    LUser  lista_users = cria_lista_USERS();
    LUser2 lista_users_detalhes = cria_lista_USERS2();
    //menu();
    alterardados();
    //ordemalfabetica(lista_cidades);

}


void menu(){

        int n;
        printf("\n**********************************************");
        printf("\n\t\t\tBEM VINDO");
        printf("\n**********************************************");
        printf("\n1. Novo Registo");
        printf("\n2. Alterar Dados");
        printf("\n3. Sair");
        printf("\n**********************************************");
        printf("\nPlease enter your option< 1 / 2 / 3 >: ");
        scanf("%d", &n);

        switch(n){
            case 1:
                registo();

            case 2:
                alterardados();
                break;
            case 3:
                printf("\n*** Obrigado por usar o programa. ***");
                exit(0);
                break;
            default:
                printf("\nErro! Numero Errado\nTente outra vez");
                menu();

                break;
        }
}

/* REGISTO E GUARDA NUM FICHEIRO*/
void registo(){


    UserData user1;
    printf("\n\t ####REGISTO####\n");
    printf("Nome: ");
    gets(user1.nome);
    printf("\nMorada: ");
    gets(user1.morada);
    printf("\nData de Nascimento: ");
    gets(user1.data_nascimento);
    printf("Telemovel: ");
    gets(user1.telemovel);



    FILE *userdados = fopen("C:\\Users\\Utilizador\\Desktop\\Projeto\\Dados.txt", "a");

    fprintf(userdados, "*%s\n", user1.nome);
    fprintf(userdados, "%s\n", user1.morada);
    fprintf(userdados, "%s\n", user1.data_nascimento);
    fprintf(userdados, "%s\n", user1.telemovel);
    printf("\nSYSTEM: Registado com Sucesso.");

    fclose(userdados);

}
void alterardados() {
    LUser user1;
    LUser utilizador;
    char linha[256], *nome;
    int i, contador = 0;
    int len_frase;
    int len;
    FILE *userdados = fopen("C:\\Users\\Utilizador\\Desktop\\Projeto\\Dados.txt", "r");
    FILE *userdados2 = fopen("C:\\Users\\Utilizador\\Desktop\\Projeto\\DadosCopia.txt", "a");
    char aux[len];
    printf("Nome: ");
    gets(user1->nome);

    for (i = 1; fgets(linha, 256, userdados) != NULL; i++) {
        len_frase = strlen(linha);
        if (linha[len_frase - 1] == '\n') {
            linha[len_frase - 1] = '\0';
        }
        if(contador == 3) {
            contador = 0;
        }
        else if(contador == 0)
        {
            fprintf(userdados2, "%s\n", linha);
            if(strcmp(linha+1,user1->nome) == 0)
            {
                contador++;
                printf("Morada: ");
                gets(user1->morada);
                fprintf(userdados2, "%s\n", user1 -> morada);
                printf("Data de Nascimento: ");
                gets(user1 ->data_nascimento);
                fprintf(userdados2, "%s\n", user1 -> data_nascimento);
                printf("Telemovel: ");
                gets(user1 ->telemovel);
                fprintf(userdados2, "%s\n", user1 -> telemovel);
            }
        }

        else
            contador+=1;
    }
    fclose(userdados);
    fclose(userdados2);
    unlink("C:\\Users\\Utilizador\\Desktop\\Projeto\\Dados.txt");
    rename("C:\\Users\\Utilizador\\Desktop\\Projeto\\DadosCopia.txt", "C:\\Users\\Utilizador\\Desktop\\Projeto\\Dados.txt");
    printf("\nSYSTEM: Utilizador alterado com Sucesso.");

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



void preferencias(){

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
        printf("\t• %s", l->nome);
        l=l->next;
    }
}



//LISTA USERS



LUser cria_lista_USERS (void) {
    LUser aux;
    aux = (LUser) malloc (sizeof (UserData));
    if (aux != NULL) {
        strcpy(aux->nome, "");
        aux->detalhes = cria_lista_USERS2();
        aux->next = NULL;
    }
    return aux;
}
LUser destroi_lista_USERS (LUser lista) {
    LUser temp_ptr;
    while (lista_vazia_USERS(lista) == 0) {
        temp_ptr = lista;
        lista= lista->next; free (temp_ptr);
    }
    free(lista);
    return NULL;
}
int lista_vazia_USERS(LUser lista) {
    return (lista->next == NULL ? 1 : 0);
}
void procura_lista_USERS (LUser lista, char chave[], LUser *ant, LUser *actual) {
    *ant = lista;
    *actual = lista->next;
    while ((*actual) != NULL && strcmp((*actual)->nome, chave) < 0) {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && strcmp((*actual)->nome, chave))
        *actual = NULL;
}

LUser insere_lista_USERS(LUser lista, char it[]) {
    LUser no;
    LUser ant, inutil;
    no = (LUser) malloc (sizeof (UserData));//reserva espaço para o nó
    if (no != NULL) {
        strcpy(no->nome, it);
        procura_lista_USERS (lista, it, &ant, &inutil);
        no->detalhes = cria_lista_USERS2();
        no->next = ant->next;
        ant->next = no;
    }
    return no;
}
void imprime_lista_USERS (LUser lista) {
    LUser l = lista->next; /* Salta o header */
    while (l) {
        printf("%s\n", l->nome);
        imprime_lista_USERS2(l->detalhes);
        l=l->next;
    }
}



//lista para os detalhes LUSERS2



LUser2 cria_lista_USERS2 (void) {
    LUser2 aux;
    aux = (LUser2) malloc (sizeof (UserData2));
    if (aux != NULL) {
        strcpy(aux->morada, "");
        strcpy(aux->data_nascimento, "");
        strcpy(aux->telemovel, "");
        aux->next = NULL;
    }
    return aux;
}

LUser2 destroi_lista_USERS2 (LUser2 lista) {
    LUser2 temp_ptr;
    while (lista_vazia_USERS2(lista) == 0) {
        temp_ptr = lista;
        lista= lista->next; free (temp_ptr);
    }
    free(lista);
    return NULL;

}
int lista_vazia_USERS2(LUser2 lista) {
    return (lista->next == NULL ? 1 : 0);
}
void procura_lista_USERS2 (LUser2 lista, char chave[], LUser2 *ant, LUser2 *actual) {
    *ant = lista;
    *actual = lista->next;
    while ((*actual) != NULL && strcmp((*actual)->morada, chave) < 0) {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && strcmp((*actual)->morada, chave))
        *actual = NULL;
}
void insere_lista_USERS2 (LUser2 lista, char it[]) {
    LUser2 no ;
    LUser2 ant, inutil;
    no = (LUser2) malloc (sizeof (UserData2));
    if (no != NULL) {
        strcpy(no->morada, it);
        procura_lista_USERS2(lista, it, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}
void imprime_lista_USERS2 (LUser2 lista) {
    LUser2 l = lista->next; /* Salta o header */
    while (l) {
        printf("%s", l->morada);
        printf("%s", l->data_nascimento);
        printf("%s", l->telemovel);
        l=l->next;
    }
}
