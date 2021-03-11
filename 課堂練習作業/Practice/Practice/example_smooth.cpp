//#include<opencv2/opencv.hpp>
//#include<iostream>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	Mat src = imread("lenna.jpg");
//	//Mat src = imread("lenna_noise.jpg");
//	Mat img_blur, img_gaussian_blur, img_median_blur;
//	blur(src, img_blur, Size(9, 9));
//	GaussianBlur(src, img_gaussian_blur, Size(9, 9), 0, 0);
//	medianBlur(src, img_median_blur, 9);
//	
//	imshow("origin", src);
//	imshow("img_blur", img_blur);
//	imshow("img_gaussian_blur", img_gaussian_blur);
//	imshow("img_median_blur", img_median_blur);
//
//	waitKey();
//}