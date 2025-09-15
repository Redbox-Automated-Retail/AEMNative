#include <iostream>

#include "net_dvdplay_aem_DPEC.h"
#include <windows.h>

typedef int(__cdecl* DPEC_OperationCallback)(int key, int opId, int res, int quickStat);
typedef int(__cdecl* DPEC_OperationCallback2)(int key, int opId, int res);
typedef int(__cdecl* DPEC_RegForAsyncEventsCallback)(int key, int event);

typedef INT_PTR(__cdecl* DPEC_ConnectFunc)();
typedef INT_PTR(__cdecl* DPEC_DisconnectFunc)();
typedef INT_PTR(__cdecl* DPEC_StartLoggingFunc)();
typedef INT_PTR(__cdecl* DPEC_KillLoggingFunc)();
typedef INT_PTR(__cdecl* DPEC_AbortOperationFunc)(int);
typedef INT_PTR(__cdecl* DPEC_GetModeFunc)();
typedef INT_PTR(__cdecl* DPEC_AddLineToLogFunc)(char*);
typedef INT_PTR(__cdecl* DPEC_KillAppWatchdogFunc)();
typedef INT_PTR(__cdecl* DPEC_StrokeAppWatchdogFunc)();
typedef INT_PTR(__cdecl* DPEC_StartAppWatchdogFunc)();
typedef INT_PTR(__cdecl* DPEC_SetModeFunc)(int);
typedef INT_PTR(__cdecl* DPEC_GetLibraryVersionFunc)(char*, char*, char*, char*);
typedef INT_PTR(__cdecl* DPEC_GetOpStateFunc)(int, int*);
typedef int(__cdecl* DPEC_RegForAsyncEventsFunc)(DPEC_RegForAsyncEventsCallback callback, int cbRegEvtKey);
typedef int(__cdecl* DPEC_StartOperationFunc)(DPEC_OperationCallback callback, jint lKey, int aLocation, jint tagType, jint var3, int* out1, int* out2);
typedef int(__cdecl* DPEC_StartOperationFunc2)(DPEC_OperationCallback2 callback, jint lKey, int aLocation, jint tagType, jint var3, char* out1, int* out2);


static const char* dpecStartLogging = "DPEC_StartLoggingService";
static const char* dpecRegForAsyncEvents = "DPEC_RegForAsyncEvents";
static const char* dpecStartOperation = "DPEC_StartOperation";
static const char* dpecKillLoggingService = "DPEC_KillLoggingService";
static const char* dpecStartLoggingService = "DPEC_StartLoggingService";
static const char* dpecDisconnect = "DPEC_Disconnect";
static const char* dpecConnect = "DPEC_Connect";
static const char* LibFileName = "DPEC_API.dll";
static const char* dpecSetMode = "DPEC_SetMode";
static const char* dpecGetMode = "DPEC_GetMode";
static const char* dpecGetOpState = "DPEC_GetOpState";
static const char* dpecAbortOperation = "DPEC_aBortOperation";
static const char* dpecStartAppWatchdog = "DPEC_StartAppWatchdog";
static const char* dpecStrokeAppWatchdog = "DPEC_StrokeAppWatchdog";
static const char* dpecKillAppWatchdog = "DPEC_KillAppWatchdog";
static const char* dpecGetLibraryVersion = "DPEC_GetLibraryVersion";
static const char* dpecAddLineToLog = "DPEC_AddLineToLog";


static JavaVM* g_java_vm = nullptr;
static HMODULE g_dpec_handle = nullptr;

jclass g_dpecClass = NULL;
jclass g_exceptionClass = NULL;

// Method IDs
jmethodID g_regForAsynEvents = NULL;
jmethodID g_commonFunction = NULL;
jmethodID g_getTaggedInfo = NULL;
jmethodID g_getStatusQuick = NULL;
jmethodID g_rotateToSlot = NULL;
jmethodID g_ejectCaseFromSlot = NULL;

// Field IDs
jfieldID g_versionMajor = NULL;
jfieldID g_versionMinor = NULL;
jfieldID g_versionBuild = NULL;
jfieldID g_versionString = NULL;

int g_quickStat = 0;
int g_slotStat = 0;
char* g_strStatus;

int __cdecl GetStatusQuickCallback(int key, int opId, int res, int quickStat)
{
    JNIEnv* env = nullptr;
    g_java_vm->AttachCurrentThread((void**)&env, nullptr);

    env->CallStaticVoidMethod(g_dpecClass, g_getStatusQuick, key, (jint)opId, (jint)res, quickStat);

    g_java_vm->DetachCurrentThread();

    return 0;
}

