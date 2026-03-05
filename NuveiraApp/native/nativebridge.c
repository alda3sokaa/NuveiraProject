#include <jni.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "com_nuveira_nuveiraapp_NativeBridge.h"

<<<<<<< HEAD
float USD_TO_TL = 44.10f; 
float globalPricePerKg = 0.0f;
float globalGrams = 0.0f;
=======
// --- Constants from your original code ---
float USD_TO_TL = 44.10f; // This matches your screenshot rate
>>>>>>> b7b5985c471464485523d241640ff8f2095aa688

const float SUEDE_BAG_COST = 26.5f;
const float CARTON_BAG_COST = 11.3f;
const float ETHANOL_50ML_COST = 20.0f;
const float BOTTLE_COST_50ML = 36.0f;
const float STICKER_COST = 4.0f;
const float LABOR_COST = 35.0f;
const float DEVELOPMENT_COST = 15.0f;
const float SAMPLE_COST = 5.0f;
const float THANK_YOU_CARD = 4.0f;
const float RAMADAN_CARD = 5.0f;
const float OIL_IN_50ML = 16.5f;
const float MARKETING_PERCENTAGE = 1.1f;
const float FAULT_PERCENTAGE = 1.03f;
const float PROFIT_PERCENTAGE = 2.2f;
const float SMALL_BATCH_TAX = 20.0f;
const float MEDIUM_BATCH_TAX = 10.0f;
const float LARGE_BATCH_TAX = 5.0f;

JNIEXPORT void JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_setExchangeRate(JNIEnv *env, jobject obj, jfloat rate) {
    USD_TO_TL = rate;
}

JNIEXPORT void JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_setOilData(JNIEnv *env, jobject obj, jfloat pricePerKg, jfloat grams) {
    globalPricePerKg = pricePerKg;
    globalGrams = grams;
}

JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_getPricePerGramTL(JNIEnv *env, jobject obj) {
    float pricePerKg = globalPricePerKg;
    if (globalGrams < 100.0f) pricePerKg += SMALL_BATCH_TAX;
    else if (globalGrams < 250.0f) pricePerKg += MEDIUM_BATCH_TAX;
    else if (globalGrams < 500.0f) pricePerKg += LARGE_BATCH_TAX;
    return (pricePerKg / 1000.0f) * USD_TO_TL;
}

JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_get50MLPrice(JNIEnv *env, jobject obj) {
    float gramPriceTl = Java_com_nuveira_nuveiraapp_NativeBridge_getPricePerGramTL(env, obj);
    float oilAmountPriceTl = OIL_IN_50ML * gramPriceTl;
<<<<<<< HEAD
=======

    // The EXACT formula from your Calculate50MLPrice function
>>>>>>> b7b5985c471464485523d241640ff8f2095aa688
    float retailPriceInTl = (oilAmountPriceTl + CARTON_BAG_COST + SUEDE_BAG_COST +
                ETHANOL_50ML_COST + BOTTLE_COST_50ML + 
                STICKER_COST + LABOR_COST + DEVELOPMENT_COST + 
                SAMPLE_COST + RAMADAN_CARD + 
                THANK_YOU_CARD) * MARKETING_PERCENTAGE
                * FAULT_PERCENTAGE * PROFIT_PERCENTAGE;
    return retailPriceInTl;
}

<<<<<<< HEAD
JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_roundToNearest100(JNIEnv *env, jobject obj, jfloat price) {
=======
JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_roundToNearest100
  (JNIEnv *env, jobject obj, jfloat price) {
    // Your original code used roundf (nearest), not ceilf (up)
    // 510.0 -> 500.0 | 551.0 -> 600.0
>>>>>>> b7b5985c471464485523d241640ff8f2095aa688
    return roundf(price / 100.0f) * 100.0f;
}

JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_getLiveRateFromC(JNIEnv *env, jobject obj) {
    return USD_TO_TL;
}

JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_getUsdRate(JNIEnv *env, jobject obj) {
    return USD_TO_TL;
}