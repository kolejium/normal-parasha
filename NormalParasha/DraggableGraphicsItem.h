#pragma once
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "Canvas.h"

class DraggableGraphicsItem : public QGraphicsItem
{
public:
	DraggableGraphicsItem(ShapeType type, QPointF position);

	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	void setType(ShapeType type);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
	ShapeType type;
	QPointF offset;
	bool dragging;
};
