/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class net_dvdplay_aem_CreditCardReader */

#ifndef _Included_net_dvdplay_aem_CreditCardReader
#define _Included_net_dvdplay_aem_CreditCardReader
#ifdef __cplusplus
extern "C" {
#endif
#undef net_dvdplay_aem_CreditCardReader_mReadTimeout
#define net_dvdplay_aem_CreditCardReader_mReadTimeout 15000L
/*
 * Class:     net_dvdplay_aem_CreditCardReader
 * Method:    startCardRead
 * Signature: (Lnet/dvdplay/aem/CreditCard;Z)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_net_dvdplay_aem_CreditCardReader_startCardRead
  (JNIEnv *, jclass, jobject, jboolean);

/*
 * Class:     net_dvdplay_aem_CreditCardReader
 * Method:    stopCardRead
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_net_dvdplay_aem_CreditCardReader_stopCardRead
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
