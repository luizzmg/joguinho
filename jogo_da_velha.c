/*
    ===============================
    Jogo da velha Humano vs Máquina
    ===============================

    == FICR - Faculdade Católica Imaculada Conceicão do Recife
    == ADS - Curso superior em Análise e Desenvolvimento de Sistemas
    == 2º Período
    == Disciplina: Estrutura de Dados
    == Prof: Fred Lucena

    == Alunos do grupo:
    == Luiz Miguel Veloso, Rodrigo Albuquerque, Alicia Vital, Juan Victor, Gledson Pessoa



    == Sobre o jogo:

        O jogo a seguir se baseia no algoritmo minimax
        para fazer as escolhas da máquina no jogo da velha.

        O algorítmo minimax se baseia na construção de uma árvore
        que simula cada possível jogada, e escolhe a melhor.

        Foi uma tarefa desafiadora implementar este algorítmo,
        mas no final ele funcionou.

        Espero que goste.
    -



    == OBSERVAÇÃO:

        O jogo é impossível de ganhar.
        Sim, é impossível ganhar da máquina com este algorítmo.
        De certa forma é divertido tentar, mas as unicas possibilidades
        para o jogador são empate e derrota.
    -
*/

#include <stdio.h>

int minimax(int turno, int primeiro_nivel);

int checar_vitoria(), preenchidos(), min(int a, int b), max(int a, int b);
void mostrar(), maquina(), jogador(), fim_jogo(), menu();

int turno_global, num_vit_jogador;
char simbolo_jogador;
char tab_global[10] = {'_','_','_','_','_','_','_','_','_'};

