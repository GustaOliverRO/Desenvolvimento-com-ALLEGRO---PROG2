#ifndef __PLAYER__ 																																	//Guardas de inclusão
#define __PLAYER__																																	//Guardas de inclusão																															//Quantidade de pixels que um quadrado se move por passo

#include "Joystick.h"
#include "Mapa.h"																																//Estrutura e procedimentos relacionados ao controle do quadrado


#define FORCA_PULO -16
#define GRAVIDADE 1
#define MOVIMENTO 1
#define PLAYER_STEP 10																														//Tamanho, em pixels, de um passo do quadrado
#define SOLO 0
#define FLUTUANDO 1
#define VELO_MAX 8



typedef struct {
	int largura;
	int altura;
	int x;
	int y;
	short Vx;
	short Vy;
	int altura_ori;
	unsigned char no_chao;
	joystick *controle;

} player;

player* player_create(int largura, int altura, int x_inicial, int y_inicial);//Protótipo da função de criação de um retângulo (para os sprites do personagem)
//void player_velo(player *element);										 //Protótipo da função de movimentação de um quadrado
//void player_move(player *element, char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y);	
void player_update(player *element, mapa *cenario, int MAX_X, int MAX_Y);
void player_destroy(player *element);										//Protótipo da função de destruição do personagem;

#endif																		//Guardas de inclusão