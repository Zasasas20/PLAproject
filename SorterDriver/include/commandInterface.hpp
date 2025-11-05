#ifndef COMMANDUTILS_H
#define COMMANDUTILS_H

#include <pybind11/embed.h> // everything needed for embedding
namespace py = pybind11;

// Class responsible for interfacing with python modules

class CommandUtils {
    public:

        CommandUtils();

        bool pushValve(int valveID);
        int setTimer(int valveID, int timer);
        bool isValveAvailable(int valveID);
        int setActiveVavles(int amountOfValves);

        void initInterface(std::string path, py::module_& interface);

        py::module_ & getESPinterface();
        py::module_ & getClusterinterface();

    private: 
        py::scoped_interpreter interpreter{};
        py::module_ mESPInterface;
        py::module_ mClusterSelectorInterface;
}; 

#endif