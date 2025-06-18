#include <iostream>
#include <mutex>
#include <memory>
#include <atomic>

// Стратегия создания (Creation Policy)
template <typename T>
struct CreateUsingNew {
    static T* Create() {
        return new T();
    }

    static void Destroy(T* p) {
        delete p;
    }
};

// Стратегия времени жизни (Lifetime Policy)
template <typename T>
struct DefaultLifetime {
    static void ScheduleDestruction(T*, void (*pFun)()) {
        std::atexit(pFun);
    }

    static void OnDeadReference() {
        throw std::runtime_error("Dead Reference Detected");
    }
};

// Стратегия потокобезопасности (Threading Policy)
class SingleThreaded {
public:
    using Lock = struct {}; // Пустая структура вместо мьютекса

    class Guard {
    public:
        Guard(Lock&) {}
    };
};

class MultiThreaded {
public:
    using Lock = std::mutex;

    class Guard {
    public:
        Guard(Lock& mtx) : mtx_(mtx) {
            mtx_.lock();
        }

        ~Guard() {
            mtx_.unlock();
        }

    private:
        Lock& mtx_;
    };
};

// Основной шаблон Singleton
template <
    typename T,
    template <typename> class CreationPolicy = CreateUsingNew,
    template <typename> class LifetimePolicy = DefaultLifetime,
    typename ThreadingModel = MultiThreaded // Изменено: теперь не шаблонный параметр
>
class SingletonHolder {
public:
    static T& Instance() {
        if (!pInstance_) {
            typename ThreadingModel::Guard guard(lock_); // Убрано <T>
            if (!pInstance_) {
                if (destroyed_) {
                    LifetimePolicy<T>::OnDeadReference();
                    destroyed_ = false;
                }

                pInstance_ = CreationPolicy<T>::Create();
                LifetimePolicy<T>::ScheduleDestruction(pInstance_, &DestroySingleton);
            }
        }
        return *pInstance_;
    }

private:
    static void DestroySingleton() {
        CreationPolicy<T>::Destroy(pInstance_);
        pInstance_ = nullptr;
        destroyed_ = true;
    }

    SingletonHolder() = delete;
    ~SingletonHolder() = delete;
    SingletonHolder(const SingletonHolder&) = delete;
    SingletonHolder& operator=(const SingletonHolder&) = delete;

    static typename ThreadingModel::Lock lock_; // Убрано <T>
    static T* pInstance_;
    static bool destroyed_;
};

// Инициализация статических членов
template <typename T, template <typename> class C, template <typename> class L, typename M>
typename M::Lock SingletonHolder<T, C, L, M>::lock_; // Убрано <T>

template <typename T, template <typename> class C, template <typename> class L, typename M>
T* SingletonHolder<T, C, L, M>::pInstance_ = nullptr;

template <typename T, template <typename> class C, template <typename> class L, typename M>
bool SingletonHolder<T, C, L, M>::destroyed_ = false;

// Пример использования
class MyClass {
public:
    void DoSomething() {
        std::cout << "Doing something..." << std::endl;
    }

private:
    MyClass() = default;
    ~MyClass() = default;

    friend struct CreateUsingNew<MyClass>;
};

// Алиас для удобства
using MySingleton = SingletonHolder<MyClass, CreateUsingNew, DefaultLifetime, MultiThreaded>;

int main() {
    MyClass& instance1 = MySingleton::Instance();
    instance1.DoSomething();

    MyClass& instance2 = MySingleton::Instance();
    instance2.DoSomething();

    std::cout << "Are instances equal? " << (&instance1 == &instance2) << std::endl;

    return 0;

}