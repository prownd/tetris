#include "tetrisgame.h"

#include<QtGui/QtGui>
#include"tetris.h"
#include<QTime>
#include <QPalette>
//#define G_HEIGHT 20
//#define G_WIDTH 10
extern Block g_CurBlock;
extern Block g_NextBlock;
extern int g_Blocks[7][4];
extern int GameArea[WIDTH][HEIGHT];
extern bool PutDown;//block down
BlockGame::BlockGame(QWidget *parent):QWidget(parent)
{
    start=true;
    time_num=1000;
    sumblock=0;
    eraselinenum=0;
    tmpblockscore=0;
    sumscore=0;
    //scorenum=0;
    b_istop=false;
    firstlineblank=true;
    b_pause=false;
    movedirect=new QTimer();
    e_istop=new QTimer();
    movedirect->setInterval (10);
    e_istop->setInterval(2);
    btnstart=new QPushButton(tr("start"),this);
    btnpause=new QPushButton(tr("pause"),this);
    btnquit=new QPushButton(tr("end"),this);
    lcdnum = new QLCDNumber(this);
    lcdnum->move(SIZE*WIDTH+50,SIZE*5+50);
    btnstart->move (SIZE*WIDTH+50,SIZE*5+50*3);
    btnpause->move(SIZE*WIDTH+50,SIZE*5+50*4);
    btnquit->move (SIZE*WIDTH+50,SIZE*5+50*5);
    btnstart->setDefault (false);
    btnpause->setDefault (false);
    btnquit->setDefault (false);
    //btnstart->focusPolicy();
    ctrl=ctrl_default;
    resize(SIZE*WIDTH+200,SIZE*HEIGHT+2);
    sid=0;
    qsrand(QTime::currentTime().msec());
//    lcdnum->setNumDigits(8);
//    lcdnum->setSegmentStyle(QLCDNumber::Filled);
//    lcdp = lcdnum->palette();
//    lcdp.setColor(QPalette::Normal,QPalette::WindowText,Qt::green);
//    lcdnum->setPalette(lcdp);
//    lcdnum->move(450,420);

    //this->setFocus ();
    connect (movedirect,SIGNAL(timeout()),this,SLOT(directchange()));
    connect(e_istop,SIGNAL(timeout()),this,SLOT(checkistop()));
    connect (btnstart,SIGNAL(clicked()),this,SLOT(s_start()));
    connect (btnpause,SIGNAL(clicked()),this,SLOT(s_pause()));
    connect (btnquit,SIGNAL(clicked()),this,SLOT(close()));
}
void BlockGame::NewBlock()
{
    g_CurBlock.id=g_NextBlock.id;
    g_CurBlock.dir=g_NextBlock.dir;
    g_CurBlock.x=X_MIN+2;
    g_CurBlock.y=0;
    g_NextBlock.id=qrand()%7;
    g_NextBlock.dir=qrand()%4;
    sumblock+=1;
}
void BlockGame::NewGame()
{
    //qsrand(2);
    qsrand(QTime::currentTime().msec());
    g_NextBlock.id=qrand()%7;
    g_NextBlock.dir=qrand()%4;
    g_NextBlock.x=X_MAX+1;
    g_NextBlock.y=1;
    NewBlock();
}
void BlockGame::Draw_CurBlock()
{

    int x,y,i;
    int X=g_CurBlock.x,Y=g_CurBlock.y;
    int block=g_Blocks[g_CurBlock.id][g_CurBlock.dir];
    QPainter painter(this);
    //QBrush   brush(QColor(255,10,110));
    QBrush   brush(QColor(100,120,255));
    painter.setBrush(brush);
    for(i=0;i<16;i++)
    {
        if(block&0x8000)
        {
            x=X+i%4;
            y=Y+i/4;
            if(i<4)
            {
                firstlineblank=false;
            }
            if(firstlineblank)
                painter.drawRect(x*SIZE,(y-1)*SIZE,SIZE,SIZE);
            else
                painter.drawRect(x*SIZE,y*SIZE,SIZE,SIZE);
        }
        block<<=1;
    }
    firstlineblank=true;

}
void BlockGame::Draw_NextBlock()
{
    int x,y,i;
    int X=g_NextBlock.x,Y=g_NextBlock.y;
    int block=g_Blocks[g_NextBlock.id][g_NextBlock.dir];
    QPainter painter(this);
    QBrush   brush(QColor(120,200,110));
    painter.setBrush(brush);
    for(i=0;i<16;i++)
    {
        if(block&0x8000)
        {
            x=X+i%4;
            y=Y+i/4;
            painter.drawRect(x*SIZE,y*SIZE,SIZE,SIZE);

        }
        block<<=1;
    }
}
void BlockGame::InitGame()
{

    QPainter painter(this);
    QPen pen1(Qt::blue,1);
    //QBrush brush(QColor(110,10,30));
    QRect rect1(1,0,SIZE*WIDTH,SIZE*HEIGHT),rect2(SIZE*WIDTH+10,0,SIZE*5,SIZE*5),rect3(410,250,210,340);
    QImage image(tr("bg.jpg"));
	//painter.drawImage(0,0,image,20,20);
    painter.setPen(pen1);
    painter.drawRect(rect1);
    //painter.setBrush(brush);
    painter.drawRect(rect2);
    //painter.drawRect(rect3);
    QPen pen2(Qt::black,1);
    painter.setPen(pen2);
    for(int j=0;j<HEIGHT;j++)
        painter.drawLine(0,j*SIZE,WIDTH*SIZE,j*SIZE);
    for(int j=0;j<WIDTH;j++)
        painter.drawLine(j*SIZE,0,j*SIZE,HEIGHT*SIZE);
    //this->setFocus ();
    //QWidget::setFocus();
    //painter.drawText(rect3,tr("WELCOME TO PLAYING BLOCK GAME!"));
}

