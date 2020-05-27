#ifndef ENEMY_H
#define ENEMY_H
#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class QPainter;
class MainWindow;
class track;
class tower1;

class enemy :public QObject
{
    Q_OBJECT
public:
    enemy(track *startpoint, MainWindow *game, const QPixmap &sprite = QPixmap(":/monster1.png"));
    ~enemy();

    void draw(QPainter &painter);
    void move();
    void getDamage(int damage);
    void getRemoved();
    void getAttacked(tower1 *attacker);
    void gotLostSight(tower1 *attacker);
    QPoint pos() const;
public slots:
    void doActivate();

private:
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    qreal			m_speed;
    QPoint			m_pos;
    track *		    m_destinationWayPoint;
    MainWindow *	m_game;
    QList<tower1 *>	m_attackedTowersList;

    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;
};



#endif // ENEMY_H
