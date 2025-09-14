#include <SDL3/SDL.h>

int main(int argc, char const *argv[])
{
    // lets initialize the SDL
    // To do it, we should look at the documentation about the SDL_Init
    // We will see there that to initialize SDL3, we can use the SDL_Init or SDL_InitSubSystem(). I will use SDL_Init
    // The signature of SDL_Init is bool SDL_Init(SDL_InitFlags flags);
    // I will choose some flag there and then use here.

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        SDL_Log("Falha ao inicializar o SDL.");
        return 1;
    }
    
    // Now, lets create a window.
    // The signature is SDL_Window * SDL_CreateWindow(const char *title, int w, int h, SDL_WindowFlags flags);

    SDL_Window * janela;

    if (janela == NULL)
    {
        SDL_Log("Falha ao criar a janela.");
        return 1;
    }

    const char * title = "JanelaEntreOEspaçoEuclidianoERimanniano";
    int w = 500;
    int h = 500;

    janela = SDL_CreateWindow(title, w, h, SDL_WINDOW_RESIZABLE);

    SDL_Delay(5000);
    SDL_Quit();

    return 0;
}
