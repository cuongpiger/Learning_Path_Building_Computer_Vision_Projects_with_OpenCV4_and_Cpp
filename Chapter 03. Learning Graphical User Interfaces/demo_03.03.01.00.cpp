#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// OpenCV includes
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

// Giá trị làm mờ ban đầu mặc định là 15/30, tức vị trí 15 trên slidebar
int blurAmount = 15;

// Trackbar call back function
static void onChange(int pos, void* userInput);

// Mouse callback
static void onMouse(int event, int x, int y, int, void* userInput);


int main(int argc, const char** argv) {
    // Read image
    Mat lena = imread("./data/lena.jpg");

    // Create window
    namedWindow("Lena");

    // Làm mờ hình ảnh
    createTrackbar("Lena", "Lena", &blurAmount, 30, onChange, &lena);

    setMouseCallback("Lena", onMouse, &lena);

    // Call to onChange to init
    onChange(blurAmount, &lena);

    // Wait app for a key to exit
    waitKey(0);

    // Destroy the window
    destroyWindow("Lena");

    return 0;
}

// Trackbar call back function
static void onChange(int pos, void* userInput) {
    // Kiểm tra giá trị làm mờ là bao nhiêu (ban đầu là 15)
    if (pos <= 0) return;

    // `Mat` object dùng để làm mờ
    Mat imgBlur;

    // Vì `userInput` truyền vào là ma trận, nên cần ép kiểu lại, ở đây là hình lena
    Mat* img = (Mat*)userInput;

    // Apply a blur filter
    // Tham số Size(pos, pos) tức là giá trị làm mờ dọc theo chiều ngàng và chiều dọc
    blur(*img, imgBlur, Size(pos, pos));

    // Show the result
    imshow("Lena", imgBlur);
}

// Mouse call back
static void onMouse(int event, int x, int y, int, void* userInput) {
    if (event != EVENT_LBUTTONDOWN) return;

    // Get the pointer input image
    Mat* img = (Mat*)userInput;

    // Draw circle
    // Tham số thứ 2 là trung tâm hình tròn, thứ 3 là bán kính, thứ 4 là màu, thứ 5 là độ dày đường vẽ
    circle(*img, Point(x, y), 10, Scalar(0, 255, 0), 3);

    // Call on change to get blurred image
    onChange(blurAmount, img);
}