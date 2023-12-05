#include <stdio.h>
#include <string.h>

int minimax(char* tab, int turno, int primeira_vez);
int checar_vitoria(char tabuleiro[10]);
void mostrar(char tab[10]);
void menu();
void jogador();
int preenchidos(char tab[10]);

char simbolo_jogador;
char* tab_global = "_________";

int turno_global;

int main(void){

    printf("Bem-vindo ao jogo da velha humano vs maquina!\n");
    printf("Com qual voce vai jogar?\n\n");

    printf("Digite 'x' ou 'o' : ");
    scanf("%c", &simbolo_jogador);

    mostrar(tab_global);

    if(simbolo_jogador == 'x'){
        turno_global = 4;
        jogador();
    }
    else{
        turno_global = 1;
        menu();
    }
}

int minimax(char* tab, int turno, int primeira_vez){

    turno ++;

    int resultado = checar_vitoria(tab);

    if (resultado != 10){
        return resultado;
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

    int backup = 0;

    for(int i = 0; i < 9; i++){
        if(tab[i] == '_'){

            tab[i] = jogador_vez;

            int resultado = minimax(tab, turno, 0);

            tab[i] = '_';

            if(resultado == desejo){
                if(primeira_vez == 1){
                    tab[i] = jogador_vez;
                }
                return desejo;
            }
            if(resultado == 0){
                backup = i;
            }
        }
    }
    if(primeira_vez == 1){
        tab[backup] = jogador_vez;
    }    
    return 0;
}
void mostrar(char tab[10]){
    for(int i = 0; i <= 6; i += 3){

    printf("%c|%c|%c", tab[i], tab[i+1], tab[i+2]);
    
    printf("   %d|%d|%d\n",i+1,i+2,i+3);
    }
}
void menu(){

    // if(checar_vitoria(tab_global) != 10){
    //     printf("terminou\n\n");
    //     fim_jogo();
    // }
    
    minimax(tab_global, turno_global, 1);
    
    jogador();
}
void jogador(){
    int local;

    mostrar(tab_global);

    printf("\nEscolha o local onde vai jogar: ");
    scanf("%d", &local);

    tab_global[local -1] = simbolo_jogador;

    menu();
}
int preenchidos(char tab[10]){
    int num = 0;

    for(int i = 0; i < 9; i++){
        if(tab[i] != '_'){
            num  ++;
        }
    }

    return num;
}
int checar_vitoria(char *tabuleiro){
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
    if(preenchidos(tabuleiro) == 9){
        return 0;
    }

    return 10;
}
void fim_jogo(){
    printf("\n\n\n\n\n");

    printf("O jogo terminou!\n\n");
}
