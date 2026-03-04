#include <jni.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    float oil_price_per_kg_usd;
    float oil_grams;
    float oil_price_per_gram_tl;
} Oil;

static Oil currentOil;
static const float USD_TO_TL = 44.0f;
static const float BATCH_TAX_RATE = 0.10f;

// 1. Fixed for the button click
JNIEXPORT void JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_setOilData
  (JNIEnv *env, jobject obj, jfloat pricePerKg, jfloat grams) {
    currentOil.oil_price_per_kg_usd = (float)pricePerKg;
    currentOil.oil_grams = (float)grams;
    currentOil.oil_price_per_gram_tl = ((float)pricePerKg / 1000.0f) * USD_TO_TL;
    // Note: use printf only for debugging, it shows up in the IntelliJ console
    printf("[C DEBUG] Set: %.2f USD/kg\n", pricePerKg);
}

// 2. Fixed for the display
JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_get50MLPrice
  (JNIEnv *env, jobject obj) {
    float oilAmountPriceInTL = 15.0f * currentOil.oil_price_per_gram_tl;
    float baseCosts = (oilAmountPriceInTL + 11.3f + 26.5f + 20.0f + 36.0f + 4.0f + 35.0f + 15.0f + 5.0f + 5.0f);
    float retailPriceInTL = baseCosts * (1.0f + BATCH_TAX_RATE) * 1.03f * 2.2f;
    return (jfloat)retailPriceInTL;
}

// 3. Keep these for stability
JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_getLiveRateFromC(JNIEnv *env, jobject obj) { return USD_TO_TL; }
JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_getUsdRate(JNIEnv *env, jobject obj) { return USD_TO_TL; }
JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_getPricePerGramTL(JNIEnv *env, jobject obj) { return currentOil.oil_price_per_gram_tl; }
JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_roundToNearest100(JNIEnv *env, jobject obj, jfloat value) { return floorf(value / 100.0f) * 100.0f; }