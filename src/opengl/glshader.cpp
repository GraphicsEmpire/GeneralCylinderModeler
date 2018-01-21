#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include "glshader.h"
#include "glselect.h"

#include "utils/path.h"
#include "utils/logger.h"

using namespace nb::utils;


namespace nb {
namespace opengl {


GLShader::GLShader()
{
    Init();
}

GLShader::GLShader(const char* pszVertexShader, const char* pszFragmentShader, const char* pszGeometryShader)
{
    Init();
    CompileFromString(pszVertexShader, pszFragmentShader);
}

GLShader::~GLShader()
{
    Cleanup();
}


void GLShader::Init()
{
    mCompiled = false;
    mRunning = false;
    mGLShaderProgram = 0;
    mVertexShaderFilePath = "inline";
    mFragmentShaderFilePath = "inline";
    mGeometryShaderFilePath = "inline";
}

void GLShader::Cleanup()
{
    if(glIsProgram(mGLShaderProgram))
        glDeleteProgram(mGLShaderProgram);
    mCompiled = false;
}

int GLShader::GetUniformLocation(const char *chrUniformName) {
    int location = glGetUniformLocation(mGLShaderProgram, chrUniformName);
    if(location < 0) {
        nbLogError("Invalid uniform variable name = [%s]", chrUniformName);
    }

    return location;
}


//Reads the shader code from file and compiles
int GLShader::CompileFromSourceFiles(const string &strVertexShaderFP, const string &strFragmentShaderFP)
{
    if((strVertexShaderFP.length() == 0)||(strFragmentShaderFP.length() == 0))
        return ERR_SHADER_FILE_NOT_FOUND;

    string strVShaderCode;
    string strFShaderCode;

    mVertexShaderFilePath = strVertexShaderFP;
    mFragmentShaderFilePath = strFragmentShaderFP;

    //ReadImageFile both files
    bool bres = ReadShaderCode(strVertexShaderFP, strVShaderCode);
    if(!bres) return ERR_SHADER_FILE_NOT_FOUND;
    bres = ReadShaderCode(strFragmentShaderFP, strFShaderCode);
    if(!bres) return ERR_SHADER_FILE_NOT_FOUND;

    return CompileFromString(strVShaderCode.c_str(), strFShaderCode.c_str());
}

int	 GLShader::CompileFromSourceFiles(const string &strVertexShaderFP, const string &strFragmentShaderFP,
                                         const string &strGeometryShaderFP) {
    if((strVertexShaderFP.length() == 0)||(strFragmentShaderFP.length() == 0)||
            (strGeometryShaderFP.length() == 0))
        return ERR_SHADER_FILE_NOT_FOUND;

    string strVShaderCode;
    string strFShaderCode;
    string strGShaderCode;

    //file path
    mVertexShaderFilePath = strVertexShaderFP;
    mFragmentShaderFilePath = strFragmentShaderFP;
    mGeometryShaderFilePath = strGeometryShaderFP;

    //ReadImageFile both files
    bool bres = ReadShaderCode(strVertexShaderFP, strVShaderCode);
    if(!bres) return ERR_SHADER_FILE_NOT_FOUND;

    bres = ReadShaderCode(strFragmentShaderFP, strFShaderCode);
    if(!bres) return ERR_SHADER_FILE_NOT_FOUND;

    bool isValidGShader = false;
    bres = ReadShaderCode(strGeometryShaderFP, strGShaderCode);
    if(bres && strGShaderCode.length() > 0)
        isValidGShader = true;

    return CompileFromString(strVShaderCode.c_str(), strFShaderCode.c_str(),
                             isValidGShader ? strGShaderCode.c_str() : NULL);
}

void GLShader::ReportShaderCompileErrors(U32 uShaderName, const string &shadertype, const string &filepath) {

    int i32InfoLogLength, i32CharsWritten;
    glGetShaderiv(uShaderName, GL_INFO_LOG_LENGTH, &i32InfoLogLength);

    char* pszInfoLog = new char[i32InfoLogLength];
    glGetShaderInfoLog(uShaderName, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
    char* pszMsg = new char[i32InfoLogLength+256];

    nbLogError("Failed to compile [%s] shader: [%s]", shadertype.c_str(), filepath.c_str());
    nbLogError("Compile log info [%s]", pszInfoLog);

    SAFE_DELETE_ARRAY(pszMsg);
    SAFE_DELETE_ARRAY(pszInfoLog);
}

//////////////////////////////////////////////////////////////////////////
int GLShader::CompileFromString(const char *vShaderCode, const char *vFragmentCode, const char *vGeometryCode)
{
    Cleanup();

    GLint isCompiled;

    //Vertex Shader
    U32 uiVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(uiVertexShader, 1, (const char**)&vShaderCode, NULL);
    glCompileShader(uiVertexShader);

    //Check if compilation succeeded
    glGetShaderiv(uiVertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled) {
        ReportShaderCompileErrors(uiVertexShader, "vertex", Path::GetFileName(mVertexShaderFilePath));
        return false;
    }

    //Fragment Shader
    U32 uiFragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(uiFragShader, 1, (const char**)&vFragmentCode, NULL);
    glCompileShader(uiFragShader);

    //Check if compilation succeeded
    glGetShaderiv(uiFragShader, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled) {
        ReportShaderCompileErrors(uiFragShader, "fragment", Path::GetFileName(mFragmentShaderFilePath));
    }

    //Geometry Shader
    U32 uiGeometryShader;
    if(vGeometryCode) {
        uiGeometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(uiGeometryShader, 1, (const char**)&vGeometryCode, NULL);
        glCompileShader(uiGeometryShader);

        //Check if compilation succeeded
        glGetShaderiv(uiGeometryShader, GL_COMPILE_STATUS, &isCompiled);
        if (!isCompiled) {
            ReportShaderCompileErrors(uiGeometryShader, "geometry", Path::GetFileName(mGeometryShaderFilePath));
        }
    }

    // Create the shader program
    mGLShaderProgram = glCreateProgram();

    //Attach all shaders
    glAttachShader(mGLShaderProgram, uiVertexShader);
    glAttachShader(mGLShaderProgram, uiFragShader);
    if(vGeometryCode)
        glAttachShader(mGLShaderProgram, uiGeometryShader);

    // Link the program
    glLinkProgram(mGLShaderProgram);

    // Check if linking succeeded in the same way we checked for compilation success
    GLint isLinked;
    glGetProgramiv(mGLShaderProgram, GL_LINK_STATUS, &isLinked);

    if (!isLinked)
    {
        int i32InfoLogLength, i32CharsWritten;
        glGetProgramiv(mGLShaderProgram, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
        char* pszInfoLog = new char[i32InfoLogLength];
        glGetProgramInfoLog(mGLShaderProgram, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
        nbLogError("Failed to link program. Linker log [%s]", pszInfoLog);

        SAFE_DELETE_ARRAY(pszInfoLog);
        return false;
    }
    mCompiled = true;
    return true;
}

void GLShader::Bind()
{
    if(!IsReadyToRun()) {
        nbLogError("Shader is not compiled yet!");
        return;
    }
    //Run program
    glUseProgram(mGLShaderProgram);
    mRunning = true;
}

void GLShader::Unbind()
{
    glUseProgram(0);
    mRunning = false;
}

bool GLShader::RemoveAllCppComments(string &shadercode)
{
    string strOutput;

    char ch1, ch2;
    bool bAppend = true;
    bool isSingleLineComment = false;

    std::replace(shadercode.begin(), shadercode.end(), '\t', ' ');
    U32 i=0;
    while(i < (shadercode.length() - 1))
    {
        ch1 = shadercode[i];
        ch2 = shadercode[i+1];
        if((ch1 == '/')&&(ch2 == '/'))
        {
            //Line Comment
            bAppend = false;
            isSingleLineComment = true;
        }
        else if((ch1 == '/')&&(ch2 == '*'))
        {
            bAppend = false;
            isSingleLineComment = false;
        }


        if(bAppend)
        {
            strOutput += ch1;
            if(i == shadercode.length() - 2)
                strOutput += ch2;
        }
        else
        {
            if(isSingleLineComment)
            {
                if((ch1 == '\r')&&(ch2 == '\n'))
                {
                    bAppend = true;
                    i++;
                }
            }
            else
            {
                if((ch1 == '*')&&(ch2 == '/'))
                {
                    bAppend = true;
                    i++;
                }
            }
        }

        i++;
    }//End While

    shadercode = strOutput;

    return true;
}



bool GLShader::ReadShaderCode(const string &strFilePath, string &strCode)
{
    std::ifstream fp;
    fp.open(strFilePath.c_str(), std::ios::binary);
    if(!fp.is_open())
        return false;

    size_t size;
    fp.seekg(0, std::ios::end);
    size = fp.tellg();
    fp.seekg(0, std::ios::beg);

    char * buf = new char[size+1];
    //ReadImageFile file content
    fp.read(buf, size);
    buf[size] = '\0';

    strCode = string(buf);
    SAFE_DELETE_ARRAY(buf);
    fp.close();

    return true;
}

bool GLShader::IsReadyToRun()
{
    return (mCompiled && (glIsProgram(mGLShaderProgram) == GL_TRUE));
}


bool GLShader::IsBinaryShaderSupported() {
    return false;
}

bool GLShader::IsGLExtensionSupported(const char *extension)
{
    // The recommended technique for querying OpenGL extensions;
    // from http://opengl.org/resources/features/OGLextensions/
    const GLubyte *extensions = NULL;
    const GLubyte *start;
    GLubyte *where, *terminator;

    // Extension names should not have spaces.
    where = (GLubyte *) strchr(extension, ' ');
    if (where || *extension == '\0')
        return 0;

    extensions = glGetString(GL_EXTENSIONS);

    // It takes a bit of care to be fool-proof about parsing the
    // OpenGL extensions string. Don't be fooled by sub-strings, etc.
    start = extensions;
    for (;;) {
        where = (GLubyte *) strstr((const char *) start, extension);
        if (!where)
            break;
        terminator = where + strlen(extension);
        if (where == start || *(where - 1) == ' ')
            if (*terminator == ' ' || *terminator == '\0')
                return true;
        start = terminator;
    }

    return false;
}

#ifdef SAVE_LOAD_BINARY_SHADER
/*!****************************************************************************
         @Function		saveBinaryProgram
         @Return		bool	True if save succeeded.
         @Description	This function takes as input the ID of a shader program object
         which should have been created prior to calling this function,
         as well as a filename to save the binary program to.
         The function will save out a file storing the binary shader
         program, and the enum value determining its format.
         ******************************************************************************/
bool GLShader::saveBinaryProgram(const char* Filename, GLuint &ProgramObjectID)
{
#if !defined (TARGET_OS_IPHONE)
    //Quick check to make sure that the program actually exists.
    GLint linked;
    glGetProgramiv(ProgramObjectID, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        //Shaders not linked correctly, no binary to retrieve.
        return false;
    }

    // Get the length of the shader binary program in memory.
    // Doing this ensures that a sufficient amount of memory is allocated for storing the binary program you retrieve.
    GLsizei length=0;
    glGetProgramiv(ProgramObjectID,GL_PROGRAM_BINARY_LENGTH_OES,&length);

    // Pointer to the binary shader program in memory, needs to be allocated with the right size.
    GLvoid* ShaderBinary = (GLvoid*)malloc(length);

    // The format that the binary is retreived in.
    GLenum binaryFormat=0;

    // Error checking variable - this should be greater than 0 after glGetProgramBinaryOES, otherwise there was an error.
    GLsizei lengthWritten=0;

    // Get the program binary from GL and save it out.
    glGetProgramBinaryOES(ProgramObjectID,length,&lengthWritten,&binaryFormat,ShaderBinary);
    if (!lengthWritten)
    {
        // Save failed. Insufficient memory allocated to write binary shader.
        return false;
    }

    // Cache the program binary for future runs
    FILE* outfile = fopen(Filename, "wb");

    if(!outfile)
    {
        printf("Failed to open %s for writing to.\n", Filename);
        return false;
    }

    // Save the binary format.
    if(!fwrite((void*)&binaryFormat,sizeof(GLenum),1,outfile)) {
        nbLogError("Couldnot write binary data to file.");
        fclose(outfile);
        return false;
    }

    // Save the actual binary program.
    if(!fwrite(ShaderBinary, length,1,outfile)) {
        nbLogError("Couldnot write binary data to file.");
        fclose(outfile);
        return false;
    }

    // Close the file.
    fclose(outfile);

    // Free the memory used by Shader Binary.
    free(ShaderBinary);
    return true;
#else
    return false;
#endif
}


/*!****************************************************************************
         @Function		loadBinaryProgram
         @Return		bool	True if load succeeded.
         @Description	This function takes as input the ID of a shader program object
         which should have been created prior to calling this function,
         as well as a filename to load the binary program from.
         The function will load in a file storing the binary shader
         program, and the enum value determining its format.
         It will then load the binary into memory.

         @Note:			This function is not able to check if the shaders have changed.
         If you change the shaders then the file this saves out either
         needs to be deleted	or a new file used.
         ******************************************************************************/
bool GLShader::loadBinaryProgram(const char* Filename, GLuint &ProgramObjectID)
{
#if !defined (TARGET_OS_IPHONE)
    // Open the file.
    FILE* infile = fopen(Filename, "rb");

    // File open failed, either doesn't exist or is empty.
    if (!infile) return false;

    // Find initialise the shader binary.
    fseek(infile, 0, SEEK_END);
    GLsizei length = (GLint)ftell(infile)-sizeof(GLenum);

    // File appears empty.
    if (!length) {
        fclose(infile);
        nbLogError("Shader binary file [%s] is empty", Filename);

        return false;
    }

    // Allocate a buffer large enough to store the binary program.
    GLvoid* ShaderBinary = (GLvoid*)malloc(length);

    // Read in the binary format
    GLenum format=0;
    fseek(infile, 0, SEEK_SET);
    fread(&format, sizeof(GLenum), 1, infile);

    // ReadImageFile in the program binary.
    fread(ShaderBinary, length, 1, infile);
    fclose(infile);

    // Create an empty shader program
    ProgramObjectID = glCreateProgram();

    // Load the binary into the program object -- no need to link!
    glProgramBinaryOES(ProgramObjectID, format, ShaderBinary, length);

    // Delete the binary program from memory.
    free(ShaderBinary);

    // Check that the program was loaded correctly, uses the same checks as when linking with a standard shader.
    GLint loaded;
    glGetProgramiv(ProgramObjectID, GL_LINK_STATUS, &loaded);
    if (!loaded)
    {
        // Something must have changed. Need to recompile shaders.
        int i32InfoLogLength, i32CharsWritten;
        glGetProgramiv(ProgramObjectID, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
        char* pszInfoLog = new char[i32InfoLogLength];
        glGetProgramInfoLog(ProgramObjectID, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
        char* pszMsg = new char[i32InfoLogLength+256];
        strcpy(pszMsg, "Failed to load binary program: ");
        strcat(pszMsg, pszInfoLog);
        printf(pszMsg);

        delete [] pszMsg;
        delete [] pszInfoLog;
        return false;
    }
    return true;
#else
    return false;
#endif
}
#endif

}
}
