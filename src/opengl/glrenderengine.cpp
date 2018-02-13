#include "glrenderengine.h"
#include "glselect.h"
#include <iostream>

using namespace std;

namespace nb {
    namespace opengl {
        GLRenderEngine::GLRenderEngine() {

        }

        void GLRenderEngine::Init() {

            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            {
                std::cout << "Failed to initialize OpenGL context" << std::endl;
                return;
            }

            glEnable(GL_MULTISAMPLE);
            glEnable(GL_LINE_SMOOTH);
            glEnable(GL_POLYGON_SMOOTH);

            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
            glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
            glEnable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);

        }

        void GLRenderEngine::SetViewPort(int x, int y, int width, int height) {
            glViewport(x, y, width, height);
        }

        void GLRenderEngine::SetClearColor(const nb::linalg::Color &color) {
            nb::linalg::Vec4<float> rgba = color.ToVec4();
            glClearColor(rgba.x, rgba.y, rgba.z, rgba.w);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }


    }
}
