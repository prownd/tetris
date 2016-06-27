#ifndef BLOCK_H
#define BLOCK_H
#include<QtGui/QtGui>
#define SIZE    30 //每个方格的单位宽度是20像素
#define HEIGHT  20
#define WIDTH   10  //定义游戏区的高度和宽度
#define X_MIN   0    //最小x坐标
#define X_MAX   10   //最大x坐标
class BlockGame;
class Block
{
       private:
                int id;  //方块的种类
                int x,y; //方块的坐标
                int dir; //方块的方向
        public:
                void OnRotate();  //翻转方块
                void OnLeft();    //方块左移
                void OnDown();    //方块下移
                void OnSink();    //方块沉底
                void OnRight();   //方块右移
                bool ChectBlock();  //检查方块是否可以移动
                void PutBlock();   //放置方块
         friend class BlockGame;
};
#endif
