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
              //Create the vertex shader
              const char* vert = GLSL(410,
                  layout(location = 0) in vec3 in_vertex;
                  uniform mat4 viewMatrix;
                  uniform mat4 projMatrix;

                  void main()
                  {
                      vec4 position = vec4(in_vertex, 1.0);
                      gl_Position = projMatrix * viewMatrix * position;
                  }
              );

              //create a fragment shader
              const char* frag = GLSL(410,
                  out vec4 outputF;

                  void main()
                  {
                      outputF = vec4(1,0,0,1);
                  }
              );

              if(!mRenderShader.CompileFromString(vert, frag)) {
                  std::cerr << "Unable to compile the shader code" << std::endl;
              }


              //create a triangle
              mTriangleMeshBuffer.Clear();
              GLMeshBuffer::GLVertexArrayPtrType vbo = mTriangleMeshBuffer.AddVertexAttribArray();

              vector<GLVertexArray::VertexBufferLayout> vLayouts;
              {
                  GLVertexArray::AttributeLayout attr(3, GLVertexArray::vatPosition, 0);
                  GLVertexArray::VertexBufferLayout layout;
                  layout.buffer.resize(0);
                  float vertices[9] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
                  unsigned vsize = sizeof(vertices) / sizeof(float);
                  std::copy(&vertices[0], & vertices[vsize], std::back_inserter(layout.buffer));

                  layout.layoutType = GLVertexArray::altSeparate;
                  layout.attributes.push_back(attr);
                  vLayouts.push_back(layout);
              }
              bool result = vbo->Import(3, vLayouts.data(), vLayouts.size());

              GLMeshBuffer::GLFaceArrayPtrType fbo = mTriangleMeshBuffer.AddFaceArray();
              U32 raw_indices [3] = {0, 1, 2};
              vector<U32> indices(raw_indices, raw_indices + 3);
              result &= fbo->Import(indices, ftTriangles);
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
            vector<GLVertexArray::VertexBufferLayout> vboCtrlPointsLayout;
            if(cdata.CountCtrlPoints() > 0) {

                GLVertexArray::AttributeLayout attr(3, GLVertexArray::vatPosition, 0);
                GLVertexArray::VertexBufferLayout layout;
                layout.buffer = cdata.GetCtrlPoints();
                layout.layoutType = GLVertexArray::altSeparate;
                layout.attributes.push_back(attr);
                vboCtrlPointsLayout.push_back(layout);
            }
            mCtrlPointMeshBufferIsValid = vboCtrlPoints->Import(cdata.CountCtrlPoints(), vboCtrlPointsLayout.data(), vboCtrlPointsLayout.size());

            //index buffer for points
            {
                std::vector<U32> indices;
                for(U32 i=0; i < cdata.CountCtrlPoints(); i++) {
                    indices.push_back(i);
                }
                GLMeshBuffer::GLFaceArrayPtrType glFaceBuffer = mCtrlPointsMeshBuffer.AddFaceArray();
                mCtrlPointMeshBufferIsValid &= glFaceBuffer->Import(indices, ftLineStrip);
            }
        }


        void DrawCtrlPoints(const nb::linalg::mat4 &modelview,
                            const nb::linalg::mat4 &projection) {
//            if(!mCtrlPointMeshBufferIsValid)
//                return;

            if(!mRenderShader.IsReadyToRun())
                return;

            glPointSize(5.0);

            //run the shader
            mRenderShader.Bind();

            //Set all uniform variables
            {
                int locModelViewMatrix = mRenderShader.GetUniformLocation("viewMatrix");
                glUniformMatrix4fv(locModelViewMatrix, 1, false, modelview.GetConstData());

                int locProjMatrix = mRenderShader.GetUniformLocation("projMatrix");
                glUniformMatrix4fv(locProjMatrix, 1, false, projection.GetConstData());
            }

            //
//            mCtrlPointsMeshBuffer.Bind();
//            mCtrlPointsMeshBuffer.Unbind();
            mTriangleMeshBuffer.Bind();
            mTriangleMeshBuffer.Unbind();

            mRenderShader.Unbind();
        }

        void DrawCurveProfile() {
            mCurveProfileMeshBuffer.Bind();
            mCurveProfileMeshBuffer.Unbind();
        }
    protected:
        GLShader mRenderShader;
        GLMeshBuffer mCtrlPointsMeshBuffer;
        GLMeshBuffer mCurveProfileMeshBuffer;
        GLMeshBuffer mTriangleMeshBuffer;
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
        //mImpl->Sync(*mCurveData);

    }

  }
}
