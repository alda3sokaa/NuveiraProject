#include <jni.h>
#include <stdio.h>

// Global State
float usd_to_tl = 44.0f;
float oil_price_per_gram_tl = 0.0f;

// Match the Java package: com.nuveira.nuveiraapp
// Format: Java_package_path_ClassName_MethodName

JNIEXPORT void JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_setOilData
(JNIEnv *env, jobject obj, jfloat pricePerKg, jfloat grams) {
    oil_price_per_gram_tl = (pricePerKg / 1000.0f) * usd_to_tl;
    printf("[C] Data set. Price per gram: %.4f TL\n", oil_price_per_gram_tl);
}

JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_get50MLPrice
(JNIEnv *env, jobject obj) {
    // Basic formula: (15g * price) + fixed costs (approx 150) * multiplier
    float result = (15.0f * oil_price_per_gram_tl + 150.0f) * 2.2f;
    return result;
}

JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_getUsdRate
(JNIEnv *env, jobject obj) {
    return usd_to_tl;
}

JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_getLiveRateFromC
(JNIEnv *env, jobject obj) {
    return usd_to_tl;
}