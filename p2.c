// Vamos usar callbacks ao invés da função main.
// Se procurarmos na documentação sobre SDL_MAIN_USE_CALLBACKS podemos ver os detalhes.
// Basicamente, criar usando callbacks nos permite usar 4 funções interessantes: SDL_AppInit, Event, Iterate e Quit

#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

SDL_Window * janela;

// Com essas 4 funções, nós conseguimos: inicializar o SDL, tratar eventos, lidar com o loop e encerrar no fim.

// Inicializar
// Temos 3 valores principais para SDL_AppResult:
// SDL_APP_FAILURE (encerra com uma mensagem de erro)
// SDL_APP_SUCCESS (encerra com uma mensagem de sucesso)
// SDL_APP_CONTINUE (não encerra, só continua o fluxo)
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) // o **appstate é algo que podemos usar para passar variáveis que nós queremos adicionar. Assim, não precisamos deixar variáveis soltas no meio da estrutura da aplicação SDL.
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        SDL_Log("Falha ao criar a janela. Erro: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    janela = SDL_CreateWindow("Janela", 500, 300, SDL_WINDOW_RESIZABLE);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_Delay(5000);
    return SDL_APP_SUCCESS;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_Quit();
}

