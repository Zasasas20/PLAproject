#ifndef VALVE_H
#define VALVE_H

#define DEFAULTTIMEOUT_MS 50000

#include <opencv2/opencv.hpp>
using namespace cv;

struct config;
class CommandUtils;

class Valve {
    public:

        Valve(int id, float sensitivity, int window, int desiredHue, bool exclude, CommandUtils* interfaceRef);

        void setSensitivity(float sensitivity);
        void setWindow(int window);
        void setDesired(int desiredHue);
        void setExclusion(bool exclude);

        bool isAvailable();
        bool push();
        bool toPush(Mat image);
        // bool isActive();
        // void activate();
        // void deactivate();

        void setTimer(int timeoutMS);
        config getConfig(Mat image);
    private:
        int mId{-1};
        float mSensitivity{-1};
        int mWindow{-1};
        int mHue{-1};
        bool mExclude{false};
        CommandUtils* mInterface{nullptr};
};

#endif