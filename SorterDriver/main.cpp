#include <iostream>
#include <commandInterface.hpp>
#include <opencv2/opencv.hpp>
#include <ROIextractionUtils.hpp>
#include <hue_histogram.hpp>
#include <lccv.hpp>
#include <libcamera_app.hpp>

using namespace cv;

int main(int, char**){
    Mat frame;
    lccv::PiCamera cam;

    cam.options->video_width=1280;
    cam.options->video_height=720;
    cam.options->framerate=30;
    cam.options->verbose=true;
    std::cout << "Hello, from SorterDriver!\n";

    cam.startVideo();

    while (waitKey(15) != 27) {
        if (!cam.getVideoFrame(frame,1000)) std::cout << "timed out!";
        else {
            while (waitKey(15) != 27)
            {
                imshow("src", frame);
                cam.getVideoFrame(frame,1000);
            }
            std::vector<Mat> images = (getROIs(frame, ROIExtractionSetup(frame).rois));

            for (Mat & roi : images) {
                imshow("roi", roi);
                while (waitKey(15) != 27);
            }
        }
    }

    // CommandUtils interface = CommandUtils();
    // interface.initInterface("valveInterface", interface.getESPinterface());
    // if (interface.pushValve('A')) std::cout << "success";
    // else std::cout << "fail";
}
