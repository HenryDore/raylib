/*******************************************************************************************
*
*   raylib [shapes] example - collision area
*
*   This example has been created using raylib 2.5 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2019 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <stdlib.h>     // Required for abs()

int main()
{
    // Initialization
    //---------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - collision area");
    
    // Box A: Moving box
    Rectangle boxA = { 10, GetScreenHeight()/2 - 50, 200, 100 };
	int boxASpeedX = 4;
	
    // Box B: Mouse moved box
    Rectangle boxB = { GetScreenWidth()/2 - 30, GetScreenHeight()/2 - 30, 60, 60 };
    
    Rectangle boxCollision = { 0 };       // Collision rectangle
    
    int screenUpperLimit = 40;      // Top menu limits
    
	bool pause = false;             // Movement pause
	bool collision = false;         // Collision detection
    
    SetTargetFPS(60);
    //----------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //-----------------------------------------------------
        // Move box if not paused
		if (!pause) boxA.x += boxASpeedX;
        
        // Bounce box on x screen limits
		if (((boxA.x + boxA.width) >= GetScreenWidth()) || (boxA.x <= 0)) boxASpeedX *= -1;
		
		// Update player-controlled-box (box02)
		boxB.x = GetMouseX() - boxB.width/2;
		boxB.y = GetMouseY() - boxB.height/2;
		
        // Make sure Box B does not go out of move area limits
		if ((boxB.x + boxB.width) >= GetScreenWidth()) boxB.x = GetScreenWidth() - boxB.width;
		else if (boxB.x <= 0) boxB.x = 0;
		
		if ((boxB.y + boxB.height) >= GetScreenHeight()) boxB.y = GetScreenHeight() - boxB.height;
		else if (boxB.y <= screenUpperLimit) boxB.y = screenUpperLimit;
        
        // Check boxes collision
        collision = CheckCollisionRecs(boxA, boxB);
		
		// Get collision rectangle (only on collision)
		if (collision) boxCollision = GetCollisionRec(boxA, boxB);
		
        // Pause Box A movement
		if (IsKeyPressed(KEY_SPACE)) pause = !pause;
        //-----------------------------------------------------
        
        // Draw
        //-----------------------------------------------------
        BeginDrawing();
        
            ClearBackground(RAYWHITE);
            
            DrawRectangle(0, 0, screenWidth, screenUpperLimit, collision? RED : BLACK);

            DrawRectangleRec(boxA, GOLD);
            DrawRectangleRec(boxB, BLUE);
            
            if (collision)
            {
                // Draw collision area
                DrawRectangleRec(boxCollision, LIME);
                
                // Draw collision message
                DrawText("COLLISION!", GetScreenWidth()/2 - MeasureText("COLLISION!", 20)/2, screenUpperLimit/2 - 10, 20, BLACK);
                
                // Draw collision area
                DrawText(FormatText("Collision Area: %i", (int)boxCollision.width*(int)boxCollision.height), GetScreenWidth()/2 - 100, screenUpperLimit + 10, 20, BLACK);
            }     

            DrawFPS(10, 10);
        
        EndDrawing();
        //-----------------------------------------------------
    }

    // De-Initialization
    //---------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------
    
    return 0;
}