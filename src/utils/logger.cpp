#include <fstream>
#include <stdexcept>
#include <sstream>
#include "path.h"
#include "logger.h"
#include "linalg/base.h"


#ifdef PS_OS_WINDOWS
#include <windows.h>
#elif defined(PS_OS_LINUX)
#include <stdarg.h>
#endif

namespace nb {
namespace utils {

void nbLog(const char* lpDesc, ...)
{
    va_list	vl;
    va_start( vl, lpDesc );

    char	buff[PS_LOG_LINE_SIZE];
#ifdef PS_SECURE_API
    vsnprintf_s( buff, _countof(buff)-1, _TRUNCATE, pFmt, vl );
#else
    vsnprintf(buff, sizeof(buff)-1, lpDesc, vl);
#endif
    va_end( vl );

    TheEventLogger::Instance().Add(buff, EventLogger::etInfo);
}

//Log a single line
void nbLog(EventLogger::LogEventType etype, const char* lpSource, int line, const char* lpDesc, ...)
{
    va_list	vl;
    va_start( vl, lpDesc );

    char	buff[PS_LOG_LINE_SIZE];
#ifdef PS_SECURE_API
    vsnprintf_s( buff, _countof(buff)-1, _TRUNCATE, pFmt, vl );
#else
    vsnprintf(buff, sizeof(buff)-1, lpDesc, vl);
#endif
    va_end( vl );

        TheEventLogger::Instance().Add(buff, etype, lpSource, line);
}


//Class EventLogger
EventLogger::EventLogger()
{
    mOnDisplayCallBack = NULL;
    string exepath = Path::GetExePath();
    mLogFilePath = Path::ChangeFileExtension(exepath, string("log"));
    mRootFilePath = Path::GetDirectoryParent(Path::GetFileDirLocation(Path::GetExePath()));
    mBufferUsageSize = 0;
    mWriteToCommandLineSeverity = etProfile;
    SetWriteFlags(BitMaskWriteEventType | BitMaskWriteEventLocation | BitMaskWriteToCommandLine | BitMaskWriteTimeStamp);
}

EventLogger::EventLogger(const char* lpFilePath, int flags)
{
    mOnDisplayCallBack = NULL;
    mLogFilePath = string(lpFilePath);
    mBufferUsageSize = 0;
    SetWriteFlags(flags);
}

EventLogger::~EventLogger()
{
    Flush();
}

void EventLogger::SetWriteFlags(int flags)
{
    mWriteEventTypeFlag = ((flags & BitMaskWriteEventType) != 0);
    mWriteTimeStampFlag = ((flags & BitMaskWriteTimeStamp) != 0);
    mWriteEventLocationFlag = ((flags & BitMaskWriteEventLocation) != 0);
    mWriteToCommandLineFlag   = ((flags & BitMaskWriteToCommandLine) != 0);    
}

void EventLogger::SetLogDisplayPolicy(bool displayOnOff, EventLogger::LogEventType severity)
{
    mWriteToCommandLineFlag = displayOnOff;
    mWriteToCommandLineSeverity = severity;
}

void EventLogger::SetLogFilePath(const string &filepath)
{
    mLogFilePath = filepath;
}

void  EventLogger::Add(const Event &event)
{
    Add(event.strDesc.c_str(), event.etype, event.strSource.c_str(), event.value);
}


void EventLogger::Add(const char *lpStrDesc, LogEventType etype, const char *lpStrSource, int value)
{
    if(lpStrDesc == NULL)
        return;

    stringstream ss;

    //Resolve event type
    if(mWriteEventTypeFlag)
    {
        if(etype == etProfile)
            ss << "PROFILE: ";
        else if(etype == etInfo)
            ss << "INFO: ";
        else if(etype == etWarning)
            ss << "WARNING: ";
        else if(etype == etError)
            ss << "ERROR: ";
    }

    //Resolve event timing
    if(mWriteTimeStampFlag)
    {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[128];

        time (&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, 128, "%Y%m%d_%H%M%S", timeinfo);
        ss << "TIME: [" << string(buffer)<< "], ";
    }

    //Resolve event source and line number
    if(mWriteEventLocationFlag && lpStrSource)
    {
        //Shorten Source Location Based on Root Path
        string source(lpStrSource);
        source = Path::GetFileName(source);
        ss << "SOURCE: [" << source << ", LINE:" << value << "], ";
    }

    //Convent event description to string
    ss << string(lpStrDesc) << endl;
    string line = ss.str();

    //lock mutex before writing to mLines
    {
        std::lock_guard<std::mutex> guard(mLinesMutex);
        mLines.push_back(line);
    }

    //Direct the final message to screen
    if(mWriteToCommandLineFlag && (etype >= mWriteToCommandLineSeverity))
        Display(line, etype);

    //Update Buffer size and Flush if ready
    mBufferUsageSize += line.length();
    if(mBufferUsageSize > PS_LOG_BUFFER_SIZE)
        Flush();
}

void EventLogger::Display(const string &line, LogEventType etype) const
{    
    if(mOnDisplayCallBack)
        mOnDisplayCallBack(line);
    else
    {
      if(etype == LogEventType::etError)
        fprintf(stderr, "NB: %s", line.c_str());
      else
        fprintf(stdout, "NB: %s", line.c_str());
    }
}


//Open File and Append
bool EventLogger::Flush()
{
    std::unique_lock<std::mutex> lock(mLinesMutex, std::defer_lock);
    if(!lock.try_lock()) {
        return false;
    }

    if(mLines.size() == 0)
        return false;

    ofstream ofs;
    if(Path::FileExists(mLogFilePath))
        ofs.open(mLogFilePath.c_str(), ios::out | ios::app);
    else
        ofs.open(mLogFilePath.c_str(), ios::out);
    if(!ofs.is_open())
        return false;

    string strLine;
    for(size_t i=0; i < mLines.size(); i++)
    {
        strLine = mLines[i];
        if(strLine.length() > 0)
        {
            ofs << strLine;
        }
    }
    ofs.close();

    mLines.resize(0);
    mBufferUsageSize = 0;
    return true;
}


}
}