int __cdecl RotateToSlotCallback(int key, int opId, int res, int slotStat)
{
    JNIEnv* env = nullptr;
    g_java_vm->AttachCurrentThread((void**)&env, nullptr);

    env->CallStaticVoidMethod(g_dpecClass, g_rotateToSlot, key, (jint)opId, (jint)res, slotStat);

    g_java_vm->DetachCurrentThread();

    return 0;
}

int __cdecl EjectCaseFromSlotCallback(int key, int opId, int res)
{
    JNIEnv* env = nullptr;
    g_java_vm->AttachCurrentThread((void**)&env, nullptr);

    env->CallStaticVoidMethod(g_dpecClass, g_ejectCaseFromSlot, key, (jint)opId, (jint)res);

    g_java_vm->DetachCurrentThread();

    return 0;
}

int __cdecl CommonFunctionCallback(int key, int opId, int res)
{
    JNIEnv* env = nullptr;
    g_java_vm->AttachCurrentThread((void**)&env, nullptr);

    env->CallStaticVoidMethod(g_dpecClass, g_commonFunction, key, (jint)opId, (jint)res);

    g_java_vm->DetachCurrentThread();

    return 0;
}

int __cdecl RegForAsyncEventsCallback(int key, int event)
{
    JNIEnv* env = nullptr;
    g_java_vm->AttachCurrentThread((void**)&env, nullptr);
    env->CallStaticVoidMethod(g_dpecClass, g_regForAsynEvents, key, event);
    g_java_vm->DetachCurrentThread();
    return 0;
}

int __cdecl GetTaggedInfoCallback(int key, int opId, int res)
{
    int offset = 0;
    char buffer[256] = { 0 };
    int length = 0; // TODO: I see no writes to the variable

    JNIEnv* env = nullptr;
    g_java_vm->AttachCurrentThread((void**)&env, nullptr);

    if (res == 0)
    {
        for (int i = 0; i < length; ++i)
            offset += sprintf_s(&buffer[offset], sizeof(buffer) - offset, "0x%02X ", static_cast<unsigned char>(g_strStatus[i]));
    }

	//buffer[offset] = '\0';
    jstring strStatus = env->NewStringUTF(buffer);

    env->CallStaticVoidMethod(g_dpecClass, g_getTaggedInfo, key, (jint)opId, (jint)res, strStatus);
    env->DeleteLocalRef(strStatus);

    g_java_vm->DetachCurrentThread();

    return 0;
}

JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_Connect(JNIEnv* env, jclass clz)
{
	env->GetJavaVM(&g_java_vm);
	g_dpec_handle = LoadLibraryA(LibFileName);
	if (g_dpec_handle == nullptr) {
		return net_dvdplay_aem_DPEC_RESULT_CANTLOADDLL;
	}

	DPEC_ConnectFunc connectFunc = GetProcAddress(g_dpec_handle, dpecConnect);
	DPEC_DisconnectFunc disconnectAddress = GetProcAddress(g_dpec_handle, dpecDisconnect);
	DPEC_StartLoggingFunc startLoggingAddress = GetProcAddress(g_dpec_handle, dpecStartLogging);
	DPEC_KillLoggingFunc killLoggingAddress = GetProcAddress(g_dpec_handle, dpecKillLoggingService);

	(*startLoggingAddress)();
	int result = connectFunc();
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

	return result;
}


