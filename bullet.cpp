#include "bullet.h"
#include "bullet.h"
#include "enemy.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPropertyAnimation>

const QSize bullet::m_fixedSize(80, 80);

bullet::bullet(QPoint startPos, QPoint targetPoint, int damage, enemy *target,MainWindow *game, const QPixmap &sprite/* = QPixmap(":/bullet.png")*/)
    : m_startPos(startPos)
    , m_targetPos(targetPoint)
    , m_sprite(sprite)
    , m_currentPos(startPos)
    , m_target(target)
    , m_game(game)
    , m_damage(damage)
{}


void bullet::draw(QPainter &painter) const{
    painter.drawPixmap(m_currentPos,m_sprite);
}

QPoint bullet::currentPos() const{
    return m_currentPos;
}

void bullet::setCurrentPos(QPoint pos){
    m_currentPos=pos;
}
//调整子弹的当前位置

void bullet::move(){
    int time=1;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(time);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));
    animation->start();
}
//子弹发生移动

void bullet::hitTarget(){
    if (m_game->m_targetenemylist().indexOf(m_target) != -1)
        m_target->getDamage(m_damage);
    m_game->removebullet(this);
}
//判断子弹打击的怪兽是否仍然存在
