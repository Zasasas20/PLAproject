#include "valve.hpp"
#include <commandInterface.hpp>
#include <hue_histogram.hpp>

Valve::Valve(int id, float sensitivity, int window, int desiredHue, bool exclude, CommandUtils* interfaceRef): 
    mId{id},
    mSensitivity{sensitivity},
    mWindow{window},
    mHue{desiredHue},
    mExclude{exclude},
    mInterface{interfaceRef} 
    {
        //activate();
        mInterface->setTimer(mId, DEFAULTTIMEOUT_MS);
}

void Valve::setSensitivity(float sensitivity) {
    mSensitivity = sensitivity;
}

void Valve::setWindow(int window) {
    mWindow = window;
}

void Valve::setDesired(int desiredHue) {
    mHue = desiredHue;
}

void Valve::setExclusion(bool exclude) {
    mExclude = exclude;
}

bool Valve::isAvailable() {
    return mInterface->isValveAvailable(mId);
}

bool Valve::push() {
    return mInterface->pushValve(mId);
}

// Note to self: Rework activation logic to be ID based
// bool Valve::isActive() {
//     return mInterface->isValveAvailable(mId);
// }

// void Valve::activate() {
//     return mInterface->isValveAvailable(mId);
// }

// void Valve::deactivate() {
//     return mInterface->isValveAvailable(mId);
// }

void Valve::setTimer(int timeoutMS) {
    mInterface->setTimer(mId, timeoutMS);
}

config Valve::getConfig(Mat image) {
    return config {
        image,
        mSensitivity,
        mWindow,
        mHue,
        mExclude
    };
}

bool Valve::toPush(Mat image) {
    return run_pipeline(getConfig(image));
}