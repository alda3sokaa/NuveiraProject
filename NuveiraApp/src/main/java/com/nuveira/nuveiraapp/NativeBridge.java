package com.nuveira.nuveiraapp;

import java.io.File;

public class NativeBridge {
    static {
        try {
            File lib = new File("NativeBridge.dll").getAbsoluteFile();
            System.load(lib.getAbsolutePath());
            System.out.println("[SUCCESS] DLL loaded from: " + lib.getAbsolutePath());
        } catch (UnsatisfiedLinkError e) {
            System.err.println("[ERROR] Could not find or load NativeBridge.dll at: " + new File("NativeBridge.dll").getAbsolutePath());
        }
    }

    public native void setOilData(float pricePerKg, float grams);
    public native float get50MLPrice();
    public native float getUsdRate();
    public native float getLiveRateFromC();

    // ADDED THESE TWO - They were missing!
    public native float getPricePerGramTL();
    public native float roundToNearest100(float value);
}