#include <Windows.h>
#include <Mmdeviceapi.h>
#include <string>
#include <iostream>
#include <vector>
#include "devices.h"

using namespace AudioDeviceManager;

int main()
{
    // EXAMPLE USUAGE
    auto audioDevices = getDevices();

    for (auto &p : audioDevices)
    {
        std::wcout << p.getName() << std::endl;
    }

    return 0;
}