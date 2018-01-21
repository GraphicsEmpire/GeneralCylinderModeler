#include "catmullromcurverender.h"
#include "catmullromcurve.h"
#include "opengl/glmeshbuffer.h"
#include "opengl/gltransform.h"
#include "opengl/glshader.h"
#include "opengl/glselect.h"

#include <functional>

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
              const char* vert = GLSL(320 core,
                  layout(location = 0) in vec3 in_vertex;
                  uniform mat4 viewMatrix;
                  uniform mat4 projMatrix;

                  void main()
                  {
                      vec4 position = vec4(in_vertex, 1.0);
                      gl_Position = projMatrix * viewMatrix * position;
                      frag_color = in_color;
                  }
              );

              //create a fragment shader
              const char* frag = GLSL(320 core,
                  out vec4 outputF;

                  void main()
                  {
                      outputF = vec4(1,0,0,1);
                  }
              );

              if(!mRenderShader.CompileFromString(vert, frag)) {
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
            vector<GLVertexArray::VertexBufferLayout> vboCtrlPointsLayout;
            if(cdata.CountCtrlPoints() > 0) {

                GLVertexArray::AttributeLayout attr(3, GLVertexArray::vatPosition);
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
                mCtrlPointMeshBufferIsValid &= glFaceBuffer->Import(indices, ftPoints);
            }
        }


        void DrawCtrlPoints(const nb::linalg::mat4 &modelview,
                            const nb::linalg::mat4 &projection) {
            if(!mCtrlPointMeshBufferIsValid)
                return;

            if(!mRenderShader.IsReadyToRun())
                return;

            //run the shader
            mRenderShader.Bind();

            //Set all uniform variables
            {
                int locModelViewMatrix = mRenderShader.GetUniformLocation("viewMatrix");
                glUniformMatrix4fv(locModelViewMatrix, 1, false, modelview.GetConstData());

                int locProjMatrix = mRenderShader.GetUniformLocation("projMatrix");
                glUniformMatrix4fv(locProjMatrix, 1, false, projection.GetConstData());
            }


            mCtrlPointsMeshBuffer.Bind();
            mCtrlPointsMeshBuffer.Unbind();

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
        GLTransform glModelView(GLTransform::mmModelView, modelview);
        GLTransform glProjection(GLTransform::mmProjection, projection);

        //bind
        glProjection.Bind();
        glModelView.Bind();

        if(mDrawCtrlPoints) {
            mImpl->DrawCtrlPoints(modelview, projection);
        }

        if(mDrawCurveProfile) {
            mImpl->DrawCurveProfile();
        }

        glProjection.Unbind();
        glModelView.Unbind();
    }

    void CatmullRomCurveRender::Sync() {

        //syncs the geometry data with opengl mesh buffers
        mImpl->Sync(*mCurveData);

    }

  }
}
