#ifndef TOWER1_H
#define TOWER1_H
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class enemy;
class MainWindow;
class QTimer;
class QPainter;

class tower1:public QObject{
    Q_OBJECT
public:
    tower1(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/3.png"));
    ~tower1();

    const  QPoint center() const;//将防御塔的坐标转换为图片中心
    void draw(QPainter *painter) const;
    void levelup();//防御塔的升级
    void check();//检查敌人是否在防御塔攻击范围内
    void losetarget();//丢失敌人目标
    void choose_enemy(enemy *enemy);//选择敌人
    void attack();//攻击
    void killenemy();
    void removebullet();
    void damage_enemy();

private slots:
    void weapon();

private:
    const QPoint t_pos;//防御塔的坐标
    int t_attackrange;//防御塔的攻击范围
    int t_attack;//防御塔的攻击伤害
    int t_attackrate;//防御塔的攻击频率
    QPixmap t_spirte;
    bool m_attack;//防御塔的攻击状态
    enemy * m_targetenemy;//防御塔的攻击对象
    QTimer * m_attacktimer;//防御塔攻击的计时器
    static const QSize ms_fixedsize;
    MainWindow * m_game;
};


#endif // TOWER1_H
