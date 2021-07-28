# 2.7. Reading/writing images
###### [demo_02.07.00.cpp](demo_02.07.00.cpp)
```cpp
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// OpenCV includes
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

int main(int argc, const char** argv) {
    Mat color = imread("./data/lena.jpg");
    Mat gray = imread("./data/lena.jpg", IMREAD_GRAYSCALE);

    // Check for invalid input
    if (!color.data) {
        cout << "Could not open or find the image." << endl;
        return -1;
    }

    // Write images
    imwrite("./data/lena_gray.jpg", gray);

    // Get same pixel with OpenCV function
    int myRow = color.cols - 1;
    int myCol = color.rows - 1;
    Vec3b pixel = color.at<Vec3b>(myRow, myCol);
    printf("Pixel value (B, G, R): (%d, %d, %d).\n", (int)pixel[0], (int)pixel[1], (int)pixel[2]);

    // Show images
    imshow("Lena BGR", color);
    imshow("Lena Gray", gray);

    // Wait for any key press
    waitKey(0);
    return 0;
}
```
![](images/02_00.png)

# 2.11. Basic data persistence and storage
## 2.11.1. Writing to FileStorage
###### [demo_02.11.01.00.cpp](demo_02.11.01.00.cpp)
```cpp
#include <opencv2/opencv.hpp>
using namespace cv;

using namespace std;

int main(int, char** argv) {
    // Create the writer
    FileStorage fs("./data/test.yml", FileStorage::WRITE);

    // Save an integer
    int fps = 5;
    fs << "fps" << fps;

    // Create some `Mat` object samples
    Mat m1 = Mat::eye(2, 3, CV_32F);
    Mat m2 = Mat::ones(3, 2, CV_32F);
    Mat result = (m1 + 1).mul(m1 + 3);

    // Write `result`
    fs << "Result" << result;

    // Release the file
    fs.release();

    // Reading "test.yml" again to check writing successfully
    FileStorage fs2("./data/test.yml", FileStorage::READ);

    // Save loaded `Mat` object and save into `r` variable
    Mat r;
    fs2["Result"] >> r;
    cout << r << endl;

    fs2.release();

    return 0;
}
```
![](images/02_01.png)