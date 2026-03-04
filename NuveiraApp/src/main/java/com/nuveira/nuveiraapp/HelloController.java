package com.nuveira.nuveiraapp;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.util.Duration;
import com.nuveira.nuveiraapp.NativeBridge;

public class HelloController  {

    static {
        System.loadLibrary("native");
    }

    private final NativeBridge bridge = new NativeBridge();

    private double currentExchangeRate = 44.00;

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
        // 1. Bind columns to data properties
        colPerfumeName.setCellValueFactory(cellData -> cellData.getValue().perfumeNameProperty());
        colPriceGram.setCellValueFactory(cellData -> cellData.getValue().priceGramProperty());
        colRetailRounded.setCellValueFactory(cellData -> cellData.getValue().retailRoundedProperty());

        // 2. Set the data list to the TableView
        resultTable.setItems(resultsList);

        // 3. Apply white text color to cells for Dark Mode
        setWhiteText(colPerfumeName);
        setWhiteText(colPriceGram);
        setWhiteText(colRetailRounded);

        // 4. Initialize the automatic exchange rate update
        setupAutoUpdateRate();
    }

    /**
     * Helper method to customize table cells with white text color
     * to ensure readability on dark backgrounds.
     */
    private void setWhiteText(TableColumn<OilResult, String> column) {
        column.setCellFactory(tc -> new TableCell<OilResult, String>() {
            @Override
            protected void updateItem(String item, boolean empty) {
                super.updateItem(item, empty);
                if (empty || item == null) {
                    setText(null);
                    setStyle("");
                } else {
                    setText(item);
                    setStyle("-fx-text-fill: white; -fx-alignment: CENTER-LEFT; -fx-font-size: 13px;");
                }
            }
        });
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

    /**
     * METHOD NOTE:
     * This is a simulated live rate for demonstration purposes.
     * Currently, it's not connected to a real bank or stock exchange API.
     * Purpose: To show how the UI and calculations dynamically update.
     * Future Task: Integrate a real-time Currency API.
     */
    private void updateLiveRate() {
        // Start from 44.00 as per management feedback
        currentExchangeRate = 44.00 + (Math.random() * 0.5);
        lblLiveRate.setText(String.format("Live USD/TL : %.2f", currentExchangeRate));

        // Console log for debugging
        System.out.println("Rate updated (Simulation): " + currentExchangeRate);
    }

    @FXML
    protected void onCalculateButtonClick() {
        try {
            // 1. Read input values from TextFields
            String name = txtName.getText();
            double pricePerKiloUSD = Double.parseDouble(txtPrice.getText()); // Oil price per Kilogram in USD
            double amountInGrams = Double.parseDouble(txtAmount.getText()); // Required amount in Grams

            // 2. Dynamic calculations based on current exchange rate (starting from 44.00)
            // Calculate the price of a single gram in Turkish Lira (TL)
            double pricePerGramTL = (pricePerKiloUSD * currentExchangeRate) / 1000;

            // Calculate total amount in TL (Price per gram * requested amount)
            double totalTL = pricePerGramTL * amountInGrams;
            double roundedTotalTL = Math.round(totalTL); // Round to the nearest whole number for retail

            // في غلط فالحسابات
            // لازم نرجع نشوف طريقة الحسابات

            // 3. Add the result to the TableView (Single entry)
            resultsList.add(new OilResult(
                    name,
                    String.format("%.2f TL/g", pricePerGramTL),
                    String.format("%.0f TL", roundedTotalTL)
            ));

            // 4. Clear input fields for next entry
            txtName.clear();
            txtPrice.clear();
            txtAmount.clear();

        } catch (NumberFormatException e) {
            // Show error alert if user inputs are not valid numbers
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Input Error");
            alert.setHeaderText(null);
            alert.setContentText("Please enter valid numbers for price and amount.");
            alert.showAndWait();
        }
    }
}