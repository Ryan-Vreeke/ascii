#pragma once
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>

#include "Canvas.h"
#include "Pixel.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT;

 public:
	MainWindow(int width, int heigth);

 private:
	Canvas *m_canvas;

 signals:
	void dataReady(std::vector<Pixel> pixels);

 public slots:
	void sendData(std::vector<Pixel> pixels);
};
