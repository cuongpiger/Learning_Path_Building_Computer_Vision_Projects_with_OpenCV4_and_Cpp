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