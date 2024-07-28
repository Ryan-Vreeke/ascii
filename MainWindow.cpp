#include "MainWindow.h"
#include "Pixel.h"

MainWindow::MainWindow()
{
  m_canvas = new Canvas(this);

	setWindowTitle("Ascii V1");
  setCentralWidget(m_canvas);

  QObject::connect(this, &MainWindow::dataReady, m_canvas, &Canvas::handleData);

	// QWidget *centralWidget = new QWidget(this);
	// setCentralWidget(centralWidget);

	// QPushButton *button = new QPushButton("Click", centralWidget);
	// button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));

	// connect(button, &QPushButton::clicked, this, &QMainWindow::close);
}

void MainWindow::sendData(std::vector<Pixel> pixels){
  emit dataReady(pixels);
}
