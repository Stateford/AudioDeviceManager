#pragma once

#include <Windows.h>
#include <Mmdeviceapi.h>
#include <string>
#include <vector>

namespace AudioDeviceManager
{
    class AudioDevice
    {
    private:
        std::wstring _name;
        IMMDevice *_device;
    public:

        static unsigned int DeviceCount;

        explicit AudioDevice(std::wstring name, IMMDevice *device);

        std::wstring getName();
    };

    std::vector<AudioDevice> getDevices();
}