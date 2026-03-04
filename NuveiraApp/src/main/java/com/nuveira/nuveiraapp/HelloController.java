package com.nuveira.nuveiraapp;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.util.Duration;

public class HelloController {

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

    private void updateLiveRate() {
        // Start from 44.00 as per management feedback
        currentExchangeRate = 44.00 + (Math.random() * 0.5);
        lblLiveRate.setText(String.format("Live USD/TL : %.2f", currentExchangeRate));
    }

    @FXML
    protected void onCalculateButtonClick() {
        try {
            String name = txtName.getText();
            double price = Double.parseDouble(txtPrice.getText());
            double amount = Double.parseDouble(txtAmount.getText());

            // Dynamic Calculation based on the Live Rate
            double pricePerGram = (price * currentExchangeRate) / 100;
            double roundedTotal = Math.round((price * amount) * currentExchangeRate);

            resultsList.add(new OilResult(name,
                    String.format("%.2f TL/g", pricePerGram),
                    String.format("%.2f TL", roundedTotal)));
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