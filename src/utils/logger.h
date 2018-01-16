#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include <time.h>
#include <mutex>
#include "linalg/base.h"
#include "singleton.h"

using namespace std;
using namespace nb;
//using namespace nb::linalg;


namespace nb {
namespace utils {

class EventLogger;

#define PS_LOG_LINE_SIZE	2048
//16 KiloBytes for the memory log
#define PS_LOG_BUFFER_SIZE  8*PS_LOG_LINE_SIZE

//define vargs funcs for logging
#define nbLogInfo(desc, ...) nb::utils::nbLog(nb::utils::EventLogger::etInfo, __FILE__, __LINE__, desc, ##__VA_ARGS__)
#define nbLogWarn(desc, ...) nb::utils::nbLog(nb::utils::EventLogger::etWarning, __FILE__, __LINE__, desc, ##__VA_ARGS__)
#define nbLogError(desc, ...) nb::utils::nbLog(nb::utils::EventLogger::etError, __FILE__, __LINE__, desc, ##__VA_ARGS__)


//Display Error Message
typedef void (*FOnDisplay)(const string& line);


/*!
* Event Logger class for writing major application events to disk. 
*/
class EventLogger {

public:
    EventLogger();

    /*!
        * Constructor for setting the log file path on disk and setting up the flags for
        * controlling how the log is written.
        * @param lpFilePath the string of the file path
        * @param flags that indicate how each log entry has to be written
        */
    EventLogger(const char* lpFilePath, int flags = 0);

    virtual ~EventLogger();

    enum LogEventType {etProfile, etInfo, etWarning, etError};
    enum LogWritePolicyBitMasks { BitMaskWriteEventType = 1,
                                  BitMaskWriteTimeStamp = 2,
                                  BitMaskWriteEventLocation = 4,
                                  BitMaskWriteToCommandLine = 8,
                                };


    //Internal Class for holding an instance of an event
    struct Event{
        EventLogger::LogEventType etype;
        string strDesc;
        string strSource;
        int value;
    };

    /*!
    * Adds an event to the event log system
    * @param e reference to the event variable
    */
    void Add(const Event &event);

    /*!
    * Adds an entry to the log system
    * @param lpStrDesc Description for this event
    * @param t type of this event
    * @param lpSource the source of the event (Can be a File, File + Function Name)
    * @param value can be line number or the error code
    */
    void Add(const char *lpStrDesc, LogEventType etype = etInfo, const char *lpStrSource = NULL, int value = 0);

    /*!
    * @param flags to control the way log entries are being written to disk
    */
    void SetWriteFlags(int flags);

    void SetLogDisplayPolicy(bool displayOnOff, LogEventType severity);

    //Set output filepath
    void SetLogFilePath(const string &filepath);

    //Set error display callback
    void SetDisplayCallBack(FOnDisplay cb) {mOnDisplayCallBack = cb;}


    //Flush the content of string buffer to disk
    bool Flush();
    
private:

    void Display(const string &line, LogEventType etype) const;

    //Private Variables
private:
    //On Display Error
    FOnDisplay mOnDisplayCallBack;

    //Flags to control serialization
    bool mWriteEventTypeFlag;
    bool mWriteTimeStampFlag;
    bool mWriteEventLocationFlag;
    bool mWriteToCommandLineFlag;

    //if urgecy is equal to more than this, then display the log
    LogEventType mWriteToCommandLineSeverity;

    U32 mBufferUsageSize;
    string mLogFilePath;
    string mRootFilePath;

    std::mutex mLinesMutex;
    std::vector<string> mLines;
};

typedef Singleton<EventLogger> TheEventLogger;

void nbLog(const char* lpDesc, ...);

/*!
* Adds a new entry to log using printf style formatting. 
*/
void nbLog(EventLogger::LogEventType etype, const char* lpSource, int line, const char* lpDesc, ...);

}
}

#endif
