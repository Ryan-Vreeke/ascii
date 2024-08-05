#include <QApplication>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <string>

#include "MainWindow.h"
#include "Pixel.h"

using namespace std;

const string& lightLevels = " .:-=+*#%@";
const string& lightLarge =
		"$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
const float res = 4.0f;
void drawAscii(cv::Mat image);

cv::Mat imageStuff()
{
	const string& imagePath = "../Lenna_(test_image).png";

	const double scaleFactor = 1.0f / res;
	cv::Mat image = cv::imread(imagePath);
	cv::Mat small;
	cv::resize(image, small,
						 cv::Size(image.cols * scaleFactor, image.rows * scaleFactor),
						 cv::INTER_AREA);

	return small;
}

std::unique_ptr<MainWindow> window;

int main(int argc, char* argv[])
{
	cv::Mat image = imageStuff();
	QApplication app(argc, argv);

	window = make_unique<MainWindow>(1000, 1000);
	window->show();


	drawAscii(image);
	return app.exec();
}

void drawAscii(cv::Mat image)
{
	cv::Mat gray;
	cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

	std::vector<Pixel> pixels;
	int h = (1000 / image.size().height);
	int w = (1000 / image.size().width);

	for (int i = 0; i < image.size().height; i++)
	{
		for (int j = 0; j < image.size().width; j++)
		{
			cv::Vec3b pixel = image.at<cv::Vec3b>(j, i);
			int lum = ((gray.at<uchar>(j, i) / 255.0f) * lightLevels.length());

			Pixel p{i * h, j * w, lightLevels[lum]};

			p.b = pixel[0];
			p.g = pixel[1];
			p.r = pixel[2];

			pixels.push_back(p);
		}
	}

	window->sendData(pixels);
}
