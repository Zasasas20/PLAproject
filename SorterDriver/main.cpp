#include <iostream>
#include <commandInterface.hpp>
#include <opencv2/opencv.hpp>
#include <ROIextractionUtils.hpp>

using namespace cv;

int main(int, char**){
    Mat frame;

    VideoCapture captureObject = VideoCapture(4);
    std::cout << "Hello, from SorterDriver!\n";

    captureObject >> frame;

    captureObject.set(CAP_PROP_FRAME_WIDTH, 1280);
    captureObject.set(CAP_PROP_FRAME_HEIGHT, 720);

    if (frame.data) {
        while (waitKey(15) != 27)
        {
            captureObject >> frame;
            imshow("src", frame);
        }
        std::vector<Mat> images = (getROIs(frame, ROIExtractionSetup(frame).rois));

        for (Mat & roi : images) {
            imshow("roi", roi);
            while (waitKey(15) != 27);
        }
    }

    // CommandUtils interface = CommandUtils();
    // interface.initInterface("valveInterface", interface.getESPinterface());
    // if (interface.pushValve('A')) std::cout << "success";
    // else std::cout << "fail";
}
