#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

 // funcao generica usada para validar variaveis do tipo char
char validarchar(char A, char B, char a, char b) {
    char e;
    do {
        scanf(" %c", &e);
        if (e != A && e != B && e != a && e != b) {
            printf("O tipo e invalido!Introduza novamente\n");
        }
    } while (e != A && e != B && e != a && e != b);
    return e;
}

// funcao generica para validar variaveis do tipo int
int validarInt(int a, int b) {
    int n;

    do {
        scanf("%d", &n);
        if (n < a || n > b)
            printf("O valor introduzido e invalido! tente novamente\n");
    } while (n < a || n > b);
    return n;
}

// funcao que ira fazer a validacao do numero de telemovel
int validarnumero(int a, int b) {
    int c;

    do {
        scanf("%d", &c);
        if (c < a || c > b)
            printf("O Numero introduzido e invalido!\nVerifique se quantidade de digitos introduzida e corresponde a 9 algarismos e se contem os prefixos nacionais:\nTMCEL (82/83) \nVodacom (84/85) \nMovitel (86/87)\n");
    } while (c < a || c > b);
    return c;
}

// funcao que tem a funcao de validar a idade
int validaridade() {
    int n;
    do {
        scanf("%d", &n);
        if (n < 0) {
            printf("Introduziu uma idade invalida! tente novamente\n");
        }
    } while (n < 0);
    return n;

}

// funcao que armazenas os dados no ficheiro
void salvarDados(char genero, int nr_telemovel, char resu_Teste, char tp_Teste, char vacina, float vlr_pagar, int idade){
    FILE *fp;
    fp  = fopen ("dados.txt", "ab");

    char buffer[100];
    snprintf(buffer, sizeof(buffer), "|%8c|%17d|%7d|%11c|%10c|%8c|%12.2f MT|\n", genero, nr_telemovel, idade, resu_Teste, tp_Teste, vacina, vlr_pagar);

    fprintf(fp, buffer);
    fclose (fp);
}

// funcao que mostra a percentagem dos casos negativos e positivos
void visualizarPER(int a, int b, int c) {

    int per_Pos, per_Neg;
    per_Pos = a * c / (a + b);
    per_Neg = b * c / (a + b);
    printf("A percentagem dos casos positivos e': %d%% \n", per_Pos);
    printf("A percentagem dos casos negativos e': %d%% \n", per_Neg);
}

// funcao que visualiza a quantidade de testes realizado de cada tupo
void visualizarTeste(int a, int b) {
    printf("TOTAL DE TESTES: %d \n", a+b);
    printf("A quantidade de testes Rapidos realizados foi: %d \n", a);
    printf("A quantidade de testes PCR realizados foi: %d \n", b);
}

// funcao que visualiza o valor total obitido
void visualizarTotal(float vlr_total) {
    //DecimalFormat mt = new DecimalFormat("###,###,###.00 MTS\n");
    printf("O valor total recebido pela empresa e': %0.2f MTS \n", vlr_total);
}

// funcao que visualiza a quantidade de pessoas que precisam de Vacina
void visualizarNaoVacinados(int cont_NV)  {
    printf("A quantidade de pessoas que precisam de Vacina: %d \n", cont_NV);
}

// funcao que visualiza a pessoa mais velha e mais nova contaminada
void visualizaPessoas(int indice, int estrogonof) {
    printf(" a pessoa mais nova contamina tem %d anos \n", indice);
    printf(" a pessoa mais velha contamina tem %d anos \n", estrogonof);
}

// funcao que gera o cabecalho das tabelas (nao necessario repetir)
void cabecalho(){
    printf("_____________________________________________________________________________________\n");
    printf("| genero | Nr de Telemovel | idade |resu_Teste | tp_Teste | vacina | valor a pagar |\n");
    printf("_____________________________________________________________________________________\n");
}

// funcao que faz a leitura do ficheiro Dados.txt
void verDados() {
    printf("********************************DADOS DA ARMAZENADOS*********************************\n"); // titulo da tabela
    cabecalho(); //chama a funcao cabecalho
    FILE *fp;

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp  = fopen ("dados.txt", "r");
    if (fp == NULL)
        printf("===============================SEM DADOS GRAVADOS====================================\n");

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
    }

    fclose(fp);
    if (line)
        free(line);
    printf("===================================FIM DA TABELA=====================================\n\n");
}

// funcao que faz a leitura do ficheiro Dados.txt
void gerarEstatisticas(char type) {
    printf("************************************ESTATISTICAS**************************************\n"); // titulo da tabela
    FILE *fp;

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int rapido = 0, pcr = 0, pos = 0, neg = 0;
    float valor_total = 0;


    fp  = fopen ("dados.txt", "r");
    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("TIPO %c\n", line[57]); 
        if (line[57] == 'R') // checa testes rapidos e conta
            rapido++;
        if (line[57] == 'P') // checa testes pcr e conta
            pcr++;
        if (line[46] == 'P') // chaca casos positivoos no ficheiro e conta
            pos++;
        if (line[46] == 'N') // checa casos negativos no ficheiro e conta
            neg++;

        if (line[73] == '1') // calcula total recebido
            valor_total+= 1000;
        if (line[73] == '3') // calcula total recebido
           valor_total+= 3500;
    }

     switch (type) {
        case 't':
            visualizarTeste(rapido, pcr); // visualiza testes
            break;
        case 'p':
            visualizarPER(pos, neg, 100); //visualiza percentagem
            break;
        case 'e':
            visualizarTotal(valor_total); //visualiza percentagem
            break;
     }

    fclose(fp);
    if (line)
        free(line);
    printf("===================================FIM DA ESTATISTICAS================================\n\n");
}

