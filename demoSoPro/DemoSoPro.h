#ifndef DEMOSOPRO_H
#define DEMOSOPRO_H

#include "demosopro_global.h"

class DEMOSOPROSHARED_EXPORT DemoSoPro
{

public:
    DemoSoPro();
    const char* getHelloWorld();
};
extern "C" DEMOSOPROSHARED_EXPORT int getSquare(int nParam);
#endif // DEMOSOPRO_H
