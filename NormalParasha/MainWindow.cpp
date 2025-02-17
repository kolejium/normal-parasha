#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	setFixedSize(800, 800);

	QWidget* window = new QWidget(this);

	ip_range_input_widget = new IpRangeInputWidget();

	canvas = new Canvas();
	canvas->setGeometry(50, 50, 500, 500);

	buttonCircle = new QPushButton(QString("Circle"));
	buttonRect = new QPushButton(QString("Rect"));
	buttonTriangle = new QPushButton(QString("Triangle"));

	connect(buttonCircle, &QPushButton::clicked, this, &MainWindow::setCircle);
	connect(buttonRect, &QPushButton::clicked, this, &MainWindow::setRect);
	connect(buttonTriangle, &QPushButton::clicked, this, &MainWindow::setTriangle);

	table = new QTableWidget();
	table->setColumnCount(2);
	table->setHorizontalHeaderLabels({ "type", "position" });

	QHBoxLayout* buttonPanel = new QHBoxLayout();
	buttonPanel->addWidget(buttonCircle);
	buttonPanel->addWidget(buttonRect);
	buttonPanel->addWidget(buttonTriangle);

	QWidget* buttonWidget = new QWidget();
	buttonWidget->setLayout(buttonPanel);
	buttonWidget->setFixedHeight(60);

	QSplitter* splitter = new QSplitter(Qt::Vertical);
	splitter->addWidget(ip_range_input_widget);
	splitter->addWidget(canvas);
	splitter->addWidget(buttonWidget);
	splitter->addWidget(table);

	splitter->setStretchFactor(0, 0);
	splitter->setStretchFactor(1, 3);
	splitter->setStretchFactor(2, 0);
	splitter->setStretchFactor(3, 2);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(splitter);

	window->setLayout(layout);
	setCentralWidget(window);

	connect(canvas, &Canvas::shapeAdded, this, &MainWindow::addShapeToTable);
}

void MainWindow::setCircle() { canvas->setShapeType(ShapeType::Circle); }
void MainWindow::setRect() { canvas->setShapeType(ShapeType::Rectangle); }
void MainWindow::setTriangle() { canvas->setShapeType(ShapeType::Triangle); }


void MainWindow::addShapeToTable(const QString& type, QPoint pos) {
	int row = table->rowCount();

	table->insertRow(row);
	table->setItem(row, 0, new QTableWidgetItem(type));
	table->setItem(row, 1, new QTableWidgetItem(QString("%1x%2").arg(pos.x()).arg(pos.y())));
}