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
    // Read image
    Mat lena = imread("./data/lena.jpg");

    // Create window
    namedWindow("Lena");

    // Show image
    imshow("Lena", lena);

    // Display overlay
    displayOverlay("Lena", "Overlay 5 secs", 5000);

    // Display status bar
    displayStatusBar("Lena", "Status-bar 5 secs", 5000);

    // Save window parameters
    saveWindowParameters("Lena");

    // Load window parameters
    loadWindowParameters("Lena");

    // Wait for any key press
    waitKey(0);

    // Destroy the window
    destroyWindow("Lena");

    return 0;
}