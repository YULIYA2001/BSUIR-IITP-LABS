package sample.controllers;

import javafx.fxml.FXML;
import javafx.scene.control.Button;

public class FaultController {

    @FXML
    private Button faultOkButton;

    @FXML
    void initialize() {

        // нажатие на кнопку Ок(птичка)
        faultOkButton.setOnAction(event -> {
            // закрыть это окно
            faultOkButton.getScene().getWindow().hide();
        });
    }
}

