#include <iostream>
#include <algorithm>
#include <opencv2/opencv.hpp>
#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME "box median filter"
#define avoid_overflow(x) ((x) > 255 ? 255:((x) < 0 ? 0: (x)))
using namespace cv;
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

void median_filter(Mat& img, int filter_height, int filter_width) {
    std::vector<unsigned char> all_valB(filter_height * filter_width);
    std::vector<unsigned char> all_valG(filter_height * filter_width);
    std::vector<unsigned char> all_valR(filter_height * filter_width);

    unsigned char* new_data = new unsigned char[img.cols * img.rows * 3]{};
    auto index_of_pixel = [&img](int x, int y, int color) ->int {
        return (y * img.cols + x) * 3 + color;
    };

    for (int i = 0;i < img.rows;i++) {
        for (int j = 0;j < img.cols;j++) {
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

                    all_valB[k * filter_width + g] = img.at<Vec3b>(y, x)[BLUE];
                    all_valG[k * filter_width + g] = img.at<Vec3b>(y, x)[GREEN];
                    all_valR[k * filter_width + g] = img.at<Vec3b>(y, x)[RED];
                }
            }
            std::sort(all_valB.begin(), all_valB.end());
            std::sort(all_valG.begin(), all_valG.end());
            std::sort(all_valR.begin(), all_valR.end());
            int size = filter_height * filter_width;
            if (size % 2 == 0){
                new_data[index_of_pixel(j, i, BLUE)] = all_valB[size / 2 - 1] + all_valB[size / 2] / 2;
                new_data[index_of_pixel(j, i, GREEN)] = all_valG[size / 2 - 1] + all_valG[size / 2] / 2;
                new_data[index_of_pixel(j, i, RED)] = all_valR[size / 2 - 1] + all_valR[size / 2] / 2;
            }
            else
            {
                new_data[index_of_pixel(j, i, BLUE)] = all_valB[size / 2];
                new_data[index_of_pixel(j, i, GREEN)] = all_valG[size / 2];
                new_data[index_of_pixel(j, i, RED)] = all_valR[size / 2];
            }
        }
    }
    memcpy(img.data, new_data, sizeof(unsigned char) * img.cols * img.rows * 3);
    delete[] new_data;
}

int main() {
    cvui::init(WINDOW_NAME);
    cv::Mat frame = cv::Mat(cv::Size(340, 380), CV_8UC3);

    Mat origin = imread("Lenna.jpg");
    Mat noise = imread("Lenna_noise.jpg");
    Mat img;
    origin.copyTo(img);
    while (cv::getWindowProperty(WINDOW_NAME, 0) >= 0) {
        frame = cv::Scalar(49, 52, 49);

        if (cvui::button(frame, 10, 10, 70, 30, "normal")) {
            origin.copyTo(img);
        }
        if (cvui::button(frame, 90, 10, 70, 30, "box filter")) {
            double filter[3][3] = { 1.0f / 9.0f,1.0f / 9.0f,1.0f / 9.0f,
                                    1.0f / 9.0f,1.0f / 9.0f,1.0f / 9.0f,
                                    1.0f / 9.0f,1.0f / 9.0f,1.0f / 9.0f, };
            filter_template(img, filter, 3, 3);
        }
        if (cvui::button(frame, 170, 10, 70, 30, "noise")) {
            noise.copyTo(img);
        }

        if (cvui::button(frame, 250, 10, 90, 30, "median filter")) {
            median_filter(img, 3, 3);
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