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
            /*
            std::cout << std::endl
                    << "OpenGL Version:  " << glbinding::ContextInfo::version() << std::endl
                    << "OpenGL Vendor:   " << glbinding::ContextInfo::vendor() << std::endl
                    << "OpenGL Renderer: " << glbinding::ContextInfo::renderer() << std::endl;
            */

            //Init gl features
            static const GLfloat lightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
            static const GLfloat lightPos[4] = { 0.0f, 9.0f, 0.0f, 1.0f };

            //Setup shading environment
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);

            //setup default light position and color
            glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
            glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
            glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

            //Smoothing effects
            glShadeModel(GL_SMOOTH);
            glEnable(GL_MULTISAMPLE);
            glEnable(GL_LINE_SMOOTH);
            glEnable(GL_POLYGON_SMOOTH);

            glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
            glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
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
