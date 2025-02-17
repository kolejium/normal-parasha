#include "Canvas.h"

#include <typeinfo>
#include "DraggableGraphicsItem.h"

Canvas::Canvas(QWidget* parent) : QGraphicsView(parent)
{
	setScene(new QGraphicsScene(this));
	setSceneRect(-5000, -5000, 10000, 10000);
	setDragMode(RubberBandDrag);
	setInteractive(true);
}

void Canvas::setShapeType(ShapeType type)
{
	if (currentShape == type)
		currentShape = ShapeType::None;
	else
		currentShape = type;
}

void Canvas::mousePressEvent(QMouseEvent* event)
{
	QPointF scenePos = mapToScene(event->pos());

	if (currentShape == ShapeType::None)
	{
		QGraphicsItem* clickedItem = itemAt(event->pos());

		bool shiftPressed = event->modifiers() & Qt::ShiftModifier;
		bool ctrlPressed = event->modifiers() & Qt::ControlModifier;

		if (!clickedItem)
		{
			if (!shiftPressed && !ctrlPressed)
				clearSelection();
		}
		else
		{
			if (clickedItem->isSelected())
			{
				offsets.clear();

				for (auto selected_item : scene()->selectedItems())
				{
					offsets[selected_item] = selected_item->pos() - scenePos;
				}
			} else
			{
				if (shiftPressed || ctrlPressed)
					clickedItem->setSelected(true);
				else
				{
					clearSelection();
					clickedItem->setSelected(true);
				}
			}
		}

		QGraphicsView::mousePressEvent(event);
	}
	else
	{
		auto item = new DraggableGraphicsItem(currentShape, scenePos);

		if (item)
		{
			scene()->addItem(item);

			emit shapeAdded(typeid(item).name(), scenePos.toPoint());
		}
	}
}

void Canvas::mouseMoveEvent(QMouseEvent* event)
{
	if (!offsets.isEmpty())
	{
		QPointF newScenePos = mapToScene(event->pos());

		for (auto it = offsets.begin(); it != offsets.end(); ++it)
		{
			it.key()->setPos(newScenePos + it.value());
		}
	}

	QGraphicsView::mouseMoveEvent(event);
}

void Canvas::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Delete)
	{
		for (QGraphicsItem* item : scene()->selectedItems())
		{
			scene()->removeItem(item);
			delete item;
		}
	}
	QGraphicsView::keyPressEvent(event);
}

void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
	offsets.clear();
	QGraphicsView::mouseReleaseEvent(event);
}


void Canvas::wheelEvent(QWheelEvent* event)
{
	constexpr qreal factor = 1.2;

	QPointF scenePos = mapToScene(event->position().toPoint());

	if (event->angleDelta().y() > 0)
	{
		scale(factor, factor);
	}
	else
	{
		scale(1.0 / factor, 1.0 / factor);
	}

	setSceneRect(scene()->sceneRect().translated(scenePos - mapToScene(event->position().toPoint())));
}

void Canvas::clearSelection() const
{
	foreach(QGraphicsItem * item, scene()->items())
	{
		item->setSelected(false);
	}
}
