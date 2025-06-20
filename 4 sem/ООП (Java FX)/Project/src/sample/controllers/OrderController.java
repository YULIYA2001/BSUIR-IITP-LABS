package sample.controllers;

import java.io.*;
import java.time.LocalDate;
import java.util.*;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import sample.Main;
import sample.classes.*;
import sample.enums.OStatus;

public class OrderController {

    @FXML
    private Label orderIdLabel;

    @FXML
    private Label wholeCostLabel;

    @FXML
    private Label discountAmountLabel;

    @FXML
    private RadioButton courierRadioButton;

    @FXML
    private RadioButton yourselfRadioButton;

    @FXML
    private Label deliveryCostLabel;

    @FXML
    private Label courierLabel;

    @FXML
    private Label deliveryAddressLabel;

    @FXML
    private Button confirmButton;

    @FXML
    private Button cancelButton;

    @FXML
    void initialize() {

        Client client = Main.currentClient;
        ArrayList<Cart> carts = loadCarts();

        loadInformation(client, carts);

        final double wholeCost = setCostOfCart(carts);
        wholeCostLabel.setText(String.format("%.2f p.", wholeCost));

        // функция расчета цены доставки
        final double deliveryPrice = 200.0/wholeCost;
        // рандомный выбор курьера
        Courier courier = chooseCourier(wholeCost);

        // Group
        ToggleGroup group = new ToggleGroup();
        courierRadioButton.setToggleGroup(group);
        yourselfRadioButton.setToggleGroup(group);

        group.selectedToggleProperty().addListener(new ChangeListener<Toggle>() {
            @Override
            public void changed(ObservableValue<? extends Toggle> ov, Toggle old_toggle, Toggle new_toggle) {
                // Has selection.
                if (group.getSelectedToggle() != null) {
                    RadioButton button = (RadioButton) group.getSelectedToggle();
                    if(button.getText().equals(courierRadioButton.getText())) {
                        courierClicked();
                    }
                    else {
                        yourselfClicked();
                    }
                }
            }

            // нажатие на кнопку Курьер (запрет, если цена < 20 р.)
            private void courierClicked() {
                // доставка от 20 р.
                if (wholeCost < 20 || courier == null) {
                    yourselfRadioButton.fire();
                }
                else {
                    deliveryCostLabel.setText(String.format("%.2f p.", deliveryPrice));
                    courierLabel.setText(courier.getName() + " " + courier.getSurname() + " ("
                            + courier.getPhoneNumber() + ")");
                    wholeCostLabel.setText(String.format("%.2f p.", deliveryPrice + wholeCost));
                }
            }

            // нажатие на кнопку Самовывоз
            private void yourselfClicked() {

                deliveryCostLabel.setText("0.00 p.");
                courierLabel.setText("-");
                wholeCostLabel.setText(String.format("%.2f p.", wholeCost));
            }
        });

        // нажатие на кнопку Отмена
        cancelButton.setOnAction(event -> {
            // закрыть это окно
            cancelButton.getScene().getWindow().hide();
        });

        // нажатие на кнопку Подтвердить
        confirmButton.setOnAction(event -> {

            // увеличить счетчик заказов
            Main.ordersCount_ID++;
            // сформировать заказ, записать в файл заказов
            // объект класса доставка
            Delivery delivery = null;
            double cost = 0;
            LocalDate date = LocalDate.now();
            if (group.getSelectedToggle() != null) {
                RadioButton button = (RadioButton) group.getSelectedToggle();
                if (button.getText().equals(courierRadioButton.getText())) {
                    delivery = new Delivery(Delivery.KindOfDelivery.COURIER, deliveryPrice,
                            date.plusDays(2), client.getAddress(), courier);
                    cost = deliveryPrice + wholeCost;
                }
                else{
                    delivery = new Delivery(Delivery.KindOfDelivery.PICKUP, 0,
                            date.plusDays(2), client.getAddress(), courier);
                    cost = wholeCost;
                }
            }

            int orderId = Integer.parseInt(orderIdLabel.getText());
            // сам заказ
            Order order = new Order(client, delivery, orderId, new OrderStatus(OStatus.NEW, date),
                    cost, carts);

            // записать в файл заказов
            orderToDB(order);

            // очистить файл-корзину
             try {
                 PrintWriter out = new PrintWriter(new FileWriter(Main.passCartsFolder
                        + "\\" + Main.currentClient.getLogin() + ".txt", false));
                 out.print("");
                 out.close();
                 System.out.println("The file " + Main.currentClient.getLogin() +
                        ".txt in Carts folder was cleaned from OrderController");
            } catch (IOException ex) {
                System.out.println(ex);
                System.out.println("WRONG IN " + Main.currentClient.getLogin() +
                        ".txt in Carts FROM Order Controller");
            }

            //TODO создать pdf отчет
            //PDDocument document = new PDDocument();
            //document.addPage(new PDPage());
            //document.save("C:/pdfBox/BlankPdf.pdf");
            //System.out.println("PDF created");
            //document.close();


            Stage parentStage = (Stage) confirmButton.getScene().getWindow();
            // найти окошко успешного заказа
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/sample/fxml/success_add_order.fxml"));
            // загрузить его
            try {
                loader.load();
            } catch (IOException e) {
                e.printStackTrace();
                System.out.print("WRONG IN success_add_order.fxml FROM OrderControler");
            }
            // отобразить окошко успешного заказа
            Parent root = loader.getRoot();
            Stage newWindow = new Stage(StageStyle.UNDECORATED);
            newWindow.setScene(new Scene(root));
            newWindow.setResizable(false);
            newWindow.initOwner(parentStage);
            newWindow.initModality(Modality.APPLICATION_MODAL);
            newWindow.showAndWait();

            // закрыть окно заказа и родителя (корзина) и переити на новое (catalog)
            Stage stage1 = (Stage) confirmButton.getScene().getWindow();
            parentStage = (Stage) stage1.getOwner();
            stage1.hide();
            parentStage.hide();

            // найти новое окно
            loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/sample/fxml/catalog.fxml"));
            // загрузить его
            try {
                loader.load();
            } catch (IOException e){
                e.printStackTrace();
                System.out.print("WRONG catalog.fxml from OrderController");
            }

            // отобразить новое окно
            root = loader.getRoot();
            Stage stage = new Stage();
            stage.setScene(new Scene(root));
            // невозможно менять размеры окна
            stage.setResizable(false);
            // иконка в углу программы
            stage.getIcons().add(new Image("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\onion.png"));
            stage.show();
        });
    }

