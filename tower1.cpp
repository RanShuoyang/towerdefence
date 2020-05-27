#include "tower1.h"
#include "enemy.h"
#include "bullet.h"
#include "mainwindow.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize tower1::ms_fixedsize(100,137);
tower1::tower1(QPoint point, MainWindow *game, const QPixmap &sprite/*= QPixmap(":/3.png")*/):
         //QObject (nullptr),
        // t_pos(point),
        // t_spirte(sprite),
         //m_game(game)
            m_attack(false)
          , t_attackrange(70)
          , t_attack(10)
          , t_attackrate(1000)
          , m_targetenemy(nullptr)
          , m_game(game)
          , t_pos(point)
          , t_spirte(sprite)
  {
       //t_attackrange=250;
      // t_attack=10;
      // t_attackrate=1000;
      // m_targetenemy=nullptr;
      // m_attack=false;
       m_attacktimer = new QTimer(this);
       connect(m_attacktimer, SIGNAL(timeout()), this, SLOT(weapon()));
   }

//攻击塔1的构造函数
tower1::~tower1(){
    delete m_attacktimer;
    m_attacktimer= nullptr;
}
//析构函数

void tower1::levelup(){
    t_spirte=QPixmap(":/4.png");
    t_attackrange=300;//攻击范围扩大
    t_attack=20;//攻击力提高
}

//升级防御塔
void tower1::draw(QPainter *painter) const{
    painter->save();
    painter->setPen(Qt::white);
    painter->drawEllipse(t_pos,t_attackrange,t_attackrange);
    static const QPoint offsetpoint(-ms_fixedsize.width()/2,-ms_fixedsize.height()/2);
    painter->translate(t_pos);
    painter->drawPixmap(offsetpoint,t_spirte);
    painter->restore();
}
//绘制防御塔1
void tower1::check(){
    if(m_targetenemy){
        QVector2D normalized(m_targetenemy->pos() - t_pos);
        normalized.normalize();
        //攻击范围内有敌人，可以攻击
        double distance1=sqrt((m_targetenemy->pos().rx()-t_pos.rx())*(m_targetenemy->pos().rx()-t_pos.rx())+(m_targetenemy->pos().ry()-t_pos.ry())*(m_targetenemy->pos().ry()-t_pos.ry()));
        if(distance1>t_attackrange){
            losetarget();
        }
        //如果防御塔和敌人的距离大于攻击距离，则判定敌人不在攻击范围内
    }
    else
    {
        // 判断是否有敌人在攻击范围内
        QList<enemy *> enemylist = m_game->m_targetenemylist();
        foreach (enemy *enemy, enemylist)
        {
            double distance2=sqrt((enemy->pos().rx()-t_pos.rx())*(enemy->pos().rx()-t_pos.rx())+(enemy->pos().ry()-t_pos.ry())*(enemy->pos().ry()-t_pos.ry()));

            if (distance2<=t_attackrange)
            {
                choose_enemy(enemy);
                break;
            }
        }
    }


}

void tower1::attack(){
    m_attacktimer->start(t_attackrate);
}

void tower1::choose_enemy(enemy *enemy){
    m_targetenemy = enemy;
    attack();
    m_targetenemy->getAttacked(this);
}

void tower1::weapon(){
    bullet *bullet = new class bullet(t_pos, m_targetenemy->pos(), t_attack, m_targetenemy, m_game);
    bullet->move();
    m_game->addbullet(bullet);
}

void tower1::killenemy(){
    if (m_targetenemy){
        m_targetenemy = nullptr;
    }
    m_attacktimer->stop();
}
//杀死怪物，停止攻击

void tower1::losetarget(){
    m_targetenemy->gotLostSight(this);
    if (m_targetenemy){
        m_targetenemy = nullptr;
    }
    m_attacktimer->stop();
}
//怪物走出了攻击范围，停止攻击
