//
// Project gencylinder
//
// Created on   : Aug 24, 2017
// Last Updated : Jan 01, 2018
// Author       : Pourya Shirazian <pourya.shirazian@intusurg.com>
//
//----------------------------------------------------------------------------------
//

#include "catmullromcurverender.h"
#include "catmullromcurve.h"
#include "opengl/glmeshbuffer.h"
#include "opengl/glshader.h"
#include "opengl/glselect.h"

#include <functional>
#include <algorithm>
#include <iterator>

using namespace std;
using namespace nb::opengl;

namespace nb {
  namespace render {

    /*!
    * Implementation of the renderer
    */
    class CatmullRomCurveRenderImpl {
    public:
        CatmullRomCurveRenderImpl():mCtrlPointMeshBufferIsValid(false) {
            //=======================================================
              //create the vertex shader
              const char* vert = GLSL(410,
                  layout(location = 0) in vec3 in_vertex;
                  uniform mat4 ViewMatrix;
                  uniform mat4 ProjMatrix;

                  void main()
                  {
                      vec4 position = vec4(in_vertex, 1.0);
                      gl_Position = ProjMatrix * ViewMatrix * position;
                  }
              );

              //create the fragment shader
              const char* frag = GLSL(410,
                  out vec4 outputF;

                  void main()
                  {
                      outputF = vec4(1,0,0,1);
                  }
              );

              if(!mCtrlPointsShader.CompileFromString(vert, frag)) {
                  std::cerr << "Unable to compile the shader code" << std::endl;
              }
        }

        virtual ~CatmullRomCurveRenderImpl() {
            mCtrlPointsMeshBuffer.Clear();
            mCurveProfileMeshBuffer.Clear();
        }

        /*!
         * \brief Sync mesh buffer from the geometry data
         * \param cdata reference of geometry data
         */
        void Sync(CatmullRomCurve& cdata) {

            //sync ctrl points
            mCtrlPointsMeshBuffer.Clear();
            GLMeshBuffer::GLVertexArrayPtrType vboCtrlPoints = mCtrlPointsMeshBuffer.AddVertexAttribArray();

            //positions
            std::vector<GLVertexArray::GLVertexAttribute> attr = {
                    GLVertexArray::GLVertexAttribute(GLVertexAttributeIndex::kPosition, 3)
            };
            mCtrlPointMeshBufferIsValid = vboCtrlPoints->Import(attr, cdata.GetCtrlPoints());

            //index buffer for points
            {
                std::vector<U32> indices;
                for(U32 i=0; i < cdata.CountCtrlPoints(); i++) {
                    indices.push_back(i);
                }
                GLMeshBuffer::GLFaceArrayPtrType glFaceBuffer = mCtrlPointsMeshBuffer.AddFaceArray();
                mCtrlPointMeshBufferIsValid &= glFaceBuffer->Import(indices, kLineStrip);
            }
        }

        void DrawCtrlPoints(const nb::linalg::mat4 &modelview,
                            const nb::linalg::mat4 &projection) {
            if(!mCtrlPointMeshBufferIsValid)
                return;

            if(!mCtrlPointsShader.IsReadyToRun())
                return;

            glPointSize(5.0);

            //run the shader
            mCtrlPointsShader.Bind();

            //Set all uniform variables
            {
                int locModelViewMatrix = mCtrlPointsShader.GetUniformLocation("ViewMatrix");
                glUniformMatrix4fv(locModelViewMatrix, 1, false, modelview.GetConstData());

                int locProjMatrix = mCtrlPointsShader.GetUniformLocation("ProjMatrix");
                glUniformMatrix4fv(locProjMatrix, 1, false, projection.GetConstData());
            }

            //
            mCtrlPointsMeshBuffer.Bind();
            mCtrlPointsMeshBuffer.Unbind();

            mCtrlPointsShader.Unbind();
        }

        void DrawCurveProfile() {
            mCurveProfileMeshBuffer.Bind();
            mCurveProfileMeshBuffer.Unbind();
        }
    protected:
        GLShader mCtrlPointsShader;
        GLMeshBuffer mCtrlPointsMeshBuffer;
        GLMeshBuffer mCurveProfileMeshBuffer;
        bool mCtrlPointMeshBufferIsValid;
    };

    /////////////////////////////////////////////////
    CatmullRomCurveRender::CatmullRomCurveRender(const std::shared_ptr<CatmullRomCurve> &cdata):
        mCurveData(cdata), mDrawCtrlPoints(true), mDrawCurveProfile(false)
    {
        mImpl.reset(new CatmullRomCurveRenderImpl());

        //register callback to call sync function automatically
        auto f = std::bind(&CatmullRomCurveRender::Sync, this);
        mCurveData->RegisterOnCurveDataChangedCallBack(f);
    }

    CatmullRomCurveRender::~CatmullRomCurveRender()
    {

    }

    void CatmullRomCurveRender::Render(const nb::linalg::mat4 &modelview,
                                       const nb::linalg::mat4 &projection)
    {
        if(mDrawCtrlPoints) {
            mImpl->DrawCtrlPoints(modelview, projection);
        }

        if(mDrawCurveProfile) {
            mImpl->DrawCurveProfile();
        }
    }

    void CatmullRomCurveRender::Sync() {

        //syncs the geometry data with opengl mesh buffers
        mImpl->Sync(*mCurveData);

    }

  }
}
