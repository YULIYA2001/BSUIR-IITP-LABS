package sample.controllers;

import java.io.*;
import java.util.*;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import sample.Main;
import sample.classes.Cart;
import sample.classes.MyJSON;

public class CartController {

    @FXML
    private Button deleteButtonA;

    @FXML
    private Label wholeCostLabel;

    @FXML
    private Button deleteButtonP;

    @FXML
    private Button deleteButtonPot;

    @FXML
    private Button deleteButtonC;

    @FXML
    private Button deleteButtonT;

    @FXML
    private Label appleLabel;

    @FXML
    private Label cucumberLabel;

    @FXML
    private Label pearLabel;

    @FXML
    private Label tomatoLabel;

    @FXML
    private Label potatoLabel;

    @FXML
    private Label sumALabel;

    @FXML
    private Label sumPLabel;

    @FXML
    private Label sumTLabel;

    @FXML
    private Label sumCLabel;

    @FXML
    private Label sumPotLabel;

    @FXML
    private Button takeOrderButton;

    @FXML
    private Label weightALabel;

    @FXML
    private Label weightPLabel;

    @FXML
    private Label weightTLabel;

    @FXML
    private Label weightCLabel;

    @FXML
    private Label weightPotLabel;

    @FXML
    private Button backButton;

    @FXML
    void initialize() {

        ArrayList<Cart> cart = loadInformation();

        // нажатие на кнопку Назад
        backButton.setOnAction(event -> {

            // перевод массива продуктов (корзин) в json строки
            ArrayList<String> data = new ArrayList<>();
            for (Cart value : cart) {
                data.add(MyJSON.toJSON(value));
            }

            // все удаленные продукты удалить из файла-корзины (переписать файл-корзину)
            try {
                PrintWriter out = new PrintWriter(new FileWriter(Main.passCartsFolder
                        + "\\" + Main.currentClient.getLogin() + ".txt", false));
                for (String s : data)
                    out.println(s);
                out.close();
                System.out.println("The file " + Main.currentClient.getLogin() +
                        ".txt in Carts folder was changed from CartController 2");
            } catch (IOException ex) {
                System.out.println(ex);
            }

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

        // нажатие на кнопку Удалить Томат
        deleteButtonT.setOnAction(event -> {

            if (!weightTLabel.getText().equals("0.0") && !sumTLabel.getText().equals("0.00 р.")){
                // извлечение цифры, перерасчет общей стоимости
                double wholeCost = Double.parseDouble(
                        wholeCostLabel.getText().split(" ")[0].replace(',','.'));
                double delCost = Double.parseDouble(
                        sumTLabel.getText().split(" ")[0].replace(',','.'));
                wholeCostLabel.setText(String.format("%.2f p.", wholeCost-delCost));

                weightTLabel.setText("0.0");
                sumTLabel.setText("0.00 р.");

                // удаление из массива продуктов (корзин)
                for (int i = 0; i < cart.size(); i++) {
                    if (cart.get(i).getProduct().getName().equals(sample.enums.FruitVegetable.TOMATO))
                        cart.remove(i);
                }
            }
        });

        // нажатие на кнопку Удалить Огурец
        deleteButtonC.setOnAction(event -> {

            if (!weightCLabel.getText().equals("0.0") && !sumCLabel.getText().equals("0.00 р.")){
                // извлечение цифры, перерасчет общей стоимости
                double wholeCost = Double.parseDouble(
                        wholeCostLabel.getText().split(" ")[0].replace(',','.'));
                double delCost = Double.parseDouble(
                        sumCLabel.getText().split(" ")[0].replace(',','.'));
                wholeCostLabel.setText(String.format("%.2f p.", wholeCost-delCost));

                weightCLabel.setText("0.0");
                sumCLabel.setText("0.00 р.");

                // удаление из массива продуктов (корзин)
                for (int i = 0; i < cart.size(); i++) {
                    if (cart.get(i).getProduct().getName().equals(sample.enums.FruitVegetable.CUCUMBER))
                        cart.remove(i);
                }
            }
        });

        // нажатие на кнопку Удалить Грушу
        deleteButtonP.setOnAction(event -> {

            if (!weightPLabel.getText().equals("0.0") && !sumPLabel.getText().equals("0.00 р.")){
                // извлечение цифры, перерасчет общей стоимости
                double wholeCost = Double.parseDouble(
                        wholeCostLabel.getText().split(" ")[0].replace(',','.'));
                double delCost = Double.parseDouble(
                        sumPLabel.getText().split(" ")[0].replace(',','.'));
                wholeCostLabel.setText(String.format("%.2f p.", wholeCost-delCost));

                weightPLabel.setText("0.0");
                sumPLabel.setText("0.00 р.");

                // удаление из массива продуктов (корзин)
                for (int i = 0; i < cart.size(); i++) {
                    if (cart.get(i).getProduct().getName().equals(sample.enums.FruitVegetable.PEAR))
                        cart.remove(i);
                }
            }
        });

        // нажатие на кнопку Удалить Картофель
        deleteButtonPot.setOnAction(event -> {

            if (!weightPotLabel.getText().equals("0.0") && !sumPotLabel.getText().equals("0.00 р.")){
                // извлечение цифры, перерасчет общей стоимости
                double wholeCost = Double.parseDouble(
                        wholeCostLabel.getText().split(" ")[0].replace(',','.'));
                double delCost = Double.parseDouble(
                        sumPotLabel.getText().split(" ")[0].replace(',','.'));
                wholeCostLabel.setText(String.format("%.2f p.", wholeCost-delCost));

                weightPotLabel.setText("0.0");
                sumPotLabel.setText("0.00 р.");

                // удаление из массива продуктов (корзин)
                for (int i = 0; i < cart.size(); i++) {
                    if (cart.get(i).getProduct().getName().equals(sample.enums.FruitVegetable.POTATO))
                        cart.remove(i);
                }
            }
        });

        // нажатие на кнопку Удалить Яблоко
        deleteButtonA.setOnAction(event -> {

            if (!weightALabel.getText().equals("0.0") && !sumALabel.getText().equals("0.00 р.")){
                // извлечение цифры, перерасчет общей стоимости
                double wholeCost = Double.parseDouble(
                        wholeCostLabel.getText().split(" ")[0].replace(',','.'));
                double delCost = Double.parseDouble(
                        sumALabel.getText().split(" ")[0].replace(',','.'));
                wholeCostLabel.setText(String.format("%.2f p.", wholeCost-delCost));

                weightALabel.setText("0.0");
                sumALabel.setText("0.00 р.");

                // удаление из массива продуктов (корзин)
                for (int i = 0; i < cart.size(); i++) {
                    if (cart.get(i).getProduct().getName().equals(sample.enums.FruitVegetable.APPLE))
                        cart.remove(i);
                }
            }
        });

        // кнопка Заказать
        takeOrderButton.setOnAction(event -> {

            double wholeCost = Double.parseDouble(
                    wholeCostLabel.getText().split(" ")[0].replace(',','.'));

            if (wholeCost != 0) {

                // перевод массива продуктов (корзин) в json строки
                ArrayList<String> data = new ArrayList<>();
                for (Cart value : cart) {
                    data.add(MyJSON.toJSON(value));
                }
                // все удаленные продукты удалить из файла-корзины (переписать файл-корзину)
                try {
                    PrintWriter out = new PrintWriter(new FileWriter(Main.passCartsFolder
                            + "\\" + Main.currentClient.getLogin() + ".txt", false));
                    for (String s : data)
                        out.println(s);
                    out.close();
                    System.out.println("The file " + Main.currentClient.getLogin() +
                            ".txt in Carts folder was changed from CartController takeOrderButton");
                } catch (IOException ex) {
                    System.out.println(ex);
                }

                Stage parentStage = (Stage) takeOrderButton.getScene().getWindow();
                FXMLLoader loader = new FXMLLoader();
                loader.setLocation(getClass().getResource("/sample/fxml/order.fxml"));
                try {
                    loader.load();
                } catch (IOException e) {
                    e.printStackTrace();
                    System.out.print("WRONG IN order.fxml from CartController");
                }
                Parent root = loader.getRoot();
                Stage newWindow = new Stage(StageStyle.UNDECORATED);
                newWindow.setScene(new Scene(root));
                newWindow.setResizable(false);
                newWindow.initOwner(parentStage);
                newWindow.initModality(Modality.APPLICATION_MODAL);
                newWindow.showAndWait();
            }
        });

    }

    private ArrayList<Cart> loadInformation() {

        // считывание корзины из файла в массив
        ArrayList<Cart> cart = new ArrayList<Cart>();
        try {
            Scanner in = new Scanner(new File(Main.passCartsFolder
                    + "\\" + Main.currentClient.getLogin() + ".txt"), "UTF-8");

            while (in.hasNextLine()) {
                cart.add(MyJSON.fromJSON(in.nextLine().trim(), Cart.class));
            }
            in.close();
        }
        catch (FileNotFoundException ex){
            System.out.println(ex);
        }

        // разделение массива на конкретные продукты
        Cart pear = null;
        Cart tomato = null;
        Cart apple = null;
        Cart potato = null;
        Cart cucumber = null;
        for (Cart value : cart) {
            switch (value.getProduct().getName()) {
                case PEAR:
                    pear = value;
                    break;
                case APPLE:
                    apple = value;
                    break;
                case POTATO:
                    potato = value;
                    break;
                case TOMATO:
                    tomato = value;
                    break;
                case CUCUMBER:
                    cucumber = value;
                    break;
            }
        }
        cart.clear();

        // заполнение полей Формы "корзина"
        appleLabel.setText("Яблоко свежее");
        cucumberLabel.setText("Огурец свежий");
        pearLabel.setText("Груша свежая");
        tomatoLabel.setText("Томат свежий");
        potatoLabel.setText("Картофель свежий");

        double wholeCost = 0.0;

        if (apple != null) {
            sumALabel.setText(String.format("%.2f p.", apple.getCostWithSale()));
            weightALabel.setText(Double.toString(apple.getAmount()));
            wholeCost += apple.getCostWithSale();
            cart.add(apple);
        }
        if (pear != null) {
            sumPLabel.setText(String.format("%.2f p.", pear.getCostWithSale()));
            weightPLabel.setText(Double.toString(pear.getAmount()));
            wholeCost += pear.getCostWithSale();
            cart.add(pear);
        }
        if (potato != null) {
            sumPotLabel.setText(String.format("%.2f p.", potato.getCostWithSale()));
            weightPotLabel.setText(Double.toString(potato.getAmount()));
            wholeCost += potato.getCostWithSale();
            cart.add(potato);
        }
        if (tomato != null) {
            sumTLabel.setText(String.format("%.2f p.", tomato.getCostWithSale()));
            weightTLabel.setText(Double.toString(tomato.getAmount()));
            wholeCost += tomato.getCostWithSale();
            cart.add(tomato);
        }
        if (cucumber != null) {
            sumCLabel.setText(String.format("%.2f p.", cucumber.getCostWithSale()));
            weightCLabel.setText(Double.toString(cucumber.getAmount()));
            wholeCost += cucumber.getCostWithSale();
            cart.add(cucumber);
        }

        wholeCostLabel.setText(String.format("%.2f p.", wholeCost));
        return cart;
    }
}



