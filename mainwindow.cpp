#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <track.h>
#include <enemy.h>
#include <bullet.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_waves(0),
    m_gamewin(false)
{
    ui->setupUi(this);
    loadtowerposition();
    addtrack();
    loadwave();
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMap()));
    timer->start(30);


}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPixmap m_Pix(":/background2.png");
    QPainter m_Painter(&m_Pix);

    foreach (const position &towerPos, m_towerpositionlist)
        towerPos.draw(m_Painter);

    foreach (const tower1 &tower, m_tower1list)
        tower.draw(&m_Painter);

    //foreach (const track *wayPoint, m_tracklist)
       // wayPoint->draw(&m_Painter);
    foreach (bullet *bullet,m_bulletlist)
        bullet->draw(m_Painter);
    foreach (enemy *enemy, m_enemylist)
        enemy->draw(m_Painter);
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_Pix);

}
MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::loadwave(){
    if(m_waves>=6){
        return false;
    }
    track *startpoint=m_tracklist.back();
    int enemystartinterval[]={100,3000,5000,7000,9000,12000};
    for(int i=0;i<6;++i){
        enemy *enemy=new class enemy(startpoint,this);
        m_enemylist.push_back(enemy);
        QTimer::singleShot(enemystartinterval[i],enemy,SLOT(doActivate()));
    }
    return true;
}
//刷新波数
void MainWindow::updateMap(){
    foreach(enemy *enemy,m_enemylist){
        enemy->move();
    }
    update();
}
//更新地图

void MainWindow::loadtowerposition(){
    QPoint positions[]=
    {
        QPoint(180,580),
        QPoint(300,580),
        QPoint(420,340),
        QPoint(680,340),
        QPoint(680,450),
        QPoint(420,450),
        QPoint(970,290),
        QPoint(1150,290)
    };
    int len=sizeof(positions)/sizeof(positions[0]);
    for(int i=0;i<len;++i){
        m_towerpositionlist.push_back(positions[i]);
    }
}//确定可以安放攻击塔的基座位置

void MainWindow::mousePressEvent(QMouseEvent *event){
   if(event->button()==Qt::LeftButton){
    QPoint p_position=event->pos();
    auto it=m_towerpositionlist.begin();
    while (it!=m_towerpositionlist.end()) {
        if(it->containpoint(p_position)&&!it->tower()){
            it->settower();
            tower1 *tower= new tower1(it->center(),this);
            m_tower1list.push_back(*tower);
            update();
            break;
        }
        ++it;
    }
   }
   if(event->button()==Qt::RightButton){
       QPoint p_position=event->pos();
       auto it=m_towerpositionlist.begin();
       while (it!=m_towerpositionlist.end()) {
           if(it->containpoint(p_position)&&it->tower()){
               it->setnotower();
               //m_tower1list.back();
               m_tower1list.pop_back();

               update();
               break;
           }
            ++it;
       }

   }
}
//建立或拆除攻击塔1
void MainWindow::mouseDoubleClickEvent(QMouseEvent *e){
    QPoint p_position=e->pos();
    auto it=m_towerpositionlist.begin();
    while (it!=m_towerpositionlist.end()) {
        if(it->containpoint(p_position)&&it->tower()){
            it->setnotower();
            m_tower1list.pop_back();
            it->settower();
            tower1 *tower= new tower1(it->center(),this);
            tower->levelup();
            m_tower1list.push_back(*tower);
            update();
            break;
        }
         ++it;
    }
}
//升级防御塔
void MainWindow::addtrack(){
    track *pos1=new track(QPoint (1400,480));
    m_tracklist.push_back(pos1);

    track *pos2=new track(QPoint (850,480));
    m_tracklist.push_back(pos2);
    pos2->setnext(pos1);

    track *pos3=new track(QPoint (850,230));
    m_tracklist.push_back(pos3);
    pos3->setnext(pos2);

    track *pos4=new track(QPoint (330,230));
    m_tracklist.push_back(pos4);
    pos4->setnext(pos3);

    track *pos5=new track(QPoint (330,480));
    m_tracklist.push_back(pos5);
    pos5->setnext(pos4);

    track *pos6=new track(QPoint (50,480));
    m_tracklist.push_back(pos6);
    pos6->setnext(pos5);

}
//添加怪物行走路线的关键点

void MainWindow::getHpDamage(int damage/*=1*/){

}


void MainWindow::removedEnemy(enemy *enemy){
    Q_ASSERT(enemy);
    m_enemylist.removeOne(enemy);
    delete  enemy;
    if(m_enemylist.empty()){
        ++m_waves;
        if(!loadwave()){
            m_gamewin=true;
        }
    }
}
//移除敌人
void MainWindow::removebullet(bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletlist.removeOne(bullet);
    delete bullet;
}
//移除子弹
void MainWindow::addbullet(bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletlist.push_back(bullet);
}
//添加子弹
QList<enemy *> MainWindow::m_targetenemylist() const
{
    return m_enemylist;
}
//返回子弹将要攻击的敌人的动态数组
