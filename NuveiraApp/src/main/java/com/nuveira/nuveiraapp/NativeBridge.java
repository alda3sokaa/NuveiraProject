package com.nuveira.nuveiraapp;

public class NativeBridge {

    static {
        System.loadLibrary("native");
    }
    public native void setOilData(float pricePerKg, float grams);
    public native float getPricePerGramTL();
    public native float get50MLPrice();
    public native float roundToNearest100(float value);
    public native float getUsdRate();
}