#ifndef TRACK_H
#define TRACK_H
#include <QPoint>
class QPainter;

class track
{
public:
    track(QPoint pos);
    void setnext(track *next);
    track * next() const;
    const QPoint pos() const;
    void draw(QPainter *painter)const;

private:
    QPoint m_pos;
    track *m_next;
};

#endif // TRACK_H
