#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50
typedef struct PdI *LPdI;
typedef struct PdI {
    char nome[N], descricao[200], horario[25];
    LPdI next;
}Ponto_Interesse;

typedef struct cidade *Lcidade;
typedef struct cidade {
    char nome_cidade[100];
    LPdI pontos;
    Lcidade next;
}Cidades;

typedef struct prefPdi *LprefPdi;
typedef struct prefPdi {
    LPdI prefPdi;
    LprefPdi next;
}Ponto_Interesse_Pref;


typedef struct User *LUser;
typedef struct User {
    char nome[N], morada[50], data_nascimento[15], telemovel[50];
    Lcidade prefLocal1;
    Lcidade prefLocal2;
    Lcidade prefLocal3;
    LprefPdi prefPontos;
    LPdI hot;
    LUser next;
}UserData;


/*cabeçalhos*/
int menu(LUser user);
void registo(LUser lista);
LUser login(LUser lista, char *nome);
void alterardados();
void listar_DadosUser(LUser lista, LUser user);

Lcidade cria_lista_CIDADES(void);
int lista_vazia_CIDADES(Lcidade lista);
void procura_lista_CIDADES(Lcidade lista, char *chave, Lcidade *ant, Lcidade *actual);
Lcidade insere_lista_CIDADES(Lcidade lista, char *it);
void imprime_lista_CIDADES(Lcidade lista);
void carrega_listaCidades_ficheiro(char *nomeFicheiro, Lcidade lista);

LPdI cria_lista_PDIS(void);
LPdI destroi_lista_PDIS(LPdI lista);
int lista_vazia_PDIS(LPdI lista);
void procura_lista_PDIS(LPdI lista, char *chave, LPdI *ant, LPdI *actual);
void imprime_lista_PDIS(LPdI lista);
void insere_lista_PDIS(LPdI lista, char *it);

//LUser cria_lista_USERS (UserData user);
LUser cria_lista_USERS(void);
LUser destroi_lista_USERS(LUser lista);
int lista_vazia_USERS(LUser lista);
void procura_lista_USERS(LUser lista, char chave[], LUser *ant, LUser *actual);
LUser insere_lista_USERS(LUser lista, UserData  user);
void imprime_lista_USERS(LUser lista);
LUser carrega_listaUsers_ficheiro(char *nomeFicheiroUsers, Lcidade listaC);
void grava_listaUsers_ficheiro(LUser lista, char *nomeFicheiroUsers);

void getUserPrefCidades(char *linha, char *pref1, char *pref2, char *pref3);
Lcidade getNoCidade(Lcidade listaC, char *cidade);
LPdI getNoPDI(Lcidade listaC, char *pdi);
LUser getNoUser(LUser listaU, char *nome);

LprefPdi cria_lista_PrefPDIs(Lcidade listaC, char *pdis);
void imprime_lista_PrefPDIs(LprefPdi lista);


void alterar_PDIHOT(LUser lista, Lcidade listaC, LUser user);
void alterar_PrefLocais(LUser lista, Lcidade listaC, LUser user);

//  Main

int main() {
    Lcidade listaCidades;
    LUser listaUsers = NULL;//lista começa a NULL
    char ficheiroUsers[] = "C:\\Users\\Utilizador\\Desktop\\novo\\Dados.txt";
    char ficheiroCidades[] = "C:\\Users\\Utilizador\\Desktop\\novo\\Cidades.txt";

    //char ficheiroUsers[] = "Dados.txt";
    //char ficheiroCidades[] = "Cidades.txt";
    int opcaoMenu;
    char nome[N];
    LUser userLogado = NULL;

    listaCidades = cria_lista_CIDADES();//lista criada aqui caso seja precisa pra outras coisas
    carrega_listaCidades_ficheiro(ficheiroCidades, listaCidades);
    listaUsers = carrega_listaUsers_ficheiro(ficheiroUsers, listaCidades);


    do {
        opcaoMenu = menu(userLogado);
        switch (opcaoMenu) {
            case 1:
                registo(listaUsers);
                break;
            case 2:
                printf("Introduza o nome: ");
                gets(nome);
                userLogado=login(listaUsers, nome);
                break;
            case 3:
                listar_DadosUser(listaUsers, userLogado);
                break;
            case 5:
                alterar_PDIHOT(listaUsers, listaCidades, userLogado);
                break;
            case 6:

                alterar_PrefLocais(listaUsers, listaCidades, userLogado);
                break;
            case 8:
                imprime_lista_USERS(listaUsers);
                break;
            case 9:
                imprime_lista_CIDADES(listaCidades);
                break;
            case 12:
                printf("\n*** Obrigado por usar o programa. ***");
                break;
            default:
                printf("\nErro! Numero Errado\nTente outra vez");
                break;
        }
    } while (opcaoMenu != 12);



    grava_listaUsers_ficheiro(listaUsers, ficheiroUsers);
    //DEPOIS DE GRAVAR É PRECISO FAZER O FREE DAS LISTAS
    //alterardados();
    //


}

