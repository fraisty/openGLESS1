//
// Created by haichao.gao on 20-10-19.
//
#include <string>
#include "jni.h"  //必须包含
#include "common/myLog.h"

#define NATIVE_JNIIMPL_CLASSNAME "com/fraisty/opengless1/esNativeRender"


#ifdef __cplusplus
extern "C" {
#endif

/**
* Class: com.fraisty.opengless1.esNativeRender.NativeJniTest
* Method: NativeJniTest
* Signature: (Ljava/lang/String;)Ljava/lang/String;
*/
JNIEXPORT jstring JNICALL esJniTest(JNIEnv *env, jobject instance, jstring strt)
{
    LOGFE("Jnifunc: esJniTest!");
    std::string strc = "Native + ";
    strc.append(env->GetStringUTFChars(strt,NULL));
    return env->NewStringUTF(strc.c_str());
}




#ifdef __cplusplus
}
#endif

//接口输出函数表  “...;”不能丢，否则注册失败
static JNINativeMethod esNativeMethods[] = {
        {"NativeJniTest",  "(Ljava/lang/String;)Ljava/lang/String;", (void *)(esJniTest) }
};


/**
 * description: 针对类名，注册多个native 接口函数
 *
 * env: 代表Java环境，通过这个环境可以调用JNIEnv中的相关方法
 * className: Java类名称
 * methods: 接口函数表
 * methodNum: 接口函数中函数的个数
*/
static int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *methods, int methodNum)
{
    jclass clazz = env->FindClass(className) ;

    if (clazz == NULL)
        return JNI_FALSE;

    if(env->RegisterNatives(clazz, methods, methodNum) < 0)
        return JNI_FALSE;

    return JNI_TRUE;
}

/**
 * description： jni入口函数, 在load lib时候被调用
 *
 * vm: java虚拟机指针
*/
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv *env = NULL;
    jint jniRes;

    jniRes = vm->GetEnv((void **) (&env), JNI_VERSION_1_6);

    if( jniRes != JNI_OK )
        return JNI_ERR;

    jniRes = registerNativeMethods(env, NATIVE_JNIIMPL_CLASSNAME,
                                   esNativeMethods, sizeof(esNativeMethods) /
                                                  sizeof(esNativeMethods[0]));
    if(jniRes != JNI_TRUE)
        return JNI_ERR;

    return JNI_VERSION_1_6;
}





