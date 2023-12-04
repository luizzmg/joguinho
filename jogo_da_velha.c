#include <stdio.h>
#include <string.h>

int minimax(char tabuleiro[10], int turno, int primeira_vez);
int checar_vitoria(char tabuleiro[10]);
void mostrar(char tab[10]);
int min(int a, int b);
int max(int a, int b);
char *copiar(char *vetor);
void menu();
void jogador();
int preenchidos(char tab[10]);
char tab_global[] = {'_','_','_','_','_','_','_','_','_'};
char simbolo_jogador;

int main(void){

    goto teste;

    char opcao;

    printf("Bem-vindo ao jogo da velha humano vs maquina!\n");
    printf("Com qual voce vai jogar?\n\n");

    printf("Digite 'x' ou 'o' : ");
    scanf(" %c", &opcao);

    if(opcao == 'x'){
        jogador();
    }
    else{
        menu();
    }

    teste:

    char tab[10] = {'_','_','_','_','_','_','_','_','_'};

    char novo[10];

    strcpy(novo, tab);

    tab[3] = 'x';

    mostrar(tab);

    mostrar(novo);

}

int minimax(char tabuleiro[10], int turno, int primeira_vez){
    
    printf("Chamada");
    
    turno ++;

    if(preenchidos(tabuleiro) == 9){
        return checar_vitoria(tabuleiro);
    }

    int desejo = 0;
    char jogador_vez;

    if(turno % 2 == 0){
        jogador_vez = 'x';
        int desejo = 1;
    }

    else{
        jogador_vez = 'o';
        int desejo = -1;
    }

    int menos_pior, backup = 0;

    for(int i = 0; i < 9; i++){
        if(tabuleiro[i] == '_'){

            tabuleiro[i] = jogador_vez;

            int resultado = minimax(tabuleiro, turno, 0);

            tabuleiro[i] = '_';

            if(jogador_vez == 'x'){
                menos_pior = max(-1, resultado);
            }
            else{
                menos_pior = min(1, resultado);
            }

            if(menos_pior == desejo){
                if(primeira_vez == 1){tab_global[i] = jogador_vez;}
                return desejo;
            }
            if(menos_pior == 0){
                backup = i;
            }
        }
    }

    if(primeira_vez == 1){tab_global[backup] = jogador_vez;}    
    return menos_pior;
}
void mostrar(char tab[10]){
    for(int i = 0; i <= 6; i += 3){

    printf("%c|%c|%c", tab[i], tab[i+1], tab[i+2]);
    
    printf("   %d|%d|%d\n",i+1,i+2,i+3);
    }
}
int min(int a, int b){
    if(a<b){return a;}
    else{return b;}
}
int max(int a, int b){
    if(a>b){return a;}
    else{return b;}
}
char *copiar(char vetor[10]){
    char copiado[10];

    for (int i = 0; i <= 9; i++){
        copiado[i] = vetor[i];
    }

    return &copiado[0];
}
void menu(){
    printf("Menu\n\n");

    // if(preenchidos(tab_global) == 9){
    //     printf("terminou\n\n");
    //     fim_jogo();
    // }

    printf("Primeira chamada");
    
    minimax(copiar(tab_global), 1, 1);
    
    printf("Continuou");
    
    jogador();
}
void jogador(){
    printf("Jogador\n\n");
    
    int local;

    mostrar(tab_global);

    printf("\nEscolha o local onde vai jogar: ");
    scanf("%d", &local);

    tab_global[local -1] = simbolo_jogador;

    menu();
}
int preenchidos(char tab[10]){
    printf("Func preenchidos");
    int num = 0;

    for(int i = 0; i < 9; i++){
        if(tab[i] != '_'){
            num  ++;
        }
    }

    return num;
}
int checar_vitoria(char tabuleiro[10]){
    /*
    0|1|2
    2|3|4
    5|6|7
    */

    char letra[] = {'x','o'};
    
    // Posições de Vitória
    int pv[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    
    for(int j = 0; j < 9; j++){
        for(int i = 0; i < 2; i++){
            if(tabuleiro[pv[j][0]]==letra[i] && tabuleiro[pv[j][1]]==letra[i] && tabuleiro[pv[j][2]]==letra[i]){
                
                if(letra[i] == 'x'){return 1;}

                else{return -1;}
            }
        }
    }
    
    // se empatou
    return 0;
}
void fim_jogo(){
    printf("\n\n\n\n\n");

    printf("O jogo terminou!\n\n");
}