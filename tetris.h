#ifndef BLOCK_H
#define BLOCK_H
#include<QtGui/QtGui>
#define SIZE    30 //ÿ������ĵ�λ�����20����
#define HEIGHT  20
#define WIDTH   10  //������Ϸ���ĸ߶ȺͿ��
#define X_MIN   0    //��Сx����
#define X_MAX   10   //���x����
class BlockGame;
class Block
{
       private:
                int id;  //���������
                int x,y; //���������
                int dir; //����ķ���
        public:
                void OnRotate();  //��ת����
                void OnLeft();    //��������
                void OnDown();    //��������
                void OnSink();    //�������
                void OnRight();   //��������
                bool ChectBlock();  //��鷽���Ƿ�����ƶ�
                void PutBlock();   //���÷���
         friend class BlockGame;
};
#endif
