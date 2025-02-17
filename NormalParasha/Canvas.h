#pragma once

#include <QGraphicsView>
#include <QMouseEvent>



enum class ShapeType { None, Circle, Rectangle, Triangle };

class Canvas : public QGraphicsView {
	Q_OBJECT

public:
	Canvas(QWidget* parent = nullptr);

	void setShapeType(ShapeType type);

	void clearSelection() const;

signals:
	void shapeAdded(const QString& type, QPoint pos);
	void shapeDeleted(const QString& type);

protected:
	void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

private:
	ShapeType currentShape = ShapeType::None;
	QMap<QGraphicsItem*, QPointF> offsets;
};