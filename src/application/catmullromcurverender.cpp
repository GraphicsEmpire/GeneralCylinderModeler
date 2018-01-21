#include "catmullromcurverender.h"
#include "catmullromcurve.h"
#include "opengl/glmeshbuffer.h"
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


        void DrawCtrlPoints() {
            if(!mCtrlPointMeshBufferIsValid)
                return;

            mCtrlPointsMeshBuffer.Bind();
            mCtrlPointsMeshBuffer.Unbind();
        }

        void DrawCurveProfile() {
            mCurveProfileMeshBuffer.Bind();
            mCurveProfileMeshBuffer.Unbind();
        }
    protected:
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
            mImpl->DrawCtrlPoints();
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
