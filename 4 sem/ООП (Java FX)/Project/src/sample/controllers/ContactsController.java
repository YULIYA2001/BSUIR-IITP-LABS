package sample.controllers;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.stage.Stage;
import sample.classes.Company;

import java.io.IOException;

public class ContactsController {

    @FXML
    private TextField workTimeTextField;

    @FXML
    private TextField nameTextField;

    @FXML
    private TextField phoneTextField;

    @FXML
    private TextField addressTextField;

    @FXML
    private TextArea addReviewTextArea;

    @FXML
    private TextArea reviewsTextArea;

    @FXML
    private Button addReviewButton;

    @FXML
    private Button backButton;

    @FXML
    void initialize() {

        // загрузка контактной информации из объекта класса компании
        loadInformationAboutCompany();

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


        // нажатие на кнопку Добавить (отзыв)
        addReviewButton.setOnAction(event -> {

            if (!addReviewTextArea.getText().trim().equals(""))
            {
                reviewsTextArea.appendText(addReviewTextArea.getText().trim()+"\n");
                Company.getInstance().setReviews(addReviewTextArea.getText()+"\n");
                addReviewTextArea.setText("");
            }
        });
    }

    private void loadInformationAboutCompany() {

        Company company = Company.getInstance();
        nameTextField.setText(company.getName());
        phoneTextField.setText(company.getPhoneNumber());
        addressTextField.setText(company.getAddress());
        workTimeTextField.setText(company.getWorkTime());

        int len = company.getReviews().size();
        for (int i=0; i<len; i++)
            reviewsTextArea.appendText(company.getReviews().get(i));
    }
}

