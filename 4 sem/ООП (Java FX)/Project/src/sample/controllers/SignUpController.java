package sample.controllers;

import javafx.scene.image.Image;
import sample.Main;
import sample.classes.Client;

import java.io.*;
import java.util.Scanner;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import sample.enums.ClientStatus;

public class SignUpController {

    @FXML
    private Button signUpConfirmButton;

    @FXML
    private TextField signUpLogin;

    @FXML
    private TextField signUpPassword;

    @FXML
    private TextField signUpName;

    @FXML
    private TextField signUpSurname;

    @FXML
    private TextField signUpPatronymic;

    @FXML
    private TextField signUpPhone;

    @FXML
    private TextField signUpAddress;

    @FXML
    private Button backButton;

    @FXML
    void initialize() {

        // нажатие на кнопку Назад
        backButton.setOnAction(event -> {

                    // закрыть это окно
                    Stage stage1 = (Stage) backButton.getScene().getWindow();
                    stage1.hide();

                    // найти новое окно
                    FXMLLoader loader = new FXMLLoader();
                    loader.setLocation(getClass().getResource("/sample/fxml/sample.fxml"));
                    // загрузить его
                    try {
                        loader.load();
                    } catch (IOException e) {
                        e.printStackTrace();
                        System.out.print("WRONG IN sample.fxml FROM sign_in.fxml");
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

        // нажатие на кнопку Подтвердить
        signUpConfirmButton.setOnAction(new EventHandler<ActionEvent>() {

            @Override
            public void handle(ActionEvent event) {

                // проверка ввода пользователя
                String surname = signUpSurname.getText().trim();
                String name = signUpName.getText().trim();
                String patronymic = signUpPatronymic.getText().trim();
                String phone = signUpPhone.getText().trim();
                String address = signUpAddress.getText().trim();
                String login = signUpLogin.getText().trim();
                String password = signUpPassword.getText().trim();

                if (!surname.equals("") && !name.equals("") && !phone.equals("") && !address.equals("")
                        && !login.equals("") && !password.equals("")) {
                    Client client;
                    if (patronymic.equals(""))
                        client = new Client(name, surname, phone, address, login, password, ClientStatus.NO);
                    else
                        client = new Client(name, patronymic, surname, phone, address,
                                login, password, ClientStatus.NO);

                    if (!addClient(client))
                    {
                        faultInFilledInformation(false);
                    }
                }
                else {
                    faultInFilledInformation(true);
                }
            }
        });
    }

    private void faultInFilledInformation(boolean isEmpty) {

        // Запомнить родительское окно
        Stage parentStage = (Stage) signUpConfirmButton.getScene().getWindow();
        // найти новое окно
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/sample/fxml/fault.fxml"));
        // загрузить его
        try {
            loader.load();
        } catch (IOException e) {
            e.printStackTrace();
            System.out.print("WRONG IN fault.fxml from sign_up");
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
        newWindow.showAndWait();
        if(isEmpty)
            System.out.println("Пользователь оставил пустые поля ввода (sign up)");
        else
            System.out.println("Пользователь ввел существующий логин или телефон (sign up)");
    }

    private boolean addClient(Client client) {

        try {
            Scanner in = new Scanner(new File(Main.passClientsDB), "UTF-8");

            String check;
            while (in.hasNextLine()) {
                check = in.nextLine();
                if (check.contains("login\":" + client.getLogin() + "\"")) {
                    signUpLogin.setText("");
                    System.out.println("ОШИБКА. Такой логин есть в БД");
                    return false;
                }
                if (check.contains("phoneNumber\":" + client.getPhoneNumber() + "\"")) {
                    signUpPhone.setText("");
                    System.out.println("ОШИБКА. Такой телефон есть в БД");
                    return false;
                }
            }
            in.close();
        }
        catch (FileNotFoundException ex){
            System.out.println(ex);
        }

        // объект в json
        String jsonStringClient = sample.classes.MyJSON.toJSON(client);

        // json-стороку в файл (базу данных)
        try(FileOutputStream fos=new FileOutputStream(sample.Main.passClientsDB, true))
        {
            // перевод строки в байты
            byte[] buffer = (jsonStringClient + "\n").getBytes();

            fos.write(buffer, 0, buffer.length);
        }
        catch(IOException ex){

            System.out.println(ex.getMessage());
        }
        System.out.println("The file ClientDB was changed from SignUpController");

        // Написать об успешной регистрации и переключить окно
        // Запомнить родительское окно
        Stage parentStage = (Stage) signUpConfirmButton.getScene().getWindow();
        // найти новое окно
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/sample/fxml/success_sign_up.fxml"));
        // загрузить его
        try {
            loader.load();
        } catch (IOException e) {
            e.printStackTrace();
            System.out.print("WRONG IN success_sign_up.fxml");
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
        newWindow.showAndWait();
        return true;
    }
}