JNIEXPORT void JNICALL Java_net_dvdplay_aem_DPEC_SetGlobalRef(JNIEnv* env, jclass clz, jstring lClassName, jstring lExceptionClassName, jstring lRegForAsynEventsName, jstring lCommonFunctionName, jstring lGetTaggedInfoName, jstring lGetStatusQuickName, jstring lRotateToSlotName, jstring lEjectCaseFromSlotName, jstring lVersionMajor, jstring lVersionMinor, jstring lVersionBuild, jstring lVersionString)
{
	const char* lClassNameChars = env->GetStringUTFChars(lClassName, nullptr);
	const char* lExceptionClassNameChars = env->GetStringUTFChars(lExceptionClassName, nullptr);
	const char* lRegForAsyncEventsNameChars = env->GetStringUTFChars(lRegForAsynEventsName, nullptr);
	const char* lCommonFunctionNameChars = env->GetStringUTFChars(lCommonFunctionName, nullptr);
	const char* lGetTaggedInfoNameChars = env->GetStringUTFChars(lGetTaggedInfoName, nullptr);
	const char* lGetStatusQuickNameChars = env->GetStringUTFChars(lGetStatusQuickName, nullptr);
	const char* lRotateToSlotNameChars = env->GetStringUTFChars(lRotateToSlotName, nullptr);
	const char* lEjectCaseFromSlotNameChars = env->GetStringUTFChars(lEjectCaseFromSlotName, nullptr);
	const char* lVersionMajorChars = env->GetStringUTFChars(lVersionMajor, nullptr);
	const char* lVersionMinorChars = env->GetStringUTFChars(lVersionMinor, nullptr);
	const char* lVersionBuildChars = env->GetStringUTFChars(lVersionBuild, nullptr);
	const char* lVersionStringChars = env->GetStringUTFChars(lVersionString, nullptr);

	g_exceptionClass = env->FindClass(lExceptionClassNameChars);
    if (g_exceptionClass)
    {
        g_dpecClass = env->FindClass(lClassNameChars);
        if (g_dpecClass)
        {
            g_regForAsynEvents = env->GetStaticMethodID(g_dpecClass, lRegForAsyncEventsNameChars, "(II)V");
            if (g_regForAsynEvents)
            {
                g_commonFunction = env->GetStaticMethodID(g_dpecClass, lCommonFunctionNameChars, "(III)V");
                if (g_commonFunction)
                {
                    g_getTaggedInfo = env->GetStaticMethodID(g_dpecClass, lGetTaggedInfoNameChars, "(IIILjava/lang/String;)V");
                    if (g_getTaggedInfo)
                    {
                        g_getStatusQuick = env->GetStaticMethodID(g_dpecClass, lGetStatusQuickNameChars, "(IIII)V");
                        if (g_getStatusQuick)
                        {
                            g_rotateToSlot = env->GetStaticMethodID(g_dpecClass, lRotateToSlotNameChars, "(IIII)V");
                            if (g_rotateToSlot)
                            {
                                g_ejectCaseFromSlot = env->GetStaticMethodID(g_dpecClass, lEjectCaseFromSlotNameChars, "(III)V");
                                if (g_ejectCaseFromSlot)
                                {
                                    g_versionMajor = env->GetStaticFieldID(g_dpecClass, lVersionMajorChars, "B");
                                    if (g_versionMajor)
                                    {
                                        g_versionMinor = env->GetStaticFieldID(g_dpecClass, lVersionMinorChars, "B");
                                        if (g_versionMinor)
                                        {
                                            g_versionBuild = env->GetStaticFieldID(g_dpecClass, lVersionBuildChars, "S");
                                            if (g_versionBuild)
                                            {
                                                g_versionString = env->GetStaticFieldID(
                                                    g_dpecClass,
                                                    lVersionStringChars,
                                                    "Ljava/lang/String;");
                                                if (!g_versionString)
                                                    env->ThrowNew(g_exceptionClass, "DPEC Bridge: can not locate gVersionString field!");
                                            }
                                            else
                                            {
                                                env->ThrowNew(g_exceptionClass, "DPEC Bridge: can not locate gVersionBuild field!");
                                            }
                                        }
                                        else
                                        {
                                            env->ThrowNew(g_exceptionClass, "DPEC Bridge: can not locate gVersionMinor field!");
                                        }
                                    }
                                    else
                                    {
                                        env->ThrowNew(g_exceptionClass, "DPEC Bridge: can not locate gVersionMajor field!");
                                    }
                                }
                                else
                                {
                                    env->ThrowNew(g_exceptionClass, "DPEC Bridge: can not locate gVersionMajor field!");
                                }
                            }
                            else
                            {
                                env->ThrowNew(g_exceptionClass, "DPEC Bridge: can not locate RotateToSlot callback method!");
                            }
                        }
                        else
                        {
                            env->ThrowNew(g_exceptionClass, "DPEC Bridge: can not locate RotateToSlot callback method!");
                        }
                    }
                    else
                    {
                        env->ThrowNew(g_exceptionClass, "DPEC Bridge: can not locate RotateToSlot callback method!");
                    }
                }
                else
                {
                    env->ThrowNew(g_exceptionClass, "DPEC Bridge: can not locate RotateToSlot callback method!");
                }
            }
            else
            {
                env->ThrowNew(g_exceptionClass, "DPEC Bridge: can not locate RegForAsyncEvent callback method!");
            }
        }
        else
        {
            env->ThrowNew(g_exceptionClass, "DPEC Bridge: can not locate callback class!");
        }
    }

    env->ReleaseStringUTFChars(lVersionMajor, lVersionMajorChars);
    env->ReleaseStringUTFChars(lVersionMinor, lVersionMinorChars);
    env->ReleaseStringUTFChars(lVersionBuild, lVersionBuildChars);
    env->ReleaseStringUTFChars(lVersionString, lVersionStringChars);
    env->ReleaseStringUTFChars(lEjectCaseFromSlotName, lEjectCaseFromSlotNameChars);
    env->ReleaseStringUTFChars(lRotateToSlotName, lRotateToSlotNameChars);
    env->ReleaseStringUTFChars(lGetStatusQuickName, lGetStatusQuickNameChars);
    env->ReleaseStringUTFChars(lGetTaggedInfoName, lGetTaggedInfoNameChars);
    env->ReleaseStringUTFChars(lCommonFunctionName, lCommonFunctionNameChars);
    env->ReleaseStringUTFChars(lRegForAsynEventsName, lRegForAsyncEventsNameChars);
    env->ReleaseStringUTFChars(lExceptionClassName, lExceptionClassNameChars);
    env->ReleaseStringUTFChars(lClassName, lClassNameChars);
}


