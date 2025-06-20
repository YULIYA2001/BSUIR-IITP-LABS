package sample.controllers;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.image.Image;
import javafx.stage.Stage;
import sample.Main;

import java.io.IOException;
import java.io.File;
import java.util.Scanner;
import java.io.FileNotFoundException;

public class AboutCompanyController {

    @FXML
    private TextArea aboutCompanyTextArea;

    @FXML
    private Button backButton;

    @FXML
    void initialize() {

        File file = new File(Main.passAboutCompany);
        try (Scanner input = new Scanner(file)) {
            while (input.hasNextLine()) {
                aboutCompanyTextArea.appendText(input.nextLine());
            }
        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
            System.out.print("WRONG WITH FILE О_нас.txt");
        }
        aboutCompanyTextArea.positionCaret(0);

        // нажатие на кнопку Назад
        backButton.setOnAction(event -> {

            // закрыть это окно
            Stage stage1 = (Stage) backButton.getScene().getWindow();
            stage1.hide();

            // найти новое окно
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/sample/fxml/catalog.fxml"));
            // загрузить его
            try {
                loader.load();
            } catch (IOException e){
                e.printStackTrace();
                System.out.print("WRONG IN catalog.fxml");
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
