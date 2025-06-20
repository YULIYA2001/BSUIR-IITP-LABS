package sample.controllers;

import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.stage.Stage;
import sample.Main;
import sample.classes.Client;

public class PersonalCabinetController {

    @FXML
    private TextField surnameTextField;

    @FXML
    private TextField patronymicTextField;

    @FXML
    private TextField phoneTextField;

    @FXML
    private TextField addressTextField;

    @FXML
    private TextField loginTextField;

    @FXML
    private TextField passwordTextField;

    @FXML
    private TextField nameTextField;

    @FXML
    private ImageView statusImageView;

    @FXML
    private Button acceptChangesButton;

    @FXML
    private TextField statusTextField;

    @FXML
    private Button backButton;

    @FXML
    void initialize() {

        // загрузка данных пользователя на форму
        loadClientInformation();

        // нажатие на кнопку Назад
        backButton.setOnAction(event -> {

            // закрыть это окно
            backButton.getScene().getWindow().hide();

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

        // нажатие на кнопку Применить изменения
        acceptChangesButton.setOnAction(event -> {

            // сохранение изменений в данных клиента
            saveClientInformationChanges();

            // закрыть это окно
            acceptChangesButton.getScene().getWindow().hide();

            // найти новое окно
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/sample/fxml/catalog.fxml"));
            // загрузить его
            try {
                loader.load();
            } catch (IOException e){
                e.printStackTrace();
                System.out.print("WRONG IN catalog.fxml FROM personal_cabinet.fxml");
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

    private void saveClientInformationChanges() {
        Client client = sample.Main.currentClient;

        boolean changed = false;

        // проверка всех полей и сохранение изменений
        if (!surnameTextField.getText().equals(client.getSurname())) {
            client.setSurname(surnameTextField.getText());
            changed = true;
        }
        if (!nameTextField.getText().equals(client.getName())) {
            client.setName(nameTextField.getText());
            changed = true;
        }
        if (!patronymicTextField.getText().equals(client.getPatronymic())) {
            client.setPatronymic(patronymicTextField.getText());
            changed = true;
        }
        if (!phoneTextField.getText().equals(client.getPhoneNumber())){
            client.setPhoneNumber(phoneTextField.getText());
            changed = true;
        }
        if (!addressTextField.getText().equals(client.getAddress())){
            client.setAddress(addressTextField.getText());
            changed = true;
        }
        if (!passwordTextField.getText().equals(client.getPassword())){
            client.setPassword(passwordTextField.getText());
            changed = true;
        }

        // сохранение "нового" клиента в файле (БД) и удаление "старого"
        if (changed) {

            // сохраняем строки в массив, удаляем лишнюю строку, добавляем новую и обратно в файл
            try {
                Scanner in = new Scanner(new File(Main.passClientsDB), "UTF-8");

                ArrayList<String> data = new ArrayList<>();
                String check;
                Client check_client;
                while (in.hasNextLine()) {
                    check = in.nextLine();
                    check_client = sample.classes.MyJSON.fromJSON(check, Client.class);
                    if (!check_client.getLogin().equals(client.getLogin()))
                        data.add(check);
                }

                // добавляем новую
                String jsonStringClient = sample.classes.MyJSON.toJSON(client);
                data.add(jsonStringClient);

                PrintWriter out = new PrintWriter(new FileWriter(Main.passClientsDB, false));
                for (String s : data)
                    out.println(s);
                in.close();
                out.close();
                System.out.println("The file ClientsDB has been changed");
            }catch (IOException ex) {
                System.out.println(ex);
            }
        }
    }

    private void loadClientInformation() {

        Client client = sample.Main.currentClient;

        surnameTextField.setText(client.getSurname());
        nameTextField.setText(client.getName());
        patronymicTextField.setText(client.getPatronymic());
        phoneTextField.setText(client.getPhoneNumber());
        addressTextField.setText(client.getAddress());
        loginTextField.setText(client.getLogin());
        passwordTextField.setText(client.getPassword());

        //вывод статуса и соответствующей картинки
        String status = client.getStatus().name().toLowerCase();
        if (status.equals("no"))
            status = "-";

        if (!status.equals("-"))
            statusImageView.setImage(new Image("/sample/images/" + status +".png"));
        statusTextField.setText(status);
    }
}