JNIEXPORT void JNICALL Java_net_dvdplay_aem_DPEC_ReleaseGlobalRef(JNIEnv* env, jclass clz)
{
	// not implemented in the original dll
}


JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_Disconnect(JNIEnv* env, jclass clz)
{
	int result = net_dvdplay_aem_DPEC_RESULT_CANTFREEDLL;

	DPEC_DisconnectFunc DPEC_Disconnect = GetProcAddress(g_dpec_handle, dpecDisconnect);
	DPEC_KillLoggingFunc DPEC_KillLoggingService = GetProcAddress(g_dpec_handle, dpecKillLoggingService);

	INT_PTR disconnectRet = DPEC_Disconnect();
	DPEC_KillLoggingService();

	if (FreeLibrary(g_dpec_handle) != 0)
	{
		result = disconnectRet;
	}

	return result;
}


JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_StartOperation(JNIEnv* env, jclass clz, jint lKey, jint aLocation, jint tagType, jint var3)
{
    int result, returnVal;
    char msg[128] = { 0 };

	DPEC_StartOperationFunc DPEC_StartOperation = (DPEC_StartOperationFunc)GetProcAddress(g_dpec_handle, dpecStartOperation);
	DPEC_StartOperationFunc2 DPEC_StartOperation2 = (DPEC_StartOperationFunc2)GetProcAddress(g_dpec_handle, dpecStartOperation);
    switch (aLocation)
    {
	    case net_dvdplay_aem_DPEC_OP_GETSTATUSQUICK:
	        result = DPEC_StartOperation(GetStatusQuickCallback, lKey, aLocation, tagType, var3, &g_quickStat, &returnVal);
            break;
		case net_dvdplay_aem_DPEC_OP_ROTATETOSLOT:
			result = DPEC_StartOperation(RotateToSlotCallback, lKey, aLocation, tagType, var3, &g_slotStat, &returnVal);
            break;
		case net_dvdplay_aem_DPEC_OP_GETTAGGEDINFO:
            result = DPEC_StartOperation2(GetTaggedInfoCallback, lKey, aLocation, tagType, var3, g_strStatus, &returnVal);
            break;
		case net_dvdplay_aem_DPEC_OP_EJECTCASEFROMSLOT:
			result = DPEC_StartOperation2(EjectCaseFromSlotCallback, lKey, aLocation, tagType, var3, nullptr, &returnVal);
            break;
		default:
            if (aLocation > 25)
            {
                sprintf_s(msg, sizeof(msg), "DPEC Bridge: Unknown OpCode was issued from AEM App! OpCode = %d.", aLocation);
                env->ThrowNew(g_exceptionClass, msg);
                result = returnVal;
            }
            else
            {
				result = DPEC_StartOperation2(CommonFunctionCallback, lKey, aLocation, tagType, var3, nullptr, &returnVal);
            }
            break;
    }

    if (result != 0)
    {
        sprintf_s(msg, sizeof(msg), "DPEC Bridge: StartOperation failed! Result = %d.", result);
        env->ThrowNew(g_exceptionClass, msg);
    }

	return returnVal;
}


// Appears unused
JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_GetOpState(JNIEnv* env, jclass clz, jint var0)
{
    int state, returnVal;
	char msg[128] = { 0 };


	DPEC_GetOpStateFunc DPEC_GetOpState = (DPEC_GetOpStateFunc)GetProcAddress(g_dpec_handle, dpecGetOpState);
	returnVal = DPEC_GetOpState(var0, &state);
    if (returnVal != 0)
    {
        sprintf_s(msg, "JNI: GetOpState failed! Result = %d.", returnVal);
		env->ThrowNew(g_exceptionClass, msg);
    }

	return state;
}

