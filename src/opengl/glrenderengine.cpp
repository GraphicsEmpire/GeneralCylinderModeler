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
            /*
            glbinding::Binding::initialize(false);

            glbinding::setAfterCallback([](const glbinding::FunctionCall &)
                                        {
                                            gl::GLenum error = glGetError();
                                            if (error != GL_NO_ERROR)
                                                std::cout << "error: " << error << std::endl;
                                        });

            std::cout << std::endl
                    << "OpenGL Version:  " << glbinding::ContextInfo::version() << std::endl
                    << "OpenGL Vendor:   " << glbinding::ContextInfo::vendor() << std::endl
                    << "OpenGL Renderer: " << glbinding::ContextInfo::renderer() << std::endl;
            */

            glEnable(GL_MULTISAMPLE);
            glEnable(GL_LINE_SMOOTH);
            glEnable(GL_POLYGON_SMOOTH);

            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
            glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
            glEnable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);

        }

        void GLRenderEngine::PreRender(int x, int y, int width, int height) {
            glViewport(x, y, width, height);
            glClearColor(1.0, 1.0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }


    }
}
