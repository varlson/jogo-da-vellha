#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define SHIFT printf("\t\t\t\t")
#define size 17
#define rows 3
#define col 3
#ifdef _WIN32
    #define cls system("cls")
#else
    #define cls system("clear")
#endif
#define salvar "salvar"
#define voltar "voltar"
#define marcar "marcar"


struct{
    char nome[30];
    int vitoria;
    int empate;
    int derrota;
}typedef Ranking;








void salvarJogo(char* fileName, char *player1, char* player2, char ** tabela);
void exibir_menu_inicial();
int carregarJogo(char ** jogo, char* fileName, char *player1, char* player2);
void exibirRanking();
void exibirTela(char **tabela);
void tablePrinter(char ** table);
char ** incializador_de_tabela();
void menu_inicial(char ** tabela);
char * decodificador_de_instrucao(char * instrucao, char*);
void player(char* jagador1, char* jagador2, char **tabela, int numJogador);
int verificador_de_regra(int r, int c, char** tabela, char );
int verificaLinha(char playerSimbol, char** tabela);
int verificaColuna(char playerSimbol, char** tabela);
int verificaDiagPrin(char playerSimbol, char** tabela);
int verificaDiagSeg(char playerSimbol, char** tabela);
int verificarEspaco(char ** tabela);
void liberarMemoria(char ** tabela);
int verificarVencedor(char ** tabela, char  playerSimbol);
void extrair_nome_ficheiro(char *jogador1, char *jogador2, char* instrucao, char ** tabela);
Ranking* carregarArquivoInicial();
Ranking* autalizarArquivoInicial(char* player, Ranking* ranking, int vitoria, int derrota, int empa);
Ranking* salvarArquivoInicial(Ranking* ranking);
void ordenarRanking(Ranking* ranking);
void visualizar(Ranking* rank);
void pc_joga(int *rw, int*cl, char**);
int pos_valido(int *rw, int *cl, char** tabela);

int main(int argc, char const *argv[])
{   
    char pla1[20];
    char pla2[20];
    char **tabela = incializador_de_tabela();
    // carregarJogo(tabela, "meujogo.txt", pla1, pla2);
    menu_inicial(tabela);    
    // verificaLinha('x', tabela);
    // verificaColuna('o', tabela);
    // verificaDiagPrin('o', tabela);
    // verificaDiagSeg('x', tabela);

    // tablePrinter( tabela);


    // carregarArquivoInicial();
    return 0;
}   



void exibirTela(char ** tabela){
    for(int i=0; i<rows; i++){
            // printf("%c", tabela[i][j]);
        for(int j=0; j<col;j++){
        }
    }


}


void tablePrinter(char ** table){

    for(int i=0; i<rows;i++){
        SHIFT;
        for(int j=0;j<col; j++){
            printf("[ %c ]", table[i][j]);
        }
        printf("\n");
    }

        printf("\n");
}

char ** incializador_de_tabela(){

    char ** tabela = (char **)malloc(rows  * sizeof(char*));

    for(int i=0; i<col;i++) tabela[i] = (char*) malloc(sizeof(char)*col);
    
    if(tabela == NULL) return NULL;

    for(int i=0; i<rows;i++){
        for(int j=0; j<col;j++){
            tabela[i][j] = ' ';
        }
    }

    return tabela;
}

int carregarJogo(char ** jogo, char* fileName, char *player1, char* player2){

    FILE* file = fopen(fileName, "r");

    if(file==NULL){
        SHIFT;
        printf("Erro no carregamento, Verifique o arquivo de jogo!\n");
        return 0;
    }


    char temp;
    int c=0;
    int r=0;

    int plaNum;
    fscanf(file, "%d\n", &plaNum);
    fscanf(file, "%s\n", player1);
    fscanf(file, "%s\n", player2);
    // getchar();
    temp = fgetc(file);

    while(temp != EOF){
        if(temp != '\n'){
            jogo[r][c] = temp;
            c++;
        }
        // printf("%c", temp);
        if(c==3){
            c=0;
            r++;
        }

        if(r==3)break;;
        temp = fgetc(file);
    }

    fclose(file);
    return 1;
}


void exibir_menu_inicial(){
    cls;
    printf("\n");
    SHIFT;
    printf("0. Sair do jogo\n");
    SHIFT;
    printf("1. Começar novo jogo\n");
    SHIFT;
    printf("2. Continuar o jogo atual\n");
    SHIFT;
    printf("3. Exibir ranking\n");
    SHIFT;
    printf("Durante o jogo digite \"voltar\" para retornarao menu.\n");
    printf("\n");

}

