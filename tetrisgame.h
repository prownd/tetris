#ifndef BLOCKGAME_H
#define BLOCKGAME_H
#include<QtGui/QtGui>
#include <QWidget>
#include<QPushButton>
#include<QTimer>
#include<QLCDNumber>
#include<QPalette>
enum CTRL{ctrl_down,ctrl_up,ctrl_left,ctrl_right,ctrl_default};
class BlockGame:public QWidget
{
    Q_OBJECT
    private:
         CTRL ctrl;
         bool start;
    public:
            BlockGame(QWidget *parent=0);
            void InitGame();   //初始化游戏界面
            void NewGame();     // 新游戏，产生新方块
            void DispatchMessage(); //翻译按键消息
            void Draw_CurBlock(); //绘制当前方块
            void Draw_NextBlock();  //绘制下一个方块
            void NewBlock();     //产生新的方块
            void RenewGameArea(); //更新游戏区，显示已落下的方块
            void EraseBlock();   //擦除要消掉的方块
            bool IsTop();
            int getscore();


            int sid;
            int time_num;
            QTimer * movedirect;
            QTimer * e_istop;
            QPushButton* btnstart;
            QPushButton* btnpause;
            QPushButton* btnquit;
            QLCDNumber *lcdnum;
            QPalette lcdp;
            bool firstlineblank;

            bool b_pause;
            bool b_istop;
            int eraselinenum;
            int sumblock;
            int sumscore;
            int tmpblockscore;
    public slots:
            void directchange();
            void s_start();
            void s_pause();
            void checkistop();
    protected:
            void paintEvent(QPaintEvent *paintevent);
            void timerEvent(QTimerEvent *timerevent);
            void keyPressEvent(QKeyEvent *keyevent);

};
#endif // BLOCKGAME_H
