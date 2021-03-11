//#include<opencv2/opencv.hpp>
//#include<iostream>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	Mat img = imread("lenna.jpg", IMREAD_GRAYSCALE);
//	//Mat img = imread("threshold.jpg", IMREAD_GRAYSCALE);
//	Mat img2, img3, img4, img5;
//
//	threshold(img, img2, 127, 255, THRESH_BINARY);
//	threshold(img, img3, 0, 255, THRESH_BINARY | THRESH_OTSU);
//
//	adaptiveThreshold(img, img4, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 31, 4);
//	adaptiveThreshold(img, img5, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 31, 4);
//	
//	imshow("­ì¹Ï", img);
//	imshow("threshold127", img2);
//	imshow("OTSU", img3);
//	imshow("adaptiveThreshold1", img4);
//	imshow("adaptiveThreshold2", img5);
//	waitKey();
//}