void menu_inicial(char ** tabela){

    int opcao;
    char palyer1[50];
    char palyer2[50];
    int playerNumer;
    char nome_do_ficheiro[20];
    Ranking *rank;
    do{

        exibir_menu_inicial();
        SHIFT;
        printf(": ");
        scanf("%d", &opcao);
        SHIFT;
        switch (opcao)
        {

        case 0:
            sleep(2);
            SHIFT;
            printf("Saindo do jogo ..... ");
            liberarMemoria(tabela);
            break;

        case 1:
            // SHIFT;
            printf("Digite numero de jogares: ");
            scanf("%d", &playerNumer);
            SHIFT;
            printf("Digite o nome do jogador 1: ");
            scanf("%s", palyer1);
            getchar();
            if(playerNumer ==2 ){
                SHIFT;
                printf("Digite o nome do jogador 2: ");
                scanf("%s", palyer2);
                getchar();

            }else{
                strcpy(palyer2, "computador");
            }
            tabela = incializador_de_tabela();
            player(palyer1, palyer2, tabela, playerNumer);
            break;

        case 2:
            getchar();
            printf("\n");
            SHIFT;
            printf("Nome do arquivo: ");
            scanf("%s", nome_do_ficheiro);
            getchar();
            if(!carregarJogo(tabela, nome_do_ficheiro, palyer1, palyer2)){
                sleep(2);
            }else{
            
            if(strcmp("computador", palyer2)==0){
                player(palyer1, palyer2, tabela,1);
            }
                player(palyer1, palyer2, tabela,2);
            }
            break;
        case 3:
            rank = carregarArquivoInicial();
            visualizar(rank);
            SHIFT;
            printf("Precione tecla para voltar");
            getchar();
            getchar();
            break;
        
        default:
            printf("Escolhe uma opção correta");
            break;
        }
    }while(opcao != 0);
}

void salvarJogo(char* fileName, char *player1, char* player2, char ** tabela){

    FILE* file = fopen(fileName, "w");
    if(!file) {
        printf("Houve um problema, nao foi possivel salvar o jogo");
        exit(1);
    }

    fprintf(file, "%d\n", 2);
    fprintf(file, "%s\n", player1);
    fprintf(file, "%s\n", player2);

    for (int i=0;i<rows; i++){
        for(int j=0; j<col;j++){
            fputc(tabela[i][j], file);
        }
            fputc('\n', file);
    }

    fclose(file);
}



