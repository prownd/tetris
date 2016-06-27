#include<QtGui/QtGui>
#include"tetris.h"
#include"tetrisgame.h"
Block g_CurBlock,g_NextBlock;
bool PutDown=false;
int GameArea[WIDTH][HEIGHT]={0};
int g_Blocks[7][4]={
    {0x0f00,0x4444,0x0f00,0x4444},//I
    {0x0660,0x0660,0x0660,0x0660},//Ìï
    {0x4460,0x02e0,0x0622,0x0740},//L
    {0x2260,0x0e20,0x0644,0x0470},//·´L
    {0x0c60,0x2640,0x0c60,0x2640},//Z
    {0x0360,0x4620,0x0360,0x4620},//·´Z
    {0x4e00,0x4c40,0x0e40,0x4640} //T
    };

bool Block::ChectBlock()
{

    int X,Y,i;
    int b=g_Blocks[id][dir];
    for(i=0;i<16;i++)
    {
        if(b&0x8000)
        {
            X=x+i%4;
            Y=y+i/4;
            if(X<X_MIN||X>=X_MAX||GameArea[X][Y]==1||Y>=HEIGHT)
                return false;
        }
        b<<=1;
    }

   return true;
}

void Block::OnRotate()
{
    int dx;
    Block temp=*this;
    temp.dir=(temp.dir+1)%4;
                if(temp.ChectBlock()==true) {dx=0;  goto rotate;}
    temp.x=x-1; if(temp.ChectBlock()==true) {dx=-1; goto rotate;}
    temp.x=x+1; if(temp.ChectBlock()==true) {dx=1;  goto rotate;}
    temp.x=x-2; if(temp.ChectBlock()==true) {dx=-2; goto rotate;}
    temp.x=x+2; if(temp.ChectBlock()==true) {dx=2;  goto rotate;}
    temp.x=x-3; if(temp.ChectBlock()==true) {dx=-3; goto rotate;}
    temp.x=x+3; if(temp.ChectBlock()==true) {dx=3;  goto rotate;}
    return;

    rotate:
           dir=temp.dir;
           x+=dx;
}
void Block::OnLeft()
{
    Block temp=*this;
    temp.x--;
    if(temp.ChectBlock()==true)
    {
        x--;
    }
}
void Block::OnRight()
{
    Block temp=*this;
    temp.x++;
    if(temp.ChectBlock()==true)
    {
        x++;
    }
}

void Block::OnDown()
{
    Block temp=*this;
    temp.y++;
    if(temp.ChectBlock()==true)
    {
        y++;
    }
    else
    {
        PutBlock();
        PutDown=true;
    }
}
void Block::PutBlock()
{
    int X,Y,i;
    int b=g_Blocks[id][dir];
    for(i=0;i<16;i++)
    {
        if(b&0x8000)
        {
            X=x+i%4;
            Y=y+i/4;
            GameArea[X][Y]=1;
        }
        b<<=1;
    }
}



void Block::OnSink()
{
    Block temp=*this;
    temp.y++;
    while(temp.ChectBlock()==true)
    {
        y++;
        temp.y++;
    }
    PutBlock();
    PutDown=true;
}