    private void orderToDB(Order order) {

        // объект в json
        String jsonStringOrder = MyJSON.toJSON(order);

        // json-стороку в файл заказов (базу данных)
        try(FileOutputStream fos=new FileOutputStream(sample.Main.passOrdersDB, true))
        {
            // перевод строки в байты
            byte[] buffer = (jsonStringOrder + "\n").getBytes();
            fos.write(buffer, 0, buffer.length);
        }
        catch(IOException ex){

            System.out.println(ex.getMessage());
        }
        System.out.println("The file OrdersDB.txt was changed from OrderController");
    }

    // назначение курьера (если нет в БД, кнопка не нажимается)
    private Courier chooseCourier(double wholeCost) {

        // считывание курьеров
        ArrayList<Courier> couriers = Company.getInstance().getCouriers();

        if (couriers.size() == 0)
        {
            // если курьеров нет, не дать клиенту нажать на доставку Курьером
            deliveryCostLabel.setText("0.00 p.");
            courierLabel.setText("-");
            wholeCostLabel.setText(String.format("%.2f p.", wholeCost));
            return null;
        }

        // выбор рандомного курьера
        Random generator = new Random();
        int randomIndex = generator.nextInt(couriers.size());

        Courier courier = couriers.get(randomIndex);
        couriers.clear();

        return  courier;
    }

    // подсчет суммы за продукты с учетом статусной скидки без учета доставки
    private double setCostOfCart(ArrayList<Cart> carts) {

        double wholeCost = 0.0;

        for (Cart cart : carts) {
            wholeCost += cart.getCostWithSale();
        }

        // учет статусной скидки
        wholeCost = wholeCost * (1 - Main.currentClient.getStatus().getAmount()/100.0);

        return wholeCost;
    }

    private void loadInformation(Client client, ArrayList<Cart> carts) {

        deliveryAddressLabel.setText(client.getAddress());
        discountAmountLabel.setText(client.getStatus().getAmount() + " %");
        orderIdLabel.setText(((Main.ordersCount_ID) + 1) + "");
    }

    private ArrayList<Cart> loadCarts() {

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
            System.out.println("WRONG IN passCartsFolder FROM OrderController");
        }

        return cart;
    }
}