void player(char* jogador1, char* jogador2, char **tabela, int numJogador){
    cls;
    int alternador=0;
    char instrucao[50] ;
    char ins_decod[7];
    char atual_jogador[50];
    // player1 = 'x'
    // player2 = 'o'

    Ranking *ranking = carregarArquivoInicial();

    char playerSimbol;
    while(1){

        tablePrinter(tabela); 
        SHIFT;
        if(alternador %2==0){
            playerSimbol = 'x';
            strcpy(atual_jogador, jogador1);
            printf("%s, digite o comando: ", jogador1);   
        }else{
            playerSimbol = 'o';
            strcpy(atual_jogador, jogador2);
            if(numJogador==1){
                printf("%s, digite o comando:\n", jogador2);
            } else{
                printf("%s, digite o comando:", jogador2);
            }
        }
        if(numJogador==1 && (alternador%2!=0)){
            sleep(1);
            strcpy(instrucao, "marcar xx");
        }else{
            fgets(instrucao, 50,stdin);
        }
        // SHIFT;
        strncpy(ins_decod, instrucao, 6);
        if(!strcmp(ins_decod, voltar)) return ;
        else if(!strcmp(ins_decod, marcar)){
            if(numJogador == 1 && alternador % 2!= 0 ){
                int rw, cl;
                pc_joga(&rw, &cl, tabela);
                // printf("pos de com %d %d \n", rw,cl);
                if(!verificador_de_regra(rw, cl,tabela, playerSimbol)){
                    printf("Jogada incorreta,do computadpr, ele vai joga novamente!\n");
                    sleep(1);
                    continue;
                }
            }else{
                int sz = strlen(instrucao);
                const char _r = instrucao[sz-2];
                const char _c = instrucao[sz-3];
                int rw = (int) _r - 48;
                int cl = (int) _c - 48;

                int vit=0, emp=0, der=0;
                if(!verificador_de_regra(rw, cl,tabela, playerSimbol)){
                    SHIFT;
                    printf("Jogada incorreta,joga novamente!\n");
                    continue;
                }
            }
            if(verificarVencedor(tabela, playerSimbol) || !verificarEspaco(tabela)){
                if(verificarVencedor(tabela, playerSimbol)){
                    SHIFT;
                    printf("Parabens %s, voce ganhou!\n", atual_jogador);
                    autalizarArquivoInicial(atual_jogador, ranking, 1, 0, 0);
                    if(strcmp(atual_jogador,jogador1)==0)
                        autalizarArquivoInicial(jogador2, ranking, 0, 0, 1);
                    else
                        autalizarArquivoInicial(jogador1, ranking, 0, 0, 1);
                }else{
                    SHIFT;
                    autalizarArquivoInicial(atual_jogador, ranking, 0, 1, 0);
                    if(strcmp(atual_jogador,jogador1)==0)
                        autalizarArquivoInicial(jogador2, ranking, 0, 1, 0);
                    else
                        autalizarArquivoInicial(jogador1, ranking, 0, 1, 0);
                    printf("Houve empate!\n");
                }   
                
                // visualizar(ranking);
                salvarArquivoInicial(ranking);
                tabela = incializador_de_tabela();
                SHIFT;
                printf("Digite qualquer tecla para continuar!\n");
                SHIFT;
                getchar();
                return;
            }
            alternador++;
        }
        else if(!strcmp(ins_decod, salvar)){
            extrair_nome_ficheiro(jogador1,jogador2, instrucao, tabela);
        }else{
            SHIFT;
            printf("Entre com instrução correta\n");
            sleep(1);
        }

        
    }

}


int verificador_de_regra(int c, int r, char** tabela , char player){

    if(r >= 3 || c >= 3){
        return 0;
    }
    if(tabela[r][c] == ' '){
        tabela[r][c] = player;
        return 1;
    }else{
        return 0;
    }
}

int verificaLinha(char playerSimbol, char** tabela){
    for(int i =0; i<rows; i++){
        int counter=0;
        for(int j=0; j<col;j++){
            if(tabela[j][i] == playerSimbol) counter++;
        }

        if(counter==3){
            return 1;
        } 
    }

    return 0;
}

int verificaColuna(char playerSimbol, char** tabela){
    for(int i =0; i<rows; i++){
        int counter=0;
        for(int j=0; j<col;j++){
            if(tabela[i][j] == playerSimbol) counter++;
        }

        if(counter==3){
            return 1;
        } 
    }

    return 0;
}

int verificaDiagPrin(char playerSimbol, char** tabela){
    int counter=0;
    for(int i =0; i<rows; i++){
        for(int j=0; j<col;j++){
            if(i==j){
                if(tabela[i][j] == playerSimbol){
                    counter++;
                } 
            }
        }
    }
    if(counter==3){
        return 1;
    } 

     return 0;
}

int verificaDiagSeg(char playerSimbol, char** tabela){
    int counter=0;
    for(int i =0; i<rows; i++){
        for(int j=0; j<col;j++){
            if(i+j == 2){
                if(tabela[i][j] == playerSimbol) counter++;
            }
        }

    }
    if(counter==3){
        return 1;
    } 

     return 0;
}

int verificarEspaco(char ** tabela){
    for(int i=0; i<rows; i++){
        for(int j=0; j<col;j++){
            if(tabela[i][j] == ' ') return 1;
        }
    }
    return 0;
}


void liberarMemoria(char ** tabela){

    for( int i=0; i<rows;i++){
        free(tabela[i]);
    }

    free(tabela);
}

int verificarVencedor(char ** tabela, char  playerSimbol){
    if(verificaColuna(playerSimbol, tabela) || 
    verificaDiagPrin(playerSimbol, tabela) ||
    verificaDiagSeg(playerSimbol, tabela) ||
    verificaLinha(playerSimbol, tabela)) return 1;
    return 0;
}

