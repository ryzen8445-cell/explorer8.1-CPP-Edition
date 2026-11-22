// test_explorer.cpp — Load loader.dll and launch explorer.exe
// Compiled with w64devkit g++ 16.2.0
// Purpose: Test that loader.dll loads and explorer launches

#include <windows.h>
#include <cstdio>
#include <stdlib.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {
    // Load loader.dll before explorer starts
    HMODULE h = LoadLibrary(TEXT("loader.dll"));
    if (h) {
        // Log that it loaded
        char logPath[MAX_PATH];
        GetModuleFileNameA(NULL, logPath, MAX_PATH);
        char* p = strrchr(logPath, '\\');
        if (p) ++p; else logPath[0] = '\0';
        strcat_s(logPath, MAX_PATH, "loader_load.txt");
        
        FILE* f = fopen(logPath, "a");
        if (f) {
            fprintf(f, "test_explorer: loader.dll loaded, about to launch explorer\n");
            fclose(f);
        }
        // Don't FreeLibrary - keep hooks active for explorer
    }
    
    // Launch explorer.exe
    HINSTANCE result = ShellExecuteA(NULL, "open", "explorer.exe", NULL, NULL, SW_SHOW);
    
    // Wait a moment then exit
    Sleep(5000);
    return 0;
}