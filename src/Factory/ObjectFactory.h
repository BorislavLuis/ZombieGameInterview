#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "Transform.h"
#include "GameObject.h"

using ObjectPtr = GameObject*;
using ObjectList = std::vector<ObjectPtr>;
enum ObjectCategory {SCENE_OBJECTS=0,GAME_OBJECTS=1};

class ObjectFactory
{
    public:

        ObjectPtr CreateObject(std::string type, Transform* tf);
        void RegisterType(std::string className,std::function<ObjectPtr(Transform* tf)> type);
        static ObjectFactory* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new ObjectFactory(); }

    private:
        ObjectFactory(){}
        static ObjectFactory* s_Instance;
        std::map<std::string,std::function<ObjectPtr(Transform* tf)>> m_TypeRegistry;
};

//template <class Type>
//class Registrar
//{
//public:
//    Registrar(std::string className)
//    {
//        ObjectFactory::GetInstance()->RegisterType(className,
//        [](Transform* tf)->ObjectPtr{
//            return new Type(tf);
//        });
//    }
//};

#endif // OBJECTFACTORY_H
