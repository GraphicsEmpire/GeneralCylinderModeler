//
// Project libumf: Unified Anisotropic Volume and Surface Mesh
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#include <string>
#include <iostream>
#include "glerror.h"
#include "glselect.h"

using namespace std;

namespace nb {
namespace utils {

void _check_gl_error(const char *file, int line) {
    GLenum code = reinterpret_cast<GLenum>(glGetError());

    while(code!=GL_NO_ERROR) {
        string error;

        if(code == GL_INVALID_OPERATION) {
            error="INVALID_OPERATION";
        }
        else if(code == GL_INVALID_ENUM) {
            error="INVALID_ENUM";
        }
        else if(code == GL_INVALID_VALUE) {
            error="INVALID_VALUE";
        }
        else if(code == GL_OUT_OF_MEMORY) {
            error="OUT_OF_MEMORY";
        }
        else if(code == GL_INVALID_FRAMEBUFFER_OPERATION) {
            error="INVALID_FRAMEBUFFER_OPERATION";
        }

        cerr << "GL_" << error.c_str() <<" - "<<file<<":"<<line<<endl;
        cout << "ERROR: GL_" << error.c_str() <<" - "<<file<<":"<<line<<endl;
        code=glGetError();
    }
}

void _check_gl_error_abort(const char* stmt, const char* fname, int line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        printf("OpenGL error %08x, at %s:%i - for %s\n", (U32)err, fname, line, stmt);
        abort();
    }
}
}
}
