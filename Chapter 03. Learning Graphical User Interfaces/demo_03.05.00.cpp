#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// OpenGL includes
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

// OpenCV includes
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

Mat frame; // lưu các khung hình từ camera
GLfloat angle = .0; // chỉnh góc hình
GLuint texture; // OpenGL texture object
VideoCapture camera;

int loadTexture() {
    if (frame.data == NULL) return -1;

    glBindTexture(GL_TEXTURE_2D, texture); // bind the texture to it's array
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, frame.data);

    return 0;
}

void on_opengl(void *param) {
    glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, texture); // load texture
    glRotatef(angle, 1.0f, 1.0f, 1.0f); // rotate plane
    
    // Create the plane
    glBegin(GL_QUADS);
    glTexCoord2d(0., 0.); glVertex2d(-1., -1.);
    glTexCoord2d(1., 0.); glVertex2d(+1., -1.);
    glTexCoord2d(1., 1.); glVertex2d(+1., +1.);
    glTexCoord2d(0., 1.); glVertex2d(-1., +1.);
    glEnd();
}

int main(int argc, const char** argv) {
    // Open Webcam
    camera.open(0);
    if (!camera.isOpened()) { // camera opens unsuccessful
        camera.open("./data/Recording3.webm");
        if (!camera.isOpened()) return -1;
    }

    // Create new windows
    namedWindow("OpenGL Camera", WINDOW_OPENGL);

    // Enable texture
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);

    setOpenGlDrawCallback("OpenGL Camera", on_opengl);

    while (waitKey(30) != 'q') {
        camera >> frame;

        // Create first texture
        loadTexture();
        updateWindow("OpenGL Camera");
        angle = angle + 4;
    }

    // Destroy the window
    destroyWindow("OpenGL Camera");
    
    return 0;
}