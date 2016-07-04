/*
 * android-specific implementation of the PresageEDK extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "PresageEDK_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_PresageStart;
static jmethodID g_PresageAdToServe;
static jmethodID g_PresageLoadAd;
static jmethodID g_PresageShowAd;
static jmethodID g_PresageLaunchEula;

namespace
{
    void onAdNotFoundShim()
    {
        s3eEdkCallbacksEnqueue (S3E_EXT_PRESAGEEDK_HASH, PRESAGE_RESULT_NO_AD);
    }

    void onAdFoundShim()
    {
        s3eEdkCallbacksEnqueue (S3E_EXT_PRESAGEEDK_HASH, PRESAGE_RESULT_OK);
    }

    void onAdClosedShim()
    {
        s3eEdkCallbacksEnqueue (S3E_EXT_PRESAGEEDK_HASH, PRESAGE_RESULT_CANCELLED);
    }

    void onAdErrorShim()
    {
        s3eEdkCallbacksEnqueue (S3E_EXT_PRESAGEEDK_HASH, PRESAGE_RESULT_ERROR);
    }

    void onAdDisplayedShim()
    {
        s3eEdkCallbacksEnqueue (S3E_EXT_PRESAGEEDK_HASH, PRESAGE_RESULT_DISPLAYED);
    }

    void onEulaFoundShim()
    {
        s3eEdkCallbacksEnqueue (S3E_EXT_PRESAGEEDK_HASH, PRESAGE_EULA_OK);
    }

    void onEulaNotFoundShim()
    {
        s3eEdkCallbacksEnqueue (S3E_EXT_PRESAGEEDK_HASH, PRESAGE_NO_EULA);
    }

    void onEulaClosedShim()
    {
        s3eEdkCallbacksEnqueue (S3E_EXT_PRESAGEEDK_HASH, PRESAGE_EULA_CANCELLED);
    }

    //Register natives here
    const JNINativeMethod nativeMethods[] =
    {
        { "onAdNotFoundNative", "()V", (void*)&onAdNotFoundShim },
        { "onAdFoundNative", "()V", (void*)&onAdFoundShim },
        { "onAdClosedNative", "()V", (void*)&onAdClosedShim },
        { "onAdErrorNative", "()V", (void*)&onAdErrorShim },
        { "onAdDisplayedNative", "()V", (void*)&onAdDisplayedShim },

        { "onEulaNotFoundNative", "()V", (void*)&onEulaNotFoundShim },
        { "onEulaFoundNative", "()V", (void*)&onEulaFoundShim },
        { "onEulaClosedNative", "()V", (void*)&onEulaClosedShim },
    };
}

s3eResult PresageEDKInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("PresageEDK");
    if (!cls)
        goto fail;

    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    // Get all the extension methods
    g_PresageStart = env->GetMethodID(cls, "PresageStart", "()V");
    if (!g_PresageStart)
        goto fail;

    g_PresageAdToServe = env->GetMethodID(cls, "PresageAdToServe", "()V");
    if (!g_PresageAdToServe)
        goto fail;

    g_PresageLoadAd = env->GetMethodID(cls, "PresageLoadAd", "()V");
    if (!g_PresageLoadAd)
        goto fail;

    g_PresageShowAd = env->GetMethodID(cls, "PresageShowAd", "()V");
    if (!g_PresageShowAd)
        goto fail;

    g_PresageLaunchEula = env->GetMethodID(cls, "PresageLaunchEula", "()V");
    if (!g_PresageLaunchEula)
        goto fail;

    env->RegisterNatives(cls, nativeMethods, sizeof(nativeMethods) / sizeof(nativeMethods[0]));

    IwTrace(PRESAGEEDK, ("PRESAGEEDK init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;

fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(PresageEDK, ("One or more java methods could not be found"));
    }

    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);
    return S3E_RESULT_ERROR;

}

void PresageEDKTerminate_platform()
{ 
    // Add any platform-specific termination code here
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->DeleteGlobalRef(g_Obj);
    g_Obj = NULL;
}

void PresageStart_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_PresageStart);
}

void PresageAdToServe_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_PresageAdToServe);
}

void PresageLaunchEula_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_PresageLaunchEula); 
}

void PresageLoadAd_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_PresageLoadAd);
}

void PresageShowAd_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_PresageShowAd);
}
