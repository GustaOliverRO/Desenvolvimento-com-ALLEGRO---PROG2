//Compilação: gcc AggressiveSquares.c Square.c Joystick.c Bullet.c Pistol.c -o AS $(pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 --libs --cflags)
//Compilação: gcc Cyber.c Mapa.c Player.c Joystick.c -o AS $(pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 --libs --cflags)

#include <allegro5/allegro5.h>																																												//Biblioteca base do Allegro
#include <allegro5/allegro_font.h>																																											//Biblioteca de fontes do Allegro
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "Player.h"
#include "Mapa.h"

#define SCREEN_MAX_Y 720
#define SCREEN_MAX_X 1280
#define LARGURA SCREEN_MAX_Y/10
#define ALTURA  SCREEN_MAX_X/10

/*void update_posicion(player *personagem){
	
	if(personagem->controle->down)
		player_move(personagem, PLAYER_STEP, 0, SCREEN_MAX_X, SCREEN_MAX_Y);
	if(personagem->controle->up)
		player_move(personagem, PLAYER_STEP, 1, SCREEN_MAX_X, SCREEN_MAX_Y);
	if(personagem->controle->left)
		player_move(personagem, PLAYER_STEP, 2, SCREEN_MAX_X, SCREEN_MAX_Y);
	if(personagem->controle->right)
		player_move(personagem, PLAYER_STEP, 3, SCREEN_MAX_X, SCREEN_MAX_Y);
}*/

int main(){

    al_init();
    al_init_primitives_addon();
    al_install_keyboard();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 25);																																						//Cria o relógio do jogo; isso indica quantas atualizações serão realizadas por segundo (30, neste caso)
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();																																					//Cria a fila de eventos; todos os eventos (programação orientada a eventos) 
	ALLEGRO_FONT* font = al_create_builtin_font();																																							//Carrega uma fonte padrão para escrever na tela (é bitmap, mas também suporta adicionar fontes ttf)
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_MAX_X, SCREEN_MAX_Y);																																			//Cria uma janela para o programa, define a largura (x) e a altura (y) da tela em píxeis (320x320, neste caso)

	al_register_event_source(queue, al_get_keyboard_event_source());																																		//Indica que eventos de teclado serão inseridos na nossa fila de eventos
	al_register_event_source(queue, al_get_display_event_source(display));																																		//Indica que eventos de tela serão inseridos na nossa fila de eventos
	al_register_event_source(queue, al_get_timer_event_source(timer));

    player *personagem = player_create(LARGURA, ALTURA, SCREEN_MAX_X/2, SCREEN_MAX_Y-200);
    if(!personagem) return 1;

	mapa *cenario = mapa_create();
	if(!cenario) return 1; //organizar depois para não acontecer vazamento de memoria, em caso de falha;

   	ALLEGRO_EVENT event;																																													//Variável que guarda um evento capturado, sua estrutura é definida em: https:		//www.allegro.cc/manual/5/ALLEGRO_EVENT
	al_start_timer(timer);																																													//Função que inicializa o relógio do programa

    while(1){

        al_wait_for_event(queue, &event);

		if (event.type == 42)
			break;
		
		else if (event.type == 30){
				//printf("A posição cartesiana atual do retangulo é ->");
				//printf("%d, %d\n\n", personagem->x, personagem->y);
				//update_posicion(personagem);
				player_update(personagem, cenario, SCREEN_MAX_X, SCREEN_MAX_Y);
				al_clear_to_color(al_map_rgb(0, 125, 250));
				mapa_draw(cenario);																																				//Substitui tudo que estava desenhado na tela por um fundo preto
				al_draw_filled_rectangle(personagem->x - (personagem->largura/2), personagem->y - personagem->altura/2, personagem->x + personagem->largura/2, personagem->y + personagem->altura/2,al_map_rgb(255, 255,255));
            	al_flip_display();
        }
		else if(event.type == 10){
			switch(event.keyboard.keycode) {
				case ALLEGRO_KEY_LEFT:
					joystick_left(personagem->controle, LIGADO); break;
				case ALLEGRO_KEY_RIGHT:
					joystick_right(personagem->controle, LIGADO); break;
				case ALLEGRO_KEY_UP:
					joystick_up(personagem->controle, LIGADO); break;
				case ALLEGRO_KEY_DOWN: 
					joystick_down(personagem->controle, LIGADO); break;
				case ALLEGRO_KEY_SPACE:
					joystick_space(personagem->controle, LIGADO); break;
			}
		}
		else if(event.type == 12){
			switch(event.keyboard.keycode) {
				case ALLEGRO_KEY_LEFT:
					joystick_left(personagem->controle, DESLIGADO); break;
				case ALLEGRO_KEY_RIGHT:
					joystick_right(personagem->controle, DESLIGADO); break;
				case ALLEGRO_KEY_UP:
					joystick_up(personagem->controle, DESLIGADO); break;
				case ALLEGRO_KEY_DOWN: 
					joystick_down(personagem->controle, DESLIGADO); break;
				case ALLEGRO_KEY_SPACE:
					joystick_space(personagem->controle, DESLIGADO); break;
			}
		}
	}

	al_destroy_font(font);																																													//Destrutor da fonte padrão
	al_destroy_display(display);																																												//Destrutor da tela
	al_destroy_timer(timer);																																												//Destrutor do relógio
	al_destroy_event_queue(queue);		
	mapa_destroy(cenario);																																								//Destrutor da fila
	player_destroy(personagem);																																												//Destrutor do quadrado do primeiro jogador

    return 0;
}