#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Player.h"
#include "Joystick.h"

void update_velocity(short *velocidade, short valor){
	//printf("o valor do abs no desvio será %d\n\n", abs((*velocidade)+valor));
	if(abs((*velocidade)+valor) < VELO_MAX)
		*velocidade = *velocidade + valor;
}

// Analisar dos pontos x e y ser uma certa porcentagem deslocado da extrema esquerda da tela;
// Observar que não utilizo 4 dos 6 parâmetros quee stou passando na função de criação;
player* player_create(int largura, int altura, int x_inicial, int y_inicial){

	player *new_player = malloc(sizeof(player));
	
	if(!new_player) return NULL;

	new_player->largura = largura;
	new_player->altura = altura;
	new_player->altura_ori = altura;

	new_player->x = x_inicial;
	new_player->y = y_inicial;

	new_player->Vx = 0;
	new_player->Vy = 0;
	new_player->no_chao = FLUTUANDO;
	new_player->controle = joystick_create();

	return new_player;
}

/*void player_velo(player *element){

	printf("Entrou na função de atualizar a velociadade\n");
	printf("Velocidade atual -> Vx:%d, Vy:%d\n", element->Vx, element->Vy);
	printf("Debug do Joystick\n");
	printf("UP-> %d\n", element->controle->up);
	printf("DOWN-> %d\n", element->controle->down);
	printf("LEFT-> %d\n", element->controle->left);
	printf("RIGHT-> %d\n", element->controle->right);

	if(element->controle->down){
		printf("Entrei para atualizar a velocidade para o DOWN\n");
		update_velocity(&element->Vy,  1);
	}
	if(element->controle->up)
		update_velocity(&element->Vy, -1);
	if(element->controle->left)
		update_velocity(&element->Vx, -1);
	if(element->controle->right)
		update_velocity(&element->Vx,  1);
}
void player_move(player *element, char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y){									//Implementação da função "player_move"

	player_velo(element);

	// Pensando em gravidade, vale talvez, passar o trajectory == 0 para o ultimo caso, 
	// pois se o usário apertar para baixo ou caso nada for passado (NULL), a gravidade puxa para baixo;
	
	if(!trajectory){ //trajectory == 0 down;
		if(((element->y + steps*element->Vy) - element->altura/2) <= max_y)
			element->y = element-> y + steps*element->Vy;
	}
	else if(trajectory == 1){ // up
		 if(((element->y + steps*element->Vy) + element->altura/2) >= max_y)
			element->y = element-> y + steps*element->Vy;
	}
	else if(trajectory == 2){ // left
		 if(((element->x + steps*element->Vx) - element->largura/2) >= 0)
			element->x = element->x + steps*element->Vx;
	}
	else if(trajectory == 3){ // rigth
		 if(((element->x + steps*element->Vx) + element->largura/2) <= max_x)
			element->x = element->x + steps*element->Vx;
	}
}*/

void player_update(player *element, mapa *cenario, int MAX_X, int MAX_Y){

	int pe_y, lado_esq, lado_dir, linha_pe, coluna_esq, coluna_dir;
	int pos_chao = MAX_Y - 100;

	// Lógica pra o Eixo X
	if(element->controle->left)
		element->Vx = -VELO_MAX;
	else if(element->controle->right)
		element->Vx = VELO_MAX;
	else
		element->Vx = 0;
	
	// Lógica para o eixo Y agachamento
	if(element->no_chao == SOLO){
		if(element->controle->down){
			element->y = element->y + element->altura_ori/4;
			element->altura = element->altura_ori/2;
		}
		else
			element->altura = element->altura_ori;
	}

	// Lógica para Cair 
	if(element->no_chao == FLUTUANDO)
		element->Vy = element->Vy + GRAVIDADE;

	if((element->controle->up || element->controle->space) && element->no_chao == SOLO){
		element->Vy = FORCA_PULO;
		element->no_chao = FLUTUANDO;
	}

	/*//Atualiza posição
	element->x = element->x + element->Vx;
	element->y = element->y + element->Vy;

	pe_y = element->y - element->altura/2;
	lado_esq = element->x - element->largura/2;
	lado_dir = element->x + element->largura/2;

	//Testa limites para eixo X da tela após atualização
	if((element->x - element->largura/2) < 0)
		element->x = element->largura/2;
	if((element->x + element->largura/2) > MAX_X)
		element->x = MAX_X - element->largura/2;

		// 2. Perguntamos ao mapa: A quina esquerda ou direita está pisando no chão?
	if (mapa_get_bloco(cenario, lado_esq, pe_y) == CHAO || 
	    mapa_get_bloco(cenario, lado_dir, pe_y) == CHAO) {
		
		// Trava a posição calculando o topo do bloco
		element->y = (pe_y / BLOCO_MAPA) * BLOCO_MAPA - (element->altura / 2);
		element->Vy = 0;
		element->no_chao = SOLO;
	}
	//Testa limites para eixo Y da tela após atualização
	if(cenario->MATRIZ_mapa[Y_bloco+1][X_bloco] == SOLO){
    //if((element->y + element->altura/2) > pos_chao){
		element->y = ((Y_bloco+1)*BLOCO_MAPA) - element->altura/2;
		element->Vy = 0;
		element->no_chao = SOLO;
	}
	if((element->y - element->altura/2) < 0){
		element->y = element->altura/2;
		element->Vy = 0;
	}*/

	// Atualiza posição
	// Assume que o player sempre esta caindo, até bater no chão;
	element->x = element->x + element->Vx;
	element->y = element->y + element->Vy;
	element->no_chao = FLUTUANDO;

	// Calcula os pixels necessário para análise do bloco atual do personagem;
	pe_y = element->y + (element->altura / 2);
	lado_esq = element->x - (element->largura / 2);
	lado_dir = element->x + (element->largura / 2);

	// Testa limites para eixo X da tela após atualização
	if((element->x - element->largura/2) < 0)
		element->x = element->largura/2;
	if((element->x + element->largura/2) > MAX_X)
		element->x = MAX_X - element->largura/2;

	// Verifica se as quinas então a tocar no chão
	if (mapa_get_bloco(cenario, lado_esq, pe_y) == CHAO ||
	mapa_get_bloco(cenario, lado_dir, pe_y) == CHAO) {
		
		// Trava a posição calculando o topo do bloco
		// Como tocou no chão, provou que não está a flutuar
		element->y = (pe_y/BLOCO_MAPA)*BLOCO_MAPA - (element->altura / 2);
		element->Vy = 0;
		element->no_chao = SOLO;
	}

	// Limite do teto da tela
	if((element->y - element->altura/2) < 0){
		element->y = element->altura/2;
		element->Vy = 0;
	}
}

void player_destroy(player *element){																													//Implementação da função "player_destroy"
	
	joystick_destroy(element->controle);																													//Destrói o controle do quadrado
	free(element);																																		//Libera a memória do quadrado na heap
}