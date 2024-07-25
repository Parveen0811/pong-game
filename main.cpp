#include <iostream>
#include <raylib.h>

using namespace std;

int playerScore=0;
int cpuScore=0;

class Ball{
    public:
    float x,y;
    int speedx,speedy;
    int radius;

    void Draw(){
        DrawCircle(x,y,radius,WHITE);
    }

    void update(){
        x=x+speedx;
        y=y+speedy;

        if(y+radius >= 800 || y-radius <= 0){
            speedy *= -1;
        }
        if(x+radius >= 1200){
            cpuScore++;
            Resetball();
        }
        if(x+radius <= 0){
            playerScore++;
            Resetball();
        }

    }
    void Resetball(){
        x=600;
        y=400;

        int speedchoice[2] = {-1,1};

        speedx *= speedchoice[GetRandomValue(0,1)];
        speedy *= speedchoice[GetRandomValue(0,1)];
    }
};

class Paddle{
    public:
    float x,y;
    float height,weidht;
    int speed;

    void Draw(){
        DrawRectangle(x,y,weidht,height,WHITE);
    }

    void update(){
        if(IsKeyDown(KEY_UP))
        {
            y -=speed;
        }else if(IsKeyDown(KEY_DOWN))
        {
            y +=speed;
        }

        if(y<=0){
            y=0;
        }

        if(y+height>=800){
            y = 800-height;
        }
    }
};

class cpupaddle: public Paddle{
    public:

    void update(int bally){
        if(y+height/2 > bally){
            y=y-speed;
        }
        if(y+height/2 <= bally){
            y=y+speed;
        }
    }
};

Ball ball;
Paddle player;
cpupaddle cpu;

int main () {

    InitWindow(1200, 800, "Pong");
    SetTargetFPS(60);
    
    ball.radius=20;
    ball.x=600;
    ball.y=400;
    ball.speedx=7;
    ball.speedy=7;

    player.x=1170;
    player.y=5;
    player.weidht=25;
    player.height=120;
    player.speed=5;

    cpu.x=5;
    cpu.y=5;
    cpu.weidht=25;
    cpu.height=120;
    cpu.speed=5;

    while(WindowShouldClose()==false) 
    {
        BeginDrawing();

        DrawLine(600,0,600,800,WHITE);
       
        if(cpuScore==10)
        {
            DrawText("Gameover",300,500,150,WHITE);
            DrawText("Press [R] to restart",400,650,40,WHITE);
            DrawText("Press [ESC] to Exit",400,700,40,WHITE);

            if(IsKeyPressed(KEY_R)){
                cpuScore=0;
                playerScore=0;
            }
        }else if(playerScore==10){
            DrawText("Winner",350,500,150,WHITE);
            DrawText("Press [R] to restart",400,650,40,WHITE);
            DrawText("Press [ESC] to Exit",400,700,40,WHITE);

            if(IsKeyPressed(KEY_R)){
                cpuScore=0;
                playerScore=0;
            }
        }
        else{
        ball.update();
        player.update();
        cpu.update(ball.y);
        }
        

        //checking for collision
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{player.x,player.y,player.weidht,player.height})){
            ball.speedx *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{cpu.x,cpu.y,cpu.weidht,cpu.height})){
            ball.speedx *= -1;
        }

        //Drawing
        ClearBackground(BLACK);
       
        player.Draw();
        ball.Draw();
        cpu.Draw();

        DrawRectangle(0,0,5,800,RED);
        DrawRectangle(1195,0,5,800,BLUE);
        DrawText(TextFormat("%i",playerScore),300,5,50,WHITE);
        DrawText(TextFormat("%i",cpuScore),900,5,50,WHITE);
        DrawCircleLines(600,400,100,WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}