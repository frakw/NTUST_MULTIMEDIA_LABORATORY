#include <opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("image1.jpg", 0);
	resize(src, src, Size(0, 0), 3, 3);
	Mat dst1, dst2, dst3;

	threshold(src, src, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

	Mat mask;
	mask = cv::getStructuringElement(MORPH_RECT, Size(5, 5));
	erode(src, dst1, mask, Point(-1, -1), 2);

	mask = cv::getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	erode(src, dst2, mask, Point(-1, -1), 2);

	mask = cv::getStructuringElement(MORPH_CROSS, Size(5, 5));
	erode(src, dst3, mask, Point(-1, -1), 2);

	
	imshow("threshold", src);
	imshow("MORPH_RECT", dst1);
	imshow("MORPH_ELLIPSE", dst2);
	imshow("MORPH_CROSS", dst2);

	mask = cv::getStructuringElement(MORPH_RECT, Size(5, 5));
	cout << "MORPH_RECT:" << endl << mask << endl;
	mask = cv::getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	cout << "MORPH_ELLIPSE:" << endl << mask << endl;
	mask = cv::getStructuringElement(MORPH_CROSS, Size(5, 5));
	cout << "MORPH_CROSS:" << endl << mask << endl;

	waitKey(0);
	destroyAllWindows();

	system("pause");
}