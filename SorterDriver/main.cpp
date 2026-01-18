#include <iostream>
#include <ROIextractionUtils.hpp>
#include <valve.hpp>
#include <lccv.hpp>
#include <libcamera_app.hpp>
#include <commandInterface.hpp>

using namespace cv;

int main(int, char**){
    Mat frame;
    lccv::PiCamera cam;

    cam.options->video_width=1280;
    cam.options->video_height=720;
    cam.options->framerate=30;
    cam.options->verbose=true;
    cam.startVideo();
    std::cout << "Initialized camera!" << '\n';

    CommandUtils * interface = new CommandUtils();
    interface->initInterface("valveInterface", interface->getESPinterface());
    std::cout << "Initialized interface!" << '\n';

    std::vector<Valve> valves;

    valves.push_back({Valve(1, 0.5, 10, 0, false, interface)});
    valves.push_back({Valve(2, 0.5, 10, 0, false, interface)});
    valves.push_back({Valve(3, 0.5, 10, 0, false, interface)});
    valves.push_back({Valve(4, 0.5, 10, 0, false, interface)});
    valves.push_back({Valve(5, 0.5, 10, 0, false, interface)});
    valves.push_back({Valve(6, 0.5, 10, 0, false, interface)});

    bool success = true;
    for (Valve v: valves) {success = success && v.push();}
    std::cout << "Valve initiation successful? " << success << '\n';

    while (waitKey(15) != 27) {
        if (!cam.getVideoFrame(frame,1000)) std::cout << "timed out!";
        else {
            cam.getVideoFrame(frame,1000);
            ROIContext context = ROIExtractionSetup(frame);
            std::vector<Mat> images = (getROIs(frame, context.rois));

            for (Mat & roi : images) {
                imshow("roi", roi);
                while (waitKey(15) != 27);
            }
        }
    }
}
