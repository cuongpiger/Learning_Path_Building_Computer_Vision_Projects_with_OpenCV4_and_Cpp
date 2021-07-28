#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// OpenCV includes
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

const int CV_GUI_NORMAL = 0x10;

int main(int argc, const char** argv) {
    // Read images
    Mat lena = imread("./data/lena.jpg");
    Mat photo = imread("./data/photo.jpg");

    // Create windows
    namedWindow("Lena", WINDOW_NORMAL);

    // Checking it Lena image has been loaded
    if (!lena.data) {
        cout << "Lena image missing!" << endl;
        return -1;
    }

    // Create a window without resizing by cursor
    namedWindow("Photo", WINDOW_AUTOSIZE);
    if (!photo.data) {
        cout << "Photo image missing!" << endl;
        return -1;
    }

    // Move windows
    moveWindow("Lena", 10, 10);
    moveWindow("Photo", 520, 10);

    // Show images
    imshow("Lena", lena);
    imshow("Photo", photo);

    // Resize window
    resizeWindow("Lena", 512, 512);

    // Wait for any key press
    waitKey(0);

    // Create 10 windows
    for (int i = 0; i < 10; ++i) {
        ostringstream ss;
        ss << "Photo" << i;
        namedWindow(ss.str());
        moveWindow(ss.str(), 20*i, 20*i);
        imshow(ss.str(), photo);
    }

    waitKey(0);

    // Destroy all windows
    destroyAllWindows();
    return 0;
}