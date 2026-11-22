// test_explorer2.cpp — Load loader.dll by full path and launch explorer
// Compiled with w64devkit g++ 16.2.0

#include <windows.h>
#include <cstdio>
#include <stdlib.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {
    // Load loader.dll by full path
    char dllPath[MAX_PATH];
    GetModuleFileNameA(NULL, dllPath, MAX_PATH);
    char* p = strrchr(dllPath, '\\');
    if (p) ++p; else dllPath[0] = '\0';
    strcat_s(dllPath, MAX_PATH, "loader.dll");
    
    HMODULE h = LoadLibraryA(dllPath);
    if (h) {
        char logPath[MAX_PATH];
        snprintf(logPath, MAX_PATH, "%sloader_load.txt", dllPath); // use dll dir
        FILE* f = fopen(logPath, "a");
        if (f) {
            fprintf(f, "test_explorer2: loader.dll loaded from %s\n", dllPath);
            fclose(f);
        }
        // Don't FreeLibrary - keep hooks active
    } else {
        // Log load failure
        char logPath[MAX_PATH];
        snprintf(logPath, MAX_PATH, "%sloader_load.txt", dllPath);
        FILE* f = fopen(logPath, "w");
        if (f) {
            fprintf(f, "test_explorer2: FAILED to load loader.dll\n");
            fclose(f);
        }
    }
    
    // Launch explorer.exe with full path
    SHELLEXECUTEINFOA sei = {0};
    sei.cbSize = sizeof(SHELLEXECUTEINFOA);
    sei.lpVerb = "open";
    sei.lpFile = "explorer.exe";
    sei.nShow = SW_SHOW;
    ShellExecuteExA(&sei);
    
    // Wait then exit
    Sleep(5000);
    return 0;
}