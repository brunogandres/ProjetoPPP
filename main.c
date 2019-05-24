#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Projeto.h"

float contadorUsers = 0;
int contadorPDISfich = 0;

//Main
int main() {
    Lcidade listaCidades;
    LUser listaUsers = NULL;//lista começa a NULL
    Lcidade listaPopularCIDADES = NULL;
    char ficheiroUsers[] = "C:\\Users\\Utilizador\\Desktop\\novo\\Dados.txt";
    char ficheiroCidades[] = "C:\\Users\\Utilizador\\Desktop\\novo\\Cidades.txt";
    Viagem a;
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
                listaUsers = registo(listaUsers);
                break;
            case 2:
                userLogado = login(listaUsers, userLogado);
                break;
            case 3:
                listar_DadosUser(userLogado);
                break;
            case 4:
                alterar_DadosUser(listaUsers, userLogado);
                break;
            case 5:
                alterar_PDIHOT(listaUsers, listaCidades, userLogado);
                break;
            case 6:
                alterar_PrefLocais(listaUsers, listaCidades, userLogado);
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
                    a = viagem(userLogado, listaUsers, listaPopularCIDADES, listaCidades);
                    if (a.Local1PDI1!=NULL)
                        imprime_Viagem(a, listaUsers);
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
    printf("\n2. Efetuar Login");
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
    printf("\nINTRODUZA O NOME:");
    gets(nome);
    user = getNoUser(lista, nome);
    if (user == NULL) {
        printf("*** Utilizador inexistente ***\n");
        return NULL;
    }
    return user;
}

/* REGISTO*/
LUser registo(LUser lista) {

    UserData user;
    int i;
    int ok = 0;
    char resposta[N];
    printf("\n######## REGISTO DE UTILIZADOR ########\n");

    do {
        printf("\n   NOME:");
        gets(resposta);

        if (resposta[0]=='\0'){
            return NULL;
        }

        if (VerificaEspacos(resposta) ==0 || VerificaAlgarismos(resposta) != 0 ) {
            printf("**Introduza um nome valido**");
        }
        else ok = 1;
    } while (ok==0);

    strcpy(user.nome, resposta);

    printf("   MORADA: ");
    gets(user.morada);

    ok = 0;
    do {
        printf("   DATA DE NASCIMENTO: ");
        gets(resposta);
        if (VerificaDataNascimento(resposta)!= 1) {
            printf("***Introduza uma data de nascimento valida (dia/mes/ano)***\n");
        }
        else ok = 1;
    } while (ok == 0);

    strcpy(user.data_nascimento, resposta);
    ok = 0;
    do {
        printf("   NUMERO DE TELEMOVEL: ");
        gets(resposta);
        if (VerificaAlgarismos(resposta) != 9 || VerificaChar(resposta)!=0) {
            printf("***Introduza um numero de telemovel valido***\n");
        }
        else ok = 1;
    } while (ok==0);

    strcpy(user.telemovel, resposta);
    user.prefLocal1 = NULL;
    user.prefLocal2 = NULL;
    user.prefLocal3 = NULL;
    user.hot = NULL;
    user.prefPontos = NULL;

    lista = insere_lista_USERS(lista, user);
    printf("\n***UTILIZADO REGISTADO COM SUCESSO***\n");
    return lista;
}
int VerificaAlgarismos(char *str) {
    int numero = 0, i;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (isdigit(str[i]) != 0)
            numero++;
    }
    return numero;
}
int VerificaDataNascimento(char *data) {
    int i;
    char *token;
    char str[15];
    int dia, mes, ano;
    char barra[2] = "/";
    strcpy(str, data);
    // Ver se só tem números e //
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != '/' && !isdigit(str[i]))
        {
            return 0;
        }
    }
    // partir pela /

    token =strtok(str, barra);
    if (token == NULL)
        return 0;
    dia = atoi(token);
    token = strtok(NULL, barra);
    if (token == NULL)
        return 0;
    mes = atoi(token);
    token = strtok(NULL, barra);
    if (token == NULL)
        return 0;
    ano = atoi(token);
    if (mes == 2 && dia > 28)
    {
        printf("Dia Invalido para mes de Fevereiro\n");
        return 0;
    }
    if (dia < 1 || dia > 31) {
        printf("Dia Invalido\n");
        return 0;
    }
    if (mes < 1 || mes > 12) {
        printf("Mes Invalido\n");
        return 0;
    }
    if (ano < 1900 || ano > 2019) {
        printf("Ano Invalido (1900 a 2019)\n");
        return 0;
    }

    return 1;
}


