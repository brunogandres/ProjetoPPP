#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
void percorre_string(char *str);
int verificaPDIemLista(LPdI pdi, LprefPdi lista);
int VerificaUserLogado(LUser user);
void imprime_Viagem(Viagem v);


float contadorUsers = 0;

//  Main

int main() {
    Lcidade listaCidades;
    LUser listaUsers = NULL;//lista começa a NULL
    LprefPdi listaPrefPDIS = NULL;
    Lcidade listaPopularCIDADES = NULL;
    LPdI listaPopularPDIS = NULL;
    char ficheiroUsers[] = "C:\\Users\\Utilizador\\Desktop\\novo\\Dados.txt";
    char ficheiroCidades[] = "C:\\Users\\Utilizador\\Desktop\\novo\\Cidades.txt";
    Viagem a;
    int opcaoMenu, TotalUtilizadores = 0;
    char nome[N];
    LUser userLogado = NULL;
    listaCidades = cria_lista_CIDADES();//lista criada aqui caso seja precisa pra outras coisas
    //listaPrefPDIS = cria_lista_PrefPDIs(listaCidades, );
    carrega_listaCidades_ficheiro(ficheiroCidades, listaCidades);
    listaUsers = carrega_listaUsers_ficheiro(ficheiroUsers, listaCidades);


    do {
        opcaoMenu = menu(userLogado);
        switch (opcaoMenu) {
            case 1:
                listaUsers = registo(listaUsers);
                break;
            case 2:
                userLogado=login(listaUsers, userLogado);
                break;
            case 3:
                listar_DadosUser(listaUsers, userLogado);
                break;
            case 4:
                alterar_DadosUser(listaUsers, userLogado);
                break;
            case 5:
                alterar_PDIHOT(listaUsers, listaCidades, userLogado);
                break;
            case 6:
                alterar_PrefLocais(listaUsers,listaCidades, userLogado);
                break;
            case 7:
                alterar_PrefPDIS(listaUsers, userLogado, listaCidades);
                break;
            case 8:
                imprime_lista_USERS(listaUsers);
                break;
            case 9:
                imprime_lista_CIDADES(listaCidades);
                break;
            case 10:
                printf("\n###TAXA POPULARIDADE CIDADES###\n");
                listaPopularCIDADES = cria_lista_CIDADES();
                insere_lista_CIDADESPop(listaPopularCIDADES, listaCidades);
                imprime_lista_POPULARIDADE(listaPopularCIDADES);
                listaPopularCIDADES = destroi_lista_CIDADES_PDIS(listaPopularCIDADES);
                break;
            case 11:
                if (VerificaUserLogado(userLogado)) {
                    listaPopularCIDADES = cria_lista_CIDADES();
                    insere_lista_CIDADESPop(listaPopularCIDADES, listaCidades);
                    a = viagem(userLogado,listaUsers, listaPopularCIDADES, listaCidades);
                    imprime_Viagem(a);
                    listaPopularCIDADES = destroi_lista_CIDADES_PDIS(listaPopularCIDADES);

                }
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
    destroi_lista_CIDADES_PDIS(listaCidades);
    destroi_lista_USERS(listaUsers);


}

int menu(LUser user) {
    int n;
    printf("\n********************************************************");
    printf("\n\t\tBEM VINDO ");
    if (user != NULL)
        printf("'%s'", user->nome);
    printf("\n********************************************************");
    printf("\n1. Registar Utilizadores");
    printf("\n2. Efetuar Login" );
    printf("\n3. Listar dados do utilizador");
    printf("\n4. Alterar dados do utilizador"); // AQui dentro pode
    printf("\n5. Alterar PDI HOT do utilizador");
    printf("\n6. Alterar preferencias de locais do utilizador");
    printf("\n7. Alterar preferencias de PDIs do utilizador");
    printf("\n8. Listar todos utilizadores e respectivos dados");
    printf("\n9. Listar Locais e seus Pontos de Interesse");
    printf("\n10. Listar Locais e PDIs mais populares");
    printf("\n11. Gerar Viagem e Ver Avaliacao");
    printf("\n12. Sair");
    printf("\n********************************************************");
    printf("\nEscolha uma opcao: ");
    scanf("%d", &n);
    getc(stdin);
    return n;
}

int VerificaUserLogado(LUser user)
{
    if (user != NULL)
        return 1;
    printf("Efetue Login!");
    return 0;
}

LUser login(LUser lista, LUser user)
{
    char nome[N];
    printf("Nome:");
    gets(nome);
    user = getNoUser(lista, nome);
    if (user == NULL) {
        printf("Utilizador inexistente\n");
        return NULL;
    }
    return user;
}
void percorre_string(char *str){
    int len, i;
    len = strlen(str);
    for(i = 0; i < len; i++){
        if(isalpha(str[i])) {
            printf("l ");
        }
    }
}

void alterar_DadosUser(LUser lista, LUser user){

    char resposta[N];
    if(VerificaUserLogado(user)){
        printf("Morada: ");
        gets(resposta);
        strcpy(user->morada, resposta);
        printf("Data de Nascimento: ");
        gets(resposta);
        strcpy(user->data_nascimento, resposta);
        printf("Numero Telemovel: ");
        gets(resposta);
        strcpy(user->telemovel, resposta);
        printf("***Dados alterados com sucesso***");

    }
}


Viagem viagem(LUser user,LUser lista, Lcidade listaCPop, Lcidade listaC){
    Viagem viagem;
    Lcidade l = listaCPop ->next;
    LPdI anterior = NULL;
    LPdI auxCidadePontos = NULL;
    LUser lu = NULL;
    int continuar = 1;
    int contador = 0;


    viagem.Local1 = NULL;
    viagem.Local2 = NULL;
    viagem.Local3 = NULL;
    viagem.Local1PDI1 = NULL;
    viagem.Local1PDI2 = NULL;
    viagem.Local1PDI3 = NULL;
    viagem.Local2PDI1 = NULL;
    viagem.Local2PDI2 = NULL;
    viagem.Local2PDI3 = NULL;
    viagem.Local3PDI1 = NULL;
    viagem.Local3PDI2 = NULL;
    viagem.Local3PDI3 = NULL;

    //pelo menos 3 preflocais
    if (user->prefLocal1 == NULL || user->prefLocal2 == NULL || user->prefLocal3 == NULL) {
        printf("Para gerar a viagem necessita de ter 3 locais de preferencia\n");
    } else {
        while (l != NULL && continuar) {
            if (strcmp(l->nome_cidade, user->prefLocal1->nome_cidade) == 0 ||
            strcmp(l->nome_cidade, user->prefLocal2->nome_cidade) == 0 ||
            strcmp(l->nome_cidade, user->prefLocal3->nome_cidade) == 0) {
                if (viagem.Local1 == NULL) {
                    viagem.Local1 = getNoCidade(listaCPop, l->nome_cidade);
                } else {
                    if (viagem.Local2 == NULL) {
                        viagem.Local2 = getNoCidade(listaCPop, l->nome_cidade);
                    } else {
                        if (viagem.Local3 == NULL) {
                            viagem.Local3 = getNoCidade(listaCPop, l->nome_cidade);
                            continuar = 0;
                        }
                    }
                }
            }
            l = l->next;
        }
        auxCidadePontos = viagem.Local1->pontos;
        anterior = auxCidadePontos;
        continuar = 1;
        //hot tratado
        while (auxCidadePontos != NULL && continuar) {
            if (strcmp(auxCidadePontos->nome, user->hot->nome) == 0) {
                viagem.Local1PDI1 = getNoPDI(listaC, auxCidadePontos->nome);
                anterior->next = auxCidadePontos->next;
                free(auxCidadePontos);
                continuar = 0; // quando
            }
            else{
                anterior = auxCidadePontos;
                auxCidadePontos = auxCidadePontos->next;
            }
        }
        auxCidadePontos = viagem.Local1->pontos;
        continuar = 1;
        anterior = auxCidadePontos;

        while (auxCidadePontos && continuar) {
                if (verificaPDIemLista(auxCidadePontos, user->prefPontos) == 1) {
                    if (viagem.Local1PDI1 == NULL) {
                        viagem.Local1PDI1 = getNoPDI(listaC, auxCidadePontos->nome);
                        anterior->next = auxCidadePontos->next;
                        free(auxCidadePontos);
                        auxCidadePontos = anterior->next;
                    } else {
                        if (viagem.Local1PDI2 == NULL) {
                            viagem.Local1PDI2 = getNoPDI(listaC, auxCidadePontos->nome);
                            anterior->next = auxCidadePontos->next;
                            free(auxCidadePontos);
                            auxCidadePontos = anterior->next;

                        } else {
                            if (viagem.Local1PDI3 == NULL) {
                                viagem.Local1PDI3 = getNoPDI(listaC, auxCidadePontos->nome);
                                anterior->next = auxCidadePontos->next;
                                free(auxCidadePontos);
                                auxCidadePontos = anterior->next;
                                continuar = 0;
                            }
                        }
                    }
                }
                else{
                    anterior = auxCidadePontos;
                    auxCidadePontos = auxCidadePontos->next;
                }
        }
        auxCidadePontos = viagem.Local1->pontos->next; // Avançar a cabeca
        if (viagem.Local1PDI1 == NULL) {
            viagem.Local1PDI1 = getNoPDI(listaC, auxCidadePontos->nome);
            auxCidadePontos = auxCidadePontos->next;
        }
        if (viagem.Local1PDI2 == NULL) {
            viagem.Local1PDI2 = getNoPDI(listaC, auxCidadePontos->nome);
            auxCidadePontos = auxCidadePontos->next;
        }
        if (viagem.Local1PDI3 == NULL) {
            viagem.Local1PDI3 = getNoPDI(listaC, auxCidadePontos->nome);
        }

        //CIDADE 2
        auxCidadePontos = viagem.Local2->pontos;
        anterior = auxCidadePontos;
        continuar = 1;
        //hot tratado
        while (auxCidadePontos != NULL && continuar) {
            if (strcmp(auxCidadePontos->nome, user->hot->nome) == 0) {
                viagem.Local2PDI1 = getNoPDI(listaC, auxCidadePontos->nome);
                anterior->next = auxCidadePontos->next;
                free(auxCidadePontos);
                continuar = 0; // quando
            }
            else{
                anterior = auxCidadePontos;
                auxCidadePontos = auxCidadePontos->next;
            }
        }
        auxCidadePontos = viagem.Local2->pontos;
        continuar = 1;
        anterior = auxCidadePontos;

        while (auxCidadePontos && continuar) {
            if (verificaPDIemLista(auxCidadePontos, user->prefPontos) == 1) {
                if (viagem.Local2PDI1 == NULL) {
                    viagem.Local2PDI1 = getNoPDI(listaC, auxCidadePontos->nome);
                    anterior->next = auxCidadePontos->next;
                    free(auxCidadePontos);
                    auxCidadePontos = anterior->next;
                } else {
                    if (viagem.Local2PDI2 == NULL) {
                        viagem.Local2PDI2 = getNoPDI(listaC, auxCidadePontos->nome);
                        anterior->next = auxCidadePontos->next;
                        free(auxCidadePontos);
                        auxCidadePontos = anterior->next;

                    } else {
                        if (viagem.Local2PDI3 == NULL) {
                            viagem.Local2PDI3 = getNoPDI(listaC, auxCidadePontos->nome);
                            anterior->next = auxCidadePontos->next;
                            free(auxCidadePontos);
                            auxCidadePontos = anterior->next;
                            continuar = 0;
                        }
                    }
                }
            }
            else{
                anterior = auxCidadePontos;
                auxCidadePontos = auxCidadePontos->next;
            }
        }
        auxCidadePontos = viagem.Local2->pontos->next; // Avançar a cabeca
        if (viagem.Local2PDI1 == NULL) {
            viagem.Local2PDI1 = getNoPDI(listaC, auxCidadePontos->nome);
            auxCidadePontos = auxCidadePontos->next;
        }
        if (viagem.Local2PDI2 == NULL) {
            viagem.Local2PDI2 = getNoPDI(listaC, auxCidadePontos->nome);
            auxCidadePontos = auxCidadePontos->next;
        }
        if (viagem.Local2PDI3 == NULL) {
            viagem.Local2PDI3 = getNoPDI(listaC, auxCidadePontos->nome);
        }

        //cidade3

        auxCidadePontos = viagem.Local3->pontos;
        anterior = auxCidadePontos;
        continuar = 1;
        //hot tratado
        while (auxCidadePontos != NULL && continuar) {
            if (strcmp(auxCidadePontos->nome, user->hot->nome) == 0) {
                viagem.Local3PDI1 = getNoPDI(listaC, auxCidadePontos->nome);
                anterior->next = auxCidadePontos->next;
                free(auxCidadePontos);
                continuar = 0; // quando
            }
            else{
                anterior = auxCidadePontos;
                auxCidadePontos = auxCidadePontos->next;
            }
        }
        auxCidadePontos = viagem.Local3->pontos;
        continuar = 1;
        anterior = auxCidadePontos;

        while (auxCidadePontos && continuar) {
            if (verificaPDIemLista(auxCidadePontos, user->prefPontos) == 1) {
                if (viagem.Local3PDI1 == NULL) {
                    viagem.Local3PDI1 = getNoPDI(listaC, auxCidadePontos->nome);
                    anterior->next = auxCidadePontos->next;
                    free(auxCidadePontos);
                    auxCidadePontos = anterior->next;
                } else {
                    if (viagem.Local3PDI2 == NULL) {
                        viagem.Local3PDI2 = getNoPDI(listaC, auxCidadePontos->nome);
                        anterior->next = auxCidadePontos->next;
                        free(auxCidadePontos);
                        auxCidadePontos = anterior->next;

                    } else {
                        if (viagem.Local3PDI3 == NULL) {
                            viagem.Local3PDI3 = getNoPDI(listaC, auxCidadePontos->nome);
                            anterior->next = auxCidadePontos->next;
                            free(auxCidadePontos);
                            auxCidadePontos = anterior->next;
                            continuar = 0;
                        }
                    }
                }
            }
            else{
                anterior = auxCidadePontos;
                auxCidadePontos = auxCidadePontos->next;
            }
        }
        auxCidadePontos = viagem.Local3->pontos->next; // Avançar a cabeca
        if (viagem.Local3PDI1 == NULL) {
            viagem.Local3PDI1 = getNoPDI(listaC, auxCidadePontos->nome);
            auxCidadePontos = auxCidadePontos->next;
        }
        if (viagem.Local3PDI2 == NULL) {
            viagem.Local3PDI2 = getNoPDI(listaC, auxCidadePontos->nome);
            auxCidadePontos = auxCidadePontos->next;
        }
        if (viagem.Local3PDI3 == NULL) {
            viagem.Local3PDI3 = getNoPDI(listaC, auxCidadePontos->nome);
        }

        //percentagens
        

    }
    return viagem;
}



int verificaPDIemLista(LPdI pdi, LprefPdi lista){
    LprefPdi l = lista->next;
    //printf("###ENTROU NA FUCN3");
    while(l){
        if(strcmp(pdi->nome, l->prefPdi->nome) == 0){
            return 1;
        }
        l = l->next;
    }
    return 0;
}


void alterar_PrefPDIS(LUser lista, LUser user, Lcidade listaC){
    int numero;
    char nome[N];
    if(VerificaUserLogado(user)){
        imprime_lista_PrefPDIs(lista->prefPontos);
        do {
            printf("1-Adicionar\n2-Eliminar\n3-Voltar:");
            scanf("%d", &numero);
            getc(stdin);
            switch (numero) {
                case 1:
                    printf("Introduza o nome do PDI a adicionar: ");
                    gets(nome);
                    user->prefPontos = adicionar_PrefPDI(user->prefPontos, nome, listaC);

                    break;
                case 2:
                    printf("Introduza o nome do PDI a eliminar: ");
                    gets(nome);
                    user->prefPontos = apagar_PrefPDI(user->prefPontos, getNoPrefPDI(user->prefPontos, nome));

                    break;
                case 3:
                    break;
                default:
                    printf("Introduza um valor valido");
            }
        } while (numero != 3);
    }
}
LprefPdi  getNoPrefPDI(LprefPdi lista, char *pdi){
    LprefPdi l = lista;
    int i, len_frase = strlen(pdi);
    while (l)
    {
        if(strcmp((l->prefPdi->nome), pdi) == 0){
            return l;
        }
        else
            l = l->next;
    }
    return NULL;
}

LprefPdi apagar_PrefPDI(LprefPdi lista, LprefPdi apagar){//APAGAR NO NA LSITA DE PREFERNCIAS PDIS CASO QUEIRA REMOVER
    LprefPdi l = lista;
    LprefPdi anterior;
    if(l == apagar){
        l->prefPdi->popular--;
        lista = lista->next;
        free(l);
        printf("PDI eliminado\n");
        imprime_lista_PrefPDIs(lista);
        return lista;
    }
    anterior = l;
    l = l->next;
    while(l != NULL){
        if(l == apagar){
            l->prefPdi->popular--;
            anterior->next = l->next;
            free(l);
            printf("PDI eliminado\n");
            imprime_lista_PrefPDIs(lista);
            return lista;
        } else{
            anterior = l;
            l = l->next;
        }
    }
    printf("PDI inexistente");
    return lista;
}
LprefPdi adicionar_PrefPDI(LprefPdi lista, char *nome, Lcidade listaC){
    LprefPdi no, anterior, ultimo;
    LPdI verificaPDI;
    if(getNoPrefPDI(lista, nome) != NULL) {
        printf("PDI ja esta nas preferencias\n");
    }
    else {//não existe na lista de pref e pode se adicionar
        verificaPDI = getNoPDI(listaC, nome);
        if(verificaPDI == NULL) {
            printf("PDI inexistente");
        }
        else {
            no = (LprefPdi) malloc(sizeof(Ponto_Interesse_Pref));
            if (no != NULL) {
                no->prefPdi = verificaPDI;
                no->prefPdi->popular++;
                no->next = NULL;

            }
            if (lista == NULL) {
                lista = no;
            } else  //encontrar o ultimo da lista e inserir o no no fim
            {
                anterior = lista;
                ultimo = lista;
                while (ultimo) {
                    anterior = ultimo;
                    ultimo = ultimo->next;
                }
                anterior->next = no;
            }
            imprime_lista_PrefPDIs(lista);
        }

    }
    return lista;


}
void alterar_PrefLocais(LUser lista, Lcidade listaC, LUser user) {

    char novoLocalPref[N], resposta[1];
    int numero, i;
    Lcidade aux;
    if(VerificaUserLogado(user)){
        if (user->prefLocal1 != NULL) {
            printf("1. Local de Preferencia ATUAL: %s\n", user->prefLocal1->nome_cidade);
            if (user->prefLocal2 != NULL) {
                printf("2. Local de Preferencia ATUAL: %s\n", user->prefLocal2->nome_cidade);
                if (user->prefLocal3 != NULL)
                    printf("3. Local de Preferencia ATUAL: %s\n", user->prefLocal3->nome_cidade);
            }
        } else {
            printf("Nao tem locais preferidos\n");
            printf("\nDeseja adicionar Locais? <S|N>");
            gets(resposta);
            if (strcmp(resposta, "S") == 0) {
                do {
                    printf("Introduza o novo Local Preferido: ");
                    gets(novoLocalPref);
                    aux = getNoCidade(listaC, novoLocalPref);
                    if (aux == NULL) {
                        printf("Local inexistente\n");
                    } else {
                        user->prefLocal1 = aux;
                        user->prefLocal1->popular++;
                    }
                } while (aux == NULL);
                do {
                    printf("Introduza o novo Local Preferido: ");
                    gets(novoLocalPref);
                    aux = getNoCidade(listaC, novoLocalPref);
                    if (aux == NULL) {
                        printf("Local inexistente\n");
                    } else {
                        user->prefLocal2 = aux;
                        user->prefLocal2->popular++;
                    }
                } while (aux == NULL);
                do {
                    printf("Introduza o novo Local Preferido: ");
                    gets(novoLocalPref);
                    aux = getNoCidade(listaC, novoLocalPref);
                    if (aux == NULL) {
                        printf("Local inexistente\n");
                    } else {
                        user->prefLocal3 = aux;
                        user->prefLocal3->popular++;
                    }
                } while (aux == NULL);
                printf("***Locais preferidos atualizados***");
                return;
            } else
                return;
        }
        do {
            printf("Qual a preferencia a alterar [1|2|3] ou [4]- Voltar:");
            scanf("%d", &numero);
            getc(stdin);
            switch (numero) {
                case 1:
                    aux = NULL;
                    printf("**Para eliminar prima ENTER**\n");
                    do {
                        printf("Introduza o novo Local Preferido: \n");
                        gets(novoLocalPref);

                        if (strlen(novoLocalPref) == 0) {
                            user->prefLocal1->popular--;
                            user->prefLocal1 = user->prefLocal2;
                            user->prefLocal2=user->prefLocal3;
                            user->prefLocal3=NULL;

                            break;
                        } else {
                            aux = getNoCidade(listaC, novoLocalPref);
                            if (aux == NULL) {
                                printf("Local inexistente\n");
                            }
                            else if(strcmp(novoLocalPref, user->prefLocal2->nome_cidade) == 0|| strcmp(novoLocalPref, user->prefLocal3->nome_cidade) == 0)
                                printf("***Local ja introduzido nas preferencias***\n");
                            else {
                                user->prefLocal1->popular--;
                                user->prefLocal1 = aux;
                                user->prefLocal1->popular++;
                            }

                        }
                    } while (aux == NULL);

                    break;
                case 2:
                    aux = NULL;
                    printf("Para eliminar prima ENTER\n");
                    do {
                        printf("Introduza o novo Local Preferido: \n");
                        gets(novoLocalPref);
                        if (strlen(novoLocalPref) == 0) {
                            user->prefLocal2->popular--;
                            user->prefLocal2=user->prefLocal3;
                            user->prefLocal3=NULL;

                            break;
                        } else {
                            aux = getNoCidade(listaC, novoLocalPref);
                            if (aux == NULL) {
                                printf("Local inexistente\n");
                            }
                            else if(strcmp(novoLocalPref, user->prefLocal1->nome_cidade) == 0|| strcmp(novoLocalPref, user->prefLocal3->nome_cidade) == 0)
                                printf("***Local ja introduzido nas preferencias***\n");
                            else {
                                user->prefLocal2->popular--;
                                user->prefLocal2 = aux;
                                user->prefLocal2->popular++;
                            }

                        }
                    } while (aux == NULL);
                    break;
                case 3:
                    aux = NULL;
                    printf("Para eliminar prima ENTER\n");
                    do {
                        printf("Introduza o novo Local Preferido: \n");
                        gets(novoLocalPref);

                        if (strlen(novoLocalPref) == 0) {
                            user->prefLocal3->popular--;
                            user->prefLocal3=NULL;

                            break;
                        } else {
                            aux = getNoCidade(listaC, novoLocalPref);
                            if (aux == NULL) {
                                printf("Local inexistente\n");
                            }
                            else if(strcmp(novoLocalPref, user->prefLocal1->nome_cidade) == 0|| strcmp(novoLocalPref, user->prefLocal2->nome_cidade) == 0)
                                printf("***Local ja introduzido nas preferencias***\n");
                            else {
                                user->prefLocal3->popular--;
                                user->prefLocal3 = aux;
                                user->prefLocal3->popular++;
                            }

                        }
                    } while (aux == NULL);
                    break;
                case 4:
                    break;
                default:
                    printf("Introduza um valor valido!\n");

            }

        } while (numero != 4);
    }
}
void alterar_PDIHOT(LUser lista, Lcidade listaC, LUser user){
    LPdI aux;
    char nomeNovoHot[N];
    if(VerificaUserLogado(user)){
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

}



void  listar_DadosUser(LUser lista, LUser user){
    if(VerificaUserLogado(user)){
        printf("Nome: %s", user->nome);
        printf("\nMorada: %s", user->morada);
        printf("\nData de Nascimento: %s", user->data_nascimento);
        printf("\nNumero Telemovel: %s", user->telemovel);
        printf("\n#####Preferencias#####\n");
        if(user->prefLocal1!=NULL) {
            printf("Preferencia1:  %s\n", user->prefLocal1->nome_cidade);
            if(user->prefLocal2!=NULL) {
                printf("Preferencia2: %s\n", user->prefLocal2->nome_cidade);
                if(user->prefLocal3!=NULL)
                    printf("Preferencia3:  %s\n", user->prefLocal3->nome_cidade);
            }
        } else{
            printf("Sem locais de preferencia\n");
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
    int i,contador = 0, len_frase;
    LUser noUser = NULL;

    UserData tempUser; //estrutura temporaria para guardar as informacoes
    FILE *ficheiroDados = fopen(nomeFicheiroUsers, "r");
    if (ficheiroDados == NULL) {
        printf("------------------------------------------\nNAO FOI POSSIVEL LER O FICHEIRO 'DADOS.TXT' COM OS DADOS DOS UTILIZADORES!\n ESPECIFIQUE O CAMINHO CORRECTO!\n------------------------------------------\n");
        return NULL;
    }

    if(ficheiroDados != NULL) {
        for (i = 0; fgets(linha, 256, ficheiroDados); i++) {
            len_frase = strlen(linha);
            if (linha[len_frase - 1] == '\n') {
                linha[len_frase - 1] = '\0';
            }

            if (linha[0] == '*')
            {
                contadorUsers++;
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
                        if(tempUser.prefLocal1 != NULL)
                            tempUser.prefLocal1->popular++;
                        tempUser.prefLocal2 = getNoCidade(listaC, pref2);
                        if(tempUser.prefLocal2 != NULL)
                            tempUser.prefLocal2->popular++;
                        tempUser.prefLocal3 = getNoCidade(listaC, pref3);
                        if(tempUser.prefLocal3 != NULL)
                            tempUser.prefLocal3->popular++;
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



void getDataPDI(char *linha, char *pdi, char *descricao, char *horario)
{
    char barra[] = "|";
    char *token;
    strcpy(pdi, strtok(linha, barra));
    token=strtok(NULL, barra);
    if (token != NULL)
        strcpy(descricao, token);
    else
        strcpy(descricao, "");
    token = strtok(NULL, barra);
    if (token != NULL)
        strcpy(horario, token);

    else
        strcpy(horario, "");
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

LPdI getNoPDI(Lcidade listaC, char *pdi){//ver se o pdi existe nas listas da cidades
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
LUser registo(LUser lista){

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
    return lista;
}

void carrega_listaCidades_ficheiro(char *nomeFicheiro, Lcidade lista) {
    int i, len;
    char leitura[1000];
    FILE *cidades = fopen(nomeFicheiro, "r");
    Lcidade noLocal = NULL;//ponteiro para correr cada nó da lista de cidades
    if (cidades == NULL) {
        printf("------------------------------------------\nNAO FOI POSSIVEL LER O FICHEIRO 'CIDADES.TXT' COM O NOME DOS LOCAIS E PONTOS DE INTERESSE!\n ESPECIFIQUE O CAMINHO CORRECTO!\n------------------------------------------\n");
        return;
    }

    for (i = 0; fgets(leitura, 1000, cidades)!=NULL; i++){

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
        aux->popular = 0;
        strcpy(aux->nome_cidade, "");
        aux->pontos = cria_lista_PDIS();
        aux->next = NULL;
    }
    return aux;
}
Lcidade destroi_lista_CIDADES_PDIS(Lcidade lista) {
    Lcidade temp_ptr;
    while (lista_vazia_CIDADES(lista) == 0) {
        lista->pontos = destroi_lista_PDIS(lista->pontos);
        temp_ptr = lista;
        lista= lista->next;
        free (temp_ptr);
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
        no->popular = 0;
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
    if (l == NULL)
    {
        printf("Nao existem cidades e pontos de interesse registados!\n");
    }
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
        aux->popular = 0;
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
        lista= lista->next;
        free (temp_ptr);
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
    char pdi[N], descricao[DESCRICAO], horario[HORARIO];
    getDataPDI(it, pdi, descricao, horario);
    no = (LPdI) malloc (sizeof (Ponto_Interesse));
    if (no != NULL) {
        no->popular = 0;
        strcpy(no->nome, pdi);
        strcpy(no->descricao, descricao);
        strcpy(no->horario, horario);
        procura_lista_PDIS (lista, pdi, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}
void imprime_lista_PDIS (LPdI lista) {
    LPdI l = lista->next; /* Salta o header */
    while (l) {
        printf("\n\t* %s", l->nome);
        if(strcmp(l->descricao,"")!=0)
            printf("\n\t  DESCRICAO: %s", l->descricao);
        if (strcmp(l->horario,"") != 0)
            printf("\n\t  HORARIO: %s", l->horario);
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
    if (l == NULL)
    {
        printf("Nao existem utiliadores registados!\n");
    }
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
LprefPdi cria_lista_PrefPDIs(Lcidade listaC,  char *pdi)//cria já colocando os elementos lá dentro
{
    LprefPdi lista = NULL;
    LprefPdi no;
    LprefPdi ultimo, anterior, inutil;
    char *token;

    token = strtok(pdi, "|");
    while(token != NULL) {
        no = (LprefPdi) malloc(sizeof(Ponto_Interesse_Pref));
        if (no != NULL) {
            no->prefPdi = getNoPDI(listaC, token);
            //procura_lista_PrefPDISPop(lista, no->prefPdi->popular, &anterior, &inutil);
            if(no->prefPdi != NULL)
                no->prefPdi->popular++;
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
void insere_lista_CIDADESPop(Lcidade lista, Lcidade listaC) {
    Lcidade no = NULL;
    Lcidade ant, inutil;
    Lcidade l = listaC->next;

    while(l != NULL) {
     //   if(l->popular != 0)
        {
            no = (Lcidade) malloc(sizeof(Cidades));
            if (no != NULL) {
                strcpy(no->nome_cidade, l->nome_cidade);
                no->popular = l->popular;
                procura_lista_CIDADESPop(lista, no->popular, &ant, &inutil);
                no->pontos  = cria_lista_PDIS();
                insere_lista_PDISPop(no->pontos, l->pontos);
                no->next = ant->next;
                ant->next = no;
            }
        }
        l = l->next;
    }
}
void procura_lista_CIDADESPop (Lcidade lista, int chave, Lcidade *ant, Lcidade *actual) {
    *ant = lista;
    *actual = lista->next;

    while ((*actual) != NULL && (*actual)->popular > chave) {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && (*actual)->popular > chave)
        *actual = NULL;
}
void imprime_lista_CIDADESPop (Lcidade lista) {
    Lcidade l = lista->next; /* Salta o header */
    float aux;
    while (l) {
        if(l->popular != 0) {
            aux = l->popular / contadorUsers;
            aux = aux * 100.0;
            printf("\n<%s> , %.f%c", l->nome_cidade, aux, '%');
        }
        l=l->next;
    }
}


LPdI cria_lista_PDISPop(){
    LPdI aux;
    aux = (LPdI)malloc(sizeof(Ponto_Interesse));
    if(aux != NULL){
        aux->popular = 0;
        strcpy(aux->nome, "");
        aux->next = NULL;
    }
    return aux;
}
void insere_lista_PDISPop(LPdI listaPopPDIS, LPdI listaPDIS) {
    LPdI no = NULL;
    LPdI ant, inutil;
    LPdI l = listaPDIS->next;

    while(l != NULL) {
     //   if (l->popular != 0)
        {
            no = (LPdI) malloc(sizeof(Ponto_Interesse));//reserva espaço para o nó
            if (no != NULL) {
                strcpy(no->nome, l->nome);
                no->popular = l->popular;
                procura_lista_PDISPop(listaPopPDIS, no->popular, &ant, &inutil);
                no->next = ant->next;
                ant->next = no;
            }
        }
        l = l->next;
    }
}
void procura_lista_PDISPop (LPdI lista, int chave, LPdI *ant, LPdI *actual) {
    *ant = lista;
    *actual = lista->next;
    while ((*actual) != NULL && (*actual)->popular > chave) {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && (*actual)->popular > chave)
        *actual = NULL;
}

void imprime_lista_PDISPop (LPdI lista) {
    LPdI l = lista->next;
    float aux;
    while (l != NULL) {
        //if(l->popular != 0)
        {
            aux = l->popular / contadorUsers;
            aux = aux * 100.0;
            printf("\t\t[%.f%c] %s \n", aux, '%', l->nome);
        }
        l = l->next;
    }
}

void imprime_lista_POPULARIDADE(Lcidade lista){
    Lcidade l = lista->next; /* Salta o header */
    float aux;
    while (l) {
        aux = l->popular / contadorUsers;
        aux = aux * 100.0;
        printf("[%.f%c]  %s \n",aux, '%', strupr(l->nome_cidade));
        //
        if(l->pontos->next == NULL)
            printf("\t\t***SEM PDIS***\n\n");
        else {
            printf("\t\t***POPULARIDADE DOS PONTOS DE INTERESSE***\n");
            imprime_lista_PDISPop(l->pontos);
            printf("\n");
        }
        l=l->next;
    }
}

void imprime_Viagem(Viagem v) {
    if (v.Local1 != NULL) {
        printf("\n############### VIAGEM GERADA ############### \n\n-- %s --> %s --> %s --\n", strupr(v.Local1->nome_cidade), strupr(v.Local2->nome_cidade), strupr(v.Local3->nome_cidade));
        printf("\nPONTOS DE INTERESSE A VISITAR:\n\n");
        printf("* %s\n", strupr(v.Local1->nome_cidade));
        printf("\t%s\n", v.Local1PDI1->nome);
        printf("\t%s\n", v.Local1PDI2->nome);
        printf("\t%s\n", v.Local1PDI3->nome);
        printf("* %s\n", strupr(v.Local2->nome_cidade));
        printf("\t%s\n",v.Local2PDI1->nome);
        printf("\t%s\n", v.Local2PDI2->nome);
        printf("\t%s\n",v.Local2PDI3->nome);
        printf("* %s\n", strupr(v.Local3->nome_cidade));
        printf("\t%s\n", v.Local3PDI1->nome);
        printf("\t%s\n", v.Local3PDI2->nome);
        printf("\t%s\n",v.Local3PDI3->nome);
    }
    else {
        printf("Não foi possível gerar a viagem!");
    }
}

