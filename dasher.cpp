#include "raylib.h"



struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main(){

    //Window variables
    const int windowWidth = 512;
    const int windowHeight = 380;



    SetTargetFPS(60);
    InitWindow(windowWidth, windowHeight, "Dapper dasher");

    const int gravity = 1'000;
    

    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowWidth/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;


    //pixels per second
    const int jumpVelocity = -600;
    //Rectangle
    /*
    const int width = 50;
    const int height = 80;

    int posY = (windowHeight - height);*/

    int velocity = 0;

    bool isInAir = false;


    //nebula hazard


    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData nebData{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, //Rec
        {windowWidth, windowHeight - nebula.height/8},  //Vector2 Pos
        0,  //Frame
        1.0/12.0,  //updateTime
        0 //Running time
    };

    AnimData neb2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, //Rec
        {windowWidth + 300, windowHeight - nebula.height/8},  //Vector2 Pos
        0,  //Frame
        1.0/16.0,  //updateTime
        0 //Running time
    };


    //nebula X velocity pixels/second
    int nebVelocity{-200};



    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        //Delta time, time since last frame
        float dT = GetFrameTime();


        //If its on the ground
        if(scarfyData.pos.y >= windowHeight-scarfyData.rec.height){
            //scarfyData.pos.y = windowHeight-scarfyData.rec.height;
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
        nebData.pos.x += nebVelocity * dT;

        neb2Data.pos.x += nebVelocity * dT;


        //update scarfy pos
        scarfyData.pos.y+= velocity * dT;



        //Update animation frame
        //frame * width/numFrames 

        //update scarfy animation frame
        //update running time

        if(!isInAir){
            scarfyData.runningTime += dT;
            
            if(scarfyData.runningTime>=scarfyData.updateTime){
                scarfyData.runningTime = 0.0;
                scarfyData.rec.x = scarfyData.frame *scarfyData.rec.width;
                scarfyData.frame++;
                if(scarfyData.frame>5){
                    scarfyData.frame = 0;
                }
            }
        }
        
        //update nebula running time
        nebData.runningTime += dT;
        if( nebData.runningTime >= nebData.updateTime){
             nebData.runningTime = 0.0;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if(nebData.frame > 7){
                nebData.frame = 0;
            }
        }

        //update nebula running time
        neb2Data.runningTime += dT;
        if( neb2Data.runningTime >= neb2Data.updateTime){
             neb2Data.runningTime = 0.0;
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if(neb2Data.frame > 7){
                neb2Data.frame = 0;
            }
        }

        //Draw scarfy
        //DrawRectangle(windowWidth/2, posY, width, height, BLUE);
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        //Draw nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);


        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

    
}