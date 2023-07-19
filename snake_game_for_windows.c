#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 20

int snakeX[100], snakeY[100]; // Snake body coordinates
int fruitX, fruitY;           // Fruit coordinates
int length = 1;               // Initial length of the snake
int score = 0;
int gameover = 0;
int direction = 3; // 1-Up, 2-Right, 3-Down, 4-Left
int speed = 300;

void setup();
void draw();
void input();
void logic();

int main()
{
    setup();

    while (!gameover)
    {
        draw();
        input();
        logic();
        Sleep(speed); // 1
    }

    system("cls");
    printf("\n\n\n\n\t\t\tYour final Score : %5d\n\n\t\t\tThank You for playing!!\n\n\n\n", score);

    return 0;
}

void setup()
{
    snakeX[0] = WIDTH / 2; // Initial position of the snake
    snakeY[0] = HEIGHT / 2;

    // Place the fruit at a random location
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
}

void draw()
{
    system("cls"); // Clear the screen

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#"); // Draw the top wall
    printf("\n");

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0)
                printf("#"); // Draw the left wall

            if (i == snakeY[0] && j == snakeX[0])
                printf("0"); // Draw the snake's head
            else if (i == fruitY && j == fruitX)
                printf("F"); // Draw the fruit
            else
            {
                int found = 0;
                for (int k = 1; k < length; k++)
                {
                    if (i == snakeY[k] && j == snakeX[k])
                    {
                        printf("S"); // Draw the snake's body
                        found = 1;
                        break;
                    }
                }

                if (!found)
                    printf(" ");
            }

            if (j == WIDTH - 1)
                printf("#"); // Draw the right wall
        }

        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#"); // Draw the bottom wall
    printf("\n");

    printf("Score: %d\n", score);

    // Sleep for a short duration to control the frame rate
    // Adjust the sleep duration to change the frame speed
    // Sleep(speed); // 2
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case '5': // Up
            if (direction != 3)
                direction = 1;
            break;
        case '2': // Down
            if (direction != 1)
                direction = 3;
            break;
        case '3': // Right
            if (direction != 4)
                direction = 2;
            break;
        case '1': // Left
            if (direction != 2)
                direction = 4;
            break;
        case 'x': // Exit
            gameover = 1;
            break;
        }
    }
}

void logic()
{
    int prevX = snakeX[0];
    int prevY = snakeY[0];
    int prev2X, prev2Y;
    snakeX[0] = prevX + (direction == 2) - (direction == 4); // Move the snake's head
    snakeY[0] = prevY + (direction == 3) - (direction == 1);

    for (int i = 1; i < length; i++)
    {
        prev2X = snakeX[i];
        prev2Y = snakeY[i];
        snakeX[i] = prevX;
        snakeY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Check for collisions with the fruit
    if (snakeX[0] == fruitX && snakeY[0] == fruitY)
    {
        score += 10;
        length++;
        fruitX = rand() % WIDTH; // Place a new fruit at a random location
        fruitY = rand() % HEIGHT;
    }

    // Check for collisions with the walls or the snake's body
    if (snakeX[0] < 0 || snakeX[0] >= WIDTH || snakeY[0] < 0 || snakeY[0] >= HEIGHT)
        gameover = 1;

    for (int i = 1; i < length; i++)
    {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
            gameover = 1;
    }

    // Sleep(speed); // Delay of 100 milliseconds   //3
}
