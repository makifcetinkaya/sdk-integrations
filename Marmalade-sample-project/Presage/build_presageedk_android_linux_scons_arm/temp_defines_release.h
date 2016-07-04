#ifndef ANDROID
#   define ANDROID 1
#endif
#ifndef I3D_ARCH_ARM
#   define I3D_ARCH_ARM 1
#endif
#ifndef I3D_OS_LINUX
#   define I3D_OS_LINUX 1
#endif
#ifndef I3D_PLATFORM_LINUX
#   define I3D_PLATFORM_LINUX 1
#endif
#ifndef IW_ASSERTION_CHANNEL_PRESAGEEDK
#   define IW_ASSERTION_CHANNEL_PRESAGEEDK 1
#endif
#ifndef IW_MKF_ANDROID_ENV
#   define IW_MKF_ANDROID_ENV 1
#endif
#ifndef IW_MKF_EDK
#   define IW_MKF_EDK 1
#endif
#ifndef IW_MKF_PRESAGEEDK_ANDROID_DEPLOYMENT
#   define IW_MKF_PRESAGEEDK_ANDROID_DEPLOYMENT 1
#endif
#ifndef IW_MKF_PRESAGEEDK_BUILD
#   define IW_MKF_PRESAGEEDK_BUILD 1
#endif
#ifndef IW_MKF_S3E_DEFAULT
#   define IW_MKF_S3E_DEFAULT 1
#endif
#ifndef IW_PLATFORM_LINUX
#   define IW_PLATFORM_LINUX 1
#endif
#ifndef IW_SDK
#   define IW_SDK 1
#endif
#ifndef IW_TRACE_CHANNEL_PRESAGEEDK
#   define IW_TRACE_CHANNEL_PRESAGEEDK 1
#endif
#ifndef IW_TRACE_CHANNEL_PRESAGEEDK_VERBOSE
#   define IW_TRACE_CHANNEL_PRESAGEEDK_VERBOSE 2
#endif
#ifndef S3E_ANDROID
#   define S3E_ANDROID 1
#endif
#ifndef S3E_ANDROID_NDK_API
#   define S3E_ANDROID_NDK_API 14
#endif
#ifndef S3E_ANDROID_NDK_VER
#   define S3E_ANDROID_NDK_VER 10
#endif
#ifndef S3E_BUILD_EXT
#   define S3E_BUILD_EXT 1
#endif
#ifndef S3E_EXT_PRESAGEEDK
#   define S3E_EXT_PRESAGEEDK 1
#endif

/* including "extra_body" specified by the mkb plugin */

#if !defined I3D_ARCH_32_BIT && !defined I3D_ARCH_64_BIT
    #if defined I3D_ARCH_AARCH64 || defined I3D_ARCH_AMD64 || defined I3D_ARCH_X86_64
        #define I3D_ARCH_64_BIT
    #else
        #define I3D_ARCH_32_BIT
    #endif
#endif
