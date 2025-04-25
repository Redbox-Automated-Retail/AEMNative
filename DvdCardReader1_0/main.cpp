#include <string>

#include "net_dvdplay_aem_CreditCardReader.h"

JNIEXPORT jstring JNICALL Java_net_dvdplay_aem_CreditCardReader_startCardRead(JNIEnv* env, jclass clz, jobject mCC, jboolean mStripSentinels)
{
	std::string cardData = "1234567890123456";
	return env->NewStringUTF(cardData.c_str());
}

JNIEXPORT jint JNICALL Java_net_dvdplay_aem_CreditCardReader_stopCardRead(JNIEnv* env, jclass clz)
{
	return 0;
}