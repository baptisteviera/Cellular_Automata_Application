#include "cell_widget.h"
#include <iostream>

CellWidget::CellWidget(QWidget* parent, int cellSize, Cell* cell)
    : QWidget(parent), cell(cell) {

    setFixedSize(cellSize, cellSize);
    setAutoFillBackground(true);

    this->updateDisplay();
    repaint();
}

void CellWidget::updateDisplay() {
    if (this->toolTip() != cell->getState()->getLabel().c_str()) {
        this->setToolTip(cell->getState()->getLabel().c_str());
    }
    if (this->palette().color(QPalette::Window) != cell->getState()->getColor()) {
        this->setColor(cell->getState()->getColor());
    }
}


void CellWidget::setColor(const QColor& color) {
    QPalette pal = palette();
    pal.setColor(QPalette::Window, color);
    setPalette(pal);
}

void CellWidget::paintEvent(QPaintEvent* event) {
    if (cell->getDirection() != NONE) {
        int rotateDegree = 0;
        switch (cell->getDirection()) {
            case UP:
                rotateDegree = 0;
                break;
            case LEFT:
                rotateDegree = -90;
                break;
            case DOWN:
                rotateDegree = 180;
                break;
            case RIGHT:
                rotateDegree = 90;
                break;
            case NONE:
                return;
                break;
        }
        // draw ant
        QPainter painter(this);
        QPainterPath path;
        path.moveTo(this->rect().left() + (this->rect().width() / 2.0), this->rect().top() + this->rect().height() / 6.0);
        path.lineTo(this->rect().left() + (this->rect().width() / 4.0), this->rect().bottom() - this->rect().height() / 6.0);
        path.lineTo(this->rect().right() - (this->rect().width() / 4.0), this->rect().bottom() - this->rect().height() / 6.0);
        path.lineTo(this->rect().left() + (this->rect().width() / 2.0), this->rect().top() + this->rect().height() / 6.0);

        painter.translate(this->rect().center());
        painter.rotate(rotateDegree);
        painter.translate(-this->rect().center());

        painter.fillPath(path, QBrush(Qt::red));
    }
}

void CellWidget::setSize(int size) {
    setFixedSize(size, size);
}

void CellWidget::setCell(Cell* cell) {
    if (this->cell == nullptr || this->cell->getDirection() != cell->getDirection()) {
        this->cell = cell;
        repaint();
    } else {
        this->cell = cell;
    }
}

Cell* CellWidget::getCell() const {
    return this->cell;
}

void CellWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        leftMouseClicked = true;
        rightMouseClicked = false;
    } else if (event->button() == Qt::RightButton) {
        leftMouseClicked = false;
        rightMouseClicked = true;
    }
}

void CellWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && leftMouseClicked) {
        leftMouseClicked = false;
        rightMouseClicked = false;
        emit leftClicked(cell->getX(), cell->getY());
    } else if (event->button() == Qt::RightButton && rightMouseClicked){
        leftMouseClicked = false;
        rightMouseClicked = false;
        emit rightClicked(cell->getX(), cell->getY());
    }
}
