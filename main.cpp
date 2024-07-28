#include <QApplication>
#include <cstdlib>
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <cmath>

#include "MainWindow.h"
#include "Pixel.h"

using namespace std;

const string& lightLevels = " .:-=+*#%@";
const int res = 8;
void drawAscii(cv::Mat image);

void imageStuff()
{
	const string& imagePath = "../Lenna_(test_image).png";

	const double scaleFactor = 1.0f / (float)res;
	cv::Mat image = cv::imread(imagePath);
	cv::Mat small;

	cv::resize(image, small,
						 cv::Size(image.cols * scaleFactor, image.rows * scaleFactor),
						 cv::INTER_AREA);


	drawAscii(small);
	// cv::imshow("Loaded Image", image);
	// cv::imshow("Downscaled Image", large);
	// cv::waitKey(0);
	// cv::destroyAllWindows();
}

std::unique_ptr<MainWindow> window;

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	window = make_unique<MainWindow>();

	window->resize(1000, 1000);
	window->show();

	imageStuff();

	return app.exec();
}

void drawAscii(cv::Mat image)
{
  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

	std::vector<Pixel> pixels;
	for (int i = 0; i < image.size().height; i++)
	{
		for (int j = 0; j < image.size().width; j++)
		{
      cv::Vec3b pixel = image.at<cv::Vec3b>(j, i);
			int lum = ((gray.at<uchar>(j, i) / 255.0f) * lightLevels.length());

			Pixel p{i * res, j * res, lightLevels[lum]}; 

      p.b = pixel[0];
      p.g = pixel[1];
      p.r = pixel[2];

			pixels.push_back(p);
		}
	}

	window->sendData(pixels);
}
