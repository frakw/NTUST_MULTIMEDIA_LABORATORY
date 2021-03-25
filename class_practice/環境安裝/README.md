到OPENCV官網安裝4.2.0版https://opencv.org/releases/

inlcude與lib資料夾放到工程目錄\
![image](include_and_lib.PNG)\
組態:所有組態	平台:所有平台\
屬性->VC++->Include目錄 => 加入include\\\
![image](include.PNG)\
屬性->VC++->程式庫目錄 => 加入lib\\\
![image](lib.PNG)\
完成後按下套用:\
![image](all.PNG)


組態:Debug	平台:所有平台\
屬性->連結器->輸入 => 加入opencv_world420d.lib\
![image](debug.PNG)

組態:Release	平台:所有平台\
屬性->連結器->輸入 => 加入opencv_world420.lib\
![image](release.PNG)

將dll資料夾中的所有.dll檔放到工程目錄下\
![image](dll.PNG)

將組態改為x64\
![image](x64.png)

將Lenna.jpg放到工程目錄下，並測試程式:
```cpp
#include<opencv2/opencv.hpp>
using namespace cv;
int main()
{
Mat img = imread("Lenna.jpg");
imshow("Hello World!", img);
waitKey();
}
```

運行結果:\
![image](finish.png)

UI安裝:\
將cvui.h放到工程目錄下\
標頭檔加入cvui.h\
![image](cvui_header.PNG)

並測試程式:
```cpp
#include <opencv2/opencv.hpp>
#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME "rgb to gray"
using namespace cv;
int main() {
    cvui::init(WINDOW_NAME);
    cv::Mat frame = cv::Mat(cv::Size(550, 580), CV_8UC3);

    Mat origin = imread("Lenna.jpg");
    Mat img;
    origin.copyTo(img);
    while (cv::getWindowProperty(WINDOW_NAME, 0) >= 0) {
        frame = cv::Scalar(49, 52, 49);
        //cvui::text(frame, 10, 10, "Hello world!");
        //
        if (cvui::button(frame, 10, 10, 250, 30, "rgb")) {
            //img = imread("Lenna.jpg");
            origin.copyTo(img);
        }
        if (cvui::button(frame, 270, 10, 250, 30, "gray")) {
            for (int i = 0; i < img.rows; i++)
            {
                for (int j = 0; j < img.cols; j++)
                {
                    Vec3b bgr = img.at<Vec3b>(i, j);
                    uchar gray_value = 0.114 * bgr[0] + 0.587 * bgr[1] + 0.299 * bgr[2];
                    img.at<Vec3b>(i, j)[0] = gray_value;
                    img.at<Vec3b>(i, j)[1] = gray_value;
                    img.at<Vec3b>(i, j)[2] = gray_value;
                }
            }
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
```

開啟檔案/儲存檔案視窗安裝:\
將portable-file-dialogs.h放到工程目錄下\
標頭檔加入portable-file-dialogs.h\
![image](pfd_header.PNG)

並測試程式:
```
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
```
windows選取檔案視窗:\
![image](pfd_loading.PNG)

成功讀取圖片:\
![image](pfd_loaded.png)