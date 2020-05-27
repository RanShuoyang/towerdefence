#include "enemy.h"
#include "track.h"
#include "tower1.h"
#include "mainwindow.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

const QSize enemy::ms_fixedSize(160,160);
enemy::enemy(track *startpoint, MainWindow *game, const QPixmap &sprite/* = QPixmap(":/monster1.png")*/):
    QObject(nullptr)
   ,m_pos(startpoint->pos())
   ,m_sprite(sprite)
    {
    m_active=false;
    m_maxHp=40;
    m_currentHp=40;
    m_speed=1.0;
    m_destinationWayPoint=startpoint->next();
    m_game=game;
}

enemy::~enemy()
{
    //m_attackedTowersList.clear();
    m_destinationWayPoint = nullptr;
    m_game = nullptr;
}
void enemy::doActivate()
{
    m_active = true;
}
void enemy::move()
{
    if (!m_active)
        return;

    if (m_pos== m_destinationWayPoint->pos())
    {
        // 敌人抵达了一个航点
        if (m_destinationWayPoint->next())
        {
            // 还有下一个航点
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->next();
        }
        else
        {
            // 表示进入基地
            m_game->getHpDamage();
            m_game->removedEnemy(this);
            return;
        }
    }

    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = m_destinationWayPoint->pos();
    // 向量标准化
    qreal movementSpeed = m_speed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;


}
void enemy::draw(QPainter &painter)
{
    if (!m_active)
        return;
    static const int Health_Bar_Width = 20;
    painter.save();

    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 - 5, -ms_fixedSize.height() / 3);
    // 绘制血条
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);


    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
    painter.drawRect(healthBarBackRect);

    painter.setBrush(Qt::green);

    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 2));
    painter.drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter.translate(m_pos);
    // 绘制敌人
    painter.drawPixmap(offsetPoint, m_sprite);

    painter.restore();
}

void enemy::getRemoved()
{
    if (m_attackedTowersList.empty())
        return;

    foreach (tower1 *attacker, m_attackedTowersList)
        attacker->killenemy();
    // 此敌人已经阵亡
    m_game->removedEnemy(this);
}

void enemy::getDamage(int damage)
{
    //m_game->audioPlayer()->playSound(LaserShootSound);
    m_currentHp -= damage;

    // 阵亡,需要移除
    if (m_currentHp <= 0)
    {
        //m_game->audioPlayer()->playSound(EnemyDestorySound);
        //m_game->awardGold(200);
        getRemoved();
    }
}







