//#include <opencv2/opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	Mat src = imread("image1.jpg", 0);
//	resize(src, src, Size(0, 0), 3, 3);
//	Mat img_erode, img_dilate, img_close, img_open;
//
//	threshold(src, src, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
//
//	Mat mask;
//	mask = cv::getStructuringElement(MORPH_RECT, Size(5, 5));
//	erode(src, img_erode, mask, Point(-1, -1), 3);
//	dilate(src, img_dilate, mask, Point(-1, -1), 3);
//	morphologyEx(src, img_close, MORPH_CLOSE, mask, Point(-1, -1), 3);
//	morphologyEx(src, img_open, MORPH_OPEN, mask, Point(-1, -1), 3);
//	
//	imshow("threshold", src);
//	imshow("erode", img_erode);
//	imshow("dilate", img_dilate);
//	imshow("close", img_close);
//	imshow("open", img_open);
//	waitKey(0);
//	destroyAllWindows();
//}