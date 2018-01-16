#ifndef PATH_H
#define PATH_H

#include <string>
#include <vector>
#include <set>
#include "linalg/base.h"


using namespace std;

namespace nb {
namespace utils {

class Path {
public:
    static string GetExePath();

    static U64 GetFileSize(const string& fpath);
    static U64 FileExists(const string& fpath);

    static bool IsDirectory(const string& path);
    static U32 GetFileNamesInDir(const string& path, vector<string>& filenames);

    static string GetFileExtension(const string& fpath);
    static string GetFileName(const string& fpath);
    static string GetFileDirLocation(const string& fpath);

    static string GetDirectoryParent(const string& fpath);


    static string ChangeFileExtension(const string& fpath, const string& new_extension_no_dots);

    /*!
     * \brief SubtractFromBeginning subtract the base path passed in as second argument from the original path
     * \param left the original path
     * \param right the path to be subtracted
     * \return a new path
     */
    static string SubtractFromBeginning(const string& left, const string& right);

    /*!
     * \brief Split the path into separate parts based on delimiters such as forwards and backward slash
     * \param fpath input file path
     * \param delimiters set of characters used as delimiters
     * \return path parts
     */
    static U32 Split(vector<string>& out_tokens, const std::string& fpath, const std::set<char> delimiters);
    static U32 Split(vector<string>& out_tokens, const std::string& fpath, const std::set<char> delimiters, char& used_delimiter);

    static string Join(const string& left, const string& right);

    static string ToUpper(const string& input);
    static string ToLower(const string& input);
};

}
}
#endif // PATH_H
