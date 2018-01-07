#ifndef MATRIX_H
#define MATRIX_H

#include <string.h>
#include <iostream>
#include <sstream>
#include "vec.h"
#include "quat.h"

namespace nb {
namespace linalg {

/*!
 * \brief A 4x4 Column-Major matrix that can be directly used with the OpenGL pipeline.
 * Refer to the associated unit-test to explore various use cases.
 */
template <typename T>
class Matrix4x4
{
protected:
    static const int mElementsCount = 16;
    static const int mRowElementsCount = 4;
    static const int mColElementsCount = 4;

public:
    Matrix4x4() { SetIdentity();}
    Matrix4x4(const Matrix4x4& rhs){
        this->CopyFrom(rhs);
    }

    /*!
     * \brief Create a column major matrix based on the values passed in.
     * \param values define elements of the matrix in column major format
     */
    explicit Matrix4x4(const T values[mElementsCount]){
        CopyFromColMajor(values);
    }

    virtual ~Matrix4x4() {}

    //Basic Ops
    int GetElementsCount() const {return mElementsCount;}
    void CopyFrom(const Matrix4x4 &rhs);

    /*!
     * \brief CopyFromColMajor assign elements from a column major matrix. This function essentially does a mem-copy
     * \param values in column major format
     */
    void CopyFromColMajor(const T *values);

    /*!
     * \brief copyFromRowMajor performs a gather operation from a row major array into the column major format.
     * \param values in row major format
     */
    void CopyFromRowMajor(const T *values);

    /*!
     * \brief GetElements assign elements to an output array in Col-Major. This function essentially does a mem-copy
     * \param values in column major format
     */
    void GetElements(T values[mElementsCount]);


    void Print() const;

    void FillZero();
    void SetIdentity();

    //Access to rows and cols and elements
    Vec4<T> GetRow(int iRow) const;
    void SetRow(int iRow, const Vec4<T> &row);

    Vec4<T> GetCol(int iCol) const;
    void SetCol(int iCol, const Vec4<T> &cold);

    Vec4<T> GetDiagonal() const;
    void SetDiagonal(const Vec4<T> &diag);

    Matrix4x4<T> GetSubMatrix(int ki, int kj) const;

    T GetElement(int iRow, int iCol) const;
    void SetElement(int iRow, int iCol, T v);
    const T* GetConstData() const {return &mElems[0][0];}
    T* GetData() {return &mElems[0][0];}

    //Transpose and Invert
    void Transpose();
    Matrix4x4<T> GetTransposed() const;

    //Invert
    Matrix4x4<T> GetInverted(int *lpIsInvertible = 0) const;
    Matrix4x4<T> GetInvertTransposed() const;
    T Determinant() const;
    T Trace() const;

    //Transformations
    Vec4<T> TransformPoint(const Vec4<T> &v) const;
    Vec3<T> TransformPoint(const Vec3<T> &v) const;
    void Scale(const Vec3<T> &s);
    void Rotate(const Quaternion<T> &q);
    void Rotate(const Vec3<T> &axis, T deg);
    void Translate(const Vec3<T> &t);

    //affine getters
    Vec3<T> GetTranslateVector() const;
    Vec3<T> GetScaleVector() const;


    //Conditionals
    bool IsIdentity() const;
    bool IsDiagonal() const;
    bool IsSymmetric() const;
    bool IsAntiSymmetric() const;
    bool IsOrthogonal() const;

    //3D Projection Matrices
    void Ortho(T left, T right, T bottom, T top, T nearPlane, T farPlane);
    void Frustum(T left, T right, T bottom, T top, T nearPlane, T farPlane);
    void Perspective(T angle, T aspect, T nearPlane, T farPlane);
    void LookAt(const Vec3<T> &eye, const Vec3<T> &center, const Vec3<T> &up);


