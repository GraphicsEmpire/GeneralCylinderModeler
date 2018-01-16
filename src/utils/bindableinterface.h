#ifndef BINDABLEINTERFACE_H
#define BINDABLEINTERFACE_H

#include <vector>
#include <memory>
#include "linalg/base.h"

using namespace std;

namespace nb {
namespace utils {

class BindableInterface
{
public:
    BindableInterface();
    virtual ~BindableInterface();

    virtual void Bind() = 0;

    virtual void Unbind() = 0;
};


template <typename T = BindableInterface>
class BindableCollection : public BindableInterface {
public:
    BindableCollection() {
    }

    virtual ~BindableCollection() {
        Clear();
    }

    typedef shared_ptr<T> BindableEntry;


    void Bind() override {
        for(U32 i=0; i < mCollection.size(); i++)
            mCollection[i]->Bind();
    }

    void Unbind() override {
        for(U32 i=0; i < mCollection.size(); i++)
            mCollection[i]->Unbind();
    }

    BindableEntry Get(U32 index) {
        if(IsEntry(index))
            return mCollection[index];
        else
            return BindableEntry();
    }

    void Add(const BindableEntry &e) {
        mCollection.push_back(e);
    }

    void Remove(U32 index) {
        mCollection.erase(mCollection.begin() + index);
    }

    U32 Count() const {
        return (U32)mCollection.size();
    }

    virtual void Clear() {
        mCollection.resize(0);
    }

    inline bool IsEntry(U32 index) const {
        return index < mCollection.size();
    }
protected:
    vector<BindableEntry> mCollection;
};

}
}

#endif // BINDABLEINTERFACE_H
