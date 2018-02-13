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
        CatmullRomCurveRenderImpl() : mCtrlPointMeshBufferIsValid(false) {
            //=======================================================
            //create the vertex shader
            const char *vert = GLSL(410,
                                    layout(location = 0)
                                    in vec3 in_vertex;
                                    uniform mat4 ViewMatrix;
                                    uniform mat4 ProjMatrix;
                                    void main() {
                                        vec4 position = vec4(in_vertex, 1.0);
                                        gl_Position = ProjMatrix * ViewMatrix * position;
                                    }
            );

            //create the fragment shader for ctrl points
            const char *frag_ctrlpoints = GLSL(410,
                out vec4 outputF;
                void main() {
                   outputF = vec4(1, 0, 0, 1);
                }
            );

            //create the fragment shader for curve profile
            const char *frag_curveprofile = GLSL(410,
                out vec4 outputF;
                void main() {
                    outputF = vec4(0, 0, 1, 1);
                }
            );

            if (!mCtrlPointsShader.CompileFromString(vert, frag_ctrlpoints)) {
                std::cerr << "Unable to compile the shader code" << std::endl;
            }

            if (!mCurveProfileShader.CompileFromString(vert, frag_curveprofile)) {
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
            mCtrlPointMeshBufferIsValid = false;

            if(cdata.CountCtrlPoints() > 0) {
                GLMeshBuffer::GLVertexArrayPtrType vboCtrlPoints = mCtrlPointsMeshBuffer.AddVertexAttribArray();

                //positions
                std::vector<GLVertexArray::GLVertexAttribute> attr = {
                        GLVertexArray::GLVertexAttribute(GLVertexAttributeIndex::kPosition, 3)
                };
                mCtrlPointMeshBufferIsValid = vboCtrlPoints->Import(attr, cdata.GetCtrlPoints());

                //index buffer for points
                {
                    std::vector<U32> indices(cdata.CountCtrlPoints());
                    for (U32 i = 0; i < cdata.CountCtrlPoints(); i++) {
                        indices[i] = i;
                    }
                    GLMeshBuffer::GLFaceArrayPtrType glFaceBuffer = mCtrlPointsMeshBuffer.AddFaceArray();
                    mCtrlPointMeshBufferIsValid &= glFaceBuffer->Import(indices, kPoints);
                }
            }

            //sync curve profile
            mCurveProfileMeshBuffer.Clear();
            mCurveProfileMeshBufferIsValid = false;

            if(cdata.CountSplines() > 0) {
                GLMeshBuffer::GLVertexArrayPtrType vboCurveProfile = mCurveProfileMeshBuffer.AddVertexAttribArray();

                //positions
                std::vector<GLVertexArray::GLVertexAttribute> attribs = {
                        GLVertexArray::GLVertexAttribute(GLVertexAttributeIndex::kPosition, 3),
//                        GLVertexArray::GLVertexAttribute(GLVertexAttributeIndex::kNormal, 3),
//                        GLVertexArray::GLVertexAttribute(GLVertexAttributeIndex::kWeight, 3),
                };

                vector<float> vpos = cdata.GetCurveProfilePoints();
                vector<float> vtan = cdata.GetCurveProfileTangents();
                vector<float> vacc = cdata.GetCurveProfileAcceleration();

                vector<float> combined_cdata;
                combined_cdata.insert(combined_cdata.end(), vpos.begin(), vpos.end());
//                combined_cdata.insert(combined_cdata.end(), vtan.begin(), vtan.end());
//                combined_cdata.insert(combined_cdata.end(), vacc.begin(), vacc.end());
                U64 sz = combined_cdata.size();

                mCurveProfileMeshBufferIsValid = vboCurveProfile->Import(attribs, combined_cdata, kSequentialBatch);

                //index buffer for points
                {
                    std::vector<U32> indices(cdata.CountCurveProfilePoints());
                    for (U32 i = 0; i < cdata.CountCurveProfilePoints(); i++) {
                        indices[i] = i;
                    }
                    GLMeshBuffer::GLFaceArrayPtrType glFaceBuffer = mCurveProfileMeshBuffer.AddFaceArray();
                    mCurveProfileMeshBufferIsValid &= glFaceBuffer->Import(indices, kLineStrip);
                }
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

        void DrawCurveProfile(const nb::linalg::mat4 &modelview,
                              const nb::linalg::mat4 &projection) {
            if(!mCurveProfileMeshBufferIsValid)
                return;

            if(!mCurveProfileShader.IsReadyToRun())
                return;

            //run the shader
            mCurveProfileShader.Bind();

            //Set all uniform variables
            {
                int locModelViewMatrix = mCtrlPointsShader.GetUniformLocation("ViewMatrix");
                glUniformMatrix4fv(locModelViewMatrix, 1, false, modelview.GetConstData());

                int locProjMatrix = mCtrlPointsShader.GetUniformLocation("ProjMatrix");
                glUniformMatrix4fv(locProjMatrix, 1, false, projection.GetConstData());
            }

            //draw curve profile
            mCurveProfileMeshBuffer.Bind();
            mCurveProfileMeshBuffer.Unbind();

            mCurveProfileShader.Unbind();

        }
    protected:
        GLShader mCtrlPointsShader;
        GLShader mCurveProfileShader;
        GLMeshBuffer mCtrlPointsMeshBuffer;
        GLMeshBuffer mCurveProfileMeshBuffer;
        bool mCtrlPointMeshBufferIsValid;
        bool mCurveProfileMeshBufferIsValid;
    };

    /////////////////////////////////////////////////
    CatmullRomCurveRender::CatmullRomCurveRender(const std::shared_ptr<CatmullRomCurve> &cdata):
        mCurveData(cdata), mDrawCtrlPoints(true), mDrawCurveProfile(true)
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
            mImpl->DrawCurveProfile(modelview, projection);
        }
    }

    void CatmullRomCurveRender::Sync() {

        //syncs the geometry data with opengl mesh buffers
        mImpl->Sync(*mCurveData);

    }

  }
}
