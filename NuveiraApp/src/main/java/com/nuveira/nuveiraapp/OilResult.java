package com.nuveira.nuveiraapp;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

// "A class representing a single row of data in the table"
public class OilResult {
    private final StringProperty perfumeName;
    private final StringProperty priceGram;
    private final StringProperty retailRounded;

    public OilResult(String perfumeName, String priceGram, String retailRounded) {
        this.perfumeName = new SimpleStringProperty(perfumeName);
        this.priceGram = new SimpleStringProperty(priceGram);
        this.retailRounded = new SimpleStringProperty(retailRounded);
    }

    public StringProperty perfumeNameProperty() { return perfumeName; }
    public StringProperty priceGramProperty() { return priceGram; }
    public StringProperty retailRoundedProperty() { return retailRounded; }
}