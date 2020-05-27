#ifndef BULLET_H
#define BULLET_H
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class enemy;
class MainWindow;

class bullet:public QObject
{
    Q_OBJECT
	Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)    
public:
    bullet(QPoint startPos, QPoint targetPoint, int damage, enemy *target,
		   MainWindow *game, const QPixmap &sprite = QPixmap(":/bullet.png"));

	void draw(QPainter &painter) const;
	void move();
	void setCurrentPos(QPoint pos);
	QPoint currentPos() const;

public slots:
	void hitTarget();
private:
    QPoint	m_startPos;
    QPoint	m_targetPos;
    QPixmap	m_sprite;
	QPoint  m_currentPos;
	enemy *m_target;
	MainWindow *m_game;
	int	 m_damage;
	static const QSize m_fixedSize;
};

#endif // BULLET_H
