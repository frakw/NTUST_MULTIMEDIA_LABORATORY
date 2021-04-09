#include <opencv2/opencv.hpp>
#define CVUI_IMPLEMENTATION
#include "cvui.h"
#include "portable-file-dialogs.h"
#if _WIN32
    #include <windows.h>
    #define DEFAULT_PATH "./"
#else
    #define DEFAULT_PATH "/tmp"
#endif

#define WINDOW_NAME "Morphology"
using namespace cv;

int main() {
    std::locale loc = std::locale::global(std::locale(""));
#if _WIN32
    ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
    cvui::init(WINDOW_NAME);
    cv::Mat frame = cv::Mat(cv::Size(1050, 750), CV_8UC3);
    Mat reversi;
    Mat reversi_rgb;
    Mat morphology;
    Mat morphology_rgb;
    int number_of_piece = -1;
    while (cv::getWindowProperty(WINDOW_NAME, 0) >= 0) {
        frame = cv::Scalar(49, 52, 49);

        if (cvui::button(frame, 10, 10, 500, 30, "load reversi")) {
            std::string filename;
            auto f = pfd::open_file(u8"路徑中不可有中文", DEFAULT_PATH,
                { "Image Files (.jpg .png)", "*.jpg *.png *.JPG *.PNG",
                  "All Files", "*" },
                pfd::opt::none);
            for (auto const& name : f.result())
                filename = name;
            if (!filename.empty()) {
                reversi = imread(filename,0);
                double resize_value = 500.0f / reversi.cols < 620.0f / reversi.rows ? 500.0f / reversi.cols : 620.0f / reversi.rows;
                resize(reversi, reversi, cv::Size(), resize_value, resize_value);
                GaussianBlur(reversi, reversi, Size(5, 5), 0, 0);
                threshold(reversi, reversi, 0, 255, THRESH_BINARY_INV | THRESH_OTSU); // 二值化
                number_of_piece = -1;
            }
        }
        if (cvui::button(frame, 520, 10, 500, 30, "load picture for morphology")) {
            std::string filename;
            auto f = pfd::open_file(u8"路徑中不可有中文", DEFAULT_PATH,
                { "Image Files (.jpg .png)", "*.jpg *.png *.JPG *.PNG",
                  "All Files", "*" },
                pfd::opt::none);
            for (auto const& name : f.result())
                filename = name;
            if (!filename.empty()) {
                morphology = imread(filename,0);
                double resize_value = 500.0f / morphology.cols < 620.0f / morphology.rows ? 500.0f / morphology.cols : 620.0f / morphology.rows;
                resize(morphology, morphology, cv::Size(), resize_value, resize_value);
                threshold(morphology, morphology, 0, 255, THRESH_BINARY_INV | THRESH_OTSU); // 二值化
            }
        }
        if (cvui::button(frame, 10, 50, 500, 30, "calculate number of piece") && !reversi.empty()) {
            Mat mask;
            mask = cv::getStructuringElement(MORPH_RECT, Size(5, 5));
            erode(reversi, reversi, mask, Point(-1, -1), 6);
            Mat labels;
            number_of_piece = connectedComponents(reversi, labels);
        }
        if (cvui::button(frame, 520, 50, 240, 30, "erode") && !morphology.empty()) {
            int filter_height = 5;
            int filter_width = 5;
            Mat result;
            result = morphology.clone();
            for (int i = 0; i < morphology.rows; i++) {
                for (int j = 0; j < morphology.cols; j++) {
                    bool erase = false;
                    for (int k = 0; k < filter_height; k++) {
                        for (int g = 0; g < filter_width; g++) {
                            int x = j + g;
                            int y = i + k;
                            if (filter_height % 2) y -= (int)(filter_height / 2);
                            else y -= (int)(filter_height / 2) - 1;
                            if (filter_width % 2) x -= (int)(filter_width / 2);
                            else x -= (int)(filter_width / 2) - 1;

                            if (y < 0) y *= -1;
                            else if (y >= morphology.rows) y = 2 * (morphology.rows - 1) - y;
                            if (x < 0) x *= -1;
                            else if (x >= morphology.cols) x = 2 * (morphology.cols - 1) - x;

                            if (morphology.at<uchar>(y, x) == 0) {
                                erase = true;
                                break;
                            }
                        }
                        if (erase) break;
                    }
                    if (erase) {
                        result.at<uchar>(i, j) = 0;
                    }
                }
            }
            morphology = result;

        }
        if (cvui::button(frame, 770, 50, 250, 30, "dilate") && !morphology.empty()) {
            int filter_height = 5;
            int filter_width = 5;
            Mat result;
            result = morphology.clone();
            for (int i = 0; i < morphology.rows; i++) {
                for (int j = 0; j < morphology.cols; j++) {
                    if (morphology.at<uchar>(i, j) == 0) continue;
                    for (int k = 0; k < filter_height; k++) {
                        for (int g = 0; g < filter_width; g++) {
                            int x = j + g;
                            int y = i + k;
                            if (filter_height % 2) y -= (int)(filter_height / 2);
                            else y -= (int)(filter_height / 2) - 1;
                            if (filter_width % 2) x -= (int)(filter_width / 2);
                            else x -= (int)(filter_width / 2) - 1;

                            if (y < 0) y *= -1;
                            else if (y >= morphology.rows) y = 2 * (morphology.rows - 1) - y;
                            if (x < 0) x *= -1;
                            else if (x >= morphology.cols) x = 2 * (morphology.cols - 1) - x;

                            result.at<uchar>(y, x) = 255;
                        }
                    }
                }
            }
            morphology = result;
        }

        if (number_of_piece != -1) {
            cvui::printf(frame, 10, 80,0.6f, 0xCECECE, "number of piece = %d", number_of_piece-1);
        }
        if (!reversi.empty()) {
            cvtColor(reversi, reversi_rgb, COLOR_GRAY2RGB);
            cvui::image(frame, 10, 100, reversi_rgb);
        }
        if (!morphology.empty()) {
            cvtColor(morphology, morphology_rgb, COLOR_GRAY2RGB);
            cvui::image(frame, 520, 100, morphology_rgb);
        }
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