void BlockGame::DispatchMessage()
{
    switch(ctrl)
    {
        case ctrl_up:g_CurBlock.OnRotate();break;
        case ctrl_down:g_CurBlock.OnSink();break;
        case ctrl_left:g_CurBlock.OnLeft();break;
        case ctrl_right:g_CurBlock.OnRight();break;
        default:g_CurBlock.OnDown();break;
    }
    ctrl=ctrl_default;
}
void BlockGame::directchange ()
{
    switch(ctrl)
    {
        case ctrl_up:g_CurBlock.OnRotate();break;
        case ctrl_down:g_CurBlock.OnSink();break;
        case ctrl_left:g_CurBlock.OnLeft();break;
        case ctrl_right:g_CurBlock.OnRight();break;
        default:break;
    }
    ctrl=ctrl_default;
    if(PutDown==true)
    {
        EraseBlock();
        NewBlock();
        sumblock+1;
        PutDown=false;
    }

    update();
}
void BlockGame::checkistop()
{
    lcdnum->display(getscore());
    if(IsTop ())
    {

        QMessageBox::warning (this,tr("game over"),tr("game over"));
        this->killTimer (sid);
        movedirect->stop();
        e_istop->stop();
        b_istop=true;

    }
}
void BlockGame::paintEvent(QPaintEvent *paintevent)
{

  InitGame();
  RenewGameArea();
  if(sid)
  {
    Draw_CurBlock();
    Draw_NextBlock();

  }
  //this->setFocus ();
}
void BlockGame::timerEvent(QTimerEvent *timerevent)
{
    //DispatchMessage();
    if(!IsTop ())
    {
        g_CurBlock.OnDown();
        if(PutDown==true)
        {
            EraseBlock();
            NewBlock();

            PutDown=false;
        }
    }
    update();
//    if(IsTop ())
//    {
//        QMessageBox::warning (this,tr("游戏结束"),tr("游戏结束"));
//        this->killTimer (sid);
//        movedirect->stop();
//        b_istop=true;
//    }
//    scorenum=1;
//    lcdnum->display(scorenum);
}
void BlockGame::keyPressEvent(QKeyEvent *keyevent)
{
    switch(keyevent->key())
    {
        case Qt::Key_Up:ctrl=ctrl_up;break;
        case Qt::Key_Down:ctrl=ctrl_down;break;
        case Qt::Key_Left:ctrl=ctrl_left;break;
        case Qt::Key_Right:ctrl=ctrl_right;break;
        default:ctrl=ctrl_default;break;
    }
}


void BlockGame::EraseBlock()
{
    int i,j,k,n,Y;
    int row[4]={0};
    bool bRow=false;
    //eraselinenum=0;
    Y=g_CurBlock.y;
    for(j=Y;j<Y+4;j++)
    {
        n=0;
        for(i=0;i<X_MAX;i++)
        {
            if(GameArea[i][j]==1)
                n++;
        }

        if(n==WIDTH)
        {
            bRow=true;
            row[j-Y]=1;
        }
    }
    if(bRow==true)
    {
        for(k=0;k<4;k++)
        {
            if(row[k]==1)
            {
                eraselinenum+=1;
                for(j=Y+k;j>0;j--)
                     for(i=0;i<X_MAX;i++)
                        {
                            GameArea[i][j]=GameArea[i][j-1];
                            GameArea[i][j-1]=0;
                        }
            }
        }
    }
}


void BlockGame::RenewGameArea()
 {
     int i,j;
     QPainter painter(this);
     QBrush brush(QColor(100,120,155));
     QRect rect;
     painter.setBrush(brush);
     for(j=0;j<HEIGHT;j++)
         for(i=0;i<X_MAX;i++)
         {
             rect.setRect(i*SIZE,j*SIZE,SIZE,SIZE);
             if(GameArea[i][j]==1) painter.drawRect(rect);
         }
}
bool BlockGame::IsTop ()
{
    for(int i=0;i<WIDTH;i++)
    {
        if(GameArea[i][0]==1)
        {
            //QMessageBox::warning (this,tr("游戏结束"),tr("游戏结束"));
            return true;
        }
    }
    return false;

}
void  BlockGame::s_start ()
{
    for(int i=0;i<WIDTH;i++)
    {
        for(int j=0;j<HEIGHT;j++)
            GameArea[i][j]=0;
    }
   //eraselinenum=0;
   sumblock=0;
   b_istop=false;
   this->killTimer (sid);
   sid=this->startTimer(time_num);
   movedirect->start ();
   e_istop->start();
   this->setFocus ();
   NewGame();
}
void BlockGame::s_pause ()
{
    if(!b_pause)
    {
        this->killTimer (sid);
        movedirect->stop ();
        e_istop->stop();
        btnpause->setText (tr("continue"));
        b_pause=true;
        this->setFocus ();
    }else
    {
        sid=this->startTimer (time_num);
        movedirect->start ();
        e_istop->start();
        btnpause->setText (tr("pause"));
        b_pause=false;
        this->setFocus ();
    }

}

int BlockGame::getscore()
{

   //tmpblockscore=eraselinenum*(eraselinenum==0?0:eraselinenum==1?100:eraselinenum==2?200:eraselinenum==3?300:400);

   sumscore=sumblock*10+eraselinenum*100;
   return sumscore;

}