// Appears unused
JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_AbortOperation(JNIEnv* env, jclass clz, jint var0)
{
    DPEC_AbortOperationFunc DPEC_AbortOperation = (DPEC_AbortOperationFunc)GetProcAddress(g_dpec_handle, dpecAbortOperation);
	int result = DPEC_AbortOperation(var0);
	return result;
}


JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_RegForAsyncEvents(JNIEnv* env, jclass clz, jint cbRegEvtKey)
{
	DPEC_RegForAsyncEventsFunc DPEC_RegForAsyncEvents = (DPEC_RegForAsyncEventsFunc)GetProcAddress(g_dpec_handle, dpecRegForAsyncEvents);
	int result = DPEC_RegForAsyncEvents(RegForAsyncEventsCallback, cbRegEvtKey);
    return result;
}


JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_SetMode(JNIEnv* env, jclass clz, jint mode)
{
	DPEC_SetModeFunc DPEC_SetMode = (DPEC_SetModeFunc)GetProcAddress(g_dpec_handle, dpecSetMode);
	int result = DPEC_SetMode(mode);
	return result;
}

// Appears unused
JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_GetMode(JNIEnv* env, jclass clz)
{
	DPEC_GetModeFunc DPEC_GetMode = GetProcAddress(g_dpec_handle, dpecGetMode);
	int result = DPEC_GetMode();
	return result;
}


JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_StartAppWatchdog(JNIEnv* env, jclass clz)
{
	DPEC_StartAppWatchdogFunc DPEC_StartAppWatchdog = GetProcAddress(g_dpec_handle, dpecStartAppWatchdog);
	int result = DPEC_StartAppWatchdog();
	return result;
}


JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_StrokeAppWatchdog(JNIEnv* env, jclass clz)
{
	DPEC_StrokeAppWatchdogFunc DPEC_StrokeAppWatchdog = GetProcAddress(g_dpec_handle, dpecStrokeAppWatchdog);
	int result = DPEC_StrokeAppWatchdog();
	return result;
}


JNIEXPORT jint JNICALL Java_net_dvdplay_aem_DPEC_KillAppWatchdog(JNIEnv* env, jclass clz)
{
	DPEC_KillAppWatchdogFunc DPEC_KillAppWatchdog = GetProcAddress(g_dpec_handle, dpecKillAppWatchdog);
	int result = DPEC_KillAppWatchdog();
	return result;
}


// Appears unused
JNIEXPORT void JNICALL Java_net_dvdplay_aem_DPEC_GetLibraryVersion(JNIEnv* env, jclass clz)
{
	DPEC_GetLibraryVersionFunc DPEC_GetLibraryVersion = (DPEC_GetLibraryVersionFunc)GetProcAddress(g_dpec_handle, dpecGetLibraryVersion);
	char buffer[84];

	DPEC_GetLibraryVersion(&buffer[0], &buffer[1], &buffer[2], &buffer[4]);

    env->SetStaticByteField(g_dpecClass, g_versionMajor, buffer[0]);
    env->SetStaticByteField(g_dpecClass, g_versionMinor, buffer[1]);
    env->SetStaticShortField(g_dpecClass, g_versionBuild, buffer[2]);
    jobject versionObj = env->AllocObject(g_dpecClass);
	jstring versionString = env->NewStringUTF(buffer);
    env->SetObjectField(versionObj, g_versionString, versionString);
    env->DeleteLocalRef(versionString);
    env->DeleteLocalRef(versionObj);
}

// Appears unused
JNIEXPORT void JNICALL Java_net_dvdplay_aem_DPEC_AddLineToLog(JNIEnv* env, jclass clz, jstring str)
{
	char* chars = (char*)env->GetStringUTFChars(str, nullptr);
	DPEC_AddLineToLogFunc DPEC_AddLineToLog = (DPEC_AddLineToLogFunc)GetProcAddress(g_dpec_handle, dpecAddLineToLog);
	DPEC_AddLineToLog(chars);
	env->ReleaseStringUTFChars(str, chars);
}

JNIEXPORT void JNICALL Java_net_dvdplay_aem_DPEC_StartLoggingService(JNIEnv* env, jclass clz)
{
	DPEC_StartLoggingFunc DPEC_StartLoggingService = GetProcAddress(g_dpec_handle, dpecStartLoggingService);
	DPEC_StartLoggingService();
}

JNIEXPORT void JNICALL Java_net_dvdplay_aem_DPEC_KillLoggingService(JNIEnv* env, jclass clz)
{
	DPEC_KillLoggingFunc DPEC_KillLoggingService = GetProcAddress(g_dpec_handle, dpecKillLoggingService);
	DPEC_KillLoggingService();
}