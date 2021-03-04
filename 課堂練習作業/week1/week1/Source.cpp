#include<opencv2/opencv.hpp>
using namespace cv;
int main()
{
	Mat img = imread("Lenna.jpg");
	imshow("Hello World!", img);
	waitKey();
}
