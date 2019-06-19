
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "visualization.h"

SDL_DisplayMode		displayMode;
SDL_Window*			window; // задаем окно для SDL

const int width = 640; // ширина окна
const int height = 480; // высота окна

static void init(void)
{

	// Инициализация SDL

	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		printf("Unable to init SDL, error: %s\n", SDL_GetError());
		exit(1);
	}

	int request = SDL_GetDesktopDisplayMode(0,&displayMode);

	// Включаем двойной буфер, настраиваем цвета

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

	// Создаем окно с заголовком "Cube", размером 640х480 и расположенным по центру экрана.

	window = SDL_CreateWindow(
			"Cube",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width, height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_GLContext glcontext = SDL_GL_CreateContext(window); // создаем контекст OpenGL

	if(window == NULL) {	// если не получилось создать окно, то выходим
		exit(1);
	}

	// Инициализация OpenGL

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // устанавливаем фоновый цвет на черный
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST); // включаем тест глубины
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float) width / (float) height, 0.1f, 100.0f); // настраиваем трехмерную перспективу
	glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим
}

void	render_UPDATE(SDL_Renderer* render, SDL_Texture* texture[], SDL_Rect* destrect[], int states[])
{
	SDL_RenderClear(render);
	if(states[0]) SDL_RenderCopy(render, texture[0],NULL,destrect[0]);
	if(states[1]) SDL_RenderCopy(render, texture[1],NULL,destrect[1]);
}

void	move_UP   (SDL_Renderer* render, SDL_Texture* texture, SDL_Rect *destrect)
{
destrect->y -= 5;
SDL_RenderClear(render);
SDL_RenderCopy(render, texture,NULL,destrect);
}
void	move_DOWN (SDL_Renderer* render, SDL_Texture* texture, SDL_Rect *destrect)
{
destrect->y += 5;
SDL_RenderClear(render);
SDL_RenderCopy(render, texture,NULL,destrect);
}
void	move_LEFT (SDL_Renderer* render, SDL_Texture* texture, SDL_Rect *destrect)
{
destrect->x -= 5;
SDL_RenderClear(render);
SDL_RenderCopy(render, texture,NULL,destrect);
}
void	move_RIGHT(SDL_Renderer* render, SDL_Texture* texture, SDL_Rect *destrect)
{
destrect->x += 5;
SDL_RenderClear(render);
SDL_RenderCopy(render, texture,NULL,destrect);
}

void
SDL_example(int argc, char **argv)
{
	init(); // инициализация

	SDL_Renderer *ren = SDL_CreateRenderer(
			window,
			-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (ren == NULL) {
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		exit (1);
	}

	SDL_Rect player_RECT;
	player_RECT.x = 0;   //Смещение полотна по Х
	player_RECT.y = 0;   //Смещение полотна по Y
	player_RECT.w = 333; //Ширина полотна
	player_RECT.h = 227; //Высота полотна

	SDL_Rect background_RECT;
	background_RECT.x = 0;
	background_RECT.y = 0;
	background_RECT.w = displayMode.w;
	background_RECT.h = displayMode.h;

	const int player_WIGHT = 333;   //Ширина исходнго изображения
	const int player_HEIGH = 227;   //Высота исходного изображения
	double TESTtexture_SCALE = 1.0; //Множетель для зумирования

	SDL_Texture *player =  IMG_LoadTexture(ren,IMAGE_DIR"player1.png");

	SDL_Surface *BMP_background = SDL_LoadBMP(IMAGE_DIR"background.abstract.bmp");
	if (BMP_background == NULL){
		printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
		exit (1);
	}

	SDL_Texture *background = SDL_CreateTextureFromSurface(ren, BMP_background);
	SDL_FreeSurface(BMP_background); //Очищение памяти поверхности
	if (player == NULL){
		printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
		exit (1);
	}

	SDL_RenderClear(ren); //Очистка рендера
	SDL_RenderCopy(ren,background,NULL,&background_RECT); //Копируем в рендер фон
	SDL_RenderCopy(ren, player, NULL, &player_RECT); //Копируем в рендер персонажа
	SDL_RenderPresent(ren); //Погнали!!

	SDL_Texture* ARRAY_textures[2] = {background, player};
	SDL_Rect* ARRAY_rect[2] = {&background_RECT, &player_RECT};
	int ARRAY_texturesState[2] = {1,1};

	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
	bool running = true;

	while(running) {

		SDL_Event event; // события SDL

		while ( SDL_PollEvent(&event) ){ // начинаем обработку событий
			if (event.type == SDL_QUIT)
				running = false;
			if (event.type == SDL_KEYDOWN)
				if (event.key.keysym.sym == SDLK_ESCAPE)
					running = false;
		}
		if((keyboardState[SDL_SCANCODE_UP])||(keyboardState[SDL_SCANCODE_W]))
			move_UP(ren,player,&player_RECT);

		if((keyboardState[SDL_SCANCODE_DOWN])||(keyboardState[SDL_SCANCODE_S]))
			move_DOWN(ren,player,&player_RECT);

		if((keyboardState[SDL_SCANCODE_LEFT])||(keyboardState[SDL_SCANCODE_A]))
			move_LEFT(ren,player,&player_RECT);

		if((keyboardState[SDL_SCANCODE_RIGHT])||(keyboardState[SDL_SCANCODE_D]))
			move_RIGHT(ren,player,&player_RECT);


//ZOOM----------------------------------------------------------------
		if(keyboardState[SDL_SCANCODE_KP_PLUS])
		{
			TESTtexture_SCALE += 0.02;
			player_RECT.h = player_HEIGH * TESTtexture_SCALE;
			player_RECT.w = player_WIGHT * TESTtexture_SCALE;
		}
		if(keyboardState[SDL_SCANCODE_KP_MINUS])
		{
			TESTtexture_SCALE -= 0.02;
			player_RECT.h = player_HEIGH * TESTtexture_SCALE;
			player_RECT.w = player_WIGHT * TESTtexture_SCALE;
		}
		render_UPDATE(ren, ARRAY_textures, ARRAY_rect, ARRAY_texturesState);	//Написанная нами функция обновления рендера
		SDL_RenderPresent(ren);
	}

	SDL_Quit(); // завершаем работу SDL и выходим
}
