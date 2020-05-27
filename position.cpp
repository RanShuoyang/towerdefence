#include "position.h"


const QSize position::ms_fixedsize(75,75);

position::position(QPoint point,const QPixmap &spirte/*=QPixmap(":/base.png")*/ ):
    m_pos(point),
    m_tower(false),
    m_spirte(spirte)
{}
//初始化防御塔位置

const  QPoint position:: center() const
{
    QPoint offsetpoint(ms_fixedsize.width()/2,ms_fixedsize.height()/2);
    return m_pos+offsetpoint;
}
//确定防御塔位置中心点的坐标
bool position::containpoint (const QPoint &pos) const{
    bool X=m_pos.x()<pos.x()&&pos.x()<(m_pos.x()+ms_fixedsize.width());
    bool Y=m_pos.y()<pos.y()&&pos.y()<(m_pos.y()+ms_fixedsize.height());
    return X&&Y;
}
//判断坐标是否在防御塔内部

void position::settower(bool  tower){
    m_tower=tower;
}
void position::setnotower(){
    m_tower=false;
}


void position::draw(QPainter &painter) const{
    painter.drawPixmap(m_pos.x(),m_pos.y(),m_spirte);
}
//绘制防御塔基座
bool position::tower()const
{
    return m_tower;
}

