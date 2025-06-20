package sample.controllers;

import java.io.*;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import sample.Main;

import sample.classes.Administrator;
import sample.classes.Client;
import sample.classes.iterator.MyIterator;
import sample.classes.iterator.TextFileReader;

public class AuthorizeController {

    @FXML
    private Button easterEggButton;

    @FXML
    private ImageView onionImage;

    @FXML
    private Button loginSignUpButton;

    @FXML
    private Button enterSignInButton;

    @FXML
    private TextField login_field;

    @FXML
    private PasswordField password_field;

    @FXML
    void initialize() {

        // кнопка Зарегистрироваться
        loginSignUpButton.setOnAction(event -> {
            // спрятать прошлое окно
            loginSignUpButton.getScene().getWindow().hide();
            // найти новое окно
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/sample/fxml/sign_up.fxml"));
            // загрузить его
            try {
                loader.load();
            } catch (IOException e){
                e.printStackTrace();
                System.out.print("WRONG IN sign_up.fxml");
            }
            // отобразить новое окно
            Parent root = loader.getRoot();
            Stage stage = new Stage();
            stage.setScene(new Scene(root));
            // невозможно менять размеры окна
            stage.setResizable(false);
            // иконка в углу программы
            stage.getIcons().add(new Image("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\onion.png"));
            stage.showAndWait();
        });

        // кнопка Войти
        enterSignInButton.setOnAction(event -> {

            // проверка ввода пользователя
            String loginText = login_field.getText().trim();
            String loginPassword = password_field.getText().trim();

            if(!loginText.equals("") && !loginPassword.equals("")){

                loginUser(loginText, loginPassword);
            }
            else{

                // вызов формы с сообщением о неверном вводе с возвратом к исходной форме
                FaultForm(true);
            }
        });

        // скрытая кнопка на перьях лука (картинка)
        easterEggButton.setOnAction(event -> {

            Image easterEgg = new Image
                    ("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\ЧиполлиноEasterEgg.png");
            onionImage.setImage(easterEgg);
        });
    }

    private void FaultForm(boolean isEmptyFields) {

        // Запомнить родительское окно
        Stage parentStage = (Stage) enterSignInButton.getScene().getWindow();
        // найти новое окно
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/sample/fxml/fault.fxml"));
        // загрузить его
        try {
            loader.load();
        } catch (IOException e){
            e.printStackTrace();
            System.out.print("WRONG IN fault.fxml from sample");
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
        if(isEmptyFields)
            System.out.println("Пользователь оставил пустые поля ввода (окно входа)");
        else
            System.out.println("Пользователь ввел неверные данные (окно входа)");
    }

    private void loginUser(String loginText, String loginPassword) {

        if (loginText.equals(Administrator.adminLogin) && loginPassword.equals(Administrator.adminPassword)){
            openAdminForm();
        }
        else {
            Client client = null;

            /* кусок кода вместо итератора
            // поиск в файле пользователя с нужным логином
            String jsonClientString = null;
            try {
                File file = new File(sample.Main.passClientsDB);
                //создаем объект FileReader для объекта File
                FileReader fr = new FileReader(file);
                //создаем BufferedReader с существующего FileReader для построчного считывания
                BufferedReader reader = new BufferedReader(fr);
                // считаем сначала первую строку
                jsonClientString = reader.readLine().trim();
                while (jsonClientString != null) {
                    // обработка на пустоту файла
                    try {
                        client = sample.classes.MyJSON.fromJSON(jsonClientString, Client.class);
                        if (client.getLogin().equals(loginText) && client.getPassword().equals(loginPassword))
                            break;
                        else
                            // считываем следующую строку
                            jsonClientString = reader.readLine();
                    } catch (Exception ex) {
                        jsonClientString = null;
                    }
                }
            }catch (IOException e) {
                e.printStackTrace();
                System.out.println("WRONG IN " + Main.passClientsDB + "FROM Controller");
            }

            if (!jsonClientString = null){
                setCurrentClient(client);
            }
            else{
                FaultForm(false);
                login_field.setText("");
                password_field.setText("");
            }*/

            TextFileReader<Client> textFileReader = new TextFileReader<>(Main.passClientsDB, Client.class);
            for (MyIterator iter = textFileReader.getIterator(); iter.hasNext();) {
                client = (Client) iter.next();
                if (client.getLogin().equals(loginText) && client.getPassword().equals(loginPassword)) {
                    setCurrentClient(client);
                    return;
                }
            }
            // вызов формы с сообщением о неверном вводе с возвратом к исходной форме
            FaultForm(false);
            login_field.setText("");
            password_field.setText("");
        }
    }

    private void setCurrentClient(Client client) {

        // записываем данные клиента в переменную для текущего клиента
        sample.Main.currentClient = client;
        System.out.println("Этот клиент входит в программу он нашелся в БД :)");
        sample.Main.currentClient.print();

        // создать клиенту файл-корзину, если ее нет (может остаться с прошлого раза)
        try {
            File file = new File(Main.passCartsFolder
                    + "\\" + Main.currentClient.getLogin() + ".txt");
            file.createNewFile();
        } catch (IOException ex) {
            System.out.println(ex);
        }

        // проводим успешную авторизацию
        // спрятать прошлое окно
        enterSignInButton.getScene().getWindow().hide();
        // найти новое окно
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/sample/fxml/catalog.fxml"));
        // загрузить его
        try {
            loader.load();
        } catch (IOException e) {
            e.printStackTrace();
            System.out.print("WRONG IN catalog.fxml FROM Controller");
        }
        // отобразить новое окно
        Parent root = loader.getRoot();
        Stage stage = new Stage();
        stage.setScene(new Scene(root));
        // невозможно менять размеры окна
        stage.setResizable(false);
        // иконка в углу программы
        stage.getIcons().add(new Image("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\onion.png"));
        stage.showAndWait();
    }

    private void openAdminForm() {

        enterSignInButton.getScene().getWindow().hide();
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/sample/fxml/administrator.fxml"));
        try {
            loader.load();
        } catch (IOException e) {
            e.printStackTrace();
            System.out.print("WRONG IN administrator.fxml FROM Controller");
        }
        // отобразить новое окно
        Parent root = loader.getRoot();
        Stage stage = new Stage();
        stage.setScene(new Scene(root));
        stage.setResizable(false);
        stage.getIcons().add(new Image("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\onion.png"));
        stage.showAndWait();
    }
}