    //Static Ops
    static inline bool IsEqual(const Matrix4x4 &a, const Matrix4x4 &b);
    static inline Matrix4x4 Mul(const Matrix4x4 &a, const Matrix4x4 &b);
    static inline Matrix4x4 Mul(const Matrix4x4 &a, T s);

    static inline Matrix4x4 InnerProduct(const Matrix4x4 &a, const Matrix4x4 &b);
    static inline T GetFrobeniousNorm(const Matrix4x4 &a, const Matrix4x4 &b);

    static inline Matrix4x4 Add(const Matrix4x4 &a, const Matrix4x4 &b);
    static inline Matrix4x4 Sub(const Matrix4x4 &a, const Matrix4x4 &b);

    //Quaternions
    //Convert from quaternion to a rotation matrix and vice versa
    static Quaternion<T> GetQuaternionFromMatrix(const Matrix4x4 &mtx);
    static Matrix4x4 GetMatrixFromQuaternion(const Quaternion<T> &q);


    //Determinant of a 2x2 matrix
    static T MatrixDet2(const T m[][4], int col0, int col1, int row0, int row1);

    //Determinant of a 3x3 matrix
    static T MatrixDet3(const T m[][4], int col0, int col1, int col2, int row0, int row1, int row2);

    //Determinant of a 4x4 matrix
    static T MatrixDet4(const T m[][4]);

    //Operators
    inline Matrix4x4& operator=(const Matrix4x4& rhs);
    inline bool operator==(const Matrix4x4& rhs) const;
    inline Matrix4x4 operator*(const Matrix4x4& rhs) const;
    inline Matrix4x4 operator*(T s) const;
    inline Matrix4x4 operator+(const Matrix4x4& rhs) const;
    inline Matrix4x4 operator-(const Matrix4x4& rhs) const;

