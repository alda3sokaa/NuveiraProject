package com.nuveira.nuveiraapp;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.util.Duration;

public class HelloController {

    // 1. REMOVED static { System.loadLibrary("native"); }
    // It should ONLY be inside NativeBridge.java to avoid duplicate loading errors.

    private final NativeBridge bridge = new NativeBridge();

    @FXML private TextField txtName;
    @FXML private TextField txtPrice;
    @FXML private TextField txtAmount;
    @FXML private Label lblLiveRate;

    @FXML private TableView<OilResult> resultTable;
    @FXML private TableColumn<OilResult, String> colPerfumeName;
    @FXML private TableColumn<OilResult, String> colPriceGram;
    @FXML private TableColumn<OilResult, String> colRetailRounded;

    private ObservableList<OilResult> resultsList = FXCollections.observableArrayList();
    private Timeline timeline;

    @FXML
    public void initialize() {
        colPerfumeName.setCellValueFactory(cellData -> cellData.getValue().perfumeNameProperty());
        colPriceGram.setCellValueFactory(cellData -> cellData.getValue().priceGramProperty());
        colRetailRounded.setCellValueFactory(cellData -> cellData.getValue().retailRoundedProperty());

        resultTable.setItems(resultsList);

        setWhiteText(colPerfumeName);
        setWhiteText(colPriceGram);
        setWhiteText(colRetailRounded);

        setupAutoUpdateRate();
    }

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

    private void setupAutoUpdateRate() {
        timeline = new Timeline(new KeyFrame(Duration.seconds(60), event -> {
            updateLiveRate();
        }));
        timeline.setCycleCount(Timeline.INDEFINITE);
        timeline.play();
        updateLiveRate();
    }

    private void updateLiveRate() {
        // 2. FIXED: Pull the actual rate from your C code instead of random math
        float rateFromC = bridge.getLiveRateFromC();
        lblLiveRate.setText(String.format("Live USD/TL : %.2f", rateFromC));
    }

    @FXML
    protected void onCalculateButtonClick() {
        try {
            String name = txtName.getText();
            float pricePerKiloUSD = Float.parseFloat(txtPrice.getText());
            float amountInGrams = Float.parseFloat(txtAmount.getText());

            // 3. JNI CALLS
            bridge.setOilData(pricePerKiloUSD, amountInGrams);

            float pricePerGramTL = bridge.getPricePerGramTL();
            float retailPrice50ML = bridge.get50MLPrice();
            float roundedPrice = bridge.roundToNearest100(retailPrice50ML);


            resultsList.add(new OilResult(
                    name,
                    String.format("%.2f TL/g", pricePerGramTL),
                    String.format("%.2f TL", roundedPrice)
            ));

            txtName.clear();
            txtPrice.clear();
            txtAmount.clear();

        } catch (NumberFormatException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Input Error");
            alert.setContentText("Please enter valid numbers for price and amount.");
            alert.showAndWait();
        }
    }
}