//
// Project libumf: Unified Anisotropic Volume and Surface Mesh
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#ifndef LIBUMF_OPENGL_GLERROR_H
#define LIBUMF_OPENGL_GLERROR_H

namespace nb {
namespace utils {

void _check_gl_error(const char *file, int line);
void _check_gl_error_abort(const char* stmt, const char* fname, int line);

///
/// Usage
/// [... some opengl calls]
/// glCheckError();
///
#define nbCheckGLError() _check_gl_error(__FILE__,__LINE__)

#ifdef _DEBUG
    #define nbCheckGLErrorAbortFailed(stmt) do { \
            stmt; \
            _check_gl_error_abort(#stmt, __FILE__, __LINE__); \
        } while (0)
#else
    #define nbCheckGLErrorAbortFailed(stmt) stmt
#endif


}
}

#endif // LIBUMF_OPENGL_GLERROR_H


