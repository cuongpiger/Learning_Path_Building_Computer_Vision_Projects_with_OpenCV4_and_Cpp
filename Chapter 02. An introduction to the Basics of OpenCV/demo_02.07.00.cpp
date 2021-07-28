#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// OpenCV includes
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
using namespace cv;

int main(int argc, const char** argv) {
    Mat color = imread("./data/lena.png");
    Mat gray = imread("./data/lena.png", CV_LOAD_IMAGE_GRAYSCALE);

    // Check for invalid input
    if (!color.data) {
        cout << "Could not open or find the image." << endl;
        return -1;
    }

    // Write images
    imwrite("./data/lena_gray.png", gray);

    // Get same pixel with OpenCV function
    int myRow = color.cols - 1;
    int myCol = color.rows - 1;
    Vec3b pixel = color.at<Vec3b>(myRow, myCol);
    cout << "Pixel value (B, G, R): (" << (int)pixel[0] << ", " << (int)pixel[1] << ", " << (int)pixel[2] << ")" << endl;

    // Show images
    imshow("Lena BGR", color);
    imshow("Lena Gray", gray);

    // Wait for any key press
    waitKey(0);
    return 0;
}