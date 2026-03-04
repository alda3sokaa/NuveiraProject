#include <jni.h>
#include "com_nuveira_nuveiraapp_NativeBridge.h"
#include <stdio.h>
#include <math.h>

typedef struct {
    float oil_price_per_kg_usd;
    float oil_grams;
    float oil_price_per_gram_tl;
} Oil;

static Oil currentOil;
static float USD_TO_TL = 43.9f;  // fallback

JNIEXPORT void JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_setOilData
  (JNIEnv *env, jobject obj, jfloat pricePerKg, jfloat grams) {
    currentOil.oil_price_per_kg_usd = pricePerKg;
    currentOil.oil_grams = grams;
    currentOil.oil_price_per_gram_tl = (pricePerKg / 1000.0f) * USD_TO_TL;
}

JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_getPricePerGramTL
  (JNIEnv *env, jobject obj) {
    return currentOil.oil_price_per_gram_tl;
}

JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_get50MLPrice
  (JNIEnv *env, jobject obj) {
    float oilAmountPriceInTL = 15.0f * currentOil.oil_price_per_gram_tl;
    float RetailPriceInTL = (oilAmountPriceInTL + 11.3f + 26.5f + 20.0f + 36.0f + 4.0f + 35.0f + 15.0f + 5.0f + 5.0f)
                            * 1.1f * 1.03f * 2.2f;
    return RetailPriceInTL;
}

JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_roundToNearest100
  (JNIEnv *env, jobject obj, jfloat value) {
    return roundf(value / 100.0f) * 100.0f;
}

JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_getUsdRate
  (JNIEnv *env, jobject obj) {
    return USD_TO_TL;
}