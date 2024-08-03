#include "MainWindow.h"
#include "Pixel.h"
#include <qboxlayout.h>

MainWindow::MainWindow() {
  m_canvas = new Canvas(this);

  setWindowTitle("Ascii V1");

  layout = new QVBoxLayout(); 
  layout->addWidget(m_canvas);
  layout->setContentsMargins(0,0,0,0);

  centralWidget = new QWidget;
  centralWidget->setLayout(layout);
  this->setCentralWidget(m_canvas);

  QObject::connect(this, &MainWindow::dataReady, m_canvas, &Canvas::handleData);
}

void MainWindow::sendData(std::vector<Pixel> pixels) { emit dataReady(pixels); }

void MainWindow::resize(int w, int h) {
  QMainWindow::resize(w, h);
  // m_canvas->resize(w, h);
}
