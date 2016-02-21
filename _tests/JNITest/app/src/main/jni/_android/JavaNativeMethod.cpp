/*!
   \file JavaNativeMethod.cpp
   \brief Allocation and registration of java native methods in c++
   \author Denis Sorokin
   \date February 15 2016
   \copyright Zeptolab, 2016
 */

#include "JavaNativeMethod.hpp"
#include "JavaEnvironment.hpp"

namespace jh
{
    bool registerJavaNativeMethods(std::string javaClassName, int methodCount, JNINativeMethod* methodDescriptions)
    {
        auto env = getCurrentJNIEnvironment();

        jclass javaClass = env->FindClass(javaClassName.c_str());
        if (javaClass == nullptr) {
            reportInternalError("unable to find class [" + javaClassName + "] for native methods registration");
            return false;
        }

        if (env->RegisterNatives(javaClass, methodDescriptions, methodCount) < 0) {
            reportInternalError("unable to register native methods for class [" + javaClassName + "]");
            return false;
        }

        return true;
    }

}
