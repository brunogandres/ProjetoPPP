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
    char nome_cidade[100];
    LPdI pontos;
    Lcidade next;
}Cidades;



typedef struct User *LUser;
typedef struct User{
    char nome[50], morada[50], data_nascimento[15], telemovel[50];
    Lcidade prefLocal1;
    Lcidade prefLocal2;
    Lcidade prefLocal3;
    LPdI prefPontos;
    LPdI hot;
    LUser next;
}UserData;


/*cabeçalhos*/
void menu(LUser lista);
void registo(LUser lista);
void alterardados();
void carrega_listaCidades_ficheiro(Lcidade lista);

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

//LUser cria_lista_USERS (UserData user);
LUser cria_lista_USERS (void);
LUser destroi_lista_USERS (LUser lista);
int lista_vazia_USERS(LUser lista);
void procura_lista_USERS (LUser lista, char chave[], LUser *ant, LUser *actual);
void insere_lista_USERS (LUser lista, UserData  user);
void imprime_lista_USERS (LUser lista);

void carrega_listaUsers_ficheiro(LUser lista, char *nomeFicheiroUsers, Lcidade listaC);
void grava_listaUsers_ficheiro(LUser lista, char *nomeFicheiroUsers);
void getUserPrefCidades(char *linha, char *pref1, char *pref2, char *pref3);
Lcidade getNoCidade(Lcidade listaC, char *pref);



//  Main

int main() {
    Lcidade lista_cidades;
    LUser lista_users;
    char ficheiroUsers[] =  "C:\\Users\\Utilizador\\Desktop\\Projeto\\Dados.txt";
    lista_cidades = cria_lista_CIDADES();//lista criada aqui caso seja precisa pra outras coisas
    lista_users = cria_lista_USERS();
    carrega_listaCidades_ficheiro(lista_cidades);

    carrega_listaUsers_ficheiro(lista_users, ficheiroUsers, lista_cidades);

    //menu(lista_users);
    //gravar para ficheiros a lista utilizadores

    //registo(lista_users);

    //grava_listaUsers_ficheiro(lista_users, ficheiroUsers);
    //DEPOIS DE GRAVAR É PRECISO FAZER O FREE DAS LISTAS
    //alterardados();
    //


}


void menu(LUser lista){

    int n;
    printf("\n**********************************************");
    printf("\n\t\t\tBEM VINDO");
    printf("\n**********************************************");
    printf("\n1. Novo Registo");
    printf("\n2. Alterar Dados");
    printf("\n3. Sair");
    printf("\n**********************************************\n");
    printf("Escolha uma opcao: < 1 / 2 / 3 >: ");
    fflush(stdin);
    scanf("%d", &n);

    switch(n){
        case 1:
            registo(lista);
            break;
        case 2:
            alterardados();
            break;
        case 3:
            printf("\n*** Obrigado por usar o programa. ***");

            break;
        default:
            printf("\nErro! Numero Errado\nTente outra vez");

            break;
    }
}


void carrega_listaUsers_ficheiro(LUser lista, char *nomeFicheiroUsers, Lcidade listaC) {
    char linha[256];
    char pref1[100], pref2[100], pref3[100];
    int i, contador = 0, len_frase;
    LUser noUser = NULL;

    UserData tempUser; //estrutura temporaria para guardar as informacoes
    FILE *ficheiroDados = fopen(nomeFicheiroUsers, "r");


    if(ficheiroDados != NULL) {
        for (i = 0; fgets(linha, 256, ficheiroDados); i++) {
            len_frase = strlen(linha);
            if (linha[len_frase - 1] == '\n') {
                linha[len_frase - 1] = '\0';
            }

            if (linha[0] == '*')
            {
                if (contador != 0)
                {
                    insere_lista_USERS(lista, tempUser);
                }
                strcpy(tempUser.nome, linha + 1);
                contador = 1;

            } else{
                switch (contador)
                {
                    case 1:
                        strcpy(tempUser.morada, linha);
                        contador++;
                        break;
                    case 2:
                        strcpy(tempUser.data_nascimento, linha);
                        contador++;
                        break;
                    case 3:
                        strcpy(tempUser.telemovel, linha);
                        contador++;

                        break;
                    case 4:
                        //Obter as preferencias
                        getUserPrefCidades(linha, pref1, pref2, pref3);
                        tempUser.prefLocal1 = getNoCidade(listaC, pref1);
                        tempUser.prefLocal2 = getNoCidade(listaC, pref2);
                        tempUser.prefLocal3 = getNoCidade(listaC, pref3);
                        printf("\nPreferencia : %s- %s-%s-%s", tempUser.prefLocal1->nome_cidade,tempUser.prefLocal2->nome_cidade, tempUser.prefLocal3->nome_cidade);
                        contador++;

                }

            }
        }
        insere_lista_USERS(lista, tempUser);
    }
}
void getUserPrefCidades(char *linha, char *pref1, char *pref2, char *pref3)
{
    char barra[] = "|";
    strcpy(pref1,strtok(linha, barra));
    strcpy(pref2,strtok(NULL, barra));
    strcpy(pref3,strtok(NULL, barra));
}

