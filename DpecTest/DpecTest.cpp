#include <windows.h>
#include <iostream>

typedef struct {
    BYTE major;      // buffer[0]
    BYTE minor;      // buffer[1]  
    WORD build;      // buffer[2-3] as little-endian word
} DPEC_VERSION;

typedef void(__cdecl* DPEC_GetLibraryVersion_t)(DPEC_VERSION*, char*);


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

    DPEC_VERSION version;
    char versionString[80];

    DPEC_GetLibraryVersion(&version, versionString);

    printf("Version: %d.%d Build %04d\n", version.major, version.minor, version.build);
    printf("Version String: %s\n", versionString);

    FreeLibrary(dpecHandle);
    return 0;
}
