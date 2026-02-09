#include <raylib.h>


using namespace std;

struct Animation {
    int first; //first frame
    int last; //last frame
    int cur; //current fram 
    float speed; //animation speed
    float duration_left; //time left for current frame
    
};

void animation_update(Animation *self){
    float dt = GetFrameTime(); //get delta time(time between frames)
    self->duration_left -= dt; //subtract delta time from duration left

    if(self->duration_left <= 0.0){
        self->duration_left = self->speed;
        self->cur++;//go to the next spriteframe

        if(self->cur > self->last){
            self->cur = self->first;
        }
    }
}

//getting the cords for the current frame??
Rectangle animation_frame(Animation *self, int num_frames_per_row){
       int x = (self->cur % num_frames_per_row) * 16.0; 
       int y = (self->cur / num_frames_per_row) * 16.0;
    
           return (Rectangle){(float)x,(float)y, 16.0, 16.0};
}



int main(){

    InitWindow(600, 400, "Aimlab game");
    Texture2D player_idle = LoadTexture("src/asset/herochar sprites(new)/herochar_idle_anim_strip_4.png");


    Animation anim = (Animation){0, 3, 0, 0.1, 0.1};
     Vector2 player_pos = {10,10}; //automaticly assums that its x and y??
    Vector2 player_pos = {10, 10}; // Assigns {x, y} because Vector2 is defined as struct { float x; float y; }
    
    SetTargetFPS(60);

     while(!WindowShouldClose()){
        animation_update(&anim);
        BeginDrawing();
        ClearBackground(WHITE);

        DrawTexturePro(player_idle,animation_frame(&anim, 4), {player_pos.x,player_pos.y,100,100},{0,0}, 0, WHITE);
        if (IsKeyDown(KEY_RIGHT)){
            player_pos.x += 2;
        }
            
        EndDrawing();
    }

    UnloadTexture(player_idle);

    

     CloseWindow();
    return 0;
}