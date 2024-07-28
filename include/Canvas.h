#pragma once

#include <QWidget>
#include <QPainter>
#include "Pixel.h"

class Canvas : public QWidget{
  Q_OBJECT

public:
  explicit Canvas(QWidget *parent = nullptr);

private:
  std::vector<Pixel> data;

protected:
  void paintEvent(QPaintEvent *event) override;

public slots:
  void handleData(std::vector<Pixel> pixels);
};

