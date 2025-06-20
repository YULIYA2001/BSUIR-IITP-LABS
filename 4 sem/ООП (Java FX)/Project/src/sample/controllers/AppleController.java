package sample.controllers;

import java.io.*;
import java.text.DecimalFormat;
import java.util.ArrayList;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.image.Image;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import sample.Main;
import sample.classes.Cart;
import sample.classes.Company;
import sample.classes.MyJSON;
import sample.classes.Product;
import sample.enums.FruitVegetable;

import java.util.Scanner;

public class AppleController {

    @FXML
    private Label isAvailableLabel;

    @FXML
    private Label priceLabel;

    @FXML
    private Label saleLabel;

    @FXML
    private Label referenceInfLabel;

    @FXML
    private Label priceWithSaleLabel;

    @FXML
    private Button toCartButton;

    @FXML
    private Slider amountSlider;

    @FXML
    private Label weightLabel;

    @FXML
    private Button backButton;

    @FXML
    void initialize() {

        // загрузка цены, наличия, скидки
        Product product = loadInformation();

        // соответствие ползунка и значения
        amountSlider.valueProperty().addListener((changed, oldValue, newValue) ->
                weightLabel.setText("" + newValue));

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

        // нажатие на кнопку В корзину
        toCartButton.setOnAction(event -> {

            String jsonApple = null;
            // ищем в корзине клиента заказ на яблоки
            try {
                Scanner in = new Scanner(new File(Main.passCartsFolder
                        + "\\" + Main.currentClient.getLogin() + ".txt"), "UTF-8");
                while (in.hasNextLine()) {
                    jsonApple = in.nextLine();
                    if (jsonApple.contains("APPLE"))
                        break;
                }
                in.close();
            }
            catch (FileNotFoundException ex){
                File file = new File(Main.passCartsFolder
                        + "\\" + Main.currentClient.getLogin() + ".txt");
            }

            String jsonNewApple = null;
            // если в корзине есть товар, добавляем к нему новое количество и пересчет суммы
            if (jsonApple != null && jsonApple.contains("APPLE")) {
                if (amountSlider.getValue() != 0.0) {
                    Cart apple = MyJSON.fromJSON(jsonApple, Cart.class);
                    double sumAmount = apple.getAmount() + amountSlider.getValue();
                    Cart newApple = new Cart(apple.getProduct(), sumAmount);
                    apple = null;    // для сборщика мусора
                    jsonNewApple = MyJSON.toJSON(newApple);
                }
            }
            // если товара нет в корзине, создаем его
            else{
                // для проверки в следующем блоке
                jsonApple = null;

                Cart cart = null;
                if (amountSlider.getValue() != 0.0) {
                    cart = new Cart(product, amountSlider.getValue());
                    jsonNewApple = MyJSON.toJSON(cart);
                }
            }

            // если все в порядке и есть json строка товара, добавляем ее в файл-корзину текущего клиента
            // если такого товара в корзине не было - просто добавление, иначе замена
            if (jsonNewApple != null && jsonApple == null) {
                try (FileOutputStream fos = new FileOutputStream(Main.passCartsFolder
                        + "\\" + Main.currentClient.getLogin() + ".txt", true)) {
                    byte[] buffer = (jsonNewApple + "\n").getBytes();
                    fos.write(buffer, 0, buffer.length);
                    System.out.println("The file " + Main.currentClient.getLogin() +
                            ".txt in Carts folder was changed from AppleController 1");
                } catch (IOException ex) {
                    System.out.println(ex.getMessage());
                }
                showSuccessOperationAdd();
            }
            else if (jsonNewApple != null && jsonApple != null){

                writeNewDeleteOld(jsonNewApple, jsonApple);
                showSuccessOperationAdd();
            }
        });
    }

    private void writeNewDeleteOld(String jsonNew, String json) {

        // сохраняем строки в массив, удаляем лишнюю строку, добавляем новую и обратно в файл
        try {
            Scanner in = new Scanner(new File(Main.passCartsFolder
                    + "\\" + Main.currentClient.getLogin() + ".txt"), "UTF-8");

            ArrayList<String> data = new ArrayList<>();
            String check;
            while (in.hasNextLine()) {
                check = in.nextLine();
                // пропустили строку для удаления
                if (!json.equals(check))
                    data.add(check);
            }

            // добавляем новую
            data.add(jsonNew);

            // переписали файл (старая строка удалена, новая в конце)
            PrintWriter out = new PrintWriter(new FileWriter(Main.passCartsFolder
                    + "\\" + Main.currentClient.getLogin() + ".txt", false));
            for (String s : data)
                out.println(s);
            in.close();
            out.close();
            System.out.println("The file " + Main.currentClient.getLogin() +
                    ".txt in Carts folder was changed from AppleController 2");
        } catch (IOException ex) {
            System.out.println(ex);
        }
    }

    private void showSuccessOperationAdd() {

        Stage parentStage = (Stage) toCartButton.getScene().getWindow();
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/sample/fxml/success_add_to_cart.fxml"));
        try {
            loader.load();
        } catch (IOException e) {
            e.printStackTrace();
            System.out.print("WRONG IN success_add_to_cart.fxml from AppleController");
        }
        Parent root = loader.getRoot();
        Stage newWindow = new Stage(StageStyle.UNDECORATED);
        newWindow.setScene(new Scene(root));
        newWindow.setResizable(false);
        newWindow.initOwner(parentStage);
        newWindow.initModality(Modality.APPLICATION_MODAL);
        newWindow.showAndWait();
    }

    private Product loadInformation() {

        // считываем продукты из БД в массив продуктов
        Product product = null;

        int len = Company.getInstance().getProducts().size();
        for (int i = 0; i < len; i++){
            if (Company.getInstance().getProducts().get(i).getName() == FruitVegetable.APPLE){
                product = Company.getInstance().getProducts().get(i);
                break;
            }
        }

        /*TODO try {
            Scanner in = new Scanner(new File(Main.passProductsDB), "UTF-8");

            while (in.hasNextLine()) {
                String check = in.nextLine().trim();
                if(check.indexOf("APPLE") != -1) {
                    product = (JSON.parseObject(check, Product.class));
                    break;
                }
            }
            in.close();
        }
        catch (FileNotFoundException ex){
            System.out.println(ex);
        }*/

        if (product != null)
            product.print();

        isAvailableLabel.setText(product.getAvailability() ? "В наличии" : "Нет в наличии");
        if (!product.getAvailability()) {
            amountSlider.setValue(0);
            amountSlider.setDisable(true);
            toCartButton.setDisable(true);
        }
        else{
            amountSlider.setDisable(false);
            toCartButton.setDisable(false);
        }
        String price = new DecimalFormat("#0.00").format(product.getPrice());
        priceLabel.setText(price + " р.");
        saleLabel.setText(product.getSale().getHaveSale() ? product.getSale().getAmount() + "%" : "-");
        if (product.getSale().getHaveSale()) {
            double priceWithSale = product.getPrice() * (1 - product.getSale().getAmount() / 100.0);
            priceWithSaleLabel.setText(priceWithSale + " p.");
        }
        else
            priceWithSaleLabel.setText("-");
        referenceInfLabel.setText(product.getReferenceInformation());

        return product;
    }
}

