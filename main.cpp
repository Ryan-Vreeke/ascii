#include <QApplication>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <numbers>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <string>

#include "MainWindow.h"
#include "Pixel.h"

using namespace std;

const string &lightLevels = " .:-=+*#%@";
const int res = 8;
void drawAscii(cv::Mat image, std::shared_ptr<std::vector<Pixel>> pixels);
cv::Mat get_image(cv::Mat frame);

std::unique_ptr<MainWindow> window;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  auto pixels = make_shared<std::vector<Pixel>>();
  window = make_unique<MainWindow>();

  cv::VideoCapture cap("../test.mp4");

  if (!cap.isOpened())
    printf("NOT OPEN");

  cv::Mat frame;
  cap >> frame;

  window->resize(frame.size().width, frame.size().height);
  window->show();

  while (cap.isOpened()) {
    cap >> frame;

    if (frame.empty())
      break;

    cv::Mat image = get_image(frame);
    drawAscii(image, pixels);

    window->sendData(*pixels);
    pixels->clear();
  }

  cap.release();
  return app.exec();
}

void drawAscii(cv::Mat image, std::shared_ptr<std::vector<Pixel>> pixels) {
  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  for (int i = 0; i < image.size().height; i++) {
    for (int j = 0; j < image.size().width; j++) {
      cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
      int lum = ((gray.at<uchar>(i, j) / 255.0f) * lightLevels.length());

      Pixel p{j * res, i * res, lightLevels[lum]};

      p.b = pixel[0];
      p.g = pixel[1];
      p.r = pixel[2];

      pixels->push_back(p);
    }
  }
}

cv::Mat get_image(cv::Mat frame) {

  cv::Mat small;

  cv::resize(frame, small, cv::Size(frame.cols / res, frame.rows / res),
             cv::INTER_AREA);

  return small;
}
