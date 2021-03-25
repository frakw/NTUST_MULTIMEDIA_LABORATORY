#include <iostream>
#include <algorithm>
#include <vector>
#include <opencv2/opencv.hpp>
#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME "box median filter"
#define avoid_overflow(x) ((x) > 255 ? 255:((x) < 0 ? 0: (x)))
using namespace cv;
using namespace std;
enum color { BLUE, GREEN, RED };
void filter_template(Mat& img,void* void_filter_in,int filter_height,int filter_width) {
    double* filter_in = (double*)void_filter_in;
    double** filter = new double* [filter_height] {};
    for (int i = 0;i < filter_height;i++) {
        filter[i] = filter_in + (i * filter_width);
    }

    unsigned char* new_data = new unsigned char[img.cols * img.rows * 3]{};

    auto index_of_pixel = [&img](int x, int y, int color) ->int {
        return (y * img.cols + x) * 3 + color;
    };

    for (int i = 0;i < img.rows;i++) {
        for (int j = 0;j < img.cols;j++) {
            double resultR = 0.0f;
            double resultG = 0.0f;
            double resultB = 0.0f;
            double resultA = 0.0f;
            for (int k = 0;k < filter_height;k++) {
                for (int g = 0;g < filter_width;g++) {
                    int x = j + g;
                    int y = i + k;
                    if (filter_height % 2) y -= (int)(filter_height / 2);
                    else y -= (int)(filter_height / 2) - 1;
                    if (filter_width % 2) x -= (int)(filter_width / 2);
                    else x -= (int)(filter_width / 2) - 1;

                    if (y < 0) y *= -1;
                    else if (y >= img.rows) y = 2 * (img.rows - 1) - y;
                    if (x < 0) x *= -1;
                    else if (x >= img.cols) x = 2 * (img.cols - 1) - x;

                    resultB += img.at<Vec3b>(y, x)[BLUE] * filter[k][g];
                    resultG += img.at<Vec3b>(y, x)[GREEN] * filter[k][g];
                    resultR += img.at<Vec3b>(y, x)[RED] * filter[k][g];
                }
            }
            new_data[index_of_pixel(j, i, BLUE)] = avoid_overflow(resultB);
            new_data[index_of_pixel(j, i, GREEN)] = avoid_overflow(resultG);
            new_data[index_of_pixel(j, i, RED)] = avoid_overflow(resultR);          
        }
    }
    delete[] filter;
    memcpy(img.data,new_data,sizeof(unsigned char) * img.cols * img.rows * 3);
    delete[] new_data;
}
void median_Blur(const Mat& src, Mat& dst, int filter_height, int filter_width) {
	vector<unsigned char> allB(filter_height * filter_width);
	vector<unsigned char> allG(filter_height * filter_width);
	vector<unsigned char> allR(filter_height * filter_width);
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			int index = 0;
			for (int k = 0; k < filter_height; k++) {
				for (int g = 0; g < filter_width; g++) {
					int x = j + g;
					int y = i + k;
					if (filter_height % 2) y -= (int)(filter_height / 2);
					else y -= (int)(filter_height / 2) - 1;
					if (filter_width % 2) x -= (int)(filter_width / 2);
					else x -= (int)(filter_width / 2) - 1;

					if (y < 0) y *= -1;
					else if (y >= src.rows) y = 2 * (src.rows - 1) - y;
					if (x < 0) x *= -1;
					else if (x >= src.cols) x = 2 * (src.cols - 1) - x;

					allB[index] = src.at<Vec3b>(y, x)[BLUE];
					allG[index] = src.at<Vec3b>(y, x)[GREEN];
					allR[index++] = src.at<Vec3b>(y, x)[RED];
				}
			}
			sort(allB.begin(), allB.end());
			sort(allG.begin(), allG.end());
			sort(allR.begin(), allR.end());
			dst.at<Vec3b>(i, j)[BLUE] = allB[allB.size() / 2];
			dst.at<Vec3b>(i, j)[GREEN] = allG[allG.size() / 2];
			dst.at<Vec3b>(i, j)[RED] = allR[allR.size() / 2];
		}
	}
}

int main() {
    cvui::init(WINDOW_NAME);
    cv::Mat frame = cv::Mat(cv::Size(550, 580), CV_8UC3);

    Mat origin = imread("Lenna.jpg");
    Mat noise = imread("Lenna_noise.jpg");
	Mat img;
    origin.copyTo(img);
    while (cv::getWindowProperty(WINDOW_NAME, 0) >= 0) {
        frame = cv::Scalar(49, 52, 49);

        if (cvui::button(frame, 10, 10, 125, 30, "normal")) {
            origin.copyTo(img);
        }
        if (cvui::button(frame, 140, 10, 125, 30, "box filter")) {
            double filter[3][3] = { 1.0f / 9.0f,1.0f / 9.0f,1.0f / 9.0f,
                                    1.0f / 9.0f,1.0f / 9.0f,1.0f / 9.0f,
                                    1.0f / 9.0f,1.0f / 9.0f,1.0f / 9.0f, };
            filter_template(img, filter, 3, 3);
        }
        if (cvui::button(frame, 270, 10, 125, 30, "noise")) {
            noise.copyTo(img);
        }

        if (cvui::button(frame, 400, 10, 125, 30, "median filter")) {
			Mat newMat = Mat::zeros(img.rows, img.cols, CV_8UC3);
			median_Blur(img, newMat, 5,5);
			img = newMat;
        }
        cvui::image(frame, 10, 50, img);
        // Update cvui internal stuff
        cvui::update();

        // Show window content
        cv::imshow(WINDOW_NAME, frame);


        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}