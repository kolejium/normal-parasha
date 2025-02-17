#pragma once

#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>

class IpRangeInputWidget : public QWidget
{
	Q_OBJECT
public:
	IpRangeInputWidget(QWidget* parent = nullptr);
	QString getStartRange() const;
	QString getEndRange() const;

private:
	QSpinBox* startOctet1;
	QSpinBox* startOctet2;
	QSpinBox* startOctet3;
	QSpinBox* startOctet4;

	QSpinBox* endOctet1;
	QSpinBox* endOctet2;
	QSpinBox* endOctet3;
	QSpinBox* endOctet4;
};
