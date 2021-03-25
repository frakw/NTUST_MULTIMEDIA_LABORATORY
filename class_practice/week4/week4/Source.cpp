#include <opencv2/opencv.hpp>
#include <string>
#include <cmath>
#include <iostream>
#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME "qrcode recovery Bilinear Interpolation resize"
using namespace cv;
using namespace std;
int main() {
    cvui::init(WINDOW_NAME);
    cv::Mat frame = cv::Mat(cv::Size(400, 450), CV_8UC3);

    Mat origin = imread("pikachu_qrcode.png");
    Mat img;
    origin.copyTo(img);
    double resize_value = 1.00001f;
    while (cv::getWindowProperty(WINDOW_NAME, 0) >= 0) {
        frame = cv::Scalar(49, 52, 49);

        if (cvui::button(frame, 10, 10, 180, 30, "pikachu_qrcode")) {
            origin.copyTo(img);
        }
        if (cvui::button(frame, 200, 10, 180, 30, "recovery")) {
            for (int i = 0; i < img.rows; i++) {
                for (int j = 0; j < img.cols; j++) {
                    img.at<Vec3b>(i, j)[0] = 255 * ((img.at<Vec3b>(i, j)[0] & 0b00000001));
                    img.at<Vec3b>(i, j)[1] = 255 * ((img.at<Vec3b>(i, j)[1] & 0b00000001));
                    img.at<Vec3b>(i, j)[2] = 255 * ((img.at<Vec3b>(i, j)[2] & 0b00000001));
                }
            }
        }
        cvui::trackbar(frame, 10, 50, 180, &resize_value, (double)0.1f, (double)5.0f);
        if (cvui::button(frame, 200, 50, 180, 30, "generate")) {
            Mat result = Mat::zeros(img.rows * resize_value, img.cols * resize_value, CV_8UC3);

            for (int i = 0; i < result.rows; i++) {
                for (int j = 0; j < result.cols; j++) {
                    double ypos = (double)i / resize_value;
                    double xpos = (double)j / resize_value;

                    double d1 = xpos - floor(xpos);
                    double d2 = ceil(xpos) - xpos;

                    double d3 = ypos - floor(ypos);
                    double d4 = ceil(ypos) - ypos;

                    for (int k = 0;k < 3;k++) {
                        result.at<Vec3b>(i, j)[k] =
                            img.at<Vec3b>(floor(ypos), floor(xpos))[k] * d2 * d4 +
                            img.at<Vec3b>(floor(ypos), ceil(xpos))[k] * d1 * d4 +
                            img.at<Vec3b>(ceil(ypos), floor(xpos))[k] * d2 * d3 +
                            img.at<Vec3b>(ceil(ypos), ceil(xpos))[k] * d1 * d3;
                    }
                }
            }
            imshow((std::to_string(resize_value) + "x").c_str(), result);

        }
        cvui::image(frame, 10, 100, img);
        // Update cvui internal stuff
        cvui::update();

        // Show window content
        cv::imshow(WINDOW_NAME, frame);


        if (cv::waitKey(20) == 27) {
            destroyAllWindows();
            break;
        }
    }

    return 0;
}
