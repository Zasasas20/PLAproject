#include "commandInterface.hpp"

CommandUtils::CommandUtils() {}

bool CommandUtils::pushValve(int valveID) {
    char successFlagStr = valveID == 0 ? mESPInterface.attr("openAllValves")().cast<std::string>()[0] : mESPInterface.attr("openValve")(valveID).cast<std::string>()[0];
    return (int)(successFlagStr - '0');
}

int CommandUtils::setTimer(int valveID, int timer) {
    std::string newTimer = valveID == 0 ? mESPInterface.attr("setAllValvesTimer")(timer).cast<std::string>() : mESPInterface.attr("setValveTimer")(valveID, timer).cast<std::string>();
    return atoi(newTimer.c_str());
}

bool CommandUtils::isValveAvailable(int valveID) {
    std::string response = valveID == 0 ? mESPInterface.attr("getSingleValveStatus")(valveID).cast<std::string>() : mESPInterface.attr("getAllValvesStatus")().cast<std::string>();
    return (int)(response[0] - '0');
}

int CommandUtils::setActiveVavles(int amountOfValves) {
    std::string response = mESPInterface.attr("updateValveCount")(amountOfValves).cast<std::string>();
    return (int)(response[0] - '0');
}

void CommandUtils::initInterface(std::string path, py::module_& interface) {
    interface = py::module_::import(path.c_str());
}

py::module_ & CommandUtils::getESPinterface(){ 
    return mESPInterface;
}
    
py::module_ & CommandUtils::getClusterinterface(){
    return mClusterSelectorInterface;
}