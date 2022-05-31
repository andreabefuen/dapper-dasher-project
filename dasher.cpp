#include "raylib.h"




int main(){

    //Window variables
    const int windowWidth = 512;
    const int windowHeight = 380;



    SetTargetFPS(60);
    InitWindow(windowWidth, windowHeight, "Dapper dasher");

    const int gravity = 1'000;
    

    Texture2D scarfy = LoadTexture("textures/scarfy.png");



    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    //pixels per second
    const int jumpVelocity = -600;
    //Rectangle
    /*
    const int width = 50;
    const int height = 80;

    int posY = (windowHeight - height);*/

    int velocity = 0;

    bool isInAir = false;

    //Animation Frame
    int frame = 0;
    //amount of time before we upddate the animation frame
    const float updateTime = 1.0/12.0;
    float runningTime;

    //nebula hazard
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};
    //nebula X velocity pixels/second
    int nebVelocity{-200};

    //nebula animation variables
    int nebFrame = 0;
    const float nebUpdateTime = 1.0/12.0;
    float nebRunningTime;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        //Delta time, time since last frame
        float dT = GetFrameTime();


        //If its on the ground
        if(scarfyPos.y >= windowHeight-scarfyRec.height){
            scarfyPos.y = windowHeight-scarfyRec.height;
            velocity = 0;
            isInAir = false;
        }
        //In the air
        else{
            velocity += gravity * dT;
            isInAir = true;
        }
        if(IsKeyPressed(KEY_SPACE) && !isInAir){
            velocity += jumpVelocity;
        }


        
        //update nebula pos
        nebPos.x += nebVelocity * dT;

        //update scarfy pos
        scarfyPos.y+= velocity * dT;



        //Update animation frame
        //frame * width/numFrames 

        //update scarfy animation frame
        //update running time
        runningTime += dT;

        if(!isInAir){
            
            if(runningTime>=updateTime){
                runningTime = 0.0;
                scarfyRec.x = frame *scarfyRec.width;
                frame++;
                if(frame>5){
                    frame = 0;
                }
            }
        }
        
        //update nebula running time
        nebRunningTime += dT;
        if(nebRunningTime >= nebUpdateTime){
            nebRunningTime = 0.0;
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if(nebFrame > 7){
                nebFrame = 0;
            }
        }

        //Draw scarfy
        //DrawRectangle(windowWidth/2, posY, width, height, BLUE);
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        //Draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

    
}