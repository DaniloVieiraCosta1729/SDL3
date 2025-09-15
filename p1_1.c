#include <SDL3/SDL.h>

int main(int argc, char const *argv[])
{
    // inicializar
    if (!SDL_Init(SDL_INIT_VIDEO |SDL_INIT_EVENTS))
    {
        SDL_Log("Erro ao inicializar.");
        return 1;
    }
    
    // Criar uma janela
    SDL_Window * janela;

    if (janela == NULL)
    {
        SDL_Log("Erro ao criar a janela.");
        return 1;
    }

    const char * titulo = "Janela";
    int w = 800;
    int h = 500;

    janela = SDL_CreateWindow(titulo, w, h, SDL_WINDOW_FULLSCREEN);  

    SDL_Delay(5000);

    SDL_Quit();
    
    return 0;
}