int menu(LUser user) {
    int n;
    printf("\n********************************************************");
    printf("\n\t\tBEM VINDO ");
    if (user != NULL)
        printf("%s", user->nome);
    printf("\n********************************************************");
    printf("\n1. Registar Utilizadores     DONE!");
    printf("\n2. Efetuar Login ");
    printf("\n3. Listar dados do utilizador   DONE!");
    printf("\n4. Alterar dados do utilizador"); // AQui dentro pode
    printf("\n5. Alterar PDI HOT do utilizador    DONE");
    printf("\n6. Alterar preferencias de locais do utilizador (Por Nome)");
    printf("\n7. Alterar preferencias de PDIs do utilizador (Por Nome)");
    printf("\n8. Listar todos utilizadores e respectivos dados   DONE!");
    printf("\n9. Listar Locais e seus Pontos de Interesse (Ordenada)     DONE!");
    printf("\n10. Listar Locais e PDIs mais populares");
    printf("\n11. Gerar Viagem e Ver Avaliacao");
    printf("\n12. Sair");
    printf("\n********************************************************");
    printf("\nEscolha uma opcao: ");
    scanf("%d", &n);
    getc(stdin);
    return n;
}
void alterar_PrefLocais(LUser lista, Lcidade listaC, LUser user){
    //Lcidade NovoLocalPreferido = getNoCidade(listaC);
    if(user->prefLocal1!=NULL) {
        printf("Local de Preferencia ATUAL: %s\n", user->prefLocal1->nome_cidade);
        if(user->prefLocal2!=NULL) {
            printf("Local de Preferencia ATUAL: %s\n", user->prefLocal2->nome_cidade);
            if(user->prefLocal3!=NULL)
                printf("Local de Preferencia ATUAL: %s\n", user->prefLocal3->nome_cidade);
        }
    }
    else{
        printf("Nao tem locais preferidos\n");
    }
    printf("Introduza o novo Local Preferido: ");

}


void alterar_PDIHOT(LUser lista, Lcidade listaC, LUser user){
    LPdI aux;
    char nomeNovoHot[N];
    printf("PDI HOT ATUAL: ");
    if(user->hot == NULL){
        printf("Nao tem Ponto de Interesse HOT");

    }
    else {
        printf("%s", user->hot->nome);
    }
    printf("\nPDI HOT NOVO: ");
    gets(nomeNovoHot);
    aux = getNoPDI(listaC, nomeNovoHot);
    if(aux == NULL){
        printf("Ponto de Interesse inexistente");
    }
    else {
        user->hot = aux;
        printf("\nPonto de Interesse HOT alterado com sucesso");
    }

}

LUser login(LUser lista, char *nome)
{
    LUser user = getNoUser(lista, nome);
    if (user == NULL) {
        printf("Utilizador inexistente\n");
        return NULL;
    }
    return user;
}

void listar_DadosUser(LUser lista, LUser user){
    if(user == NULL){
        printf("Efetue o Login\n");
    }
    else{
        printf("Nome: %s", user->nome);
        printf("\nMorada: %s", user->morada);
        printf("\nData de Nascimento: %s", user->data_nascimento);
        printf("\nNumero Telemovel%s", user->telemovel);
        printf("\n#####Preferencias#####\n");
        if(user->prefLocal1!=NULL) {
            printf("Preferencia1:  %s\n", user->prefLocal1->nome_cidade);
            if(user->prefLocal2!=NULL) {
                printf("Preferencia2: %s\n", user->prefLocal2->nome_cidade);
                if(user->prefLocal3!=NULL)
                    printf("Preferencia3:  %s\n", user->prefLocal3->nome_cidade);
            }
        }
        if(user->hot!=NULL) {
            printf("PDI HOT: %s\n", user->hot->nome);
        }
        else{
            printf("Sem Ponto de Interesse HOT\n");
        }
        imprime_lista_PrefPDIs(user->prefPontos);
    }



}
LUser getNoUser(LUser listaU, char *nome){
    LUser l = listaU;
    int i, len_frase = strlen(nome);
    if(strcmp(nome, " ") == 0){
        return NULL;
    }
    while (l)
    {
        if(strcmp((l->nome), (nome)) == 0){
            return l;
        }
        else
            l = l->next;
    }
    return NULL;
}

