package com.nuveira.nuveiraapp;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

import java.io.IOException;


public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        // Set Stage Icon (Top Logo)
        try {
            Image icon = new Image(getClass().getResourceAsStream("/com/nuveira/nuveiraapp/Nuveira Logo/nuv.ico"));
            stage.getIcons().add(icon);
        } catch (Exception e) {
            System.out.println("Icon resource not found " + e.getMessage());
        }

        // In HelloApplication.java file
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("hello-view.fxml"));
// Increased width and height to match the professional design
        Scene scene = new Scene(fxmlLoader.load(), 600, 450);
        stage.setTitle("Nuveira App");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}