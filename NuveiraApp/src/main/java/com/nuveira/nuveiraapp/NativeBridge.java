package com.nuveira.nuveiraapp;

import java.io.File;

public class NativeBridge {
    static {
        try {
            // This version prints exactly where it's looking before it tries to load
            String libraryPath = new File("NativeBridge.dll").getAbsolutePath();
            System.out.println("[DEBUG] Attempting to load DLL from: " + libraryPath);

            System.load(libraryPath);
            System.out.println("[SUCCESS] DLL loaded successfully!");
        } catch (Throwable e) {
            System.err.println("[CRITICAL ERROR] DLL Load Failed!");
            e.printStackTrace(); // This will show us the REAL reason it failed
        }
    }

    public native void setOilData(float pricePerKg, float grams);
    public native float get50MLPrice();
    public native float getUsdRate();
    public native float getLiveRateFromC();

    // ADDED THESE TWO - They were missing!
    public native float getPricePerGramTL();
    public native float roundToNearest100(float value);
    public native void setExchangeRate(float rate);

}