LUser carrega_listaUsers_ficheiro(char *nomeFicheiroUsers, Lcidade listaC) {
    LUser lista=NULL;
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
                    lista = insere_lista_USERS(lista, tempUser);
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
                        contador++;
                        break;
                    case 5: //PDI HOT

                        tempUser.hot = getNoPDI(listaC, linha);

                        contador++;
                        break;
                    case 6:
                        //linha
                        tempUser.prefPontos=cria_lista_PrefPDIs(listaC, linha);
                        contador++;
                        break;
                }

            }
        }
        lista =  insere_lista_USERS(lista, tempUser);
    }
    return lista;
}

LprefPdi cria_lista_PrefPDIs(Lcidade listaC,  char *pdis)//cria já colocando os elementos lá dentro
{
    LprefPdi lista = NULL;
    LprefPdi no;
    LprefPdi ultimo, anterior;
    char *token;

    token = strtok(pdis, "|");
    while(token != NULL) {
        no = (LprefPdi) malloc(sizeof(Ponto_Interesse_Pref));
        if (no != NULL) {
            no->prefPdi = getNoPDI(listaC, token);
            no->next = NULL;

        }
        if(lista == NULL)
        {
            lista = no;
        }
        else  //encontrar o ultimo da lista e inserir o no no fim
        {
            anterior = lista;
            ultimo = lista;
            while (ultimo)
            {
                anterior = ultimo;
                ultimo = ultimo->next;
            }
            anterior->next = no;
        }
        token = strtok(NULL, "|");
    }
        return lista;

}


void getUserPrefCidades(char *linha, char *pref1, char *pref2, char *pref3)
{
    char barra[] = "|";
    strcpy(pref1,strtok(linha, barra));
    strcpy(pref2,strtok(NULL, barra));
    strcpy(pref3,strtok(NULL, barra));
    //Se nao tiver preferencia fica com um espaço

}

Lcidade getNoCidade(Lcidade listaC, char *cidade){
    Lcidade l = listaC->next;
    int i, len_frase = strlen(cidade), len_frase1;
    if(strcmp(cidade, " ") == 0){
        return NULL;
    }
    while (l)
    {
        if(strcmp((l->nome_cidade), (cidade)) == 0){

            return l;
        }
        else
            l = l->next;
    }
    return NULL;
}

LPdI getNoPDI(Lcidade listaC, char *pdi){
    Lcidade l = listaC->next; // saltar o header
    LPdI pdiaux ;
    while(l)
    {

        pdiaux = l->pontos;
        pdiaux = pdiaux->next;  //AVANCA A CABEÇA - APAGAR
        while(pdiaux)
        {
            if(strcmp(pdi, pdiaux->nome) == 0)
            {
                return pdiaux;
            }
            pdiaux = pdiaux->next;
        }
        l = l->next;
    }
    return NULL;
}
void grava_listaUsers_ficheiro(LUser lista, char *nomeFicheiroUsers)
{
    FILE *dados = fopen(nomeFicheiroUsers, "w");
    LUser l = lista;
    char pref1[100], pref2[100], pref3[100], hot[50];
    while (l != NULL)
    {
        fprintf(dados, "*%s\n", l->nome);
        fprintf(dados, "%s\n", l->morada);
        fprintf(dados, "%s\n", l->data_nascimento);
        fprintf(dados, "%s\n", l->telemovel);
        if(l->prefLocal1 == NULL){
            strcpy(pref1, " ");
        } else{
            strcpy(pref1, l->prefLocal1->nome_cidade);
        }
        if(l->prefLocal2 == NULL){
            strcpy(pref2, " ");
        } else{
            strcpy(pref2, l->prefLocal2->nome_cidade);
        }
        if(l->prefLocal3 == NULL){
            strcpy(pref3, " ");
        } else{
            strcpy(pref3, l->prefLocal3->nome_cidade);
        }
        fprintf(dados, "%s|%s|%s\n", pref1, pref2, pref3);
        if(l->hot == NULL) {
            fprintf(dados, " \n");
        } else{
            fprintf(dados,"%s\n", l->hot->nome);
        }
        LprefPdi aux = l->prefPontos;
        int inicio=1;
        while(aux != NULL) {
            if(inicio ==1) {
                fprintf(dados,"%s", aux->prefPdi->nome);
                inicio=0;
            }
            else
                fprintf(dados,"|%s", aux->prefPdi->nome);
            aux = aux->next;
        }
        fprintf(dados,"\n");
        l = l->next;


    }
    fclose(dados);
}


