#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSplitter>

#include "Canvas.h"
#include "IpRangeInputWidget.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);

private slots:
	void setCircle();
	void setRect();
	void setTriangle();
	void addShapeToTable(const QString& type, QPoint pos);

private:
	Canvas* canvas;

	QPushButton* buttonCircle;
	QPushButton* buttonRect;
	QPushButton* buttonTriangle;

	QTableWidget* table;

	IpRangeInputWidget* ip_range_input_widget;
};
