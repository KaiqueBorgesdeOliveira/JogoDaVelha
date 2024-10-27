#include <stdio.h>
#include <stdlib.h>

// Declarando a Matriz do Jogo da Velha, 2 Vetores, tipo caractere que irão receber os nomes dos jogadores (Variável Global).

char jogo [3][3];
char jogador1[50], jogador2[50];

// Percorrendo a matriz linha x coluna, adiciona '_' a posição em branco.

void inicialmatriz(){
     int i, j;
     for(i = 0; i < 3; i++){
           for(j = 0; j < 3; j++){
                 jogo[i][j] = 'a';
           }      
     }     
}

// Função  verifica cada posição da matriz "Se Sim" Ao digitar X ou 0 retorna a função como true, "Se não" false.

int everdade(char letra){
        if(letra == 'X' || letra == '0'){
            return 1;
        }else {
            return 0;
        }
        
}

// Verifica se a coordenada digitada pelo usuário é valida.

int posicao_valida(int x, int y){
    if (x >= 0 && x < 3)
    {
        if(y >= 0 && y < 3){
            return 1;
        }
    }
    return 0;
}

// Verifica se uma posição da matriz é vazia

int posicaoVazia(int x, int y){
    if (jogo[x][y] != 'X' && jogo[x][y] != '0')
    {
        return 1;
    }
    return 0;
}

// Identifica vitória por Linha.

int ganhouLinhas(){
    int i, j, igual = 1;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 2; j++)
        {
            if(everdade(jogo[i][j]) && jogo[i][j] == jogo[i][j+1]){
                igual++;
            }

        }
        if(igual == 3){
            return 1;
        }
        igual = 1;
    }
    return 0;
}

// Identifica vitória por Colunas.

int ganhouColunas(){
    int i, j, igual = 1;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 2; j++)
        {
            if(everdade(jogo[j][i]) && jogo[j][i] == jogo[j+1][i]){
                igual++;
            }

        }
        if(igual == 3){
            return 1;
        }
        igual = 1;
    }
    return 0;
}

// Identifica vitória por Diagonal Principal.

int ganhouDiagPrincipal() {
    int i, igual = 1;
    for(i = 0; i < 2; i++){
        if (everdade(jogo[i][i]) && jogo[i][i] == jogo[i+1][i+1])
        
            igual++; 
    }
        if (igual == 3)
            return 1;
        else
            return 0;           
}

// Identifica vitória por Diagonal Secundária.

int ganhouDiagSecundaria() {
    int i, igual = 1;
    for(i = 0; i < 2; i++){
        if (everdade(jogo[i][3-i-1]) && jogo[i][3-i-1] == jogo[i+1][3-i-2])
            igual++;
    }
        if (igual == 3)
            return 1;
        else
            return 0;
}

// Imprimi a Matriz na tela

void imprimir(){
    int l, c;

    printf("\n\t   0  1  2\n");
    for (l = 0; l < 3; l++) 
    {
        printf("\t%d", l);
        for (c = 0; c < 3; c++)
        {
            if (everdade(jogo[l][c]))
            {
                if (c < 2)
                {
                    printf(" %c |", jogo[l][c]);
                }else{
                    printf(" %c ", jogo[l][c]);
                }
            }else{
                if(c < 2){
                    printf("   |");
                }else{
                    printf("   ");
                }
                
            }

        }
        if (l < 2)
        {
            printf("\n\t  ----------\n");
        }
        

    }
    
}

// Core. Parte Principal do Jogo.

void jogar(){
    int x, y, valida, jogadas = 0, ganhou = 0, ordem = 1;

    do 
    {
        do
        {
            imprimir();
            printf("\nDigite a coordenada que deseja jogar: ");
            scanf("%d%d", &x, &y);
            valida = posicao_valida(x, y);
                if (valida == 1)
                {
                    valida += posicaoVazia(x, y);
                }
                
        } while (valida != 2);
        
        if (ordem == 1)
        {
            jogo[x][y] = 'X';
        }else{
            jogo[x][y] = '0';
        }

        jogadas++;
        ordem++;

        if (ordem == 3)
        {
            ordem = 1;
        }
        
        ganhou += ganhouLinhas();
        ganhou += ganhouColunas();
        ganhou += ganhouDiagPrincipal();
        ganhou += ganhouDiagSecundaria();
    
    }while (ganhou == 0 && jogadas < 9);
    if (ganhou != 0)
    {
        if (ordem - 1 == 1)
        {
            printf("\nParabens! Voce venceu %s\n", jogador1);
        }else{
            printf("\nParabens! Voce venceu %s\n", jogador2);
        }
    }else{
        printf("\nNinguem Ganhou ^^\n\n");
    }

}

int main(){
    int op;

    printf("Jogador 1 Digite seu nome: ");
    fgets(jogador1, 50, stdin);

    printf("Jogador 2 Digite seu nome: ");
    fgets(jogador2, 50, stdin);
    do{
        inicialmatriz();
        jogar();
        printf("Deseja Jogar novamente?\n1 para Sim\n2 para Nao\n");
        scanf("%d", &op);
    }while (op == 1);
    
    return 0;
}
