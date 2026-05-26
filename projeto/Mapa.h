#ifndef __MAPA__
#define __MAPA__

#define CEU 0
#define CHAO 1
#define NUVEM 2
#define BLOCO_MAPA 80
#define MAPA_LINHAS 9                                                               // MAPA_LINHAS * BLOCO_MAPA == SCREEN_Y
#define MAPA_COLUNAS 16                                                             // MAPA_COLUNAS * BLOCO_MAPA == SCREEN_X



typedef struct {
    int MATRIZ_mapa [MAPA_LINHAS][MAPA_COLUNAS];
} mapa;

// Protótipos das funções do mapa
mapa* mapa_create();
void mapa_draw(mapa *element);
int mapa_get_bloco(mapa *element, int px, int py);
void mapa_destroy(mapa *element);

#endif