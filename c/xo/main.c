#include <stdio.h>


#define BOARD_SIZE 3

typedef unsigned char byte;
typedef struct BoardPlayer{
    byte icon;
} BoardPlayer;

byte BOARD_STATUS[BOARD_SIZE][BOARD_SIZE] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
};


int checkForWinner(BoardPlayer *player, byte y, byte x){
    char found = 0, i;

    for(i=0;i < BOARD_SIZE;i++){
        if(BOARD_STATUS[i][x] == player -> icon)
            found++;
    }

    if(found == 3)
        return 1;
    found = 0;

    for(i=0;i < BOARD_SIZE;i++){
        if(BOARD_STATUS[y][i] == player -> icon)
            found++;
    }

    if(found == 3)
        return 1;
    found = 0;
    
    for(i=0;i < BOARD_SIZE; i++){
        if(BOARD_STATUS[i][i] == player -> icon)
            found++;
    }

    if(found == 3)
        return 1;
    found = 0;

    for(i=2;i >= 0; i--){
        if(BOARD_STATUS[i][BOARD_SIZE - (i+1)] == player -> icon)
            found++;
    }
    return found == 3;
}

void printBoard(){
    byte y, x;

    for(y=0;y < BOARD_SIZE;y++){
        for(x=0;x < BOARD_SIZE;x++){
            printf("|\t%c\t", BOARD_STATUS[y][x]);
        }
        printf("|\n");
    }
}

byte move(BoardPlayer *player, byte y, byte x){
    byte position = BOARD_STATUS[y][x];

    if(y >= BOARD_SIZE || x >= BOARD_SIZE){
        printf("Board max width & height is %d\n", BOARD_SIZE);
        return -1;
    }

    if(position != 0){
        printf("Block is already cached with %c\n", position);
        return -1;
    }
    
    BOARD_STATUS[y][x] = player -> icon;
    return 0;
}

int main(int argc, char *argv[]){
    unsigned short x=0, y=0, moves=0;
    BoardPlayer playerX = {.icon='X'};
    BoardPlayer playerO = {.icon='O'};
    BoardPlayer *currentPlayer = &playerO; 

    while(moves != 9){
        printBoard();
        printf("(%c)>>> ", currentPlayer -> icon);
        scanf("%hu %hu", &y, &x);

        if(!move(currentPlayer, y, x)){
            if(checkForWinner(currentPlayer, y, x)){
                printf("winner is %c\n", currentPlayer -> icon);
                return 0;
            }
            currentPlayer = currentPlayer == &playerX ? &playerO : &playerX;
            moves++;
        };
        putchar('\n'); // making things look cleaner
    }
    
    if(moves == 9)
        printf("Board is out of moves\n");
    return 0;
}