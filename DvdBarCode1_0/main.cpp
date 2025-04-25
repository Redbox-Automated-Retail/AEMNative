#include <string>

#include "net_dvdplay_aem_BarCodeReader.h"

JNIEXPORT jstring JNICALL Java_net_dvdplay_aem_BarCodeReader_readBarCode(JNIEnv* env, jclass clz, jobject mBarCode, jstring angleList, jboolean aSaveImage, jstring aFilename)
{
	std::string barcodeString = "1234567890";
	return env->NewStringUTF(barcodeString.c_str());

}

JNIEXPORT void JNICALL Java_net_dvdplay_aem_BarCodeReader_showVideoFormatDlg(JNIEnv* env, jclass clz)
{
	
}

JNIEXPORT void JNICALL Java_net_dvdplay_aem_BarCodeReader_showVideoSourceDlg(JNIEnv* env, jclass clz)
{
	
}

JNIEXPORT void JNICALL Java_net_dvdplay_aem_BarCodeReader_showVideoDisplayDlg(JNIEnv* env, jclass clz)
{
	
}

JNIEXPORT void JNICALL Java_net_dvdplay_aem_BarCodeReader_showVideoCompressionDlg(JNIEnv* env, jclass clz)
{
	
}

JNIEXPORT jint JNICALL Java_net_dvdplay_aem_BarCodeReader_getVolume(JNIEnv* env, jclass clz)
{
	return 0;
}

JNIEXPORT void JNICALL Java_net_dvdplay_aem_BarCodeReader_setVolume(JNIEnv* env, jclass clz, jint aVol)
{
	
}

JNIEXPORT void JNICALL Java_net_dvdplay_aem_BarCodeReader_startButton(JNIEnv* env, jclass clz)
{
	
}

JNIEXPORT jboolean JNICALL Java_net_dvdplay_aem_BarCodeReader_checkInstance(JNIEnv* env, jclass clz)
{
	return true;
}