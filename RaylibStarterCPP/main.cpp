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
    int screenHeight = 700;

    int racketSpeed = 200;

    Vector2 ballSpeed{200, 200};
    
    float speedPerBump = 1.5;

    bool p1win = false;
    bool p2win = false;

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
        if(player1.y < 0)
        {
            player1.y = 0;
        }

        if (player1.y > screenHeight - 120) {
            player1.y = screenHeight - 120;
        }

        if (player2.y < 0)
        {
            player2.y = 0;
        }

        if (player2.y > screenHeight - 120) {
            player2.y = screenHeight - 120;
        }

        //move ball
        if (p1win == false && p2win == false)
        {
            ball.y -= ballSpeed.y * deltaTime;
            ball.x += ballSpeed.x * deltaTime;
        }

        //check ball colisions and change direction and speed accordingly
        if (ball.y <= 0)
        {
            ballSpeed.y *= -1;
            
            //whenever you see this bit it means the ball is speeding up
            if (ballSpeed.y < 0)
            {
                ballSpeed.y -= speedPerBump;
            }
            else {
                ballSpeed.y += speedPerBump;
            }

            if (ballSpeed.x < 0)
            {
                ballSpeed.x -= speedPerBump;
            }
            else {
                ballSpeed.x += speedPerBump;
            }
        }

        if (ball.y >= screenHeight - 20)
        {
            ballSpeed.y *= -1;
            if (ballSpeed.y < 0)
            {
                ballSpeed.y -= speedPerBump;
            }
            else {
                ballSpeed.y += speedPerBump;
            }

            if (ballSpeed.x < 0)
            {
                ballSpeed.x -= speedPerBump;
            }
            else {
                ballSpeed.x += speedPerBump;
            }
        }

        if (CheckCollisionRecs(player1, ball)) {
            ballSpeed.x *= -1;


            //my way
            ///this section changes the direction of the ball so that it will go in a certain direction depending on where it hits the paddle
            float ballPaddleDiffY = (player1.y + player1.height / 2) - (ball.y + ball.height / 2);
            float ballPaddleDiffX = (ball.x + ball.width / 2) - (player1.x + player1.width / 2);

            float origanalMagnitude = sqrt(ballSpeed.x * ballSpeed.x + ballSpeed.y * ballSpeed.y);

            //we set ballSpeed to the distances here becuase when normailized they become the direction
            ballSpeed.y = ballPaddleDiffY;
            ballSpeed.x = ballPaddleDiffX;

            float triangleMagnitude = sqrt(ballSpeed.x * ballSpeed.x + ballSpeed.y * ballSpeed.y);

            //mormalizing ballSpeed
            ballSpeed.y /= triangleMagnitude;
            ballSpeed.x /= triangleMagnitude;

            //we put the origanal speed back on ballSpeed with the new direction
            ballSpeed.y *= origanalMagnitude;
            ballSpeed.x *= origanalMagnitude;

            /*float angle = sin(ballPaddleDiffX / ballPaddleDiffY);

            
            |\
            | \
            |  \ <----------this angle
            |---\
            |    \
            |     \
            |      \
            |       \
            |        \
            ----------
                  ^this length = ballPaddleDiffX
*/



            //chat gpt way
            /*
            float ballPaddleDiff = (ball.y + ball.height / 2) - (player1.y + player1.height / 2);
            float ballSpeedModule = sqrt(ballXSpeed * ballXSpeed + ballYSpeed * ballYSpeed);

            float ballAngle = ballPaddleDiff * .8f;

            ballXSpeed = ballSpeedModule * cos(ballAngle);
            ballYSpeed = ballSpeedModule * sin(ballAngle);

            ballXSpeed /= ballSpeedModule;
            ballYSpeed /= ballSpeedModule;
            ballYSpeed *= 200;
            ballXSpeed *= 200;
            */
            
            
            if (ballSpeed.y < 0)
            {
                ballSpeed.y -= speedPerBump;
            }
            else {
                ballSpeed.y += speedPerBump;
            }

            if (ballSpeed.x < 0)
            {
                ballSpeed.x -= speedPerBump;
            }
            else {
                ballSpeed.x += speedPerBump;
            }
        }

        if (CheckCollisionRecs(player2, ball)) {
            ballSpeed.x *= -1;
            
            float ballPaddleDiffY = (player2.y + player2.height / 2) - (ball.y + ball.height / 2);
            float ballPaddleDiffX = (ball.x + ball.width / 2) - (player2.x + player2.width / 2);

            float origanalMagnitude = sqrt(ballSpeed.x * ballSpeed.x + ballSpeed.y * ballSpeed.y);

            ballSpeed.y = ballPaddleDiffY;
            ballSpeed.x = ballPaddleDiffX;

            float triangleMagnitude = sqrt(ballSpeed.x * ballSpeed.x + ballSpeed.y * ballSpeed.y);

            ballSpeed.y /= triangleMagnitude;
            ballSpeed.x /= triangleMagnitude;

            ballSpeed.y *= origanalMagnitude;
            ballSpeed.x *= origanalMagnitude;
            
            
            if (ballSpeed.y < 0)
            {
                ballSpeed.y -= speedPerBump;
            }
            else {
                ballSpeed.y += speedPerBump;
            }

            if (ballSpeed.x < 0)
            {
                ballSpeed.x -= speedPerBump;
            }
            else {
                ballSpeed.x += speedPerBump;
            }
        }

        if (ball.x <= 0) {
            ++player2Score.score;
            ball.x = screenWidth / 2 - 10;
            ball.y = screenHeight / 2 - 10;
            if (player2Score.score == 4) {
                p2win = true;
            }
        }
        
        if (ball.x >= screenWidth - 10) {
            ++player1Score.score;
            ball.x = screenWidth / 2 - 10;
            ball.y = screenHeight / 2 - 10;
            if (player1Score.score == 4) {
                p1win = true;
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        if (p1win == false && p2win == false)
        {
            player1Score.DrawScore();
            player2Score.DrawScore();

            DrawRectangle(player1.x, player1.y, player1.width, player1.height, RAYWHITE);

            DrawRectangle(player2.x, player2.y, player2.width, player2.height, RAYWHITE);

            DrawRectangle(ball.x, ball.y, ball.width, ball.height, RAYWHITE);
        }
        else if (p1win == true) {
            DrawText("Congrats! P1 you are the winner", 190, 300, 20, RAYWHITE);
        }
        else {
            DrawText("Congrats! P2 you are the winner", 190, 300, 20, RAYWHITE);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}