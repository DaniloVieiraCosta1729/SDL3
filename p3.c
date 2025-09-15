#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>

// Sobre Eventos

int main(int argc, char const *argv[])
{
    // inicializar:
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        SDL_Log("Erro: %s\n", SDL_GetError());
        return 1;
    }
    
    // criar janela
    SDL_Window * janela;

    if (janela == NULL)
    {
        SDL_Log("Erro: %s\n", SDL_GetError());
        return 1;
    }
    

    const char * titulo = "Titulo";
    int w = 500;
    int h = 300;

    janela = SDL_CreateWindow(titulo, w, h, SDL_WINDOW_RESIZABLE);

    // Sobre os eventos: SDL_Event é uma union que contém as structeres de eventos usados em SDL.
    // SDL_Event usa um Uint8 padding[128] por questões de performance e de conformidade com a ABI.
    // Temos duas formas principais de usar SDL_Event: lendo eventos da fila ou colocando eventos na fila de eventos.
    // Pela documentação, há duas formas de ler eventos: SDL_PollEvent e SDL_PeepEvents, mas vou aprender o SDL_PollEvent aqui.

    // Vamos criar uma instância vazia de SDL_Event
    SDL_Event evento;

    // Vamos usar um loop que continua repetindo enquanto houver eventos para tratar.
    // Podemos fazer esse loop com o SDL_PollEvent citado. SDL_PollEvent remove o próximo evento da fila e, se não houver nenhum evento como próximo, ele retorna 0 (o que deve finalizar o loop). Enquanto houver evento ele retorna 1.

    // O SDL_PollEvent(&variavel) vai remover um evento da fila e "colocá-lo" no endereço &variável, ou seja, ele vai preencher o evento que nós passarmos para ele com as informações dos eventos que ele remover da fila e, em seguida vai fazer o retorno como expliquei acima.

    // Em particular, quando SDL_PollEvent preenche o evento, ele tbm preenche o campo type. Logo, com esse campo informado, podemos criar um switch case para tratar diferentes eventos de formas diferentes, caso queiramos.

    // Vou o exemplo da documentação mais de perto e escolher tratar um evento que trata o movimento do mouse.

    // Olhando a union SDL_Event, vemos que o tipo que queremos observar aqui é o SDL_EVENT_MOUSE_MOTION; Há outros eventos relacionados com mouse, mas esse é o que lida com o movimento dele.

    char running = 1;
    while (running)
    {
        while (SDL_PollEvent(&evento))
        {
            // usando um switch case para tratar eventos de um tipo específico.
            switch (evento.type)
            {
            case SDL_EVENT_MOUSE_MOTION:
                SDL_Log("O mouse esta se movendo.");
                SDL_Log("posicao: (%f, %f)", evento.motion.x, evento.motion.y);
                break;
            case SDL_EVENT_KEY_DOWN:
                SDL_Log("Tecla pressionada.");
                // na documentação, acima de header, podemos ver como acessar os campos para conseguir tratar de forma mais específica os eventos.
                // temos, para SDL_EVENT_DOWN e UP temos event.key.* em que * é o campo que queremos.
                SDL_Log("Tecla: %d\n", evento.key.key);
                break;
            case SDL_EVENT_QUIT:
                running = 0;
                break;
            default:
                break;
            }
        }
    }
    
    SDL_Log("Fila de eventos vazia =)");

    SDL_Quit();

    return 0;
}
