#ifndef POSITION_H
#define POSITION_H
#include <QPoint>
#include <QPainter>
#include <QSize>
#include <QPixmap>
class position
{
public:
    position(QPoint point,const QPixmap &spirte=QPixmap(":/base.png") );
    bool tower() const;
    void settower(bool  tower=true);
    const QPoint center() const;
    bool containpoint (const QPoint &pos) const;
    void draw(QPainter &painter) const;
    void setnotower();
private:
    QPoint m_pos;
    bool m_tower;
    QPixmap m_spirte;
    static const QSize ms_fixedsize;
};

#endif // POSITION_H
