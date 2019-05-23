//
// Created by Utilizador on 23/05/2019.
//

#ifndef NOVO_PROJETO_H
#define NOVO_PROJETO_H
#define N 50
#define DESCRICAO 500
#define HORARIO   250

typedef struct PdI *LPdI;
typedef struct PdI {
    char nome[100], descricao[DESCRICAO], horario[HORARIO];
    int popular;
    LPdI next;
}Ponto_Interesse;

typedef struct cidade *Lcidade;
typedef struct cidade {
    int popular;
    char nome_cidade[100];
    LPdI pontos;
    Lcidade next;
}Cidades;

typedef struct prefPdi *LprefPdi;
typedef struct prefPdi {
    LPdI prefPdi;
    int contadorPDIS;
    LprefPdi next;
}Ponto_Interesse_Pref;

typedef struct popCidade *LPopCidade;
typedef struct popCidade {
    Lcidade popCidade;
    LPopCidade next;
}Cidades_Populares;

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

typedef struct viagem {
    Lcidade Local1;
    Lcidade Local2;
    Lcidade Local3;
    LPdI Local1PDI1;
    LPdI Local1PDI2;
    LPdI Local1PDI3;
    LPdI Local2PDI1;
    LPdI Local2PDI2;
    LPdI Local2PDI3;
    LPdI Local3PDI1;
    LPdI Local3PDI2;
    LPdI Local3PDI3;
}Viagem;

/*cabeçalhos*/
int menu(LUser user);
LUser registo(LUser lista);
LUser login(LUser lista, LUser user);
void listar_DadosUser(LUser lista, LUser user);
void getDataPDI(char *linha, char *pdi, char *descricao, char *horario);

Lcidade cria_lista_CIDADES(void);
int lista_vazia_CIDADES(Lcidade lista);
void procura_lista_CIDADES(Lcidade lista, char *chave, Lcidade *ant, Lcidade *actual);
Lcidade insere_lista_CIDADES(Lcidade lista, char *it);
void imprime_lista_CIDADES(Lcidade lista);
void carrega_listaCidades_ficheiro(char *nomeFicheiro, Lcidade lista);
Lcidade destroi_lista_CIDADES_PDIS(Lcidade lista);

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
LprefPdi  getNoPrefPDI(LprefPdi lista, char *pdi);

LprefPdi cria_lista_PrefPDIs(Lcidade listaC, char *pdi);
void imprime_lista_PrefPDIs(LprefPdi lista);


void alterar_PDIHOT(LUser lista, Lcidade listaC, LUser user);
void alterar_PrefPDIS(LUser lista, LUser user, Lcidade listaC);
void alterar_PrefLocais(LUser lista, Lcidade listaC, LUser user);
LprefPdi apagar_PrefPDI(LprefPdi lista, LprefPdi apagar);
LprefPdi adicionar_PrefPDI(LprefPdi lista, char *nome, Lcidade listaC);

void alterar_DadosUser(LUser lista, LUser user);


Lcidade cria_lista_CidadePop(Lcidade listaC);
void procura_lista_CIDADESPop (Lcidade lista, int chave, Lcidade *ant, Lcidade *actual);
void insere_lista_CIDADESPop(Lcidade lista, Lcidade listaC);
void imprime_lista_CIDADESPop (Lcidade lista);

void procura_lista_PDISPop (LPdI lista, int chave, LPdI *ant, LPdI *actual);

void insere_lista_PDISPop(LPdI listaPopPDIS, LPdI listaPDIS);
LPdI cria_lista_PDISPop();
void imprime_lista_PDISPop (LPdI lista);
Viagem viagem(LUser user,LUser lista, Lcidade listaCPop, Lcidade listaC);
void imprime_lista_POPULARIDADE(Lcidade lista);

void procura_lista_PrefPDISPop (LprefPdi lista, int chave, LprefPdi *ant, LprefPdi *actual);
int VerificaAlgarismos(char *str);
int VerificaChar(char *str);
int verificaPDIemLista(LPdI pdi, LprefPdi lista);
int VerificaUserLogado(LUser user);
void imprime_Viagem(Viagem v, LUser lista);
#endif //NOVO_PROJETO_H
