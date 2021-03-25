//#include <windows.h>
//#include <string>
//#include <tchar.h>
//#include <opencv2/opencv.hpp>
//#include <cmath>
//#define CVUI_IMPLEMENTATION
//#include "cvui.h"
//#include "portable-file-dialogs.h"
//#if _WIN32
//#define DEFAULT_PATH "./"
//#else
//#define DEFAULT_PATH "/tmp"
//#endif
//
//#define WINDOW_NAME "Histogram"
//using namespace cv;
//
//void drawHistImg(const Mat& src, Mat& dst);
//int main() {
//    std::locale loc = std::locale::global(std::locale(""));
//    cvui::init(WINDOW_NAME);
//    cv::Mat frame = cv::Mat(cv::Size(1050, 750), CV_8UC3);
//    Mat source_img;
//    Mat target_img;
//    Mat source_origin;
//    while (cv::getWindowProperty(WINDOW_NAME, 0) >= 0) {
//        frame = cv::Scalar(49, 52, 49);
//
//        if (cvui::button(frame, 10, 10, 500, 30, "load source")) {
//            std::string filename;
//            auto f = pfd::open_file(u8"路徑中不可有中文", DEFAULT_PATH,
//                { "Image Files (.jpg .png)", "*.jpg *.png *.JPG *.PNG",
//                  "All Files", "*" },
//                pfd::opt::none);
//            for (auto const& name : f.result())
//                filename = name;
//            if (!filename.empty()) {
//                source_origin = imread(filename);
//                double resize_value = 500.0f / source_origin.cols < 620.0f / source_origin.rows  ? 500.0f / source_origin.cols : 620.0f / source_origin.rows;
//                resize(source_origin, source_origin, cv::Size(), resize_value, resize_value);
//                source_origin.copyTo(source_img);
//            }
//        }
//        if (cvui::button(frame, 520, 10, 500, 30, "load target")) {
//            std::string filename;
//            auto f = pfd::open_file(u8"路徑中不可有中文", DEFAULT_PATH,
//                { "Image Files (.jpg .png)", "*.jpg *.png *.JPG *.PNG",
//                  "All Files", "*" },
//                pfd::opt::none);
//            for (auto const& name : f.result())
//                filename = name;
//            if (!filename.empty()) {
//                target_img = imread(filename);
//                double resize_value = 500.0f / target_img.cols < 620.0f / target_img.rows ? 500.0f / target_img.cols : 620.0f / target_img.rows;
//                resize(target_img, target_img, cv::Size(), resize_value, resize_value);
//            }
//        }
//        if (cvui::button(frame, 10, 50, 500, 30, "Histogram equalization") && !source_img.empty()) {
//            double table[256][3] = { 0 };
//            for (int i = 0; i < 256; i++) {
//                table[i][0] = 0.0f;
//                table[i][1] = 0.0f;
//                table[i][2] = 0.0f;
//            }
//            for (int i = 0; i < source_img.rows; i++) {
//                for (int j = 0; j < source_img.cols; j++) {
//                    ++table[source_img.at<Vec3b>(i, j)[0]][0];
//                    ++table[source_img.at<Vec3b>(i, j)[1]][1];
//                    ++table[source_img.at<Vec3b>(i, j)[2]][2];
//                }
//            }
//            double total_pixel = source_img.rows * source_img.cols;
//            table[0][0] /= total_pixel;
//            table[0][1] /= total_pixel;
//            table[0][2] /= total_pixel;
//            for (int i = 1; i < 256; i++) {
//                table[i][0] /= total_pixel;
//                table[i][0] += table[i - 1][0];
//                table[i][1] /= total_pixel;
//                table[i][1] += table[i - 1][1];
//                table[i][2] /= total_pixel;
//                table[i][2] += table[i - 1][2];
//            }
//
//            for (int i = 0; i < source_img.rows; i++) {
//                for (int j = 0; j < source_img.cols; j++) {
//                    source_img.at<Vec3b>(i, j)[0] = std::round(table[source_img.at<Vec3b>(i, j)[0]][0] * 255.0f);
//                    source_img.at<Vec3b>(i, j)[1] = std::round(table[source_img.at<Vec3b>(i, j)[1]][1] * 255.0f);
//                    source_img.at<Vec3b>(i, j)[2] = std::round(table[source_img.at<Vec3b>(i, j)[2]][2] * 255.0f);
//                }
//            }
//        }
//        if (cvui::button(frame, 520, 50, 500, 30, "Histogram match") && !source_img.empty() && !target_img.empty()) {
//            double source_table[256][3] = { 0 };
//            for (int i = 0; i < 256; i++) {
//                source_table[i][0] = 0.0f;
//                source_table[i][1] = 0.0f;
//                source_table[i][2] = 0.0f;
//            }
//            for (int i = 0; i < source_img.rows; i++) {
//                for (int j = 0; j < source_img.cols; j++) {
//                    ++source_table[source_img.at<Vec3b>(i, j)[0]][0];
//                    ++source_table[source_img.at<Vec3b>(i, j)[1]][1];
//                    ++source_table[source_img.at<Vec3b>(i, j)[2]][2];
//                }
//            }
//            double total_pixel = source_img.rows * source_img.cols;
//            source_table[0][0] /= total_pixel;
//            source_table[0][1] /= total_pixel;
//            source_table[0][2] /= total_pixel;
//            for (int i = 1; i < 256; i++) {
//                source_table[i][0] /= total_pixel;
//                source_table[i][0] += source_table[i - 1][0];
//                source_table[i][1] /= total_pixel;
//                source_table[i][1] += source_table[i - 1][1];
//                source_table[i][2] /= total_pixel;
//                source_table[i][2] += source_table[i - 1][2];
//            }
//
//
//            double target_table[256][3] = { 0 };
//            for (int i = 0; i < 256; i++) {
//                target_table[i][0] = 0.0f;
//                target_table[i][1] = 0.0f;
//                target_table[i][2] = 0.0f;
//            }
//            for (int i = 0; i < target_img.rows; i++) {
//                for (int j = 0; j < target_img.cols; j++) {
//                    ++target_table[target_img.at<Vec3b>(i, j)[0]][0];
//                    ++target_table[target_img.at<Vec3b>(i, j)[1]][1];
//                    ++target_table[target_img.at<Vec3b>(i, j)[2]][2];
//                }
//            }
//            total_pixel = target_img.rows * target_img.cols;
//            target_table[0][0] /= total_pixel;
//            target_table[0][1] /= total_pixel;
//            target_table[0][2] /= total_pixel;
//            for (int i = 1; i < 256; i++) {
//                target_table[i][0] /= total_pixel;
//                target_table[i][0] += target_table[i - 1][0];
//                target_table[i][1] /= total_pixel;
//                target_table[i][1] += target_table[i - 1][1];
//                target_table[i][2] /= total_pixel;
//                target_table[i][2] += target_table[i - 1][2];
//            }
//
//            uchar final_table[256][3] = { 0 };
//
//            for (int i = 0; i < 256; i++) {
//                double min0 = 999.0f;
//                double min1 = 999.0f;
//                double min2 = 999.0f;
//                for (int j = 0; j < 256; j++) {
//                    if (fabs(source_table[i][0] - target_table[j][0]) < min0) {
//                        min0 = fabs(source_table[i][0] - target_table[j][0]);
//                        final_table[i][0] = j;
//                    }
//
//                    if (fabs(source_table[i][1] - target_table[j][1]) < min1) {
//                        min1 = fabs(source_table[i][1] - target_table[j][1]);
//                        final_table[i][1] = j;
//                    }
//
//                    if (fabs(source_table[i][2] - target_table[j][2]) < min2) {
//                        min2 = fabs(source_table[i][2] - target_table[j][2]);
//                        final_table[i][2] = j;
//                    }
//                }
//            }
//
//            for (int i = 0; i < source_img.rows; i++) {
//                for (int j = 0; j < source_img.cols; j++) {
//                    source_img.at<Vec3b>(i, j)[0] = final_table[source_img.at<Vec3b>(i, j)[0]][0];
//                    source_img.at<Vec3b>(i, j)[1] = final_table[source_img.at<Vec3b>(i, j)[1]][1];
//                    source_img.at<Vec3b>(i, j)[2] = final_table[source_img.at<Vec3b>(i, j)[2]][2];
//                }
//            }
//        }
//        if (cvui::button(frame, 10, 90, 500, 30, "reset") && !source_img.empty()) {
//            source_origin.copyTo(source_img);
//        }
//
//        if (cvui::button(frame, 520, 90, 500, 30, "save")) {
//            std::string filename;
//            auto f = pfd::save_file(u8"路徑中不可有中文", "save.png",
//                { "Image Files (.jpg .png)", "*.jpg *.png *.JPG *.PNG",
//                  "All Files", "*" },
//                pfd::opt::none);
//            for (auto const& name : f.result())
//                filename += name;
//            if (!filename.empty() && !source_img.empty())imwrite(filename, source_img);
//        }
//
//        if (!source_img.empty()) cvui::image(frame, 10, 130, source_img);
//        if (!target_img.empty()) cvui::image(frame, 520, 130, target_img);
//
//
//        // Update cvui internal stuff
//        cvui::update();
//
//        // Show window content
//        cv::imshow(WINDOW_NAME, frame);
//
//
//        if (cv::waitKey(20) == 27) {
//            break;
//        }
//    }
//
//    return 0;
//}
//
//
//void drawHistImg(const Mat& src, Mat& dst) {
//    int histSize = 256;
//    float histMaxValue = 0;
//    for (int i = 0; i < histSize; i++) {
//        float tempValue = src.at<float>(i);
//        if (histMaxValue < tempValue) {
//            histMaxValue = tempValue;
//        }
//    }
//
//    float scale = (0.9 * 256) / histMaxValue;
//    for (int i = 0; i < histSize; i++) {
//        int intensity = static_cast<int>(src.at<float>(i) * scale);
//        line(dst, Point(i, 255), Point(i, 255 - intensity), Scalar(0));
//    }
//}



