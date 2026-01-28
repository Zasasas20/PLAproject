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

    valves.push_back({Valve(1, 0.5, 10, 0, false, interface)}); // Red (0-10 and 170-180)
    valves.push_back({Valve(2, 0.5, 10, 150, false, interface)}); // Purple (140-160)
    valves.push_back({Valve(3, 0.5, 5, 30, false, interface)}); // Yellow (25-35)
    valves.push_back({Valve(4, 0.5, 10, 0, false, interface)}); // Red (0-10 and 170-180)
    valves.push_back({Valve(5, 0.5, 15, 55, false, interface)}); // Green (40-70)
    valves.push_back({Valve(6, 0.5, 20, 110, false, interface)}); // Blue (90-130)

    bool success = true;
    bool initialized = false;
    for (Valve v: valves) {success = success && v.push();}
    std::cout << "Valve initiation successful? " << success << '\n';
    ROIContext context;

    while (waitKey(15) != 27) {
        if (!cam.getVideoFrame(frame,1000)) std::cout << "timed out!" << '\n';
        else {
            cam.getVideoFrame(frame,1000);
            Mat rotated;
            rotate(frame, rotated, ROTATE_180);
            if (!initialized) {
                context = ROIExtractionSetup(rotated);
                if(context.pumps.size() > 0) initialized = true;
            }
            std::vector<Mat> images = (getROIs(rotated, context.rois));

            int i = 1;
            if (context.rois.size() <= 6 && context.rois.size() > 2) {
                for (Mat & roi : images) {
                    if (!roi.empty()) {
                        std::string name = "roi";
                        name += std::to_string(i);
                        imshow(name, roi);
                        bool result = valves[6-i].toPush(roi);
                        if (result) std::cout << valves[6-i].push() << '\n';
                        i++;
                    }
                }  
            }
        }
    }
}
