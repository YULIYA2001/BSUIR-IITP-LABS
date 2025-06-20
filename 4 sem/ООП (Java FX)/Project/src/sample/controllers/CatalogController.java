package sample.controllers;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import java.io.IOException;

public class CatalogController {

    @FXML
    private Button appleButton;

    @FXML
    private Button cucumberButton;

    @FXML
    private Button potatoButton;

    @FXML
    private Button pearButton;

    @FXML
    private Button tomatoButton;

    @FXML
    private Button cartButton;

    @FXML
    private Button contactsButton;

    @FXML
    private Button aboutCompanyButton;

    @FXML
    private Button exitButton;

    @FXML
    private Button cabinetButton;

    @FXML
    void initialize() {

        // кнопка Выход
        exitButton.setOnAction(new EventHandler<>() {

            @Override
            public void handle(ActionEvent event) {

                // Запомнить родительское окно
                Stage parentStage = (Stage) exitButton.getScene().getWindow();
                // найти новое окно
                FXMLLoader loader = new FXMLLoader();
                loader.setLocation(getClass().getResource("/sample/fxml/exit.fxml"));
                // загрузить его
                try {
                    loader.load();
                } catch (IOException e) {
                    e.printStackTrace();
                    System.out.print("WRONG IN exit.fxml");
                }
                // отобразить новое окно
                Parent root = loader.getRoot();
                // окно без верхнего стандартного меню
                Stage newWindow = new Stage(StageStyle.UNDECORATED);
                newWindow.setScene(new Scene(root));
                // невозможно менять размеры окна
                newWindow.setResizable(false);

                // Установить родительское окно - окно регистрации с кнопкой подтвердить
                newWindow.initOwner(parentStage);
                // никакое окно не будет активно, пока это не закроют
                newWindow.initModality(Modality.APPLICATION_MODAL);
                newWindow.show();
            }
        });

        // кнопка Контакты
        contactsButton.setOnAction(event -> {

            // спрятать старое окно
            contactsButton.getScene().getWindow().hide();
            // найти новое окно
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/sample/fxml/contacts.fxml"));
            // загрузить его
            try {
                loader.load();
            } catch (IOException e){
                e.printStackTrace();
                System.out.print("WRONG IN contacts.fxml");
            }
            // отобразить новое окно
            Parent root = loader.getRoot();
            Stage newWindow = new Stage();
            newWindow.setScene(new Scene(root));
            // невозможно менять размеры окна
            newWindow.setResizable(false);

            newWindow.getIcons().add(new Image("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\onion.png"));
            newWindow.show();
        });

        // кнопка О компании
        aboutCompanyButton.setOnAction(event -> {

            // спрятать старое окно
            aboutCompanyButton.getScene().getWindow().hide();
            // найти новое окно
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/sample/fxml/about_company.fxml"));
            // загрузить его
            try {
                loader.load();
            } catch (IOException e){
                e.printStackTrace();
                System.out.print("WRONG IN about_company.fxml");
            }
            // отобразить новое окно
            Parent root = loader.getRoot();
            Stage newWindow = new Stage();
            newWindow.setScene(new Scene(root));
            // невозможно менять размеры окна
            newWindow.setResizable(false);

            newWindow.getIcons().add(new Image("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\onion.png"));
            newWindow.show();
        });

        // кнопка Личный кабинет
        cabinetButton.setOnAction(event -> {

            // спрятать старое окно
            cabinetButton.getScene().getWindow().hide();
            // найти новое окно
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/sample/fxml/personal_cabinet.fxml"));
            // загрузить его
            try {
                loader.load();
            } catch (IOException e){
                e.printStackTrace();
                System.out.print("WRONG IN personal_cabinet.fxml");
            }
            // отобразить новое окно
            Parent root = loader.getRoot();
            Stage newWindow = new Stage();
            newWindow.setScene(new Scene(root));
            // невозможно менять размеры окна
            newWindow.setResizable(false);

            newWindow.getIcons().add(new Image("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\onion.png"));
            newWindow.show();
        });

        // кнопка Яблоко
        appleButton.setOnAction(event -> {

            // спрятать старое окно
            appleButton.getScene().getWindow().hide();
            // найти новое окно
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/sample/fxml/apple.fxml"));
            // загрузить его
            try {
                loader.load();
            } catch (IOException e){
                e.printStackTrace();
                System.out.print("WRONG IN apple.fxml");
            }
            // отобразить новое окно
            Parent root = loader.getRoot();
            Stage newWindow = new Stage();
            newWindow.setScene(new Scene(root));
            // невозможно менять размеры окна
            newWindow.setResizable(false);

            newWindow.getIcons().add(new Image("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\onion.png"));
            newWindow.show();
        });

        // кнопка Огурец
        cucumberButton.setOnAction(event -> {

            // спрятать старое окно
            cucumberButton.getScene().getWindow().hide();
            // найти новое окно
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/sample/fxml/cucumber.fxml"));
            // загрузить его
            try {
                loader.load();
            } catch (IOException e){
                e.printStackTrace();
                System.out.print("WRONG IN cucumber.fxml");
            }
            // отобразить новое окно
            Parent root = loader.getRoot();
            Stage newWindow = new Stage();
            newWindow.setScene(new Scene(root));
            // невозможно менять размеры окна
            newWindow.setResizable(false);

            newWindow.getIcons().add(new Image("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\onion.png"));
            newWindow.show();
        });

        // кнопка Картофель
        potatoButton.setOnAction(event -> {

            // спрятать старое окно
            potatoButton.getScene().getWindow().hide();
            // найти новое окно
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/sample/fxml/potato.fxml"));
            // загрузить его
            try {
                loader.load();
            } catch (IOException e){
                e.printStackTrace();
                System.out.print("WRONG IN potato.fxml");
            }
            // отобразить новое окно
            Parent root = loader.getRoot();
            Stage newWindow = new Stage();
            newWindow.setScene(new Scene(root));
            // невозможно менять размеры окна
            newWindow.setResizable(false);

            newWindow.getIcons().add(new Image("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\onion.png"));
            newWindow.show();
        });

        // кнопка Груша
        pearButton.setOnAction(event -> {

            // спрятать старое окно
            pearButton.getScene().getWindow().hide();
            // найти новое окно
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/sample/fxml/pear.fxml"));
            // загрузить его
            try {
                loader.load();
            } catch (IOException e){
                e.printStackTrace();
                System.out.print("WRONG IN pear.fxml");
            }
            // отобразить новое окно
            Parent root = loader.getRoot();
            Stage newWindow = new Stage();
            newWindow.setScene(new Scene(root));
            // невозможно менять размеры окна
            newWindow.setResizable(false);

            newWindow.getIcons().add(new Image("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\onion.png"));
            newWindow.show();
        });

        // кнопка Томат
        tomatoButton.setOnAction(event -> {

            // спрятать старое окно
            tomatoButton.getScene().getWindow().hide();
            // найти новое окно
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/sample/fxml/tomato.fxml"));
            // загрузить его
            try {
                loader.load();
            } catch (IOException e){
                e.printStackTrace();
                System.out.print("WRONG IN tomato.fxml");
            }
            // отобразить новое окно
            Parent root = loader.getRoot();
            Stage newWindow = new Stage();
            newWindow.setScene(new Scene(root));
            // невозможно менять размеры окна
            newWindow.setResizable(false);

            newWindow.getIcons().add(new Image("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\onion.png"));
            newWindow.show();
        });

        // кнопка Корзина
        cartButton.setOnAction(event -> {

            // спрятать старое окно
            cartButton.getScene().getWindow().hide();
            // найти новое окно
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/sample/fxml/cart.fxml"));
            // загрузить его
            try {
                loader.load();
            }
            catch (IOException e){
                e.printStackTrace();
                System.out.print("WRONG IN cart.fxml from CatalogController");
            }
            // отобразить новое окно
            Parent root = loader.getRoot();
            Stage newWindow = new Stage();
            newWindow.setScene(new Scene(root));
            // невозможно менять размеры окна
            newWindow.setResizable(false);

            newWindow.getIcons().add(new Image("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\onion.png"));
            newWindow.show();
        });
    }
}

