#include "DraggableGraphicsItem.h"

#include <QPainter>

DraggableGraphicsItem::DraggableGraphicsItem(ShapeType type, QPointF position) : type(type), dragging(false)
{
	setPos(position);
	setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
}

QRectF DraggableGraphicsItem::boundingRect() const
{
	return QRectF(-25, -25, 50, 50);
}

void DraggableGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setPen(Qt::black);
	painter->setBrush(Qt::gray);

	switch (type)
	{
	case ShapeType::Circle:
		painter->drawEllipse(-25, -25, 50, 50);
		break;
	case ShapeType::Rectangle:
		painter->drawRect(-25, -25, 50, 50);
		break;
	case ShapeType::Triangle:
		QPolygonF triangle;
		triangle << QPointF(0, -25) << QPointF(25, 25) << QPointF(-25, 25);
		painter->drawPolygon(triangle);
		break;
	}

	if (isSelected())
	{
		QPen selectionPen(Qt::yellow);

		selectionPen.setWidth(3);

		painter->setPen(selectionPen);
		painter->setBrush(Qt::transparent);
		painter->drawRect(boundingRect());
	}
}

void DraggableGraphicsItem::setType(ShapeType type)
{
	this->type = type;

	update();
}

void DraggableGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	//setSelected(true);

	//dragging = true;
	//QGraphicsItem::mousePressEvent(event);
}
