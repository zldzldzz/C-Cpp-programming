#ifndef CARDMEMORY_H
#define CARDMEMORY_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#define WIDTH 770
#define HEIGHT 780

extern int hint;          // hint 변수를 외부에서 참조 가능하게 선언
extern int wrongCount[4]; // wrongCount 변수를 외부에서 참조 가능하게 선언

class CardMemory
{
public:
    SDL_Rect rect;        // 카드 위치, 크기 지정
    SDL_Texture *texture; // 카드의 뒷면 혹은 앞면
    int cardValue;        // 카드의 고유 값
    bool isRevealed;      // 카드가 공개되었는지 여부

    CardMemory();
    ~CardMemory();
};

// 함수 선언
void shuffleArray(int *array, int size);
void flipCardPositionsHorizontally(int cardCount, CardMemory *cards);
int initializeCards(int cardCount, int *cardValues, CardMemory *cards, SDL_Renderer *renderer, char cardImage[][16]);
void renderBackFaces(int cardCount, CardMemory *cards, SDL_Renderer *renderer, SDL_Texture *backTexture);
void showCorrectCards(int cardCount, CardMemory *cards, SDL_Renderer *renderer, int time);
void renderAllBack(int cardCount, CardMemory *cards, SDL_Renderer *renderer, SDL_Texture *backTexture);
int playRound(int cardCount, int targetCount, int *cardValues, CardMemory *cards, SDL_Renderer *renderer, SDL_Texture *backTexture, int stage);

#endif // CARDMEMORYL_H