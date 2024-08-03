#pragma once
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

#include "Canvas.h"
#include "Pixel.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT;

 public:
	MainWindow();
  void resize(int w, int h);


 private:
	Canvas *m_canvas;
  QVBoxLayout *layout;
  QWidget *centralWidget;

 signals:
	void dataReady(std::vector<Pixel> pixels);

 public slots:
	void sendData(std::vector<Pixel> pixels);
};
