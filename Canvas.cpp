#include "Canvas.h"


Canvas::Canvas(QWidget *parent) : QWidget(parent) { 
}

void Canvas::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	painter.setBrush(Qt::black);
  QFont font{"Ariel", 6};
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