// Meto que visualiza a tabela
void visualizarTabela(char genero, int nr_telemovel, char resu_Teste, char tp_Teste, char vacina, float vlr_pagar, int idade) {

    printf("*******************************DADOS DA ULTIMA VENDA*********************************\n"); //titulo da tabela
    cabecalho(); // chama cabecalho
    printf("|%8c|%17d|%7d|%11c|%10c|%8c|%12.2f MT|\n", genero, nr_telemovel, idade, resu_Teste, tp_Teste, vacina, vlr_pagar); //to see
    printf("_____________________________________________________________________________________\n");
    printf("\n");
}

// funcao que acha a maior idade
int achar_Maior(int indice, int idade, int cont_Pos) {
    if (indice > idade)
        indice = idade;

    return indice;
}

// funcao que acha a menor idade
int achar_Menor(int estrogonof, int idade, int cont_Pos) {
    if (estrogonof < idade)
        estrogonof = idade;
    return estrogonof;
}

// funcao que visualiza dados do programador
void visualizaDados() {
    printf("Dado do Programador\n");
}

    // funcao do Menu.
void menu() {
    char genero = ' ', resu_Teste = ' ', tp_Teste = ' ', vacina = ' ';
    int idade = 0, op, cont_R = 0, cont_PCR = 0, cont_Pos = 0, cont_NEG = 0, cont_NV = 0, idade_menor = 0, idade_maior = 0, indice = 0, estrogonof = 0;
    int nr_telemovel = 0;
    const float RAP = 1000, PCR = 3500;
    const int PER = 100;
    float vlr_pagar = 0, vlr_total = 0;
    bool passou = true;

    do {
        printf("\n");
        printf("*************************MENU***********************\n");

        printf("1. Receber os dados do Paciente\n");
        printf("2. Visualizar todos os dados em forma de tabela\n");
        printf("3. Quantidade de Testes que foram feitos de cada Tipo\n");
        printf("4. Visualizar a percentagem dos casos Positivos e Negativos\n");
        printf("5. Valor total obtido pela empresa.\n");
        printf("6. Quantidade de pessoas que precisam de Vacina\n");
        printf("7 Achar a pessoa mais velha e mais nova contaminada\n");
        printf("8. Visualizar dados do programador\n");
        printf("9. Sair do Programa\n");
        printf("\n");
        printf("Por favor Escolha uma opcao\n");

        printf("\n");

        op = validarInt(1, 9);

        switch (op) {
            case 1:
                printf("Introduza o tipo de teste que deseja realizar (R-Rapido P-PCR)\n");
                tp_Teste = validarchar('R', 'P', 'r', 'p');
                printf("\n");
                printf("Introduza a idade do paciente(>0)\n");
                idade = validarInt(0, 122);
                printf("\n");
                printf("Introduza o numero de telemovel do paciente ( Note que ele deve ter 9 digitos)\n");
                nr_telemovel = validarnumero(820000000, 879999999);

                printf("\n");
                printf("Introduza o genero do paciente (M-masculino e F-femenino)\n");
                genero = validarchar('M', 'F', 'm', 'f');
                printf("\n");
                printf("Introduza o resultado do teste do paciente (P-positivo ou N-negativo)\n");
                resu_Teste = validarchar('P', 'N', 'p', 'n');
                printf("\n");
                printf("informe o estado de vacinacao do paciente (S-sim ou N-nao)\n");
                vacina = validarchar('S', 'N', 's', 'n');

                switch (tp_Teste) {
                    case 'R':
                        vlr_pagar = RAP;
                        cont_R++;
                        break;

                    case 'P':
                        vlr_pagar = PCR;
                        cont_PCR++;
                        break;
                }

                switch (resu_Teste) {
                    case 'P':
                        cont_Pos++;

                        if (cont_Pos == 1)
                            indice = idade;

                        idade_maior = achar_Maior(indice, idade, cont_Pos);
                        idade_menor = achar_Menor(indice, idade, cont_Pos);
                        break;

                    case 'N':
                        cont_NEG++;
                        break;
                }

                switch (vacina) {
                    case 'S':
                        visualizarTabela(genero, nr_telemovel,resu_Teste, tp_Teste, vacina, vlr_pagar, idade);
                        salvarDados(genero, nr_telemovel,resu_Teste, tp_Teste, vacina, vlr_pagar, idade);
                        break;
                    case 'N':
                        cont_NV++;
                        break;
                }

                vlr_total += vlr_pagar;
                passou = false;
                break;

            case 2:
                verDados();
                if (passou == true)
                    printf("porfavor execute a primeira opcao\n");
                else
                    verDados();
                    //visualizarTabela(genero, nr_telemovel,resu_Teste, tp_Teste, vacina, vlr_pagar, idade);
                break;
            case 3:
                gerarEstatisticas('t'); //ver estatistica do tipo testes feitos (f)
                break;
            case 4:
                gerarEstatisticas('p'); //ver estatistica do tipo percentagem feitos (p)
                break;
            case 5:
                gerarEstatisticas('e'); //ver valor arrecadado (o)
                break;
            case 6:
                if (passou == true)
                    printf("porfavor execute a primeira opcao\n");
                else
                    visualizarNaoVacinados(cont_NV);
                break;
            case 7:
                if (passou == true)
                    printf("porfavor execute a primeira opcao\n");
                else
                    visualizaPessoas(indice, estrogonof);
                break;
            case 8:
                visualizaDados();
                break;
            case 9:
                printf(" Ate a proxima :)\n");
        }
    } while (op != 9);
}

int main() {
    printf("|=============SISTEMA DE GESTAO COVID==============|\n");
    menu();
    return 0;
}