void extrair_nome_ficheiro(char *jogador1, char *jogador2, char* instrucao, char ** tabela){


    int counter=0;
    int start=0, end=0;
    int act=0;
    for(int i=0; i<strlen(instrucao); i++){
        if(act){
            if(instrucao[i] != '.'){
                counter++;
            }else{
                end=i;
                break;
            }
        }

        if(instrucao[i] == ' '){
            act=1;
            start = i+1;
        }
    }


    char nome[counter+4];   

    for(int i=start,j=0; i<end;i++, j++){
        nome[j] = instrucao[i];
    }

    strncat(nome, ".txt ", 4);
    // printf("nome: %s", nome);

    salvarJogo(nome, jogador1, jogador2,  tabela);
    SHIFT;
    printf("Arquivo \"%s\" salvo com sucesso!\n", nome);
}

Ranking* carregarArquivoInicial(){
    
    int quant;
    Ranking *ranking = (Ranking*)malloc(sizeof(Ranking) * 10);
    FILE* file = fopen("velha.ini", "r");
    if(!file){
        SHIFT;
        printf("O arquivo de ranking nao encontrado!\n");
        return NULL;
    }

    fscanf(file, "%d\n", &quant);

    if(quant >= 1){
        int vit, emp, der;
        char nome[30];
        for(int i=0; i<quant; i++){
            fscanf(file, "%s\n", nome);
            fscanf(file, "%d\n", &vit);
            fscanf(file, "%d\n", &emp);
            fscanf(file, "%d\n", &der);

            ranking[i].vitoria = vit;
            ranking[i].empate = emp;
            ranking[i].derrota = der;
            strcpy(ranking[i].nome, nome);
        }
    }


    for(int i=quant;i<10;i++){
        ranking[i].vitoria=-1;
    }

    fclose(file);
    return ranking;
}



void ordenarRanking(Ranking* ranking){
   int i, j, temp;  
   for(i = 0; i < 10; i++)    
    {    
      for(j = i+1; j < 10; j++)    
        {    
            if(ranking[j].vitoria > ranking[i].vitoria)    
            {    
                Ranking temp = ranking[i];    
                ranking[i] = ranking[j];    
                ranking[j] = temp;     
            }     
        }     
    }     
    // visualizar(ranking);
}

Ranking* autalizarArquivoInicial(char* player, Ranking* ranking, int vitoria, int empate, int derrota){
    
    int j;

    for(int i=0; i<10;i++){
        if(ranking[i].vitoria != -1){
            if(strcmp(ranking[i].nome, player) == 0){
                if(vitoria){
                    ranking[i].vitoria++;
                }else if(derrota){
                    ranking[i].derrota++;
                }else{
                    ranking[i].empate++;
                }

                ordenarRanking(ranking);
                return ranking;
            }
        }else{
            break;
        }
    }

    for(j=0; j<10;j++){
        if(ranking[j].vitoria == -1) break;
    }

    strcpy(ranking[j].nome, player);
    ranking[j].vitoria = vitoria;
    ranking[j].derrota = derrota;
    ranking[j].empate = empate;


    ordenarRanking(ranking);
    
    return ranking;
}


Ranking* salvarArquivoInicial(Ranking* ranking){

    int counter=0;

    for(int i=0; i<10;i++){
        if(ranking[i].vitoria != -1){
            counter++;
        }
    }

    FILE* file = fopen("velha.ini", "w");
    if(!file) {
        printf("Houve um problema, nao foi possivel salvar o ranking");
        exit(1);
    }

    fprintf(file, "%d\n", counter);

    for(int i=0;i<counter;i++){
        fprintf(file, "%s\n", ranking[i].nome);
        fprintf(file, "%d ", ranking[i].vitoria);
        fprintf(file, "%d ", ranking[i].empate);
        fprintf(file, "%d\n", ranking[i].derrota);
    }


    fclose(file);
}

void pc_joga(int *rw, int*cl, char** tabela){

    srand(time(0));
    while(1){
        *rw = rand()%3;
        *cl = rand()%3;
        if(pos_valido(rw,cl, tabela)){
            return ;
        }
    }
}

void visualizar(Ranking* rank){

    // SHIFT;
    printf("..:: Ranking ::...\n");
    for(int i=0; i<10; i++){
        if(rank[i].vitoria != -1){
            SHIFT;
            printf("%s\n", rank[i].nome);
            SHIFT;
            printf("%d ", rank[i].vitoria);
            printf("%d ", rank[i].empate);
            printf("%d\n", rank[i].derrota);
            printf("\n");
        }

    }
}


int pos_valido(int *rw, int *cl, char** tabela){

    if(tabela[*rw][*cl] == ' ')
        return 1;
    else
        return 0;
}