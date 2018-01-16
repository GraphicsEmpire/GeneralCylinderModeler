#include <sstream>
#include <fstream>
#include <algorithm>
#include "path.h"

#ifdef PS_OS_MAC
    #include <mach-o/dyld.h>
    #include <unistd.h>		/* execve */
    #include <libgen.h>		/* dirname */
    #include <dirent.h>
#elif defined(PS_OS_WINDOWS)
    #include <io.h>
    #include "Windows.h"
    #include "dirent/include/dirent.h"
#elif defined(PS_OS_LINUX)
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <dirent.h>
    #include <unistd.h>
#endif

using namespace nb::utils;


std::string Path::GetExePath()
{
    char exePath[1024];
#ifdef PS_OS_MAC
    uint32_t szExePath;
    if(_NSGetExecutablePath(exePath, &szExePath) == 0)
        exePath[szExePath+1] = 0;
    else {
        exePath[0] = 0;
        printf("Not enough memory to get exepath. Needs %d\n", szExePath);
    }

#elif defined(PS_OS_WINDOWS)
    WCHAR wszExeName[MAX_PATH + 1];
    wszExeName[MAX_PATH] = 0;
    GetModuleFileNameW(NULL, wszExeName, sizeof(wszExeName) - 1);
    WideCharToMultiByte(CP_ACP, 0, wszExeName, -1, (LPSTR)exePath, sizeof(exePath), NULL, NULL);
#elif defined(PS_OS_LINUX)
    //getcwd only retrieves the current working directory
    //getcwd(exePath, (int)szBuffer);

    pid_t pid = getpid();
    stringstream ss;
    ss << "/proc/" << pid << "/exe";
    string process_path = ss.str();

    int nCharsWritten = readlink(process_path.c_str(), exePath, 1024);
    if(nCharsWritten != -1)
    {
        exePath[nCharsWritten] = 0;
    }
#endif

    return string(exePath);
}

U64 Path::GetFileSize(const string& fpath)
{
    ifstream ifs(fpath.c_str(), ios::in | ios::binary );
    if(!ifs.is_open())
        return 0;

    long begin, end;
    begin = ifs.tellg();
    ifs.seekg(0, ios::end);
    end = ifs.tellg();
    ifs.close();

    return end - begin;
}

U64 Path::FileExists(const string &fpath)
{
    ifstream ifs(fpath.c_str(), ios::in | ios::binary );
    if(ifs.is_open())
    {
        ifs.close();
        return true;
    }
    else
    {
        return false;
    }
}

bool Path::IsDirectory(const string &path)
{
#ifdef PS_OS_LINUX
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
#else
    DIR* dir = opendir(path.c_str());
    bool result = false;
    if(dir) {
        struct dirent *ent;
        ent = readdir (dir);
        if(ent != NULL) {
            result = (ent->d_type == DT_DIR || ent->d_type == DT_REG);
        }
        closedir(dir);
    }

    return result;
#endif
}

U32 Path::GetFileNamesInDir(const string &path, vector<string>& filenames)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL) {
        //print all the files and directories within directory
        while ((ent = readdir (dir)) != NULL) {
            printf ("%s\n", ent->d_name);

            //if it is a regular file then add it
            if(ent->d_type ==  DT_REG)
                filenames.push_back(string(ent->d_name));
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }

    return (U32)filenames.size();
}

string Path::GetFileExtension(const string &fpath)
{
    string::size_type idx;
    idx = fpath.rfind('.');
    if(idx != std::string::npos)
    {
        return fpath.substr(idx+1);
    }
    else
    {
        // No extension found
        return string("");
    }
}

string Path::GetFileName(const string &fpath)
{
    std::set<char> delims {'\\', '/'};
    vector<string> tokens;
    Path::Split(tokens, fpath, delims);

    string fnameonly = fpath;
    if(tokens.size() > 0)
        fnameonly = tokens.back();
    return fnameonly;
}

string Path::GetFileDirLocation(const string &fpath)
{
    if (fpath == ".") return ".";
    std::set<char> delims {'\\', '/'};
    char d;
    vector<string> tokens;
    Path::Split(tokens, fpath, delims, d);
    string fdir;
    for(U32 i=0; i < tokens.size() - 1; i++) {
        fdir = fdir + tokens[i] + d;
    }    

    return fdir;
}

string Path::GetDirectoryParent(const string &fpath)
{
    std::set<char> delims {'\\', '/'};
    char d;
    vector<string> tokens;
    Path::Split(tokens, fpath, delims, d);
    string fdir;
    for(U32 i=0; i < tokens.size() - 1; i++) {
        fdir = fdir + tokens[i] + d;
    }

    return fdir;
}

string Path::ChangeFileExtension(const string &fpath, const string &new_extension_no_dots)
{
    string output = fpath;
    string::size_type idx = output.rfind('.');
    if(idx != std::string::npos)
    {
        output = output.substr(0, idx + 1) + new_extension_no_dots;
    }
    return output;
}

string Path::SubtractFromBeginning(const string& left, const string& right) {
    string output = left;
    string::size_type idx = output.find(right);
    if(idx != std::string::npos)
        output = output.substr(idx + right.length() + 1);
    return output;
}


U32 Path::Split(vector<string>& out_tokens, const std::string& fpath, const std::set<char> delimiters)
{
    char d;
    return Path::Split(out_tokens, fpath, delimiters, d);
}

U32 Path::Split(vector<string>& out_tokens, const string &fpath, const std::set<char> delimiters, char &used_delimiter)
{    
    char const* pch = fpath.c_str();
    char const* start = pch;
    for(; *pch; ++pch)
    {
        if (delimiters.find(*pch) != delimiters.end())
        {
            used_delimiter = *pch;
            if (start != pch)
            {
                std::string str(start, pch);
                out_tokens.push_back(str);
            }
            else
            {
                out_tokens.push_back("");
            }
            start = pch + 1;
        }
    }
    out_tokens.push_back(start);

    return (U32)out_tokens.size();
}

string Path::Join(const string &left, const string &right)
{
    std::set<char> delims {'\\', '/'};
    char chend = left.back();
    if(delims.find(chend) != delims.end()) {
        return left + right;
    }
    else {
        #ifdef PS_OS_WINDOWS
            char mydelimiter = '\\';
        #else
            char mydelimiter = '/';
        #endif

        return left + mydelimiter + right;
    }
}

string Path::ToUpper(const string &input)
{
    string result = input;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return toupper(c); });
    return result;
}

string Path::ToLower(const string &input)
{
    string result = input;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return tolower(c); });
    return result;
}
