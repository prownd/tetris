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
            void InitGame();   //��ʼ����Ϸ����
            void NewGame();     // ����Ϸ�������·���
            void DispatchMessage(); //���밴����Ϣ
            void Draw_CurBlock(); //���Ƶ�ǰ����
            void Draw_NextBlock();  //������һ������
            void NewBlock();     //�����µķ���
            void RenewGameArea(); //������Ϸ������ʾ�����µķ���
            void EraseBlock();   //����Ҫ�����ķ���
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
