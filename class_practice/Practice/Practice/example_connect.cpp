//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//using namespace std;
//
//int main() {
//	Mat src = imread("image2.jpg", 0);
//	Mat src_binary_inv;
//
//	threshold(src, src_binary_inv, 0, 255, THRESH_BINARY_INV | THRESH_OTSU); // ¤G­È¤Æ
//
//	Mat labels;
//	int number_labels = connectedComponents(src_binary_inv, labels);
//	cout << "number_labels: " << number_labels << endl;
//
//	imshow("origin", src);
//	imshow("src_binary_inv", src_binary_inv);
//
//	waitKey(0);
//	return 0;
//}