Lcidade getNoCidade(Lcidade listaC, char *pref){
    Lcidade l = listaC->next;
    int i, len_frase = strlen(pref), len_frase1;
    if(strcmp(pref, " ") == 0){
        return NULL;
    }
    while (l)
    {
        if(strcmp(l->nome_cidade, pref) == 0){
            return l;
        }
        else
            l = l->next;
    }
}
void grava_listaUsers_ficheiro(LUser lista, char *nomeFicheiroUsers)
{
    FILE *dados = fopen(nomeFicheiroUsers, "w");
    LUser l = lista->next;
    while (l != NULL)
    {
        fprintf(dados, "*%s\n", l->nome);
        fprintf(dados, "%s\n", l->morada);
        fprintf(dados, "%s\n", l->data_nascimento);
        fprintf(dados, "%s\n", l->telemovel);
        l = l->next;
    }
}


/* REGISTO E GUARDA NUM FICHEIRO*/
void registo(LUser lista){

    UserData user;

    printf("\n\t ####REGISTO####");
    printf("\n");
    printf("Nome:");
    gets(user.nome);
    printf("\nMorada: ");
    gets(user.morada);
    printf("\nData de Nascimento: ");
    gets(user.data_nascimento);
    printf("Telemovel: ");
    gets(user.telemovel);

    insere_lista_USERS(lista, user);
}





void alterardados() {

}




void carrega_listaCidades_ficheiro(Lcidade lista) {
    int i, len;
    char leitura[256];
    FILE *cidades = fopen("C:\\Users\\Utilizador\\Desktop\\Projeto\\Cidades.txt", "r");
    Lcidade noLocal = NULL;//ponteiro para correr cada nó da lista de cidades


    for (i = 0; fgets(leitura, 256, cidades)!=NULL; i++){

        if (leitura[0] == '*' ) {
            len = strlen(leitura);
            if(leitura[len-1] == '\n')
                leitura[len - 1] = '\0';
            noLocal = insere_lista_CIDADES(lista, leitura + 1);
        }
        else {
            insere_lista_PDIS(noLocal->pontos, leitura+1);
        }
    }
    //imprime_lista_CIDADES(lista);
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
        printf("%s", l->nome_cidade);
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
        l = l->next;
    }
}



//LISTA USERS

LUser cria_lista_USERS (void) {
    LUser aux;
    aux = (LUser) malloc (sizeof (UserData));
    if (aux != NULL) {
        strcpy(aux->nome, "");
        strcpy(aux->morada, "");
        strcpy(aux->data_nascimento, "");
        strcpy(aux->telemovel, "");
        aux->prefLocal1 = NULL;
        aux->prefLocal2 = NULL;
        aux->prefLocal3 = NULL;
        aux->prefPontos = NULL;

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

void procura_lista_USERS (LUser lista, char chave[], LUser *ant, LUser *actual)
{
    *ant = lista;
    *actual = lista->next;
    while ((*actual) != NULL && (*actual)->nome < chave)
    {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && (*actual)->nome != chave)
        *actual = NULL;   /* Se elemento não encontrado*/
}
void insere_lista_USERS (LUser lista, UserData  user) {
    LUser no ;
    LUser ultimo, anterior;


    no = (LUser) malloc (sizeof (UserData));
    if (no != NULL) {
        strcpy(no->nome, user.nome);
        strcpy(no->morada, user.morada);
        strcpy(no->data_nascimento, user.data_nascimento);
        strcpy(no->telemovel, user.telemovel);
        no->next = NULL;
    }

    // introduzir na lista
    if(lista->next == NULL)
    {
        lista->next = no;
    }
    else  //encontrar o ultimo da lista e inserir o no no fim
    {
        anterior = lista;
        ultimo = lista->next; /* Salta o header */
        while (ultimo)
        {
            anterior = ultimo;
            ultimo = ultimo->next;
        }
        anterior->next = no;
    }
}
void imprime_lista_USERS (LUser lista) {
    LUser l = lista->next; /* Salta o header */
    while (l) {
        printf("%s\n", l->nome);
        printf("%s\n", l->morada);
        printf("%s\n", l->data_nascimento);
        printf("%s\n", l->telemovel);
        l = l->next;
    }
}
