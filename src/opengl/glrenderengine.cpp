#include "glrenderengine.h"
#include "glselect.h"
#include <iostream>

using namespace std;

namespace nb {
    namespace opengl {
        GLRenderEngine::GLRenderEngine() {

        }

        void GLRenderEngine::Init() {
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


            glEnable(GL_DEPTH_TEST);

            //set pure black clearcolor
            glClearColor(0.5, 0.5, 0.5, 0.5);
        }

        void GLRenderEngine::PreRender(int x, int y, int width, int height) {
            glViewport(x, y, width, height);
            glClearColor(0.5, 0.5, 0.5, 0.5);
            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_DEPTH_BUFFER_BIT);

        }


    }
}