int VerificaChar(char *str) {
    int letras = 0, i;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (isalpha(str[i]) != 0)
            letras++;
    }
    return letras;
}

int VerificaEspacos(char *str) {
    int  i;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ')
            return 1;
    }
    return 0;
}
void alterar_DadosUser(LUser lista, LUser user) {

    char resposta[N];
    int ok = 0;

    if (VerificaUserLogado(user)) {
        printf("   MORADA: ");
        gets(resposta);

        strcpy(user->morada, resposta);

        do {
            printf("   DATA DE NASCIMENTO: ");
            gets(resposta);
            if (VerificaDataNascimento(resposta) != 1) {
                printf("***Introduza uma data de nascimento valida (dia/mes/ano)***\n");
            }
            else ok = 1;
        } while (ok == 0);

        strcpy(user->data_nascimento, resposta);

        ok = 0;
        do {
            printf("   NUMERO DE TELEMOVEL: ");
            gets(resposta);
            if (VerificaAlgarismos(resposta) != 9 || VerificaChar(resposta) != 0) {
                printf("***Introduza um numero de telemovel valido***\n");
            }
            else ok = 1;
        } while (ok == 0);

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
    float aux;


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
        if (user->hot!=NULL) {
            while (auxCidadePontos != NULL && continuar) {
                if (strcmp(auxCidadePontos->nome, user->hot->nome) == 0) {
                    viagem.Local1PDI1 = getNoPDI(listaC, auxCidadePontos->nome);
                    anterior->next = auxCidadePontos->next;
                    free(auxCidadePontos);
                    continuar = 0; // quando
                } else {
                    anterior = auxCidadePontos;
                    auxCidadePontos = auxCidadePontos->next;
                }
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
        if (user->hot!=NULL) {
            while (auxCidadePontos != NULL && continuar) {
                if (strcmp(auxCidadePontos->nome, user->hot->nome) == 0) {
                    viagem.Local2PDI1 = getNoPDI(listaC, auxCidadePontos->nome);
                    anterior->next = auxCidadePontos->next;
                    free(auxCidadePontos);
                    continuar = 0; // quando
                } else {
                    anterior = auxCidadePontos;
                    auxCidadePontos = auxCidadePontos->next;
                }
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
        if (user->hot!=NULL) {
            while (auxCidadePontos != NULL && continuar) {
                if (strcmp(auxCidadePontos->nome, user->hot->nome) == 0) {
                    viagem.Local3PDI1 = getNoPDI(listaC, auxCidadePontos->nome);
                    anterior->next = auxCidadePontos->next;
                    free(auxCidadePontos);
                    continuar = 0; // quando
                } else {
                    anterior = auxCidadePontos;
                    auxCidadePontos = auxCidadePontos->next;
                }
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

    }
    return viagem;
}

int verificaPDIemLista(LPdI pdi, LprefPdi lista) {
    LprefPdi l = lista;
    //printf("###ENTROU NA FUCN3");
    while (l) {
        if (strcmp(pdi->nome, l->prefPdi->nome) == 0) {
            return 1;
        }
        l = l->next;
    }
    return 0;
}


void alterar_PrefPDIS(LUser lista, LUser user, Lcidade listaC) {
    int numero;
    char nome[N];

    if (VerificaUserLogado(user)) {
        imprime_lista_PrefPDIs(user->prefPontos);
        do {
            printf("\n1-Adicionar\n2-Eliminar\n3-Voltar:");
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
LprefPdi  getNoPrefPDI(LprefPdi lista, char *pdi) {
    LprefPdi l = lista;
    int i, len_frase = strlen(pdi);
    while (l)
    {
        if (strcmp(strupr((l->prefPdi->nome)),strupr(pdi)) == 0) {
            return l;
        }
        else
            l = l->next;
    }
    return NULL;
}

LprefPdi apagar_PrefPDI(LprefPdi lista, LprefPdi apagar) {//APAGAR NO NA LSITA DE PREFERNCIAS PDIS CASO QUEIRA REMOVER
    LprefPdi l = lista;
    LprefPdi anterior;
    if (l == apagar) {
        l->contadorPDIS--;
        l->prefPdi->popular--;
        lista = lista->next;
        free(l);
        printf("PDI eliminado\n");
        imprime_lista_PrefPDIs(lista);
        return lista;
    }
    anterior = l;
    l = l->next;
    while (l != NULL) {
        if (l == apagar) {
            l->contadorPDIS--;
            l->prefPdi->popular--;
            anterior->next = l->next;
            free(l);
            printf("PDI eliminado\n");
            imprime_lista_PrefPDIs(lista);
            return lista;
        }
        else {
            anterior = l;
            l = l->next;
        }
    }
    printf("PDI inexistente");
    return lista;
}
LprefPdi adicionar_PrefPDI(LprefPdi lista, char *nome, Lcidade listaC) {
    LprefPdi no, anterior, ultimo;
    LPdI verificaPDI;
    if (getNoPrefPDI(lista, nome) != NULL) {
        printf("PDI ja esta nas preferencias\n");
    }
    else {//não existe na lista de pref e pode se adicionar
        verificaPDI = getNoPDI(listaC, nome);
        if (verificaPDI == NULL) {
            printf("PDI inexistente");
        }
        else {
            no = (LprefPdi)malloc(sizeof(Ponto_Interesse_Pref));
            if (no != NULL) {
                no->prefPdi = verificaPDI;
                no->prefPdi->popular++;
                no->contadorPDIS++;
                no->next = NULL;

            }
            if (lista == NULL) {
                lista = no;
            }
            else  //encontrar o ultimo da lista e inserir o no no fim
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

    char novoLocalPref[N], resposta[3];
    int numero, i;
    Lcidade aux;

    if (VerificaUserLogado(user)) {
        if (user->prefLocal1 != NULL) {
            printf("1. Local de Preferencia ATUAL: %s\n", user->prefLocal1->nome_cidade);
            if (user->prefLocal2 != NULL) {
                printf("2. Local de Preferencia ATUAL: %s\n", user->prefLocal2->nome_cidade);
                if (user->prefLocal3 != NULL)
                    printf("3. Local de Preferencia ATUAL: %s\n", user->prefLocal3->nome_cidade);
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
                                user->prefLocal2 = user->prefLocal3;
                                user->prefLocal3 = NULL;

                                break;
                            }
                            else {
                                aux = getNoCidade(listaC, novoLocalPref);
                                if (aux == NULL) {
                                    printf("Local inexistente\n");
                                }
                                else if (strcmp(novoLocalPref, user->prefLocal2->nome_cidade) == 0 || strcmp(novoLocalPref, user->prefLocal3->nome_cidade) == 0)
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
                                user->prefLocal2 = user->prefLocal3;
                                user->prefLocal3 = NULL;

                                break;
                            }
                            else {
                                aux = getNoCidade(listaC, novoLocalPref);
                                if (aux == NULL) {
                                    printf("Local inexistente\n");
                                }
                                else if (strcmp(novoLocalPref, user->prefLocal1->nome_cidade) == 0 || strcmp(novoLocalPref, user->prefLocal3->nome_cidade) == 0)
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
                                user->prefLocal3 = NULL;

                                break;
                            }
                            else {
                                aux = getNoCidade(listaC, novoLocalPref);
                                if (aux == NULL) {
                                    printf("Local inexistente\n");
                                }
                                else if (strcmp(novoLocalPref, user->prefLocal1->nome_cidade) == 0 || strcmp(novoLocalPref, user->prefLocal2->nome_cidade) == 0)
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
        else {
            printf("\nNAO TEM LOCAIS PREFERIDOS!\n");
            printf("\nDeseja adicionar Locais? <S|N>");
            gets(resposta);
            if (strcmp(resposta, "S") == 0 || strcmp(resposta, "s") == 0) {
                do {
                    printf("Introduza o novo Local Preferido 1: ");
                    gets(novoLocalPref);
                    aux = getNoCidade(listaC, novoLocalPref);
                    if (aux == NULL) {
                        printf("Local inexistente\n");
                    }
                    else {
                        user->prefLocal1 = aux;
                        user->prefLocal1->popular++;
                    }
                } while (aux == NULL);
                do {
                    printf("Introduza o novo Local Preferido 2: ");
                    gets(novoLocalPref);
                    aux = getNoCidade(listaC, novoLocalPref);
                    if (aux == NULL) {
                        printf("Local inexistente\n");
                    }
                    else {
                        if (user->prefLocal1==aux)
                        {
                            printf("Este local ja foi escolhido\n");
                            aux = NULL;
                        }
                        else {
                            user->prefLocal2 = aux;
                            user->prefLocal2->popular++;
                        }
                    }
                } while (aux == NULL);
                do {
                    printf("Introduza o novo Local Preferido 3: ");
                    gets(novoLocalPref);
                    aux = getNoCidade(listaC, novoLocalPref);
                    if (aux == NULL) {
                        printf("Local inexistente\n");
                    }
                    else {
                        if (user->prefLocal1 == aux || user->prefLocal2 == aux)
                        {
                            printf("Este local ja foi escolhido\n");
                            aux = NULL;
                        }
                        else {
                            user->prefLocal3 = aux;
                            user->prefLocal3->popular++;
                        }
                    }
                } while (aux == NULL);
                printf("***Locais preferidos atualizados***");
            }
        }
    }
}
void alterar_PDIHOT(LUser lista, Lcidade listaC, LUser user) {
    LPdI aux;
    char nomeNovoHot[N];
    if (VerificaUserLogado(user)) {
        printf("PDI HOT ATUAL: ");
        if (user->hot == NULL) {
            printf("Nao tem Ponto de Interesse HOT");

        }
        else {
            printf("%s", user->hot->nome);
        }
        do {
            printf("\nPDI HOT NOVO: ");
            gets(nomeNovoHot);

            if (nomeNovoHot[0] == '\0') {
                return;
            }
            aux = getNoPDI(listaC, nomeNovoHot);
            if (aux == NULL) {
                printf("Ponto de Interesse inexistente");
            }
        } while (aux == NULL);
        user->hot = aux;
        printf("\n**Ponto de Interesse HOT alterado com sucesso**");

    }

}



void  listar_DadosUser(LUser user) {
    if (VerificaUserLogado(user)) {
        printf("\n######## DADOS UTILIZADOR ########\n");
        printf("   NOME: %s", user->nome);
        printf("\n   MORADA: %s", user->morada);
        printf("\n   DATA DE NASCIMENTO: %s", user->data_nascimento);
        printf("\n   TELEMOVEL: %s", user->telemovel);
        printf("\n\n* PREFERENCIAS\n");

        if (user->prefLocal1 != NULL) {
            printf("   Pref. Local 1: %s\n", user->prefLocal1->nome_cidade);
            if (user->prefLocal2 != NULL) {
                printf("   Pref. Local 2: %s\n", user->prefLocal2->nome_cidade);
                if (user->prefLocal3 != NULL)
                    printf("   Pref. Local 3: %s\n", user->prefLocal3->nome_cidade);
            }
        }
        else {
            printf("   Nao existem locais preferidos definidos!\n");
        }
        if (user->hot != NULL) {
            printf("   PDI HOT: %s\n", user->hot->nome);
        }
        else {
            printf("   Sem Ponto de Interesse HOT definido\n");
        }
        imprime_lista_PrefPDIs(user->prefPontos);
        printf("\n");
    }
}
LUser getNoUser(LUser listaU, char *nome) {
    LUser l = listaU;
    if (strcmp(nome, " ") == 0) {
        return NULL;
    }
    while (l)
    {
        if (strcmp((l->nome), (nome)) == 0) {
            return l;
        }
        else
            l = l->next;
    }
    return NULL;
}

LUser carrega_listaUsers_ficheiro(char *nomeFicheiroUsers, Lcidade listaC) {
    LUser lista = NULL;
    char linha[256];
    char pref1[100], pref2[100], pref3[100];
    int i, contador = 0, len_frase;
    LUser noUser = NULL;

    UserData tempUser; //estrutura temporaria para guardar as informacoes
    FILE *ficheiroDados = fopen(nomeFicheiroUsers, "r");
    if (ficheiroDados == NULL) {
        printf("------------------------------------------\nNAO FOI POSSIVEL LER O FICHEIRO 'DADOS.TXT' COM OS DADOS DOS UTILIZADORES!\n ESPECIFIQUE O CAMINHO CORRECTO!\n------------------------------------------\n");
        return NULL;
    }

    if (ficheiroDados != NULL) {
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

            }
            else {
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
                        if (tempUser.prefLocal1 != NULL)
                            tempUser.prefLocal1->popular++;
                        tempUser.prefLocal2 = getNoCidade(listaC, pref2);
                        if (tempUser.prefLocal2 != NULL)
                            tempUser.prefLocal2->popular++;
                        tempUser.prefLocal3 = getNoCidade(listaC, pref3);
                        if (tempUser.prefLocal3 != NULL)
                            tempUser.prefLocal3->popular++;
                        contador++;
                        break;
                    case 5: //PDI HOT

                        tempUser.hot = getNoPDI(listaC, linha);

                        contador++;
                        break;
                    case 6:
                        //linha
                        tempUser.prefPontos = cria_lista_PrefPDIs(listaC, linha);
                        contador++;
                        break;
                }

            }
        }
        lista = insere_lista_USERS(lista, tempUser);
    }
    return lista;
}



void getDataPDI(char *linha, char *pdi, char *descricao, char *horario)
{
    char barra[] = "|";
    char *token;
    strcpy(pdi, strtok(linha, barra));
    token = strtok(NULL, barra);
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
    strcpy(pref1, strtok(linha, barra));
    strcpy(pref2, strtok(NULL, barra));
    strcpy(pref3, strtok(NULL, barra));
    //Se nao tiver preferencia fica com um espaço

}

Lcidade getNoCidade(Lcidade listaC, char *cidade) {
    Lcidade l = listaC->next;
    int i, len_frase = strlen(cidade), len_frase1;
    if (strcmp(cidade, " ") == 0) {
        return NULL;
    }
    while (l)
    {
        if (strcmp(strupr(l->nome_cidade), strupr(cidade)) == 0) {
            return l;
        }
        else
            l = l->next;
    }
    return NULL;
}

LPdI getNoPDI(Lcidade listaC, char *pdi) {//ver se o pdi existe nas listas da cidades
    Lcidade l = listaC->next; // saltar o header
    LPdI pdiaux;
    while (l)
    {

        pdiaux = l->pontos;
        pdiaux = pdiaux->next;  //AVANCA A CABEÇA - APAGAR
        while (pdiaux)
        {
            if (strcmp(strupr(pdi), strupr(pdiaux->nome)) == 0)
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
        if (l->prefLocal1 == NULL) {
            strcpy(pref1, " ");
        }
        else {
            strcpy(pref1, l->prefLocal1->nome_cidade);
        }
        if (l->prefLocal2 == NULL) {
            strcpy(pref2, " ");
        }
        else {
            strcpy(pref2, l->prefLocal2->nome_cidade);
        }
        if (l->prefLocal3 == NULL) {
            strcpy(pref3, " ");
        }
        else {
            strcpy(pref3, l->prefLocal3->nome_cidade);
        }
        fprintf(dados, "%s|%s|%s\n", pref1, pref2, pref3);
        if (l->hot == NULL) {
            fprintf(dados, " \n");
        }
        else {
            fprintf(dados, "%s\n", l->hot->nome);
        }
        LprefPdi aux = l->prefPontos;
        int inicio = 1;
        while (aux != NULL) {
            if (inicio == 1) {
                fprintf(dados, "%s", aux->prefPdi->nome);
                inicio = 0;
            }
            else
                fprintf(dados, "|%s", aux->prefPdi->nome);
            aux = aux->next;
        }
        fprintf(dados, "\n");
        l = l->next;


    }
    fclose(dados);
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

    for (i = 0; fgets(leitura, 1000, cidades) != NULL; i++) {

        if (leitura[0] == '*') {
            len = strlen(leitura);
            if (leitura[len - 1] == '\n')
                leitura[len - 1] = '\0';
            noLocal = insere_lista_CIDADES(lista, leitura + 1);
        }
        else {
            len = strlen(leitura);
            contadorPDISfich++;
            if (leitura[len - 1] == '\n')
                leitura[len - 1] = '\0';
            insere_lista_PDIS(noLocal->pontos, leitura + 1);
        }
    }
    //imprime_lista_CIDADES(lista);
    fclose(cidades);
}



//Lista ligada para as cidades

Lcidade cria_lista_CIDADES(void) {
    Lcidade aux;
    aux = (Lcidade)malloc(sizeof(Cidades));
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
        lista = lista->next;
        free(temp_ptr);
    }
    free(lista);
    return NULL;
}
int lista_vazia_CIDADES(Lcidade lista) {
    return (lista->next == NULL ? 1 : 0);
}
void procura_lista_CIDADES(Lcidade lista, char chave[], Lcidade *ant, Lcidade *actual) {
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
    no = (Lcidade)malloc(sizeof(Cidades));//reserva espaço para o nó
    if (no != NULL) {
        no->popular = 0;
        strcpy(no->nome_cidade, it);
        procura_lista_CIDADES(lista, it, &ant, &inutil);
        no->pontos = cria_lista_PDIS();
        no->next = ant->next;
        ant->next = no;
    }
    return no;
}
void imprime_lista_CIDADES(Lcidade lista) {
    Lcidade l = lista->next; /* Salta o header */
    if (l == NULL)
    {
        printf("Nao existem cidades e pontos de interesse registados!\n");
    }
    while (l) {
        printf("\n%s", l->nome_cidade);
        imprime_lista_PDIS(l->pontos);
        l = l->next;
    }
}


/*LISTA LIGADA PARA OS PONTOS DE INTERESSE*/

LPdI cria_lista_PDIS(void) {
    LPdI aux;
    aux = (LPdI)malloc(sizeof(Ponto_Interesse));
    if (aux != NULL) {
        aux->popular = 0;
        strcpy(aux->nome, "");
        strcpy(aux->descricao, "");
        strcpy(aux->horario, "");
        aux->next = NULL;
    }
    return aux;
}
LPdI destroi_lista_PDIS(LPdI lista) {
    LPdI temp_ptr;
    while (lista_vazia_PDIS(lista) == 0) {
        temp_ptr = lista;
        lista = lista->next;
        free(temp_ptr);
    }
    free(lista);
    return NULL;

}
int lista_vazia_PDIS(LPdI lista) {
    return (lista->next == NULL ? 1 : 0);
}
void procura_lista_PDIS(LPdI lista, char chave[], LPdI *ant, LPdI *actual) {
    *ant = lista;
    *actual = lista->next;
    while ((*actual) != NULL && strcmp((*actual)->nome, chave) < 0) {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && strcmp((*actual)->nome, chave))
        *actual = NULL;
}
void insere_lista_PDIS(LPdI lista, char it[]) {
    LPdI no;
    LPdI ant, inutil;
    char pdi[N], descricao[DESCRICAO], horario[HORARIO];
    getDataPDI(it, pdi, descricao, horario);
    no = (LPdI)malloc(sizeof(Ponto_Interesse));
    if (no != NULL) {
        no->popular = 0;
        strcpy(no->nome, pdi);
        strcpy(no->descricao, descricao);
        strcpy(no->horario, horario);
        procura_lista_PDIS(lista, pdi, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}
void imprime_lista_PDIS(LPdI lista) {
    LPdI l = lista->next; /* Salta o header */
    while (l) {
        printf("\n\t* %s", l->nome);
        if (strcmp(l->descricao, "") != 0)
            printf("\n\t  DESCRICAO: %s", l->descricao);
        if (strcmp(l->horario, "") != 0)
            printf("\n\t  HORARIO: %s", l->horario);
        l = l->next;
    }
}


//LISTA USERS

LUser destroi_lista_USERS(LUser lista) {
    LUser temp_ptr;
    while (lista_vazia_USERS(lista) == 0) {
        temp_ptr = lista;
        lista = lista->next; free(temp_ptr);
    }
    free(lista);
    return NULL;

}
int lista_vazia_USERS(LUser lista) {
    return (lista->next == NULL ? 1 : 0);
}
void procura_lista_USERS(LUser lista, char chave[], LUser *ant, LUser *actual)
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
LUser insere_lista_USERS(LUser lista, UserData  user) {
    LUser no;
    LUser ultimo, anterior;

    //cria o no
    no = (LUser)malloc(sizeof(UserData));
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
    if (lista == NULL)
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
void imprime_lista_USERS(LUser lista) {
    LUser l = lista;
    if (l == NULL)
    {
        printf("Nao existem utiliadores registados!\n");
    }
    while (l) {
        printf("\n######## DADOS UTILIZADOR ########\n");
        printf("   NOME: %s", l->nome);
        printf("\n   MORADA: %s", l->morada);
        printf("\n   DATA DE NASCIMENTO: %s", l->data_nascimento);
        printf("\n   TELEMOVEL: %s", l->telemovel);
        printf("\n\n* PREFERENCIAS\n");

        if (l->prefLocal1 != NULL) {
            printf("   Pref. Local 1: %s\n", l->prefLocal1->nome_cidade);
            if (l->prefLocal2 != NULL) {
                printf("   Pref. Local 2: %s\n", l->prefLocal2->nome_cidade);
                if (l->prefLocal3 != NULL)
                    printf("   Pref. Local 3: %s\n", l->prefLocal3->nome_cidade);
            }
        }
        else {
            printf("   Nao existem locais preferidos definidos!\n");
        }
        if (l->hot != NULL) {
            printf("   PDI HOT: %s\n", l->hot->nome);
        }
        else {
            printf("   Sem Ponto de Interesse HOT definido\n");
        }
        imprime_lista_PrefPDIs(l->prefPontos);
        printf("\n");
        l = l->next;
    }
}



void imprime_lista_PrefPDIs(LprefPdi lista) {
    LprefPdi l = lista;
    if (l == NULL) {
        printf("   Sem Pontos de Interesse preferidos");
        return;
    }

    while (l != NULL) {
        printf("   Pref. PDI: %s\n", l->prefPdi->nome);
        l = l->next;
    }
}
LprefPdi cria_lista_PrefPDIs(Lcidade listaC, char *pdi)//cria já colocando os elementos lá dentro
{
    LprefPdi lista = NULL;
    LprefPdi no;
    LprefPdi ultimo, anterior, inutil;
    char *token;

    token = strtok(pdi, "|");
    while (token != NULL) {
        no = (LprefPdi)malloc(sizeof(Ponto_Interesse_Pref));
        if (no != NULL) {
            no->contadorPDIS = 0;
            no->prefPdi = getNoPDI(listaC, token);
            //procura_lista_PrefPDISPop(lista, no->prefPdi->popular, &anterior, &inutil);
            if (no->prefPdi != NULL) {
                no->contadorPDIS++;
                no->prefPdi->popular++;
            }
            no->next = NULL;

        }
        if (lista == NULL)
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

    while (l != NULL) {
        //   if(l->popular != 0)
        {
            no = (Lcidade)malloc(sizeof(Cidades));
            if (no != NULL) {
                strcpy(no->nome_cidade, l->nome_cidade);
                no->popular = l->popular;
                procura_lista_CIDADESPop(lista, no->popular, &ant, &inutil);
                no->pontos = cria_lista_PDIS();
                insere_lista_PDISPop(no->pontos, l->pontos);
                no->next = ant->next;
                ant->next = no;
            }
        }
        l = l->next;
    }
}
void procura_lista_CIDADESPop(Lcidade lista, int chave, Lcidade *ant, Lcidade *actual) {
    *ant = lista;
    *actual = lista->next;

    while ((*actual) != NULL && (*actual)->popular > chave) {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && (*actual)->popular > chave)
        *actual = NULL;
}
void imprime_lista_CIDADESPop(Lcidade lista) {
    Lcidade l = lista->next; /* Salta o header */
    float aux;
    while (l) {
        if (l->popular != 0) {
            aux = l->popular / contadorUsers;
            aux = aux * 100.0;
            printf("\n<%s> , %.f%c", l->nome_cidade, aux, '%');
        }
        l = l->next;
    }
}


LPdI cria_lista_PDISPop() {
    LPdI aux;
    aux = (LPdI)malloc(sizeof(Ponto_Interesse));
    if (aux != NULL) {
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

    while (l != NULL) {
        //   if (l->popular != 0)
        {
            no = (LPdI)malloc(sizeof(Ponto_Interesse));//reserva espaço para o nó
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
void procura_lista_PDISPop(LPdI lista, int chave, LPdI *ant, LPdI *actual) {
    *ant = lista;
    *actual = lista->next;
    while ((*actual) != NULL && (*actual)->popular > chave) {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && (*actual)->popular > chave)
        *actual = NULL;
}

void imprime_lista_PDISPop(LPdI lista) {
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

void imprime_lista_POPULARIDADE(Lcidade lista) {
    Lcidade l = lista->next; /* Salta o header */
    float aux;
    while (l) {
        aux = l->popular / contadorUsers;
        aux = aux * 100.0;
        printf("[%.f%c]  %s \n", aux, '%', strupr(l->nome_cidade));
        //
        if (l->pontos->next == NULL)
            printf("\t\t***SEM PDIS***\n\n");
        else {
            printf("\t\t***POPULARIDADE DOS PONTOS DE INTERESSE***\n");
            imprime_lista_PDISPop(l->pontos);
            printf("\n");
        }
        l = l->next;
    }
}



void imprime_Viagem(Viagem v, LUser lista) {

    float aux, aux1, aux2;
    int contador = 0, contadorPrefPdisTotal = 0, contadorPrefPdisIncluidos = 0, contadorLocaisIncluidos = 0;
    LUser lu = lista;
    LprefPdi l = NULL;
    int locais = 0;

    while (lu != NULL) {
        if (lu->hot != NULL) {
            if ((strcmp(lu->hot->nome, v.Local1PDI1->nome) == 0) || (strcmp(lu->hot->nome, v.Local1PDI2->nome) == 0) || (strcmp(lu->hot->nome, v.Local1PDI3->nome) == 0) || (strcmp(lu->hot->nome, v.Local2PDI1->nome) == 0) || (strcmp(lu->hot->nome, v.Local2PDI2->nome) == 0) || (strcmp(lu->hot->nome, v.Local2PDI3->nome) == 0) || (strcmp(lu->hot->nome, v.Local3PDI1->nome) == 0) || (strcmp(lu->hot->nome, v.Local3PDI2->nome) == 0) || (strcmp(lu->hot->nome, v.Local3PDI3->nome) == 0)) {
                contador++;
            }
        }
        lu = lu->next;
    }
    lu = lista;


    while (lu != NULL) {

        if (lu->prefPontos != NULL) {
            l = lu->prefPontos;
            while (l) {
                contadorPrefPdisTotal++;
                if ((strcmp(l->prefPdi->nome, v.Local1PDI1->nome) == 0)
                    || (strcmp(l->prefPdi->nome, v.Local1PDI2->nome) == 0)
                    || (strcmp(l->prefPdi->nome, v.Local1PDI3->nome) == 0)
                    || (strcmp(l->prefPdi->nome, v.Local2PDI1->nome) == 0)
                    || (strcmp(l->prefPdi->nome, v.Local2PDI2->nome) == 0)
                    || (strcmp(l->prefPdi->nome, v.Local2PDI3->nome) == 0)
                    || (strcmp(l->prefPdi->nome, v.Local3PDI1->nome) == 0)
                    || (strcmp(l->prefPdi->nome, v.Local3PDI2->nome) == 0)
                    || (strcmp(l->prefPdi->nome, v.Local3PDI3->nome) == 0)) {
                    contadorPrefPdisIncluidos++;
                }
                l = l->next;
            }

        }

        lu = lu->next;
    }
    //ponto1
    lu = lista;
    while (lu != NULL) {
        if (lu->prefLocal1 != NULL) {
            locais++;
            if (strcmp(lu->prefLocal1->nome_cidade, v.Local1->nome_cidade) == 0
                || strcmp(lu->prefLocal1->nome_cidade, v.Local2->nome_cidade) == 0
                || strcmp(lu->prefLocal1->nome_cidade, v.Local3->nome_cidade) == 0) {
                contadorLocaisIncluidos++;
            }
            if (lu->prefLocal2 != NULL) {
                locais++;
                if (strcmp(lu->prefLocal2->nome_cidade, v.Local1->nome_cidade) == 0
                    || strcmp(lu->prefLocal2->nome_cidade, v.Local2->nome_cidade) == 0
                    || strcmp(lu->prefLocal2->nome_cidade, v.Local3->nome_cidade) == 0) {
                    contadorLocaisIncluidos++;
                }
                if (lu->prefLocal3 != NULL) {
                    locais++;
                    if (strcmp(lu->prefLocal3->nome_cidade, v.Local1->nome_cidade) == 0
                        || strcmp(lu->prefLocal3->nome_cidade, v.Local2->nome_cidade) == 0
                        || strcmp(lu->prefLocal3->nome_cidade, v.Local3->nome_cidade) == 0) {
                        contadorLocaisIncluidos++;
                    }
                }
            }
        }
        lu = lu->next;
    }


    //pontinho1
    aux2 = (float)contadorLocaisIncluidos / locais;
    aux2 = aux2 * 100;
    //pontinho2
    aux = (float)contador / contadorUsers;
    aux = aux * 100.0;
    //pontinho3

    aux1 = (float)contadorPrefPdisIncluidos / contadorPrefPdisTotal;
    aux1 = aux1 * 100.0;



    if (v.Local1 != NULL) {
        printf("\n############### VIAGEM GERADA ############### \n\n-- %s --> %s --> %s --\n", strupr(v.Local1->nome_cidade), strupr(v.Local2->nome_cidade), strupr(v.Local3->nome_cidade));
        printf("\nPONTOS DE INTERESSE A VISITAR:\n\n");
        printf("* %s\n", strupr(v.Local1->nome_cidade));
        printf("\t%s\n", v.Local1PDI1->nome);
        printf("\t%s\n", v.Local1PDI2->nome);
        printf("\t%s\n", v.Local1PDI3->nome);
        printf("* %s\n", strupr(v.Local2->nome_cidade));
        printf("\t%s\n", v.Local2PDI1->nome);
        printf("\t%s\n", v.Local2PDI2->nome);
        printf("\t%s\n", v.Local2PDI3->nome);
        printf("* %s\n", strupr(v.Local3->nome_cidade));
        printf("\t%s\n", v.Local3PDI1->nome);
        printf("\t%s\n", v.Local3PDI2->nome);
        printf("\t%s\n\n", v.Local3PDI3->nome);
        printf("PERCENTAGEM DE UTILIZADORES EM QUE O PDI HOT ESTA INCLUIDO NESTA VIAGEM: %.f%c\n", aux, '%');
        printf("PERCENTAGEM DAS PREFERENCIAS DE PDI: %.f%c\n", aux1, '%');
        printf("PERCENTAGEM DE UTILIZADORES QUE TEM PELO MENOS 1 LOCAL FAVORITO ENTRE OS INCLUIDOS NA VIAGEM:  %.f%c\n", aux2, '%');

    }
    else {
        printf("Não foi possível gerar a viagem!");
    }

}

