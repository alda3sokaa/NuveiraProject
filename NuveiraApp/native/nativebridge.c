#include <jni.h>
#include "com_nuveira_nuveiraapp_NativeBridge.h"
#include <stdio.h>
#include <math.h>

// Struct to hold our state in C memory
typedef struct {
    float oil_price_per_kg_usd;
    float oil_grams;
    float oil_price_per_gram_tl;
} Oil;

static Oil currentOil;
static float USD_TO_TL = 44.0f;  // Current fallback rate

// 1. Set the initial data and calculate the base TL price
JNIEXPORT void JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_setOilData
  (JNIEnv *env, jobject obj, jfloat pricePerKg, jfloat grams) {
    currentOil.oil_price_per_kg_usd = pricePerKg;
    currentOil.oil_grams = grams;
    
    // Calculation: (USD Price / 1000g) * Exchange Rate
    currentOil.oil_price_per_gram_tl = (pricePerKg / 1000.0f) * USD_TO_TL;
    
    printf("[C DEBUG] Data Set: %.2f USD/kg -> %.4f TL/gram\n", pricePerKg, currentOil.oil_price_per_gram_tl);
}

// 2. Return the calculated price per gram
JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_getPricePerGramTL
  (JNIEnv *env, jobject obj) {
    return currentOil.oil_price_per_gram_tl;
}

// 3. Calculate the retail price for 50ML based on the formula
JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_get50MLPrice
  (JNIEnv *env, jobject obj) {
    // 15 grams used for 50ml logic
    float oilAmountPriceInTL = 15.0f * currentOil.oil_price_per_gram_tl;
    
    // Sum of all costs + Markups (Tax 1.1, Margin 1.03, Profit/Dist 2.2)
    float baseCosts = (oilAmountPriceInTL + 11.3f + 26.5f + 20.0f + 36.0f + 4.0f + 35.0f + 15.0f + 5.0f + 5.0f);
    float RetailPriceInTL = baseCosts * 1.1f * 1.03f * 2.2f;
    
    return RetailPriceInTL;
}

// 4. Utility to round values to the nearest 100
JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_roundToNearest100
  (JNIEnv *env, jobject obj, jfloat value) {
    return roundf(value / 100.0f) * 100.0f;
}

// 5. Getter for the exchange rate
JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_getUsdRate
  (JNIEnv *env, jobject obj) {
    return USD_TO_TL;
}