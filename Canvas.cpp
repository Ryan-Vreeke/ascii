#include "Canvas.h"


Canvas::Canvas(QWidget *parent) : QWidget(parent) { 
  setFixedSize(800, 800); 
}

void Canvas::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	painter.setBrush(Qt::black);
  QFont font{"Ariel", 8};
  painter.setFont(font);

  for(const auto& p : data){
    painter.setPen(QColor(p.r, p.g, p.b));
    painter.drawText(QPoint(p.x, p.y), QString(p.c));
  }
}

void Canvas::handleData(std::vector<Pixel> pixels)
{
  data = pixels;
  update();
}