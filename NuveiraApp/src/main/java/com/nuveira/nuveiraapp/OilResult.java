package com.nuveira.nuveiraapp;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class OilResult {
    private final StringProperty perfumeName;
    private final StringProperty priceGram;
    private final StringProperty retailRounded;
    private final double actualCost; // // Calculate the actual cost: Price per gram * Number of grams

    public OilResult(String perfumeName, String priceGram, String retailRounded, double actualCost) {
        this.perfumeName = new SimpleStringProperty(perfumeName);
        this.priceGram = new SimpleStringProperty(priceGram);
        this.retailRounded = new SimpleStringProperty(retailRounded);
        this.actualCost = actualCost;
    }

    public StringProperty perfumeNameProperty() { return perfumeName; }
    public StringProperty priceGramProperty() { return priceGram; }
    public StringProperty retailRoundedProperty() { return retailRounded; }

    public double getActualCost() { return actualCost; } // دالة لجلب التكلفة للجمع

    public double getTotalPriceValue() {
        try {
            return Double.parseDouble(retailRounded.get().replaceAll("[^0-9.]", ""));
        } catch (Exception e) { return 0.0; }
    }
}