#include <opencv2/opencv.hpp>
#define CVUI_IMPLEMENTATION
#include "cvui.h"
#include "portable-file-dialogs.h"
#if _WIN32
#define DEFAULT_PATH "./"
#else
#define DEFAULT_PATH "/tmp"
#endif

#define WINDOW_NAME "test"
using namespace cv;

int main() {
    std::locale loc = std::locale::global(std::locale(""));
    cvui::init(WINDOW_NAME);
    cv::Mat frame = cv::Mat(cv::Size(1050, 750), CV_8UC3);
    Mat source_img;
    while (cv::getWindowProperty(WINDOW_NAME, 0) >= 0) {
        frame = cv::Scalar(49, 52, 49);

        if (cvui::button(frame, 10, 10, 1000, 30, "load image")) {
            std::string filename;
            auto f = pfd::open_file(u8"路徑中不可有中文", DEFAULT_PATH,
                { "Image Files (.jpg .png)", "*.jpg *.png *.JPG *.PNG",
                  "All Files", "*" },
                pfd::opt::none);
            for (auto const& name : f.result())
                filename = name;
            if (!filename.empty()) {
                source_img = imread(filename);
                double resize_value = 1000.0f / source_img.cols < 620.0f / source_img.rows  ? 1000.0f / source_img.cols : 620.0f / source_img.rows;
                resize(source_img, source_img, cv::Size(), resize_value, resize_value);
            }
        }

        if (!source_img.empty()) cvui::image(frame, 10, 50, source_img);
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