package sample.controllers;

import javafx.fxml.FXML;
import javafx.scene.control.Button;

public class SuccessAddOrderController {

    @FXML
    private Button successAddOkButton;

    @FXML
    void initialize() {

        // нажатие на кнопку Ок(птичка)
        successAddOkButton.setOnAction(event -> {
            // закрыть это окно
            successAddOkButton.getScene().getWindow().hide();
        });
    }
}
