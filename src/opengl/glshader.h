#pragma once
#ifndef GLSHADER_H
#define GLSHADER_H

#include <vector>
#include "linalg/vec.h"
#include "utils/bindableinterface.h"

using namespace nb::linalg;

#define GL_SUCCESS		   1
#define ERR_SHADER_FILE_NOT_FOUND -1
#define ERR_SHADER_COMPILE_ERROR  -2
#define ERR_SHADER_LINK_ERROR	  -3

namespace nb {
    namespace opengl {
        
        #define GLSL(version, shader)  "#version " #version "\n" #shader

        //An OpenGL shader program
        class GLShader : public nb::utils::BindableInterface
        {
        public:
            GLShader();
            GLShader(const char* pszVertexShader, const char* pszFragmentShader, const char* pszGeometryShader = NULL);
            virtual ~GLShader();
            
            enum ShaderType {stVertex = 0, stFragment = 1, stGeometry = 2};
                        
            //After analysis is done we fetch the locations of uniforms
            int  GetUniformLocation(const char *chrUniformName);
            
            //After analysis is done user can get the location where attribs set Automatically
            int  GetAttribLocation(const char *chrAttribName);
            bool    SetAttribLocation(const char *chrAttribName, int idxLoc);
            
            U32  GetProgram() const { return mGLShaderProgram;}
            
            //Status
            bool IsCompiled() const {return mCompiled;}
            bool IsRunning() const {return mRunning;}
            bool IsReadyToRun();
            
            
            int	 CompileFromSourceFiles(const string &strVertexShaderFP, const string &strFragmentShaderFP);
            
            int	 CompileFromSourceFiles(const string &strVertexShaderFP, const string &strFragmentShaderFP,
                                           const string &strGeometryShaderFP);
            
            
            /*
             * Compiles shader code and performs an analysis on the number variables defined.
             * Reports compile and link errors. This function attaches all attribute variables to
             * their locations based on their position in the list (i.e. First Found first position)
             * All Found attributes are added to attributes list and all uniforms are being put in the
             * uniforms list.
             * @param vShaderCode string containing Vertex Shader code.
             * @param vFragmentCode string containing Fragment Shader code.
             * @return 1 if successfully compile and link the shader program
             */
            int  CompileFromString(const char *vShaderCode, const char *vFragmentCode, const char *vGeometryCode = NULL);
            
            //Load and Save Binary Shaders
            static bool IsBinaryShaderSupported();
            static bool IsGLExtensionSupported(const char *extension);
            
            bool LoadBinaryProgram(const char *Filename, U32 &ProgramObjectID);
            bool SaveBinaryProgram(const char *Filename, U32 &ProgramObjectID);
            
            //Program run
            void Bind() override;
            
            //Program stop
            void Unbind() override;
            
        protected:
            void Init();
            void Cleanup();

            void ReportShaderCompileErrors(U32 uShaderName, const string &shadertype, const string &filepath);
            bool RemoveAllCppComments(string &strCode);
            bool ReadShaderCode(const string &strFilePath, string &strCode);
            
        protected:
            U32   mGLShaderProgram;
            bool  mCompiled;
            bool  mRunning;

            string mVertexShaderFilePath;
            string mFragmentShaderFilePath;
            string mGeometryShaderFilePath;
        };
        
    }
}
#endif


