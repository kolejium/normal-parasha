#include "IpRangeInputWidget.h"

#include <QLabel>
#include <QHBoxLayout>


IpRangeInputWidget::IpRangeInputWidget(QWidget* parent) : QWidget(parent)
{
    auto createIpSpinBox = [this]() -> QSpinBox*
        {
            QSpinBox* spin_box = new QSpinBox(this);
            spin_box->setRange(0, 255);
            spin_box->setFixedWidth(80);
            return spin_box;
        };

    startOctet1 = createIpSpinBox();
    startOctet2 = createIpSpinBox();
    startOctet3 = createIpSpinBox();
    startOctet4 = createIpSpinBox();

	endOctet1 = createIpSpinBox();
    endOctet2 = createIpSpinBox();
    endOctet3 = createIpSpinBox();
    endOctet4 = createIpSpinBox();


    QHBoxLayout* layout = new QHBoxLayout(this);

    layout->addWidget(startOctet1);
    layout->addWidget(new QLabel("."));
    layout->addWidget(startOctet2);
    layout->addWidget(new QLabel("."));
    layout->addWidget(startOctet3);
    layout->addWidget(new QLabel("."));
    layout->addWidget(startOctet4);

    layout->addWidget(new QLabel(" ---- "));

    layout->addWidget(endOctet1);
    layout->addWidget(new QLabel("."));
    layout->addWidget(endOctet2);
    layout->addWidget(new QLabel("."));
    layout->addWidget(endOctet3);
    layout->addWidget(new QLabel("."));
    layout->addWidget(endOctet4);

    setLayout(layout);
}

QString IpRangeInputWidget::getStartRange() const
{
    return QString("%1.%2.%3.%4")
        .arg(startOctet1->value())
        .arg(startOctet2->value())
        .arg(startOctet3->value())
        .arg(startOctet4->value());
}

QString IpRangeInputWidget::getEndRange() const
{
    return QString("%1.%2.%3.%4")
        .arg(endOctet1->value())
        .arg(endOctet2->value())
        .arg(endOctet3->value())
        .arg(endOctet4->value());
}