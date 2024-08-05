#include "MainWindow.h"
#include "Pixel.h"

MainWindow::MainWindow(int width, int height)
{
  m_canvas = new Canvas(this);

	setWindowTitle("Ascii V1");
  this->resize(width, height);
  m_canvas->resize(width, height);

  setCentralWidget(m_canvas);

  QObject::connect(this, &MainWindow::dataReady, m_canvas, &Canvas::handleData);
}

void MainWindow::sendData(std::vector<Pixel> pixels){
  emit dataReady(pixels);
}
