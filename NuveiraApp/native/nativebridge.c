#include <jni.h>
#include <stdio.h>
#include <math.h>
#include "com_nuveira_nuveiraapp_NativeBridge.h"

float globalPricePerKg = 0.0f;
float globalGrams = 0.0f;

// 1. Capture the data from the text fields
JNIEXPORT void JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_setOilData
  (JNIEnv *env, jobject obj, jfloat pricePerKg, jfloat grams) {
    globalPricePerKg = pricePerKg;
    globalGrams = grams;
}

// 2. Calculate Gram Price with 20.0 tax and 44.10 rate
JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_getPricePerGramTL
  (JNIEnv *env, jobject obj) {
    float usdToTl = 44.10f; // Matching your screenshot
    float tax = 0.0f;

    if (globalGrams < 100.0f) tax = 20.0f;
    else if (globalGrams < 250.0f) tax = 15.0f;
    else if (globalGrams < 500.0f) tax = 10.0f;

    // (Price + Tax) * Rate / 1000
    float taxedPriceInTl = (globalPricePerKg + tax) * usdToTl;
    return taxedPriceInTl / 1000.0f;
}

// 3. Calculate 50ML Price
JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_get50MLPrice
  (JNIEnv *env, jobject obj) {
    float gramPrice = Java_com_nuveira_nuveiraapp_NativeBridge_getPricePerGramTL(env, obj);
    return gramPrice * 50.0f; 
}

// 4. Round UP to nearest 100
JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_roundToNearest100
  (JNIEnv *env, jobject obj, jfloat value) {
    // If value is 510, this returns 600
    return ceilf(value / 100.0f) * 100.0f;
}

JNIEXPORT jfloat JNICALL Java_com_nuveira_nuveiraapp_NativeBridge_getLiveRateFromC
  (JNIEnv *env, jobject obj) {
    return 44.10f;
}