    friend class Quaternion<T>;


protected:
    //elements
    T mElems[mColElementsCount][mRowElementsCount];
};

template<typename T>
void Matrix4x4<T>::CopyFrom(const Matrix4x4 &rhs)
{
    memcpy(this->mElems, rhs.mElems, mElementsCount * sizeof(T));
}

template<typename T>
void Matrix4x4<T>::CopyFromColMajor(const T *values)
{
    memcpy(this->mElems, values, mElementsCount * sizeof(T));
}

//copies from row major
template<typename T>
void Matrix4x4<T>::CopyFromRowMajor(const T *values) {
    for(int iRow=0; iRow < mRowElementsCount; iRow++) {
        for(int iCol=0; iCol < mColElementsCount; iCol++) {
            mElems[iCol][iRow] = values[iRow * mColElementsCount + iCol];
        }
    }
}

template<typename T>
void Matrix4x4<T>::GetElements(T *values)
{
    memcpy(values, this->mElems, mElementsCount * sizeof(T));
}

template <typename T>
void Matrix4x4<T>::FillZero()
{
    memset(mElems, 0, mElementsCount * sizeof(T));
}

template <typename T>
void Matrix4x4<T>::SetIdentity()
{
    FillZero();
    for(int i=0; i < mColElementsCount; i++)
        this->mElems[i][i] = 1.0;
}

template <typename T>
Vec4<T> Matrix4x4<T>::GetRow(int iRow) const
{
    Vec4<T> row;
    for(int iCol=0; iCol < mColElementsCount; iCol++)
        row.SetElement(iCol, this->mElems[iCol][iRow]);
    return row;
}

template <typename T>
Vec4<T> Matrix4x4<T>::GetCol(int iCol) const
{
    Vec4<T> col;
    for(int iRow=0; iRow < mRowElementsCount; iRow++)
        col.SetElement(iRow, this->mElems[iCol][iRow]);
    return col;
}

template <typename T>
Vec4<T> Matrix4x4<T>::GetDiagonal() const
{
    Vec4<T> diag;
    for(int i=0; i<mRowElementsCount; i++)
        diag.SetElement(i, this->mElems[i][i]);
    return diag;
}

template <typename T>
void Matrix4x4<T>::SetRow(int iRow, const Vec4<T> &row)
{
    for(int i=0; i<mColElementsCount; i++)
        this->mElems[i][iRow] = row.GetElement(i);
}

template <typename T>
void Matrix4x4<T>::SetCol(int iCol, const Vec4<T> &col)
{
    for(int i=0; i<mRowElementsCount; i++)
        this->mElems[iCol][i] = col.GetElement(i);
}

template <typename T>
void Matrix4x4<T>::SetDiagonal(const Vec4<T> &diag)
{
    for(int i=0; i<mColElementsCount; i++)
        this->mElems[i][i] = diag.GetElement(i);
}


template <typename T>
Matrix4x4<T> Matrix4x4<T>::GetSubMatrix(int ki, int kj) const
{
    Matrix4x4<T> output;
    int row;
    int dstCol = 0, dstRow = 0;
    for(int col = 0;col < mColElementsCount;col++)
    {
        if(col == kj){
            continue;
        }
        for(dstRow = 0, row = 0;row < mRowElementsCount; row++)
        {
            if(row == ki){
                continue;
            }
            output.mElems[dstCol][dstRow] = this->mElems[col][row];
            dstRow++;
        }
        dstCol++;
    }

    return output;
}

template <typename T>
T Matrix4x4<T>::GetElement(int iRow, int iCol) const
{
    return this->mElems[iCol][iRow];
}

template <typename T>
void Matrix4x4<T>::SetElement(int iRow, int iCol, T v)
{
    this->mElems[iCol][iRow] = v;
}

template <typename T>
void Matrix4x4<T>::Transpose()
{
    Matrix4x4<T> temp;
    //Row
    for(int i=0; i < mRowElementsCount; i++)
        for(int j=0; j<mColElementsCount; j++)
            temp.mElems[i][j] = this->mElems[j][i];
    this->CopyFrom(temp);
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::GetTransposed() const
{
    Matrix4x4<T> output = *this;
    output.Transpose();
    return output;
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::GetInverted(int *lpIsInvertible) const
{
    Matrix4x4<T> inv;
    T det = this->Determinant();
    if (det == 0.0f)
    {
        if (lpIsInvertible)
            *lpIsInvertible = false;
        return inv;
    }
    det = 1.0f / det;

    inv.mElems[0][0] = MatrixDet3(mElems, 1, 2, 3, 1, 2, 3) * det;
    inv.mElems[0][1] = -MatrixDet3(mElems, 0, 2, 3, 1, 2, 3) * det;
    inv.mElems[0][2] = MatrixDet3(mElems, 0, 1, 3, 1, 2, 3) * det;
    inv.mElems[0][3] = -MatrixDet3(mElems, 0, 1, 2, 1, 2, 3) * det;
    inv.mElems[1][0] = -MatrixDet3(mElems, 1, 2, 3, 0, 2, 3) * det;
    inv.mElems[1][1] = MatrixDet3(mElems, 0, 2, 3, 0, 2, 3) * det;
    inv.mElems[1][2] = -MatrixDet3(mElems, 0, 1, 3, 0, 2, 3) * det;
    inv.mElems[1][3] = MatrixDet3(mElems, 0, 1, 2, 0, 2, 3) * det;
    inv.mElems[2][0] = MatrixDet3(mElems, 1, 2, 3, 0, 1, 3) * det;
    inv.mElems[2][1] = -MatrixDet3(mElems, 0, 2, 3, 0, 1, 3) * det;
    inv.mElems[2][2] = MatrixDet3(mElems, 0, 1, 3, 0, 1, 3) * det;
    inv.mElems[2][3] = -MatrixDet3(mElems, 0, 1, 2, 0, 1, 3) * det;
    inv.mElems[3][0] = -MatrixDet3(mElems, 1, 2, 3, 0, 1, 2) * det;
    inv.mElems[3][1] = MatrixDet3(mElems, 0, 2, 3, 0, 1, 2) * det;
    inv.mElems[3][2] = -MatrixDet3(mElems, 0, 1, 3, 0, 1, 2) * det;
    inv.mElems[3][3] = MatrixDet3(mElems, 0, 1, 2, 0, 1, 2) * det;
    //inv.flagBits = flagBits;

    if (lpIsInvertible)
        *lpIsInvertible = true;
    return inv;
}


template <typename T>
Matrix4x4<T> Matrix4x4<T>::GetInvertTransposed() const
{
    Matrix4x4<T> inv = this->GetInverted();
    return inv.GetTransposed();
}

template <typename T>
inline T Matrix4x4<T>::MatrixDet2(const T m[][4], int col0, int col1, int row0, int row1)
{
    return m[col0][row0] * m[col1][row1] - m[col0][row1] * m[col1][row0];
}


// Calculate the determinant of a 3x3 sub-matrix.
//     | A B C |
// M = | D E F |   det(M) = A * (EI - HF) - B * (DI - GF) + C * (DH - GE)
//     | G H I |
template <typename T>
inline T Matrix4x4<T>::MatrixDet3(const T m[][4], int col0, int col1, int col2, int row0, int row1, int row2)
{
    return m[col0][row0] * MatrixDet2(m, col1, col2, row1, row2)
            - m[col1][row0] * MatrixDet2(m, col0, col2, row1, row2)
            + m[col2][row0] * MatrixDet2(m, col0, col1, row1, row2);
}

// The 4x4 matrix inverse algorithm is based on that described at:
// http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q24
// Some optimization has been done to avoid making copies of 3x3
// sub-matrices and to unroll the loops.
template <typename T>
inline T Matrix4x4<T>::MatrixDet4(const T m[][4])
{
    T det;
    det  = m[0][0] * MatrixDet3(m, 1, 2, 3, 1, 2, 3);
    det -= m[1][0] * MatrixDet3(m, 0, 2, 3, 1, 2, 3);
    det += m[2][0] * MatrixDet3(m, 0, 1, 3, 1, 2, 3);
    det -= m[3][0] * MatrixDet3(m, 0, 1, 2, 1, 2, 3);
    return det;
}

template <typename T>
T Matrix4x4<T>::Determinant() const
{
    return MatrixDet4(mElems);
}

template <typename T>
T Matrix4x4<T>::Trace() const
{
    T sum = 0.0;
    for(int i=0; i<mColElementsCount; i++)
        sum += this->mElems[i][i];
    return sum;
}

//Full Map
template <typename T>
Vec4<T> Matrix4x4<T>::TransformPoint(const Vec4<T> &v) const
{
	Vec4<T> result;

	//Col, Row
    result.x = this->mElems[0][0] * v.x + this->mElems[1][0] * v.y + this->mElems[2][0] * v.z + this->mElems[3][0] * v.w;
    result.y = this->mElems[0][1] * v.x + this->mElems[1][1] * v.y + this->mElems[2][1] * v.z + this->mElems[3][1] * v.w;
    result.z = this->mElems[0][2] * v.x + this->mElems[1][2] * v.y + this->mElems[2][2] * v.z + this->mElems[3][2] * v.w;
    result.w = this->mElems[0][3] * v.x + this->mElems[1][3] * v.y + this->mElems[2][3] * v.z + this->mElems[3][3] * v.w;

	return result;
}

//Full Map
template <typename T>
Vec3<T> Matrix4x4<T>::TransformPoint(const Vec3<T> &v) const
{
	Vec4<T> v4(v, 1.0);
	Vec4<T> r4 = TransformPoint(v4);

	assert(r4.w != 0.0);
	T wInv = 1.0/r4.w;
	r4.x = r4.x * wInv;
	r4.y = r4.y * wInv;
	r4.z = r4.z * wInv;
	return r4.GetXYZ();
}


template <typename T>
void Matrix4x4<T>::Scale(const Vec3<T> &s)
{
	Matrix4x4<T> work;
    work.mElems[0][0] = s.x;
    work.mElems[1][1] = s.y;
    work.mElems[2][2] = s.z;
    *this = Mul(*this, work);
}

template <typename T>
void Matrix4x4<T>::Rotate(const Quaternion<T> &q)
{
	Matrix4x4<T> work = GetMatrixFromQuaternion(q);
    *this = Mul(*this, work);
}

template <typename T>
void Matrix4x4<T>::Rotate(const Vec3<T> &axis, T deg)
{
	Quaternion<T> q;
    q.FromAxisAngle(axis, deg);
    Rotate(q);
}


template <typename T>
void Matrix4x4<T>::Translate(const Vec3<T> &t)
{
	Matrix4x4<T> work;
    work.mElems[3][0] = t.x;
    work.mElems[3][1] = t.y;
    work.mElems[3][2] = t.z;
	*this = Mul(*this, work);
}

template <typename T>
Vec3<T> Matrix4x4<T>::GetTranslateVector() const {
	Vec4<T> t = GetCol(3);
	T invW = 1.0 / t.w;
	return Vec3<T>(t.x, t.y, t.z) * invW;
}

template <typename T>
Vec3<T> Matrix4x4<T>::GetScaleVector() const {
	return GetDiagonal().GetXYZ();
}

//Conditionals
template <typename T>
bool Matrix4x4<T>::IsIdentity() const
{
    Matrix4x4<T> ident;
    return IsEqual(ident, *this);
}

template <typename T>
bool Matrix4x4<T>::IsDiagonal() const
{
    for(int i=0; i<mColElementsCount; i++)
        for(int j=0; j<mRowElementsCount; j++)
        {
            if(i!=j && mElems[i][j] != 0.0f)
                return false;
        }
    return true;
}

template <typename T>
bool Matrix4x4<T>::IsSymmetric() const
{
    return IsEqual(*this, this->GetTransposed());
}

template <typename T>
bool Matrix4x4<T>::IsAntiSymmetric() const
{
    //a skew-symmetric (or antisymmetric or antimetric[1]) matrix is a square matrix A whose
    //transpose is also its negative; that is, it satisfies the equation A = −AT.
    return IsEqual(*this, Mul(this->GetTransposed(), -1.0));
}

template <typename T>
bool Matrix4x4<T>::IsOrthogonal() const
{
    //an orthogonal matrix is a square matrix with real entries whose columns and rows are orthogonal unit vectors (i.e., orthonormal vectors).
    //Equivalently, a matrix Q is orthogonal if its transpose is equal to its inverse.
    return IsEqual(this->GetTransposed(), this->GetInverted());
}

//Friend Functions
template <typename T>
bool Matrix4x4<T>::IsEqual(const Matrix4x4<T> &a, const Matrix4x4<T> &b)
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            if(AreSame<T>(a.mElems[i][j], b.mElems[i][j]) == false)
                return false;
        }

    return true;
}


template <typename T>
Matrix4x4<T> Matrix4x4<T>::Mul(const Matrix4x4<T> &a, const Matrix4x4<T> &b)
{
    Matrix4x4<T> output;
    output.FillZero();
    for(int iCol=0; iCol < 4; iCol++ )
        for(int iRow=0; iRow < 4; iRow++ )
            for(int k=0; k < 4; k++ )
                output.mElems[iCol][iRow] += a.mElems[k][iRow] * b.mElems[iCol][k];
    return output;
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::Mul(const Matrix4x4<T> &a, T s)
{
    Matrix4x4<T> output;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            output.mElems[i][j] = s * a.mElems[i][j];
        }
    return output;
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::InnerProduct(const Matrix4x4<T> &a, const Matrix4x4<T> &b)
{
    Matrix4x4<T> output;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            output.mElems[i][j] = a.mElems[i][j] * b.mElems[i][j];
    return output;
}

template <typename T>
T Matrix4x4<T>::GetFrobeniousNorm(const Matrix4x4<T> &a, const Matrix4x4<T> &b)
{
    T sum = 0;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            sum += a.mElems[i][j] * b.mElems[i][j];
    return sum;
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::Add(const Matrix4x4<T> &a, const Matrix4x4<T> &b)
{
    Matrix4x4<T> output;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            output.mElems[i][j] = a.mElems[i][j] + b.mElems[i][j];
        }
    return output;

}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::Sub(const Matrix4x4<T> &a, const Matrix4x4<T> &b)
{
    Matrix4x4<T> output;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            output.mElems[i][j] = a.mElems[i][j] - b.mElems[i][j];
        }
    return output;
}

//Quaternion From Matrix
template <typename T>
Quaternion<T> Matrix4x4<T>::GetQuaternionFromMatrix(const Matrix4x4<T> &mtx)
{
    float tr = mtx.mElems[0][0] + mtx.mElems[1][1] + mtx.mElems[2][2];
    quat res;

    // check the diagonal
    if (tr > 0.0f )
    {
        float s = (float) sqrt ( (double) (tr + 1.0f) );
        res.w = s * 0.5f;
        s = 0.5f / s;
        res.x = (mtx.mElems[1][2] - mtx.mElems[2][1]) * s;
        res.y = (mtx.mElems[2][0] - mtx.mElems[0][2]) * s;
        res.z = (mtx.mElems[0][1] - mtx.mElems[1][0]) * s;
    }
    else
    {
        // diagonal is negative
        int nxt[3] = {1, 2, 0};
        float  qa[4];

        int i = 0;

        if (mtx.mElems[1][1] > mtx.mElems[0][0]) i = 1;
        if (mtx.mElems[2][2] > mtx.mElems[i][i]) i = 2;

        int j = nxt[i];
        int k = nxt[j];

        float s = sqrt ( ((mtx.mElems[i][i] - (mtx.mElems[j][j] + mtx.mElems[k][k])) + 1.0f) );

        qa[i] = s * 0.5f;

        if (s != 0.0f ) s = 0.5f / s;

        qa[3] = (mtx.mElems[j][k] - mtx.mElems[k][j]) * s;
        qa[j] = (mtx.mElems[i][j] + mtx.mElems[j][i]) * s;
        qa[k] = (mtx.mElems[i][k] + mtx.mElems[k][i]) * s;

        res.x = qa[0];
        res.y = qa[1];
        res.z = qa[2];
        res.w = qa[3];
    }

    return res;
}

//quaternion must be normalized and matrix t in column-major format
template <typename T>
Matrix4x4<T> Matrix4x4<T>::GetMatrixFromQuaternion(const Quaternion<T> &q)
{
    float xx = q.x * q.x;
    float yy = q.y * q.y;
    float zz = q.z * q.z;
    float xy = q.x * q.y;
    float xz = q.x * q.z;
    float yz = q.y * q.z;
    float wx = q.w * q.x;
    float wy = q.w * q.y;
    float wz = q.w * q.z;

    Matrix4x4<T> mtx;
    mtx.mElems[0][0] = 1 - 2 * ( yy + zz );
    mtx.mElems[1][0] =     2 * ( xy - wz );
    mtx.mElems[2][0] =     2 * ( xz + wy );

    mtx.mElems[0][1] =     2 * ( xy + wz );
    mtx.mElems[1][1] = 1 - 2 * ( xx + zz );
    mtx.mElems[2][1] =     2 * ( yz - wx );

    mtx.mElems[0][2] =     2 * ( xz - wy );
    mtx.mElems[1][2] =     2 * ( yz + wx );
    mtx.mElems[2][2] = 1 - 2 * ( xx + yy );

    mtx.mElems[3][0] = mtx.mElems[3][1] = mtx.mElems[3][2] = 0.0f;
    mtx.mElems[0][3] = mtx.mElems[1][3] = mtx.mElems[2][3] = 0.0f;
    mtx.mElems[3][3] = 1.0f;

    return mtx;
}

/*!
    Multiplies this matrix by another that applies an orthographic
    projection for a window with lower-left corner (\a left, \a bottom),
    upper-right corner (\a right, \a top), and the specified \a nearPlane
    and \a farPlane clipping planes.

    \sa frustum(), perspective()
*/
template <typename T>
void Matrix4x4<T>::Ortho(T left, T right, T bottom, T top, T nearPlane, T farPlane)
{
    // Bail out if the projection volume is zero-sized.
    if (left == right || bottom == top || nearPlane == farPlane)
        return;

    // Construct the projection.
    T width = right - left;
    T invheight = top - bottom;
    T clip = farPlane - nearPlane;
    Matrix4x4<T> m;
    m.mElems[0][0] = 2.0f / width;
    m.mElems[1][0] = 0.0f;
    m.mElems[2][0] = 0.0f;
    m.mElems[3][0] = -(left + right) / width;
    m.mElems[0][1] = 0.0f;
    m.mElems[1][1] = 2.0f / invheight;
    m.mElems[2][1] = 0.0f;
    m.mElems[3][1] = -(top + bottom) / invheight;
    m.mElems[0][2] = 0.0f;
    m.mElems[1][2] = 0.0f;
    m.mElems[2][2] = -2.0f / clip;
    m.mElems[3][2] = -(nearPlane + farPlane) / clip;
    m.mElems[0][3] = 0.0f;
    m.mElems[1][3] = 0.0f;
    m.mElems[2][3] = 0.0f;
    m.mElems[3][3] = 1.0f;
    //m.flagBits = Translation | Scale;

    // Apply the projection.
    *this = m;
}

/*!
    Multiplies this matrix by another that applies a perspective
    frustum projection for a window with lower-left corner (\a left, \a bottom),
    upper-right corner (\a right, \a top), and the specified \a nearPlane
    and \a farPlane clipping planes.

    \sa ortho(), perspective()
*/
template <typename T>
void Matrix4x4<T>::Frustum(T left, T right, T bottom, T top, T nearPlane, T farPlane)

{
    // Bail out if the projection volume is zero-sized.
    if (left == right || bottom == top || nearPlane == farPlane)
        return;

    // Construct the projection.
    Matrix4x4<T> m;
    T width = right - left;
    T invheight = top - bottom;
    T clip = farPlane - nearPlane;
    m.mElems[0][0] = 2.0f * nearPlane / width;
    m.mElems[1][0] = 0.0f;
    m.mElems[2][0] = (left + right) / width;
    m.mElems[3][0] = 0.0f;
    m.mElems[0][1] = 0.0f;
    m.mElems[1][1] = 2.0f * nearPlane / invheight;
    m.mElems[2][1] = (top + bottom) / invheight;
    m.mElems[3][1] = 0.0f;
    m.mElems[0][2] = 0.0f;
    m.mElems[1][2] = 0.0f;
    m.mElems[2][2] = -(nearPlane + farPlane) / clip;
    m.mElems[3][2] = -2.0f * nearPlane * farPlane / clip;
    m.mElems[0][3] = 0.0f;
    m.mElems[1][3] = 0.0f;
    m.mElems[2][3] = -1.0f;
    m.mElems[3][3] = 0.0f;
    //m.flagBits = General;

    // Apply the projection.
    *this = m;
}

/*!
    Multiplies this matrix by another that applies a perspective
    projection.  The field of view will be \a angle degrees within
    a window with a given \a aspect ratio.  The projection will
    have the specified \a nearPlane and \a farPlane clipping planes.

    \sa ortho(), frustum()
*/
template <typename T>
void Matrix4x4<T>::Perspective(T angle, T aspect, T nearPlane, T farPlane)
{
    // Bail out if the projection volume is zero-sized.
    if (nearPlane == farPlane || aspect == 0.0f)
        return;

    // Construct the projection.
    Matrix4x4<T> m;
    T radians = (angle / 2.0f) * Pi / 180.0f;
    T sine = sin(radians);
    if (sine == 0.0f)
        return;

    T cotan = cos(radians) / sine;
    T clip = farPlane - nearPlane;
    m.mElems[0][0] = cotan / aspect;
    m.mElems[1][0] = 0.0f;
    m.mElems[2][0] = 0.0f;
    m.mElems[3][0] = 0.0f;
    m.mElems[0][1] = 0.0f;
    m.mElems[1][1] = cotan;
    m.mElems[2][1] = 0.0f;
    m.mElems[3][1] = 0.0f;
    m.mElems[0][2] = 0.0f;
    m.mElems[1][2] = 0.0f;
    m.mElems[2][2] = -(nearPlane + farPlane) / clip;
    m.mElems[3][2] = -(2.0f * nearPlane * farPlane) / clip;
    m.mElems[0][3] = 0.0f;
    m.mElems[1][3] = 0.0f;
    m.mElems[2][3] = -1.0f;
    m.mElems[3][3] = 0.0f;
    //m.flagBits = General;

    // Apply the projection.
    *this = m;
}

/*!
    Multiplies this matrix by another that applies an \a eye position
    transformation.  The \a center value indicates the center of the
    view that the \a eye is looking at.  The \a up value indicates
    which direction should be considered up with respect to the \a eye.
*/
template <typename T>
void Matrix4x4<T>::LookAt(const Vec3<T> &eye, const Vec3<T> &target, const Vec3<T> &up)
{
    Vec3<T> forward = (target - eye).GetNormalized();
    Vec3<T> side = Vec3<T>::Cross(forward, up).GetNormalized();
    Vec3<T> upVector = Vec3<T>::Cross(side, forward);

    //compute M1
    Matrix4x4<T> M1;
    M1.SetIdentity();
    M1.mElems[0][0] = side.x;
    M1.mElems[1][0] = side.y;
    M1.mElems[2][0] = side.z;

    M1.mElems[0][1] = upVector.x;
    M1.mElems[1][1] = upVector.y;
    M1.mElems[2][1] = upVector.z;

    M1.mElems[0][2] = -forward.x;
    M1.mElems[1][2] = -forward.y;
    M1.mElems[2][2] = -forward.z;

    //compute M2
    Matrix4x4<T> M2;
    M2.SetIdentity();
    M2.Translate(Vec3<T>::Mul(-1.0f, eye));

    *this = Matrix4x4<T>::Mul(M1, M2);
}



//Operators
template <typename T>
Matrix4x4<T>& Matrix4x4<T>::operator=(const Matrix4x4& rhs)
{
    this->CopyFrom(rhs);
    return (*this);
}

template <typename T>
bool Matrix4x4<T>::operator==(const Matrix4x4& rhs) const
{
    return IsEqual(*this, rhs);
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4& rhs) const
{
    return Mul(*this, rhs);
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::operator*(T s) const
{
    return Mul(*this, s);
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::operator+(const Matrix4x4& rhs) const
{
    return Add(*this, rhs);
}

template <typename T>
Matrix4x4<T> Matrix4x4<T>::operator-(const Matrix4x4& rhs) const
{
    return Sub(*this, rhs);
}

template <typename T>
void Matrix4x4<T>::Print() const {

    std::stringstream ss;
    //ss.precision(6);

    for(int iRow=0; iRow<4; iRow++)
    {
        for(int iCol=0; iCol<4; iCol++)
        {
            ss << GetElement(iRow, iCol) << string(", ");
        }
        ss << std::endl;
    }

    std::cout << ss.str();
}


typedef Matrix4x4<nbReal> mat4;

//Debugging Functions
void MtxPrint(const mat4& a);



}
}
#endif // PS_MATRIX_H