int main(void){
    printf("Bem-vindo ao jogo da velha humano vs maquina!\n");
    menu();

    return 0;
}
void menu()           // exibe o menu principal
{
    printf("Com qual voce vai jogar? (obs: o 'x' sempre comeca)\n\n");
    printf("Digite x ou o : ");
    scanf("%c", &simbolo_jogador);

    if(simbolo_jogador == 'x' || simbolo_jogador == 'X'){
        num_vit_jogador = 1;
        turno_global = 4;

        // turno com num par que vai ser somado no inicio do minimax.
        // a jogada da máquina vai ser um 'o'

        jogador(); // o 'x' sempre começa (nesse caso o jogador)
    }
    else if (simbolo_jogador == 'o' || simbolo_jogador == 'O'){
        num_vit_jogador = -1;
        turno_global = 1;

        // turno com num impar que vai ser somado no inicio do minimax.
        // a jogada da máquina vai ser um 'x'

        maquina(); // o 'x' sempre começa (nesse caso a máquina)
    }
    else{
        printf("Opcao invalida.\n");
        menu();
    }
}
int minimax(int turno, int primeiro_nivel) // algoritmo protagonista de IA
{
    /*
    Essa parte do código é interessante.

    Foi difícil conseguir aplicar esse algoritmo,
    mas aí está ele.
    */    

    int teste, menos_pior = 0, backup = 20, novo;
    char simbolo_vez;

    teste = checar_vitoria();
    
    if(teste != 10){
        return teste; // chegamos numa folha da árvore
    }

    // temos que considerar as duas possibilidades de vez
    // o algoritmo faz a melhor escolha para cada simbolo
    // dependendo do nivel da arvore, pode ser a vez de x ou de o 

    turno ++;

    if(turno % 2 == 0){
        simbolo_vez = 'x'; 
        // vez de x (turnos pares)
        menos_pior = -1;   
        // ele vai procurar algo menos pior que isso
        // ou seja, maior, que é o max
    }
    else{
        simbolo_vez = 'o'; 
        // vez de o (turnos ímpares)
        menos_pior = 1;    
        // ele vai procurar algo menos pior que isso
        // ou seja, menor, que é o min 
    }

    for(int i = 0; i < 9; i++){
        if(tab_global[i] == '_'){
            /* 
            agora vamos fazer e desfazer cada jogada
            em cada possibilidade vazia no tabuleiro
            para ver se nesse galho dá para ter vitória
            */

            tab_global[i] = simbolo_vez;

            int resultado = minimax(turno, 0);

            tab_global[i] = '_';

            if(simbolo_vez == 'x') // quando é vez de x
            {    
                novo = max(menos_pior, resultado);

                if(primeiro_nivel == 1 && menos_pior < novo){
                    backup = i;
                }
                menos_pior = novo;
            }
            else if(simbolo_vez == 'o') // quando é vez de o
            {
                novo = min(menos_pior, resultado);
                
                if(primeiro_nivel == 1 && menos_pior > novo){
                    backup = i;
                }
                menos_pior = novo;
            }
        }
    }
    if(primeiro_nivel == 1) // quando estamos na raiz da arvore de simulação
    {
        tab_global[backup] = simbolo_vez; // fazendo a melhor jogada
    }
    return menos_pior;
}
void mostrar()        // exibe o tabuleiro atual
{
    for(int i = 0; i <= 6; i += 3){

    printf("%c|%c|%c", tab_global[i], tab_global[i+1], tab_global[i+2]);
    
    printf("   %d|%d|%d\n",i+1,i+2,i+3);
    }
}
void maquina()        // vez da máquina
{
    minimax(turno_global, 1);

    if(checar_vitoria(tab_global) != 10){
        fim_jogo();
    }
    else{jogador();}
}
void jogador()        // vez do jogador
{
    int local, perguntar = 1;

    do{ 
        mostrar(tab_global);
        printf("\nEscolha o local onde vai jogar: ");
        scanf("%d", &local);
        printf("\n\n\n");

    if(local < 1 || local > 9)
    {
        printf("Digite uma opcao valida\n");
    }
    else if(tab_global[local - 1] != '_')
        
    {
        printf("\nEste local ja esta preenchido. Digite uma opcao valida.\n");
        
    }
    else{
        perguntar = 0;
    }
    }while(perguntar == 1);

    tab_global[local -1] = simbolo_jogador; // o usuário jogou

    if(checar_vitoria() != 10){
        fim_jogo(); // acabou
    }
    else{maquina();} // vez da máquina
}
int preenchidos()     // retorna a quantidade de espaços preenchidos
{
    int cont = 0;

    for(int i = 0; i < 9; i++) // percorrendo todos os espaços
    {
        if(tab_global[i] != '_') // está preenchido
        {
            cont  ++;
        }
    }
    return cont;
}
int checar_vitoria()  // retorna 0 se velha, +1 se x, -1 se o, e 0 se NDA
{
    int num_vitoria = 1; //na primeira passada é assim 
    char letra = 'x';    // na segunda muda pq vamos olhar 'o'

    
    for(int k = 0; k<2; k++) // percorrendo 'x' (vence como +1) e 'o' (vence como -1)
    {
        for(int i = 0; i < 3; i+=3) // percorrendo as possibilidades horizontais e verticais
        {
            if(tab_global[i] == letra && tab_global[i+1] == letra && tab_global[i+2] == letra){
                return num_vitoria; // vitoria horizontal
            }
            if(tab_global[i] == letra && tab_global[i+3] == letra && tab_global[i+6] == letra){
                return num_vitoria; // vitoria vertical
            }
        }

        if(tab_global[0] == letra && tab_global[4] == letra && tab_global[8] == letra)
        {
            return num_vitoria; // vitoria diagonal assim: '-.
        }
        if(tab_global[2] == letra && tab_global[4] == letra && tab_global[6] == letra)
        {
            return num_vitoria; // vitoria diagonal assim: .-'
        }
        num_vitoria = -1; // trocando numero
        letra = 'o';      // trocando a letra
    }
    if(preenchidos() == 9)
    {
        return 0; // se chegou aqui deu empate
    }
    return 10; // inconlusivo (nem vitoria nem empate)
}
void fim_jogo()       // é chamada quando o jogo termina para finalizar
{
    printf("\n\n\n\n\n");

    printf("O jogo terminou!\n\n");

    mostrar(tab_global);

    int resultado = checar_vitoria(tab_global);

    if(resultado == num_vit_jogador)
    {
        printf("\nParabens, voce venceu...\n\n");
        printf("\nEmbora isso seja impossivel neste nivel de dificuldade\n\n");
    }
    else if(resultado == num_vit_jogador * -1)
    {
        printf("\nNao foi dessa vez...\n\n");
        printf("\nParece que voce perdeu\n\n");
    }
    else{
        printf("\nParece que temos um empate.\n\n");
    }

    char opcao = '#';

    do{
    printf("Quer jogar novamente?\nDigite s ou n: ");
    scanf("%c", &opcao);

    if(opcao == 's' || opcao == 'S'){
        menu();
    }
    }while(opcao != '#');
}
int min(int a, int b) // escolhe o menor entre dois valores
{
    if(a<b){return a;}
    else{return b;}
}
int max(int a, int b) // escolhe o maior entre dois valores
{
    if(a>b){return a;}
    else{return b;}
}