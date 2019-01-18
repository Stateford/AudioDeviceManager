#include "devices.h"

namespace AudioDeviceManager
{
    // STATIC MEMBERS
    unsigned int AudioDevice::DeviceCount = 0;

    // Constructor
    AudioDevice::AudioDevice(std::wstring name, IMMDevice *device) 
    {
        _name = name;
        _device = device;
    }

    std::wstring AudioDevice::getName()
    {
        return _name;
    }

    std::vector<AudioDevice> getDevices()
    {
        // Initalize
        CoInitialize(NULL);
        const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
        const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
        IMMDeviceEnumerator *pEnumerator = NULL;
        // get the enumerator object
        auto hr = CoCreateInstance(
            CLSID_MMDeviceEnumerator, NULL,
            CLSCTX_ALL, IID_IMMDeviceEnumerator,
            (LPVOID*)&pEnumerator);

        if (hr != S_OK)
            throw "ERROR";
        
        // grab a collection of all devices
        IMMDeviceCollection *pDeviceCollection = NULL;
        pEnumerator->EnumAudioEndpoints(eAll, DEVICE_STATE_ACTIVE, &pDeviceCollection);
        UINT deviceCount;
        pDeviceCollection->GetCount(&deviceCount);

        std::vector<AudioDevice> audioDevices;

        for (unsigned int i = 0; i < deviceCount; i++)
        {
            IMMDevice *pDevice = NULL;
            IPropertyStore *pProperty = NULL;
            // get the item in the array
            pDeviceCollection->Item(i, &pDevice);
            // get properties
            pDevice->OpenPropertyStore(STGM_READ, &pProperty);

            // get 2nd property key (the name of the object)
            PROPERTYKEY key;
            pProperty->GetAt(2, &key);
            // get the 2nd property name
            PROPVARIANT propVari;
            pProperty->GetValue(key, &propVari);
            // pointer to string at this location in the struct
            LPWSTR _name = propVari.pwszVal;
            std::wstring name(_name);

            // get the type of audio device
            pProperty->GetAt(1, &key);
            pProperty->GetValue(key, &propVari);

            name += L'(' + std::wstring(propVari.pwszVal) + L')';

            audioDevices.push_back(AudioDevice(name, pDevice));
        }
        return audioDevices;
    }
}