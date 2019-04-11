#include <stdio.h>


void lerficheiro();

int main() {
    lerficheiro();
    return 0;
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