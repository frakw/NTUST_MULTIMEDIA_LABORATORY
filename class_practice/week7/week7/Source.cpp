#include <cmath>
#include <opencv2/opencv.hpp>
#define CVUI_IMPLEMENTATION
#include "cvui.h"
#include "portable-file-dialogs.h"
#if _WIN32
#define DEFAULT_PATH "./"
#else
#define DEFAULT_PATH "/tmp"
#endif

#define WINDOW_NAME "sobel"
using namespace cv;

int main() {
    std::locale loc = std::locale::global(std::locale(""));
    cvui::init(WINDOW_NAME);
    cv::Mat frame = cv::Mat(cv::Size(800, 750), CV_8UC3);
    Mat source_img;
    Mat img;
    while (cv::getWindowProperty(WINDOW_NAME, 0) >= 0) {
        frame = cv::Scalar(49, 52, 49);

        if (cvui::button(frame, 10, 10, 750, 30, "load image")) {
            std::string filename;
            auto f = pfd::open_file(u8"路徑中不可有中文", DEFAULT_PATH,
                { "Image Files (.jpg .png)", "*.jpg *.png *.JPG *.PNG",
                  "All Files", "*" },
                pfd::opt::none);
            for (auto const& name : f.result())
                filename = name;
            if (!filename.empty()) {
                source_img = imread(filename);
                double resize_value = 1000.0f / source_img.cols < 620.0f / source_img.rows ? 1000.0f / source_img.cols : 620.0f / source_img.rows;
                resize(source_img, source_img, cv::Size(), resize_value, resize_value);
                img = source_img.clone();
            }
        }
        if (cvui::button(frame, 10, 50, 750, 30, "sobel") && !img.empty()) {
            int filter_height = 3;
            int filter_width = 3;
            float filter_sx[3][3] =
            {
                -1.0f,0.0f,1.0f,
                -2.0f,0.0f,2.0f,
                -1.0f,0.0f,1.0f,    
            };
            float filter_sy[3][3] =
            {
                -1.0f,-2.0f,-1.0f,
                0.0f,0.0f,0.0f,
                1.0f,2.0f,1.0f,
            };
            Mat result = img.clone();
            for (int i = 0; i < img.rows; i++) {
                for (int j = 0; j < img.cols; j++) {
                    int gx[3], gy[3];
                    gx[0] = 0; gy[0] = 0;
                    gx[1] = 0; gy[1] = 0;
                    gx[2] = 0; gy[2] = 0;
                    for (int k = 0; k < filter_height; k++) {
                        for (int g = 0; g < filter_width; g++) {
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

                            for (int color = 0; color < 3; color++) {
                                gx[color] += filter_sx[k][g] * img.at<Vec3b>(y, x)[color];
                                gy[color] += filter_sy[k][g] * img.at<Vec3b>(y, x)[color];
                            }
                        }
                    }
                    for (int color = 0; color < 3; color++) {
                         int G = sqrtf(gx[color] * gx[color] + gy[color] * gy[color]);
                         if (G > 255) G = 255;
                         result.at<Vec3b>(i, j)[color] = G;
                    }
                }
            }
            img = result;
        }

        if (!source_img.empty()) cvui::image(frame, 10, 100, img);
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