/* REGISTO*/
void registo(LUser lista){

    UserData user;

    printf("\n\t ####REGISTO####");
    printf("\nNome:");
    gets(user.nome);
    printf("Morada: ");
    gets(user.morada);
    printf("Data de Nascimento: ");
    gets(user.data_nascimento);
    printf("Telemovel: ");
    gets(user.telemovel);
    user.prefLocal1 = NULL;
    user.prefLocal2 = NULL;
    user.prefLocal3 = NULL;
    user.hot = NULL;
    user.prefPontos = NULL;
    lista = insere_lista_USERS(lista, user);
    printf("***UTILIZADO REGISTADO COM SUCESSO***");
}





void alterardados() {

}




void carrega_listaCidades_ficheiro(char *nomeFicheiro, Lcidade lista) {
    int i, len;
    char leitura[256];
    FILE *cidades = fopen(nomeFicheiro, "r");
    Lcidade noLocal = NULL;//ponteiro para correr cada nó da lista de cidades


    for (i = 0; fgets(leitura, 256, cidades)!=NULL; i++){

        if (leitura[0] == '*' ) {
            len = strlen(leitura);
            if(leitura[len-1] == '\n')
                leitura[len - 1] = '\0';
            noLocal = insere_lista_CIDADES(lista, leitura + 1);
        }
        else {
            len = strlen(leitura);
            if(leitura[len-1] == '\n')
                leitura[len - 1] = '\0';
            insere_lista_PDIS(noLocal->pontos, leitura+1);
        }
    }
    //imprime_lista_CIDADES(lista);
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
        printf("\n%s", l->nome_cidade);
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
        printf("\n\t• %s", l->nome);
        l = l->next;
    }
}


//LISTA USERS

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
LUser insere_lista_USERS (LUser lista, UserData  user) {
    LUser no ;
    LUser ultimo, anterior;

    //cria o no
    no = (LUser) malloc (sizeof (UserData));
    if (no != NULL) {
        strcpy(no->nome, user.nome);
        strcpy(no->morada, user.morada);
        strcpy(no->data_nascimento, user.data_nascimento);
        strcpy(no->telemovel, user.telemovel);
        no->prefLocal1 = user.prefLocal1;
        no->prefLocal2 = user.prefLocal2;
        no->prefLocal3 = user.prefLocal3;
        no->hot = user.hot;
        no->prefPontos = user.prefPontos;
        no->next = NULL;
    }

    // introduzir na lista
    if(lista == NULL)
    {
        lista = no;
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
    return lista;
}
void imprime_lista_USERS (LUser lista) {
    LUser l = lista;
    while (l) {
        printf("%s", l->nome);
        printf("\n%s", l->morada);
        printf("\n%s", l->data_nascimento);
        printf("\n%s", l->telemovel);
        printf("\n#####Preferencias#####\n");
        if(l->prefLocal1!=NULL) {
            printf("Pref1 %s\n", l->prefLocal1->nome_cidade);
            if(l->prefLocal2!=NULL) {
                printf("Pref2 %s\n", l->prefLocal2->nome_cidade);
                if(l->prefLocal3!=NULL)
                    printf("Pref3 %s\n", l->prefLocal3->nome_cidade);
            }
        }
        else{
            printf("Nao tem locais preferidos\n");
        }
        if(l->hot!=NULL) {
            printf("PDI HOT: %s\n", l->hot->nome);
        }
        else{
            printf("Sem Ponto de Interesse HOT\n");
        }
        imprime_lista_PrefPDIs(l->prefPontos);
        printf("\n------------------\n");

        l = l->next;
    }
}
void imprime_lista_PrefPDIs(LprefPdi lista){
    LprefPdi l = lista;
    if(l == NULL) {
        printf("Sem pontos de interesse preferidos");
        return;
    }

    while (l != NULL){
        printf("Preferencia PDI: %s\n", l->prefPdi->nome);
        l = l->next;
    }


}
