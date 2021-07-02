#include "bslider.h"

BSlider::BSlider(QWidget* parent) : QSlider(parent) {}

BSlider::BSlider(Qt::Orientation orientation, QWidget* parent)
    : QSlider(orientation, parent) {}

void BSlider::sliderChange(QAbstractSlider::SliderChange change)
{
    QSlider::sliderChange(change);

    if (change == QAbstractSlider::SliderValueChange )
    {
        QStyleOptionSlider opt;
        initStyleOption(&opt);

        QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
        QPoint bottomRightCorner = sr.bottomLeft();

        QToolTip::showText(mapToGlobal( QPoint( bottomRightCorner.x(), bottomRightCorner.y() ) ), QString::number(value()), this);
    }
}
