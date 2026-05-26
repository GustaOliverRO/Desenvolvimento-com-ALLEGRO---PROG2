#include <stdlib.h>
#include "Joystick.h"


//Implementação da função "joystick_create"
joystick* joystick_create(){

	joystick *controle = malloc (sizeof(joystick));									//Aloca memória na heap para um novo controle
	if (!controle) return NULL;														//Se a alocação não deu certo, retorna erro
	
	controle->right = 0;															//Insere o estado de desligado para o botão de movimentação à esquerda
	controle->left = 0;																//Insere o estado de desligado para o botão de movimentação à direita
	controle->up = 0;																//Insere o estado de desligado para o botão de movimentação para cima
	controle->down = 0;																//Insere o estado de desligado para o botão de movimentação para baixo
	controle->space = 0;
	return controle;																//Retorna o novo controle
}

//Implementação da função "joystick_destroy"; libera a memória do elemento na heap
void joystick_destroy(joystick *element){ free(element); }							

//Implementação da função "joystick_left"; muda o estado do botão
void joystick_left(joystick *element, int estado){ element->left = estado; }	

//Implementação da função "joystick_right"; muda o estado do botão
void joystick_right(joystick *element, int estado){ element->right = estado; }

//Implementação da função "joystick_up"; muda o estado do botão
void joystick_up(joystick *element, int estado){ element->up = estado; }

//Implementação da função "joystick_down"; muda o estado do botão
void joystick_down(joystick *element, int estado){ element->down = estado; }

//Implementação da função "joystick_space"; muda o estado do botão
void joystick_space(joystick * element, int estado){ element->space = estado; }
