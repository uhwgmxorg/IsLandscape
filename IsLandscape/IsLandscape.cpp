#include <iostream>

//#define _CRT_SECURE_NO_WARNINGS // must use in Project -> Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions
#include <windows.h>
#include <io.h>

// please refer: 
// https://github.com/nothings/stb
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

char szVersion[] = "1.0.0.0";

bool bShowHelp = false;            // -h
bool bShowCmdLineList = false;     // -s
bool bExitAtUserResponse = false;  // -ur
bool bShowImageInfo = false;       // -i

LPCWSTR szwImageFileName;
char szImageFileName[FILENAME_MAX];

//-------------------------------------------
// file_exists
//-------------------------------------------
inline bool file_exists(const std::string& name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

//-------------------------------------------
// GetImageFileName
//-------------------------------------------
LPCWSTR GetImageFileName(int argc, char *argv[])
{
    LPCWSTR szwFilename;
    wchar_t wtext[FILENAME_MAX];

    if (argc > 1)
    {
        if (strlen(argv[1]) + 1 > FILENAME_MAX)
        {
            std::cout << "Memory error filename too long!!" << "\n";
            if (bExitAtUserResponse)
                system("pause");
            exit(-1);
        }
        mbstowcs(wtext, argv[1], strlen(argv[1]) + 1); // plus null
        szwFilename = wtext;
        WideCharToMultiByte(CP_UTF8, 0, szwFilename, -1, szImageFileName, FILENAME_MAX, NULL, NULL); // just to show the file name in single chars
    }
    else
        szwFilename = NULL;

    if (!file_exists(szImageFileName))
    {
        std::cout << szImageFileName << " file not found" << "\n";
        if (bExitAtUserResponse)
            system("pause");
        szwFilename = NULL;
        memset(szImageFileName, 0, FILENAME_MAX);
        exit(-1);
    }

    return szwFilename;
}

//-------------------------------------------
// CmdOptionExists
//-------------------------------------------
bool CmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

//-------------------------------------------
// ProcessCommandLine
//-------------------------------------------
void ProcessCommandLine(int argc, char *argv[])
{
    if (argc == 1) bShowHelp = true;

    if (CmdOptionExists(argv, argv + argc, "-s"))  bShowCmdLineList = true;
    if (CmdOptionExists(argv, argv + argc, "-h"))  bShowHelp = true;
    if (CmdOptionExists(argv, argv + argc, "-ur")) bExitAtUserResponse = true;
    if (CmdOptionExists(argv, argv + argc, "-i"))  bShowImageInfo = true;

    if (bShowHelp)
    {
        std::cout << " Synopsis:\n";
        std::cout << " IsLandscape gets an image file as a parameter and returns 1 [exit(1);]\n";
        std::cout << " if the image is in landscape format or 0 [exit(0);] if it is in portrait\n";
        std::cout << " format. For using in .bat files.\n";
        std::cout << " use:" << "\n";
        std::cout << "   IsLandscape [file] [-option]" << "\n";
        std::cout << "     option:" << "\n";
        std::cout << "       -h Show help" << "\n";
        std::cout << "       -s Show list of command line params (if any)" << "\n";
        std::cout << "       -ur Only end the program when user has pressed a key" << "\n";
        std::cout << "       -i Show info of the image" << "\n";
        std::cout << "     example:" << "\n";
        std::cout << "       IsLandscape 00ab9c.jpg" << "\n";
        std::cout << "       IsLandscape 4a7d06.jpg -ur" << "\n";

        if (bExitAtUserResponse)
            system("pause");

        exit(0);
    }

    szwImageFileName = GetImageFileName(argc, argv);

    if (bShowCmdLineList)
    {
        std::cout << "---- command line parameter ----" << "\n";
        std::cout << "File is:" << "\n";
        std::cout << szImageFileName << "\n";
        for (int i = 2; i < argc; i++)
            std::cout << argv[i] << "\n";
        std::cout << "--------------------------------" << "\n";
    }
}

//-------------------------------------------
// main
//-------------------------------------------
int main(int argc, char *argv[])
{
#ifdef DEBUG
    std::cout << "Program IsLandscape Debug Version " << szVersion << "\n\n";
#else
    std::cout << "Program IsLandscape Release Version " << szVersion << "\n\n";
#endif // DEBUG

    ProcessCommandLine(argc, argv);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *image = stbi_load(szImageFileName, &width, &height, &channels, STBI_rgb);
    if (bShowImageInfo)
    {
        std::cout << "width    " << width << "\n";
        std::cout << "height   " << height << "\n";
        std::cout << "channels " << channels << "\n";
        if (width >= height)
            std::cout << "image is in landscape format\n";
        else
            std::cout << "image is in portrait format\n";
    }
    stbi_image_free(image);

    if (bExitAtUserResponse)
        system("pause");

    if (width >= height)
        exit(1);
    else
        exit(0);
}