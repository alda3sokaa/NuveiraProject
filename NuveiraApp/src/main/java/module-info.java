module com.nuveira.nuveiraapp {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.net.http;
    requires com.fasterxml.jackson.databind;
    requires de.jensd.fx.glyphs.fontawesome;
    requires de.jensd.fx.glyphs.commons;

    opens com.nuveira.nuveiraapp to javafx.fxml;
    exports com.nuveira.nuveiraapp;
}