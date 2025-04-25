#include "net_dvdplay_aem_NMC.h"
#include <string>

JNIEXPORT jint JNICALL Java_net_dvdplay_aem_NMC_NmcInit(JNIEnv* env, jclass clz, jstring port, jint baud)
{
	return 0;
}

JNIEXPORT void JNICALL Java_net_dvdplay_aem_NMC_NmcShutdown(JNIEnv* env, jclass clz)
{

}

// Appears unused
JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_NmcHardReset(JNIEnv* env, jclass clz, jbyte var0)
{
	return true;
}

// Appears unused
JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_NmcNoOp(JNIEnv* env, jclass clz, jbyte var0)
{
	return true;
}


JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_NmcDefineStatus(JNIEnv* env, jclass clz, jbyte var0, jbyte var1)
{
	return true;
}

JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_NmcReadStatus(JNIEnv* env, jclass clz, jbyte var0, jbyte var1)
{
	return true;
}

JNIEXPORT jint JNICALL Java_net_dvdplay_aem_NMC_NmcGetStat(JNIEnv* env, jclass clz, jbyte var0)
{
	return 0;
}

JNIEXPORT void JNICALL Java_net_dvdplay_aem_NMC_ErrorPrinting(JNIEnv* env, jclass clz, jint var0)
{

}

// Appears unused
JNIEXPORT jchar JNICALL Java_net_dvdplay_aem_NMC_SioOpen(JNIEnv* env, jclass clz, jstring var0, jint var1)
{
	return 'a';
}

// Appears unused
JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_SioClose(JNIEnv* env, jclass clz, jchar var0)
{
	return true;
}

// Appears unused
JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_SioPutChars(JNIEnv* env, jclass clz, jchar var0, jstring var1, jint var2)
{
	return true;
}

// Appears unused
JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_SioChangeBaud(JNIEnv* env, jclass clz, jchar var0, jint var1)
{
	return true;
}

// Appears unused
JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_SioClrInbuf(JNIEnv* env, jclass clz, jchar var0)
{
	return true;
}

JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_IoClrOutBit(JNIEnv* env, jclass clz, jbyte var0, jint var1)
{
	return true;
}

JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_IoBitDirIn(JNIEnv* env, jclass clz, jbyte var0, jint var1)
{
	return true;
}

JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_IoBitDirOut(JNIEnv* env, jclass clz, jbyte var0, jint var1)
{
	return true;
}

JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_IoInBitVal(JNIEnv* env, jclass clz, jbyte var0, jint var1)
{
	return true;
}

JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_IoSetOutBit(JNIEnv* env, jclass clz, jbyte var0, jint var1)
{
	return true;
}

JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_IoSetPWMVal(JNIEnv* env, jclass clz, jbyte var0, jbyte var1, jbyte mLevel)
{
	return true;
}

JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_ServoSetGain(JNIEnv* env, jclass clz, jbyte var0, jint aServoKp, jint aServoKd, jint aServoKi, jint aServoIntegrationLimit, jbyte aServoOutputLimit, jbyte aServoCurrentLimit, jint aServoPositionErrorLimit, jbyte aServoServoRate, jbyte aServoDeadbandComp)
{
	return true;
}

JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_ServoStopMotor(JNIEnv* env, jclass clz, jbyte var0, jbyte var1)
{
	return true;
}

JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_ServoLoadTraj(JNIEnv* env, jclass clz, jbyte var0, jbyte var1, jint aLocation, jint aVelocity, jint aAcceleration, jbyte iPwm)
{
	return true;
}

JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_NMC_ServoSetHoming(JNIEnv* env, jclass clz, jbyte var0, jbyte var1)
{
	return true;
}

JNIEXPORT jint JNICALL Java_net_dvdplay_aem_NMC_ServoGetHome(JNIEnv* env, jclass clz, jbyte var0)
{
	return 0;
}

JNIEXPORT jint JNICALL Java_net_dvdplay_aem_NMC_ServoGetPos(JNIEnv* env, jclass clz, jbyte var0)
{
	return 0;
}

JNIEXPORT jstring JNICALL Java_net_dvdplay_aem_NMC_getTimeZoneInfo(JNIEnv* env, jclass clz)
{
	std::string timeZoneInfo = "TimeZoneInfo";
	return env->NewStringUTF(timeZoneInfo.c_str());
}

JNIEXPORT void JNICALL Java_net_dvdplay_aem_NMC_setTimeZoneInfo(JNIEnv* env, jclass clz, jint lBias, jint lDSTBias, jint lUsesDST, jint mTimeZoneAutoAdj)
{

}