//#include <opencv2/opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//
//int main()
//{
//	Mat img = imread("image.jpg", 0);
//	double scale = 0.2;
//	// 圖片太大先縮小
//	resize(img, img, Size(0, 0), scale, scale);
//
//	// do something
//
//
//
//	Mat labels;
//	int number_labels = connectedComponents(img, labels);
//	cout << "共有: " << number_labels - 1;
//
//	imshow("origin_img", img);
//	waitKey(0);
//}