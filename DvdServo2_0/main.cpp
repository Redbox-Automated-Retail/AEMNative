#include "net_dvdplay_aem_DPEC.h"
#include <windows.h>

typedef INT_PTR(WINAPI* DPEC_ConnectFunc)(void);
typedef INT_PTR(WINAPI* DPEC_DisconnectFunc)(void);
typedef INT_PTR(WINAPI* DPEC_StartLoggingFunc)(void);
typedef INT_PTR(WINAPI* DPEC_KillLoggingFunc)(void);
typedef INT_PTR(WINAPI* DPEC_AbortOperationFunc)(int);


static JavaVM* g_java_vm = nullptr;
static HMODULE g_dpec_handle = nullptr;

JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_Connect(JNIEnv* env, jclass clz)
{
	env->GetJavaVM(&g_java_vm);
	g_dpec_handle = LoadLibraryA("DPEC_API.dll");
	if (g_dpec_handle == nullptr) {
		return net_dvdplay_aem_DPEC_RESULT_CANTLOADDLL;
	}

	DPEC_ConnectFunc connectFunc = GetProcAddress(g_dpec_handle, "DPEC_Connect");
	DPEC_DisconnectFunc disconnectAddress = GetProcAddress(g_dpec_handle, "DPEC_Disconnect");
	DPEC_StartLoggingFunc startLoggingAddress = GetProcAddress(g_dpec_handle, "DPEC_StartLoggingService");
	DPEC_KillLoggingFunc killLoggingAddress = GetProcAddress(g_dpec_handle, "DPEC_KillLoggingService");

	(*startLoggingAddress)();
	INT_PTR result = connectFunc();
	if (result != 0)
	{
		(*disconnectAddress)();
		(*killLoggingAddress)();
		Sleep(100);
		if (FreeLibrary(g_dpec_handle) == 0)
		{
			return net_dvdplay_aem_DPEC_RESULT_CANTFREEDLL;
		}
	}

	return static_cast<jint>(result);
}


JNIEXPORT void JNICALL Java_net_dvdplay_aem_DPEC_SetGlobalRef(JNIEnv* env, jclass clz, jstring lClassName, jstring lExceptionClassName, jstring lRegForAsynEventsName, jstring lCommonFunctionName, jstring lGetTaggedInfoName, jstring lGetStatusQuickName, jstring lRotateToSlotName, jstring lEjectCaseFromSlotName, jstring lVersionMajor, jstring lVersionMinor, jstring lVersionBuild, jstring lVersionString)
{
	
}


JNIEXPORT void JNICALL Java_net_dvdplay_aem_DPEC_ReleaseGlobalRef(JNIEnv* env, jclass clz)
{
	
}


JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_Disconnect(JNIEnv* env, jclass clz)
{
	INT_PTR result = net_dvdplay_aem_DPEC_RESULT_CANTFREEDLL;

	DPEC_DisconnectFunc disconnectFunc = GetProcAddress(g_dpec_handle, "DPEC_Disconnect");
	DPEC_KillLoggingFunc killLoggingFunc = GetProcAddress(g_dpec_handle, "DPEC_KillLoggingService");

	INT_PTR disconnectRet = disconnectFunc();
	killLoggingFunc();

	if (FreeLibrary(g_dpec_handle) != 0)
	{
		result = disconnectRet;
	}

	return static_cast<jint>(result);
}


JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_StartOperation(JNIEnv* env, jclass clz, jint lKey, jint aLocation, jint tagType, jint var3)
{
	return 0;
}


// Appears unused
JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_GetOpState(JNIEnv* env, jclass clz, jint var0)
{
	return 0;
}

// Appears unused
JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_AbortOperation(JNIEnv* env, jclass clz, jint var0)
{
	DPEC_AbortOperationFunc abortFunc = (DPEC_AbortOperationFunc)GetProcAddress(g_dpec_handle, "DPEC_AbortOperation");
	INT_PTR result = abortFunc(var0);
	return static_cast<jint>(result);
}


JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_RegForAsyncEvents(JNIEnv* env, jclass clz, jint cbRegEvtKey)
{
	return 0;
}


JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_SetMode(JNIEnv* env, jclass clz, jint mode)
{
	return 0;
}

// Appears unused
JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_GetMode(JNIEnv* env, jclass clz)
{
	return 0;
}


JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_StartAppWatchdog(JNIEnv* env, jclass clz)
{
	return 0;
}


JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_StrokeAppWatchdog(JNIEnv* env, jclass clz)
{
	return 0;
}


JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_KillAppWatchdog(JNIEnv* env, jclass clz)
{
	return 0;
}


// Appears unused
JNIEXPORT void JNICALL Java_net_dvdplay_aem_DPEC_GetLibraryVersion(JNIEnv* env, jclass clz)
{
	
}

// Appears unused
JNIEXPORT void JNICALL Java_net_dvdplay_aem_DPEC_AddLineToLog(JNIEnv* env, jclass clz, jstring var0)
{
	
}

JNIEXPORT void JNICALL Java_net_dvdplay_aem_DPEC_StartLoggingService(JNIEnv* env, jclass clz)
{
	DPEC_StartLoggingFunc startLoggingFunc = GetProcAddress(g_dpec_handle, "DPEC_StartLoggingService");
	startLoggingFunc();
}

JNIEXPORT void JNICALL Java_net_dvdplay_aem_DPEC_KillLoggingService(JNIEnv* env, jclass clz)
{
	DPEC_KillLoggingFunc killLoggingFunc = GetProcAddress(g_dpec_handle, "DPEC_KillLoggingService");
	killLoggingFunc();
}