#ifndef SINGLETON_H
#define SINGLETON_H

namespace nb {
namespace utils {

template <typename T>
class Singleton {
public:
    static T& Instance() {
        static T instance;
        return instance;
    }

protected:
    Singleton() {}

public:
    Singleton(Singleton const&) = delete;
    void operator=(Singleton const&) = delete;


};

}
}
#endif // SINGLETON_H
