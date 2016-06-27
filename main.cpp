#include<QApplication>
#include"tetris.h"
#include"tetrisgame.h"
int main(int argc,char ** argv)
{
    QApplication app(argc,argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    BlockGame mygame;
    mygame.show ();
    return app.exec ();
}
