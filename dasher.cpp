#include "raylib.h"



struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool IsOnGround(AnimData data, int windowHeight){
   return data.pos.y >= windowHeight - data.rec.height;
}

AnimData UpdateAnimData(AnimData data, float dT, int maxFrames){
     data.runningTime += dT;
            
    if(data.runningTime>=data.updateTime){
        data.runningTime = 0.0;
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if(data.frame>maxFrames){
            data.frame = 0;
        }
    }
    return data;
}

int main(){

    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;
    

    SetTargetFPS(60);
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper dasher");

    const int gravity = 1'000;
    

    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
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

    const int sizeOfNebulae = 6;
    AnimData nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;

        nebulae[i].pos.x = windowDimensions[0] + i * 300;
    }


    //nebula X velocity pixels/second
    int nebVelocity{-200};



    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        //Delta time, time since last frame
        float dT = GetFrameTime();


        //If its on the ground
        if(IsOnGround(scarfyData, windowDimensions[1])){
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


        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].pos.x += nebVelocity * dT;
            
        }
        

        //update scarfy pos
        scarfyData.pos.y+= velocity * dT;



        //Update animation frame
        //frame * width/numFrames 

        //update scarfy animation frame

        if(!isInAir){
            scarfyData = UpdateAnimData(scarfyData, dT, 5);
        }
        
        //update nebula running time

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = UpdateAnimData(nebulae[i], dT, 7);
        }
        
        //Draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        //Draw nebula
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);

        }


        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

    
}