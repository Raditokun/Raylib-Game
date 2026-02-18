#include <raylib.h>


using namespace std;

struct Animation {
    int first; //first frame
    int last; //last frame
    int cur; //current fram 
    float speed; //animation speed
    float duration_left; //time left for current frame
    
    
};

bool animation_update(Animation *self){
    float dt = GetFrameTime(); //get delta time(time between frames)
    self->duration_left -= dt; //subtract delta time from duration left

    if(self->duration_left <= 0.0){
        self->duration_left = self->speed;
        self->cur++;//go to the next spriteframe

        if(self->cur > self->last){
            self->cur = self->first;
            return true;
        }
    }
    return false;
}

//getting the cords for the current frame
//the math for finding the x and y position of each frame in the sprite sheet
Rectangle animation_frame(Animation *self, int num_frames_per_row){
       int x = (self->cur % num_frames_per_row) * 16.0; 
       int y = (self->cur / num_frames_per_row) * 16.0;
    
           return (Rectangle){(float)x,(float)y, 16.0, 16.0};
}



int main(){

    InitWindow(600, 400, "Aimlab game");
    Texture2D player_idle = LoadTexture("src/asset/herochar sprites(new)/herochar_idle_anim_strip_4.png");
    Texture2D player_run = LoadTexture("src/asset/herochar sprites(new)/herochar_run_anim_strip_6.png");
    Texture2D player_attack = LoadTexture("src/asset/herochar sprites(new)/herochar_sword_attack_anim_strip_4.png");
    Texture2D player_jump = LoadTexture("src/asset/herochar sprites(new)/herochar_jump_up_anim_strip_3.png");

    Animation anim_idle = (Animation){0, 3, 0, 0.1, 0.1};
    Animation anim_run = (Animation){0, 5, 0, 0.1, 0.1};
    Animation anim_attack =  (Animation){0, 3, 0, 0.1, 0.1};
    Animation anim_jump = (Animation){0, 2, 0, 0.15f, 0.15f};
     Vector2 player_pos = {10,300}; //automaticly assums that its x and y??



      //bool state
     bool attack = false;
     

     //jump physics
    float velocity_y = 0.0f;   //jump velocity 
    float gravity = 0.5f;        
    float jump_force = 10.0f;    
    float ground_level = 300.0f; 
    bool is_on_ground = false;

     
    
     
 
    
    SetTargetFPS(60);

     while(!WindowShouldClose()){

        //jump logic    
        velocity_y += gravity; //gravity

        player_pos.y += velocity_y; //??

        if (player_pos.y >= ground_level) {
            player_pos.y = ground_level;
            velocity_y = 0.0f;
            is_on_ground = true;
        } else {
            is_on_ground = false;
        }//??

        if(IsKeyPressed(KEY_SPACE) && is_on_ground && !attack){
            velocity_y = -jump_force; //apply jump force
            is_on_ground = false; 

        anim_jump.cur = 0; // reset frame  
        }
          



        //Attack Logic
        if (IsKeyPressed(KEY_ENTER) && !attack){
         attack = true;
         anim_attack.cur = 0; //reset attack animation to first frame
         anim_attack.duration_left = anim_attack.speed  ; //reset duration left
     }

     if(attack){
        if(animation_update(&anim_attack)){
            attack = false;
            anim_attack.cur = 0;
        }
     }else{
        if(is_on_ground){
        animation_update(&anim_idle);
        animation_update(&anim_run);
        }else{
            animation_update(&anim_jump);
        }
        if(IsKeyDown(KEY_LEFT)){
            player_pos.x -= 2;

        }
        if(IsKeyDown(KEY_RIGHT)){
            player_pos.x += 2;

        }
        
     }


        BeginDrawing();
        ClearBackground(WHITE);
        

        
        if (attack){
            DrawTexturePro(player_attack,animation_frame(&anim_attack, 4), {player_pos.x,player_pos.y,100,100},{0,0}, 0, WHITE);

        }
        else if (!is_on_ground){
            DrawTexturePro(player_jump,animation_frame(&anim_jump, 3), {player_pos.x,player_pos.y,100,100},{0,0}, 0, WHITE);
        }
        else if (IsKeyDown(KEY_LEFT)){
            Rectangle source = animation_frame(&anim_run, 6);
            source.width *= -1; //flip the sprite
             DrawTexturePro(player_run,source, {player_pos.x,player_pos.y,100,100},{0,0}, 0, WHITE);
            
        }
        else if (IsKeyDown(KEY_RIGHT)){
            DrawTexturePro(player_run,animation_frame(&anim_run, 6), {player_pos.x,player_pos.y,100,100},{0,0}, 0, WHITE);
            
        } else {
            DrawTexturePro(player_idle,animation_frame(&anim_idle, 4), {player_pos.x,player_pos.y,100,100},{0,0}, 0, WHITE);
        }
        
            
        EndDrawing();
    }

    UnloadTexture(player_idle);
    UnloadTexture(player_run);
    UnloadTexture(player_attack);
    UnloadTexture(player_jump);

    

    CloseWindow();
    return 0;
}