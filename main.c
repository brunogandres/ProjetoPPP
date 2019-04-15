#include <stdio.h>

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


void lerficheiro();
void registo();
void ordemalfabetica();


int main() {
    registo();
}




void lerficheiro()
{
    FILE *cidades = fopen("C:\\Users\\Bruno Gandres\\Desktop\\Projeto\\Cidades.txt", "r");
    int i;
    char leitura[50];
    for(i = 0; fgets(leitura, 256, cidades); i++){
        printf("%s", leitura);
    }
    fclose(cidades);

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
void ordemalfabetica()
{

}
