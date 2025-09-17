// Esse arquivo explora as funções clear. A assinatura em geral é bool SDL_RendererClear(SDL_Renderer * renderer);
// renderer é algo que está aparencendo somente agora para mim. Assim como precisamos de uma janela para nossas aplicações, também precisamos de um "contexto de renderização", onde vamos aplicar as construções gráficas. Pelo menos é o que eu entendi até o momento.

// Percebi que a abordagem de callbacks é predominante nos exemplos, então vou seguí-la.

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// vamos começar criando uma janela e um renderer

static SDL_Window * janela;
const char * titulo = "Cores";
int w = 500;
int h = 300;

static SDL_Renderer * renderizador;

// Só para lembrar. Com callbacks o programa ganha a estrutura init -> event -> iterate -> Quit

SDL_AppResult SDL_AppInit(void **appstate, int argc, char * argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO)) // Pesquisar mais sobre a função SDL_Init()
    {
        SDL_Log("Falha: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Cores", w, h, SDL_WINDOW_FULLSCREEN, &janela, &renderizador)) // função que cria o rederizador e a janela.
    {
        SDL_Log("Erro: %s ", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    return SDL_APP_CONTINUE;
}

SDL_Event * evento;

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *evento)
{
    switch (evento->type)
    {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
        break;

    case SDL_EVENT_KEY_DOWN:
        return SDL_APP_SUCCESS;

    default:
        break;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    // aqui começa a lógica da renderização;
    // o exemplo faz a seguinte escolha: ele pega quantos segundos faz que a aplicação foi inicializada, calcula o seno disso, multiplica por 0,5 e soma com 0,5;
    // a razão para isso é que, como a imagem de seno é [-1, 1], precisamos multiplicar a função para que tenhamos valores entre 0 e 1, caso contrário, não vamos conseguir indicar as cores.
    // para que a cor alterede forma interessante e não fique simplesmente indo do preto ao branco, ele colocou uma defasagem no argumento de seno.
    // Vou colocar a mesma defasagem, porém, com valores diferentes, pois acho mais natural usar um ângulo que esteja entre pi/2 e - pi/2.

    // função SDL_GetTicks(); Retorna a qtd. de milissegundos entre o início da aplicação e agora.
    const double agora = ((double) SDL_GetTicks()) / 1000; // const não será um problema, pois o Clear vai limpar o renderer e colocar um novo a cada frame.
    const float vermelho = 0.5 + 0.5 * SDL_sin(agora);
    const float verde = 0.5 + 0.5 * SDL_sin(agora + 3.14159/3);
    const float azul = 0.5 + 0.5 * SDL_sin(agora - 3.14159/3);

    SDL_SetRenderDrawColorFloat(renderizador, vermelho, verde, azul, 0.9);

    // vamos limpar o renderizador para poder aplicar as novas cores
    SDL_RenderClear(renderizador);
    SDL_RenderPresent(renderizador);

    return SDL_APP_CONTINUE;

}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{

}