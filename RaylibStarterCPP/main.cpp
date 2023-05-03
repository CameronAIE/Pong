/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "ScoreCubes.h"

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1000;
    int screenHeight = 800;

    int racketSpeed = 200;

    float ballXSpeed = 100;
    float ballYSpeed = 100;

    int p1Score = 0;
    int p2Score = 0;
    
    float speedPerBump = 1.5;

    Rectangle player1 { 50, screenHeight / 2 - 60, 20 , 120};
    Rectangle player2 { screenWidth - 70, screenHeight / 2 - 60, 20 , 120 };

    Rectangle ball{ screenWidth / 2 - 10, screenHeight / 2 - 10, 20, 20 };

    ScoreCubes player1Score(screenWidth * .25);
    ScoreCubes player2Score(screenWidth * .75);

    InitWindow(screenWidth, screenHeight, "PONG");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        //get the deltaTime for this frame
        float deltaTime = GetFrameTime();

        //check input for all rackets
        if (IsKeyDown(KEY_DOWN)) {
            player2.y += racketSpeed * deltaTime;
        }

        if (IsKeyDown(KEY_UP)) {
            player2.y -= racketSpeed * deltaTime;
        }

        if (IsKeyDown(KEY_S)) {
            player1.y += racketSpeed * deltaTime;
        }

        if (IsKeyDown(KEY_W)) {
            player1.y -= racketSpeed * deltaTime;
        }

        //move rackets on screen if they went off


        //move ball
        ball.y -= ballYSpeed * deltaTime;
        ball.x += ballXSpeed * deltaTime;

        //check ball colisions and change direction and speed accordingly
        if (ball.y <= 0)
        {
            ballYSpeed -= ballYSpeed * 2;
            if (ballYSpeed < 0)
            {
                ballYSpeed -= speedPerBump;
            }
            else {
                ballYSpeed += speedPerBump;
            }

            if (ballXSpeed < 0)
            {
                ballXSpeed -= speedPerBump;
            }
            else {
                ballXSpeed += speedPerBump;
            }
        }

        if (ball.y >= screenHeight - 20)
        {
            ballYSpeed -= ballYSpeed * 2;
            if (ballYSpeed < 0)
            {
                ballYSpeed -= speedPerBump;
            }
            else {
                ballYSpeed += speedPerBump;
            }

            if (ballXSpeed < 0)
            {
                ballXSpeed -= speedPerBump;
            }
            else {
                ballXSpeed += speedPerBump;
            }
        }

        if (CheckCollisionRecs(player1, ball)) {
            ballXSpeed -= ballXSpeed * 2;
            if (ballYSpeed < 0)
            {
                ballYSpeed -= speedPerBump;
            }
            else {
                ballYSpeed += speedPerBump;
            }

            if (ballXSpeed < 0)
            {
                ballXSpeed -= speedPerBump;
            }
            else {
                ballXSpeed += speedPerBump;
            }
        }

        if (CheckCollisionRecs(player2, ball)) {
            ballXSpeed -= ballXSpeed * 2;
            if (ballYSpeed < 0)
            {
                ballYSpeed -= speedPerBump;
            }
            else {
                ballYSpeed += speedPerBump;
            }

            if (ballXSpeed < 0)
            {
                ballXSpeed -= speedPerBump;
            }
            else {
                ballXSpeed += speedPerBump;
            }
        }

        if (ball.x <= 0) {
            player2Score.score + 1;
            player2Score.UpdateScore();
            ball.x = screenWidth / 2 - 10;
            ball.y = screenHeight / 2 - 10;
        }
        
        if (ball.x >= screenWidth - 10) {
            player1Score.score + 1;
            player1Score.UpdateScore();
            ball.x = screenWidth / 2 - 10;
            ball.y = screenHeight / 2 - 10;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        player1Score.DrawScore();
        player2Score.DrawScore();

        DrawRectangle(player1.x, player1.y, player1.width, player1.height, RAYWHITE);

        DrawRectangle(player2.x, player2.y, player2.width, player2.height, RAYWHITE);

        DrawRectangle(ball.x, ball.y, ball.width, ball.height, RAYWHITE);

        //DrawText("Congrats! You created your first window!", 190, 200, 20, RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}