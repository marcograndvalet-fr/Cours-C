#include "sys/ioctl.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

#include "config.h"
#include "internals.h"
#include "display.h"
#include "food.h"



void backgroundSetup(int nx, int ny, int bg[]){
    int i;
    for( i=0; i<nx; i++){
        bg[i] = 1;
    }
    for( i=0; i<nx; i++){
        bg[(ny-1)*nx + i] = 1;
    }
    for( i=0; i<ny; i++){
        bg[i*nx] = 1;
    }
    for( i=0; i<ny; i++){
        bg[i*nx+nx-1] = 1;
    }
}


void add_snake(Snake* snake,int bg[], int nx, int ny){
    int l = snake->length;
    for (int i = 0; i<l ; i++){
        bg[snake->body[i].y * nx +snake->body[i].x] = 1;
    }

}

void remove_snake(Snake* snake, int bg[],int nx,int ny){
    int l = snake->length;
    for (int i = 0; i<l ; i++){
        bg[snake->body[i].y * nx +snake->body[i].x] = 0;
    }
}

void snake_movement(char k, int dxdy[2]){
    if(k=='d'||k=='6'){
        // Right                                                                      
        dxdy[0] = 1;
        dxdy[1] = 0;
    }else if(k=='q'||k=='4'){
        // Left                                                                       
        dxdy[0] = -1;
        dxdy[1] = 0;
    }else if(k=='s'||k=='2'){
        // Down                                                                        
        dxdy[0] = 0;
        dxdy[1] = 1;
    }else if(k=='z'||k=='8'){
        // Up                                                                      
        dxdy[0] = 0;
        dxdy[1] = -1;
    }
}


bool verifyBorder(Snake* snake, int nx, int ny){
    // Return false if the snake is out of bounds
    //        true otherwise
    int x = snake->body[0].x;
    int y = snake->body[0].y;
    return y == 0 || y == ny-1 || x == 0 || x == nx-1;
}




void setupSnake(Snake* snake, int init_size){
    // Initialize the snake with the given initial size
    snake->length = init_size;
    
    for (int i = 0; i< init_size; i++){
        snake->body[i].x = init_size - i + 1;
        snake->body[i].y = 1;
    }

}

void update_snake_coordinates(struct Snake* snake, int dxdy[2], int nx){
    // Update the snake coordinates based on the current direction
    
    int l = snake->length;
    for (int i = 1; i< l ; i++){
        snake->body[l-i].x = snake->body[l-i-1].x;
        snake->body[l-i].y = snake->body[l-i-1].y;
        // suicide si il se rentre dedans
        if (snake->body[0].x + dxdy[0] + nx * (snake->body[0].y + dxdy[1]) == snake->body[i].x + nx*snake->body[i].y  ){
            exit(1);
        }
    }

    snake->body[0].x = snake->body[0].x + dxdy[0];
    snake->body[0].y = snake->body[0].y + dxdy[1];

}

void startGame(int lap, int nx, int ny, Snake* snake, int bg[]){
    char key;

    int dxdy[2]={1, 0};
    int food[2]={0, 0};

    createFood( bg, food, nx, ny );

    while(true){
        frameSleep(lap);
        if( keyEvent() ){
            key = getchar(); 
            snake_movement(key, dxdy);
        }
        backgroundClear();
        add_snake( snake, bg, nx, ny );
        printFrame(nx, ny, bg);
        remove_snake(snake, bg, nx, ny);
        bool out = verifyBorder(snake, nx, ny);
        if(out){
            exit(1);
        }
        bool eat = eatFood(food, snake);
        if(eat){
            createFood(bg, food, nx, ny);
            snake->length += 1;
            snake->body[snake->length - 1].x = -1;
            snake->body[snake->length - 1].y = -1; 
            lap = lap * 0.8 + 4 ;
        }
        printf("%d; %d\n", dxdy[0], dxdy[1]);
        update_snake_coordinates(snake, dxdy,nx);
    }
}



int main(){
    const int snake_init_sz = 3;
    const int nx = 50;
    const int ny = 25;
    const int lap= 200;

    int background[nx*ny];
    for(int i=0; i<nx*ny; i++){
        background[i] = -1;
    }

    Snake snake;
    backgroundSetup(nx, ny, background);
    setupSnake(&snake, snake_init_sz);
    // Test only //  

    //add_snake(snake, background, nx, ny);
    //printFrame(nx, ny, background);
    // Test only // 

    startGame(lap, nx, ny,&snake, background);
    return EXIT_SUCCESS;
}





