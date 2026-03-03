package com.nuveira.nuveiraapp;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.util.Duration;

public class HelloController {

    // Bind Input Fields
    @FXML private TextField txtName;
    @FXML private TextField txtPrice;
    @FXML private TextField txtAmount;
    @FXML private Label lblLiveRate;

    // Bind Table and Columns
    @FXML private TableView<OilResult> resultTable;
    @FXML private TableColumn<OilResult, String> colPerfumeName;
    @FXML private TableColumn<OilResult, String> colPriceGram;
    @FXML private TableColumn<OilResult, String> colRetailRounded;

    private ObservableList<OilResult> resultsList = FXCollections.observableArrayList();

    //  Timeline Variable
    private Timeline timeline;

    @FXML
    public void initialize() {
        // Bind Columns
        colPerfumeName.setCellValueFactory(cellData -> cellData.getValue().perfumeNameProperty());
        colPriceGram.setCellValueFactory(cellData -> cellData.getValue().priceGramProperty());
        colRetailRounded.setCellValueFactory(cellData -> cellData.getValue().retailRoundedProperty());
        resultTable.setItems(resultsList);

        //  Setup Auto-Update
        setupAutoUpdateRate();
    }

    // Auto-Update Function
    private void setupAutoUpdateRate() {
        // Create a timeline to update the rate every 60 seconds (Interval is adjustable)
        timeline = new Timeline(new KeyFrame(Duration.seconds(60), event -> {
            updateLiveRate();
        }));
        timeline.setCycleCount(Timeline.INDEFINITE); // Infinite Loop
        timeline.play(); // Start Update

        // Update rate upon application startup
        updateLiveRate();
    }

    private void updateLiveRate() {
        double currentRate = 30.50 + (Math.random() * 0.5); // ليه بنستخدم math.random هنا؟
        lblLiveRate.setText(String.format("Live USD/TL : %.4f", currentRate));
        System.out.println("Rate updated automatically!");
    }

    @FXML
    protected void onCalculateButtonClick() {
        try {
            // Read Values and Calculate
            String name = txtName.getText();
            double price = Double.parseDouble(txtPrice.getText());
            double amount = Double.parseDouble(txtAmount.getText());
            // System.out.println("Price = " + price); سعر الزيت بالدولار (للكيلو)
            // System.out.println("Amount = " + amount); عدد جرامات الزيت
            double total = price * amount;
            double pricePerGram = (price * 30) / 100;
            double roundedTotal = Math.round(total * 30);

            // في غلط فالحسابات
            // لازم نرجع نشوف طريقة الحسابات

            // Add Result
            resultsList.add(new OilResult(name, String.format("%.2f TL/g", pricePerGram), String.format("%.2f TL", roundedTotal)));

            // Clear Fields
            txtName.clear();
            txtPrice.clear();
            txtAmount.clear();

        } catch (NumberFormatException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setContentText("Please enter valid numbers.");
            alert.showAndWait();
        }
    }
}