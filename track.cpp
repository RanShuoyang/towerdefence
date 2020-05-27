#include "track.h"
#include "QPoint"
#include "QPainter"

track::track(QPoint pos):m_pos(pos),m_next(nullptr){}

void track::setnext(track *next) {
    m_next=next;
}

track* track::next() const{
    return m_next;
}

const QPoint track::pos() const{
    return m_pos;
}

void track::draw(QPainter *painter) const{
    painter->save();
    painter->setPen(Qt::black);
    painter->drawEllipse(m_pos,5,5);

    painter->drawEllipse(m_pos,10,10);
    if(m_next){
        painter->drawLine(m_pos,m_next->m_pos);
    }
    painter->restore();
}
