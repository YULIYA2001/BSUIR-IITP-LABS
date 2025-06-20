package sample.controllers;

import java.io.IOException;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.stage.Stage;

public class SuccessSignUpController {

    @FXML
    public Label successLabel;

    @FXML
    private Button successSignUpOkButton;

    @FXML
    void initialize() {

        // нажатие на кнопку Ок(птичка)
        successSignUpOkButton.setOnAction(event -> {

            // закрыть это окно и родителя и переити на новое (вход)
            Stage stage1 = (Stage) successSignUpOkButton.getScene().getWindow();
            Stage parentStage = (Stage) stage1.getOwner();
            stage1.hide();
            parentStage.hide();

            // найти новое окно
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/sample/fxml/sample.fxml"));
            // загрузить его
            try {
                loader.load();
            } catch (IOException e){
                e.printStackTrace();
                System.out.print("WRONG sample.fxml");
            }

            // отобразить новое окно
            Parent root = loader.getRoot();
            Stage stage = new Stage();
            stage.setScene(new Scene(root));
            // невозможно менять размеры окна
            stage.setResizable(false);
            // иконка в углу программы
            stage.getIcons().add(new Image("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\onion.png"));
            stage.show();
        });
    }
}

