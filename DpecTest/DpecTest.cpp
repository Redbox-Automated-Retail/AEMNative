#include <windows.h>
#include <iostream>

typedef void(__cdecl* DPEC_GetLibraryVersion_t)(char*, char*, char*, char*);


int main() {
    HMODULE dpecHandle = LoadLibraryA("DPEC_API.dll");
    if (!dpecHandle) {
        std::cerr << "Failed to load DPEC_API.dll\n";
        return 1;
    }

    auto DPEC_GetLibraryVersion = (DPEC_GetLibraryVersion_t)GetProcAddress(dpecHandle, "DPEC_GetLibraryVersion");
    if (!DPEC_GetLibraryVersion) {
        std::cerr << "Failed to find DPEC_GetLibraryVersion\n";
        return 1;
    }

    char buffer[84];

    DPEC_GetLibraryVersion(&buffer[0],
        &buffer[1],
        &buffer[2],
        &buffer[4]);

    std::cout << buffer << "\n";

    FreeLibrary(dpecHandle);
    return 0;
}
