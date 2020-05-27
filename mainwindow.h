#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"position.h"
#include"tower1.h"
#include<QList>

namespace Ui {
class MainWindow;
}

class enemy;
class track;
class bullet;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void BaseDamage();
    void getHpDamage(int damage = 1);
    void removedEnemy(enemy *enemy);
    bool loadwave();
    void mouseDoubleClickEvent(QMouseEvent *e);
    void removebullet(bullet *bullet);
    void addbullet(bullet *bullet);
    QList<enemy *> m_targetenemylist() const;
public slots:
    void updateMap();
private:
    Ui::MainWindow *ui;
    QList<position>m_towerpositionlist;
    void loadtowerposition();
    QList<tower1>m_tower1list;
    QList<track*>m_tracklist;
    void addtrack();
    QList<enemy*> m_enemylist;
    int m_waves;
    bool m_gamewin;
    QList<bullet*>m_bulletlist;
};

#endif // MAINWINDOW_H
