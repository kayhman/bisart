#pragma once

template<typename T>
class Singleton
{
private:
    static T* instance;
  public:
    static T* getInstance();
    static T* createInstance(T* inst);
};

template <typename T> T* Singleton<T>::instance = NULL;

template<typename T>
T* Singleton<T>::getInstance() {
    return Singleton::instance;
}

template<typename T>
T* Singleton<T>::createInstance(T* inst)
{
    if(Singleton::instance)
      return inst;
    else
       Singleton::instance = inst;
    return inst;
}
