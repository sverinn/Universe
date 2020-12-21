#include "WinHeader.h"

#include <iostream>
#include <cstdio>
#include <fstream>


// For debugging
#include <io.h>
#include <fcntl.h>


#define UNUSED(x) (void)(x)       // Unused param (C compatible - not applicable to expressions)

class outbuf : public std::streambuf {
public:
    outbuf() {
        setp(0, 0);
    }

    virtual int_type overflow(int_type c = traits_type::eof()) {
        return fputc(c, stdout) == EOF ? traits_type::eof() : c;
    }
};

void CallConsole()
{
    //UNUSED(hInstance);
    //    UNUSED(hPrevInst);
    //UNUSED(lpCmdLine);
    //UNUSED(nShowCmd); // This param is used


    // create the console
    if (AllocConsole()) {
        FILE* pCout;
        freopen_s(&pCout, "CONOUT$", "w", stdout);
        SetConsoleTitle(L"Debug Console");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    }

    // set std::cout to use my custom streambuf
    outbuf ob;
    std::streambuf* sb = std::cout.rdbuf(&ob);

    // make sure to restore the original so we don't get a crash on close!
    std::cout.rdbuf(sb);
};