#ifndef PYSCRIPTTOOLS_H
#define PYSCRIPTTOOLS_H
#include "Simulation.h"
#include "PyGenVisitor.h"


namespace PyScriptTools {
    void genPyScript(Simulation *simulation, std::string pyScriptName,
                     std::string outputDataFileName);
    std::string printDouble(double input);
    bool isSquare();
    bool isHexagonal();
    bool testPyScript(Simulation *simulation);

}

#endif // PYSCRIPTTOOLS_H
