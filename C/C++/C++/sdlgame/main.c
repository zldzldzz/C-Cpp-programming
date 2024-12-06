#include "CardMemoryL.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>

int wrongCount[4] = {0}; // 각 라운드 틀린 수 체크
int hint = 0;            // 힌트 사용 횟수

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL Initialization Fail: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("SDL Memory Game",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WIDTH, HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (!window)
    {
        printf("SDL Initialization Fail: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    char cardImage[17][16] = {
        "imgs/free01.png", "imgs/free02.png", "imgs/free03.png", "imgs/free04.png",
        "imgs/free05.png", "imgs/free06.png", "imgs/free07.png", "imgs/free08.png",
        "imgs/free09.png", "imgs/free10.png", "imgs/free11.png", "imgs/free12.png",
        "imgs/free13.png", "imgs/free14.png", "imgs/free15.png", "imgs/free16.png"};

    srand(time(NULL));
    SDL_Surface *backSurface = IMG_Load("imgs/free00.png");
    SDL_Texture *backTexture = SDL_CreateTextureFromSurface(renderer, backSurface);
    SDL_FreeSurface(backSurface);
    int cardValues[16];

    cardValues[0] = 14;

    for (int i = 1; i < 16; i++)
    {
        cardValues[i] = rand() % 16;
    }
    std::sort(cardValues, cardValues + 16);

    int stages[4] = {4, 6, 9, 16};
    CardMemory cards[16];

    for (int stage = 0; stage < 4; stage++)
    {
        int cardCount = stages[stage];
        int targetCount = initializeCards(cardCount, cardValues, cards, renderer, cardImage);

        for (int i = 0; i < cardCount; i++)
        {
            SDL_RenderCopy(renderer, cards[i].texture, NULL, &cards[i].rect);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay((stage + 1) * 2000);

        renderBackFaces(cardCount, cards, renderer, backTexture);

        if (playRound(cardCount, targetCount, cardValues, cards, renderer, backTexture, stage) == -1)
        {
            break;
        }
    }

    SDL_DestroyTexture(backTexture);
    for (int i = 0; i < 16; i++)
    {
        if (cards[i].texture != NULL)
        {
            SDL_DestroyTexture(cards[i].texture);
        }
    }

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // 프로그램 종료 후 각 라운드별 틀린 횟수와 힌트 사용 횟수 출력
    printf("\n1라운드 틀린 횟수: %d\n", wrongCount[0]);
    printf("2라운드 틀린 횟수: %d\n", wrongCount[1]);
    printf("3라운드 틀린 횟수: %d\n", wrongCount[2]);
    printf("4라운드 틀린 횟수: %d\n", wrongCount[3]);
    printf("전체 힌트 사용 횟수: %d\n", hint);

    return 0;
}
