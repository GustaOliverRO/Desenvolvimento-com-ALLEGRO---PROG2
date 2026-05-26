#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_primitives.h>
#include "Mapa.h"



mapa* mapa_create() {
    
    mapa *new_mapa = malloc(sizeof(mapa));

    if(!new_mapa)
        return NULL;
    
    int cenario[MAPA_LINHAS][MAPA_COLUNAS] = {
        {0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,0},
        {0,0,0,2,0,0,0,2,0,0,0,2,0,0,0,2},
        {0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    for(int i = 0; i < MAPA_LINHAS; i++){
        for(int j = 0; j < MAPA_COLUNAS; j++)
            new_mapa->MATRIZ_mapa[i][j] = cenario[i][j];
    }
                                    
    return new_mapa;
}

void mapa_draw(mapa *element){

    int x, y; // Variaveis para eu conseguir desehar o chão;
    ALLEGRO_COLOR cor_do_chao = al_map_rgb(169,42,42); //MARROM
    ALLEGRO_COLOR cor_da_nuvem = al_map_rgb(255,255,255); //BRANCO

    // ta muito feio isso aqui
    for(int i = 0; i < MAPA_LINHAS; i++){
        for(int j = 0; j < MAPA_COLUNAS; j++){
            if(element->MATRIZ_mapa[i][j] == CHAO){
                x = j * BLOCO_MAPA;
                y = i * BLOCO_MAPA;

                al_draw_filled_rectangle(x, y, x + BLOCO_MAPA, y + BLOCO_MAPA,cor_do_chao);
                printf("Desenhando chao no X: %d, Y: %d\n", x, y);
                //al_draw_rectangle(x, y, x + BLOCO_MAPA, y + BLOCO_MAPA, cor_borda, 2);            }
            }
            else if(element->MATRIZ_mapa[i][j] == NUVEM){
                x = j * BLOCO_MAPA;
                y = i * BLOCO_MAPA;

                al_draw_filled_rectangle(x, y, x + BLOCO_MAPA, y + BLOCO_MAPA,cor_da_nuvem);
            }
        }
    }
}

int mapa_get_bloco(mapa *element, int px, int py){

    int coluna = px / BLOCO_MAPA;
    int linha = py / BLOCO_MAPA;

    // Trava de segurança: se perguntar algo fora da tela, trata como CEU
    if (linha < 0 || linha >= MAPA_LINHAS || coluna < 0 || coluna >= MAPA_COLUNAS) // Muito Condicional;
        return CEU;

    return element->MATRIZ_mapa[linha][coluna];
}

void mapa_destroy(mapa *element){
    
    free(element);
}

