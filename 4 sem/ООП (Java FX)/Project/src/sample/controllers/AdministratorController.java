package sample.controllers;

import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.RadioButton;
import javafx.scene.control.Tab;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;
import sample.Main;
import sample.classes.*;
import sample.enums.ClientStatus;

public class AdministratorController {

    @FXML
    private Tab clientsTab;

    @FXML
    private Tab couriersTab;

    @FXML
    private Tab productsTab;

    @FXML
    private Tab ordersTab;

    @FXML
    private Tab reviewsTab;

    @FXML
    private Tab companyTab;

    @FXML
    private TextArea clientsTextArea;

    @FXML
    private TextField searchClientTextField;

    @FXML
    private ToggleGroup groupCl;

    @FXML
    private RadioButton surnameClientRadioButton;

    @FXML
    private Button findClientButton;

    @FXML
    private ChoiceBox<String> statusChoiceBox;

    @FXML
    private Button changeClientStatusButton;

    @FXML
    private TextField clientLoginTextField;

    @FXML
    private ChoiceBox<String> statusChangeChoiceBox;

    @FXML
    private TextArea couriersTextArea;

    @FXML
    private TextField searchCourierTextField;

    @FXML
    private RadioButton idRadioButton;

    @FXML
    private ToggleGroup group;

    @FXML
    private Button findCourierButton;

    @FXML
    private Button addCourierButton;

    @FXML
    private Button deleteCourierButton;

    @FXML
    private TextField surnameCourierTextField;

    @FXML
    private TextField nameCourierTextField;

    @FXML
    private TextField patronymicCourierTextField;

    @FXML
    private TextField phoneCourierTextField;

    @FXML
    private TextArea productsTextArea;

    @FXML
    private Button changeProductButton;

    @FXML
    private ChoiceBox<String> nameProductChoiceBox;

    @FXML
    private TextField priceProductTextField;

    @FXML
    private TextField aboutProductTextField;

    @FXML
    private RadioButton availableRadioButton;

    @FXML
    private RadioButton notAvailableRadioButton;

    @FXML
    private RadioButton saleRadioButton;

    @FXML
    private RadioButton notSaleRadioButton;

    @FXML
    private TextField saleProductTextField;

    @FXML
    private TextArea ordersTextArea;

    @FXML
    private TextField profitTextField;

    @FXML
    private TextField searchOrderTextField;

    @FXML
    private Button findOrderButton;

    @FXML
    private TextArea reviewsTextArea;

    @FXML
    private Button deleteReviewButton;

    @FXML
    private TextField deleteReviewTextField;

    @FXML
    private TextField phoneTextField;

    @FXML
    private TextField addressTextField;

    @FXML
    private TextArea aboutCompanyTextArea;

    @FXML
    private TextField workTimeTextField;

    @FXML
    private Button changeCompanyButton;

    @FXML
    private Button showButton;

    @FXML
    private Button exitButton;
    @FXML
    void initialize() {

        Administrator admin = new Administrator();
        // вывод прибыли на вкладке Заказы
        profitTextField.setText(admin.returnProfit() + " p.");

        // создание Выбора статуса (3 шт.)
        statusChoiceBox.setItems(FXCollections.observableArrayList(
                "DIAMOND", "PLATINUM", "GOLD", "SILVER", "BRONZE", "NO"));
        statusChoiceBox.setValue("NO");
        statusChangeChoiceBox.setItems(FXCollections.observableArrayList(
                "DIAMOND", "PLATINUM", "GOLD", "SILVER", "BRONZE", "NO"));
        statusChangeChoiceBox.setValue("NO");
        nameProductChoiceBox.setItems(FXCollections.observableArrayList(
                "Огурец свежий", "Томат свежий", "Картофель свежий", "Яблоко свежее", "Груша свежая",
                "Выбрать"));
        nameProductChoiceBox.setValue("Выбрать");

        // блокировка ввода размера скидки (если выбрано "нет скидки")
        notSaleRadioButton.setOnAction(event ->{
            saleProductTextField.setDisable(true);
            saleProductTextField.setText("0");
        });

        // разблокировка ввода размера скидки (если выбрано "есть скидка")
        saleRadioButton.setOnAction(event ->{
            saleProductTextField.setDisable(false);
            saleProductTextField.setText("");
        });

        // кнопка Изменить информацию о продукте
        changeProductButton.setOnAction(event -> {

            // определение типа выбранного продукта
            String kind = defineProduct(nameProductChoiceBox.getValue());
            if (kind == null)
                return;

            // поиск продукта в списке продуктов (по названию)
            Company company = Company.getInstance();
            Product product = null;
            for (int i = 0; i < company.getProducts().size(); i++){
                if(company.getProducts().get(i).getName().name().equals(kind)){
                    product = company.getProducts().get(i);
                    break;
                }
            }
            // принятие внесенных изменений
            try {
                double price = Double.parseDouble(priceProductTextField.getText());
                int saleAmount = Integer.parseInt(saleProductTextField.getText());
                boolean availability = availableRadioButton.isSelected();
                boolean isSale = saleRadioButton.isSelected();
                String about = aboutProductTextField.getText();

                productsTextArea.setText("Товар " + nameProductChoiceBox.getValue() + " изменен c \n\n");
                product.print(productsTextArea);

                product.setPrice(price);
                product.setAvailability(availability);
                product.getSale().setAmount(saleAmount);
                product.getSale().setHaveSale(isSale);
                product.setReferenceInformation(about);

                productsTextArea.appendText("\n На: \n");
                product.print(productsTextArea);
            }
            catch (Exception ex){
                productsTextArea.setText("Недопустимый ввод");
            }
        });

        // выбор продукта из списка -> его загрузка на экран (управление nameProductChoiceBox)
        nameProductChoiceBox.getSelectionModel().selectedItemProperty().addListener(
                (ObservableValue<? extends String> ov, String old_val, String new_val)-> {

                    String kind = defineProduct(new_val);
                    if (kind == null)
                        return;

                    Company company = Company.getInstance();
                    for (int i = 0; i < company.getProducts().size(); i++){
                        if(company.getProducts().get(i).getName().name().equals(kind)){
                            Product product = company.getProducts().get(i);
                            priceProductTextField.setText(product.getPrice()+"");
                            if (product.getAvailability())
                                availableRadioButton.fire();
                            else
                                notAvailableRadioButton.fire();
                            aboutProductTextField.setText(product.getReferenceInformation());
                            if (!product.getSale().getHaveSale()) {
                                notSaleRadioButton.fire();
                                saleProductTextField.setDisable(true);
                            }
                            else
                                saleRadioButton.fire();
                            saleProductTextField.setText(product.getSale().getAmount()+"");
                            break;
                        }
                    }
                }
        );

        // кнопка Сохранить изменения информации о компании
        changeCompanyButton.setOnAction(event -> {

            Company company = Company.getInstance();
            if (!company.getPhoneNumber().equals(phoneTextField.getText().trim())){
                company.setPhoneNumber(phoneTextField.getText().trim());
            }
            if (!company.getAddress().equals(addressTextField.getText().trim())){
                company.setAddress(addressTextField.getText().trim());
            }
            if (!company.getWorkTime().equals(workTimeTextField.getText().trim())){
                company.setWorkTime(workTimeTextField.getText().trim());
            }
            // сохранить фойл О_компании
            try {
                PrintWriter out = new PrintWriter(new FileWriter(Main.passAboutCompany, false));
                out.print(aboutCompanyTextArea.getText());
                out.close();
            } catch (IOException ex) {
                System.out.println(ex);
                System.out.println("WRONG IN О_нас.txt FROM AdministratorController");
            }
            System.out.println("The file О_нас was updated from AdministratorController");
        });

        // кнопка Удалить отзыв
        deleteReviewButton.setOnAction(event -> {

            if (!deleteReviewTextField.getText().trim().equals("")) {
                try {
                    int rowNum = Integer.parseInt(deleteReviewTextField.getText().trim());
                    Company c = Company.getInstance();

                    if (c.getReviews().size() >= rowNum) {
                        reviewsTextArea.setText("Удален отзыв:\n");
                        reviewsTextArea.appendText(c.getReviews().get(rowNum - 1));
                        c.getReviews().remove(rowNum - 1);
                        deleteReviewTextField.clear();
                        return;
                    } else {
                        deleteReviewTextField.setText("Строка не найдена");
                    }
                } catch (Exception ex) {
                    String review = deleteReviewTextField.getText().trim();
                    Company c = Company.getInstance();

                    for (int i = 0; i < c.getReviews().size(); i++) {
                        if (c.getReviews().get(i).equals(review + "\n")) {
                            reviewsTextArea.setText("Удален отзыв:\n");
                            reviewsTextArea.appendText(c.getReviews().get(i));
                            c.getReviews().remove(i);
                            deleteReviewTextField.clear();
                            return;
                        }
                    }
                    deleteReviewTextField.setText("Строка не найдена");
                }
            }
        });

        // кнопка Добавление курьера
        addCourierButton.setOnAction(event -> {

            boolean find = false;
            // проверка на пустые поля
            if (!surnameCourierTextField.getText().trim().isEmpty() &&
                    !nameCourierTextField.getText().trim().isEmpty() &&
                    !phoneCourierTextField.getText().trim().isEmpty()) {
                // проверка на наличие клиента с таким же номером телефона
                for (Courier c : Company.getInstance().getCouriers()) {
                    if (phoneCourierTextField.getText().equals(c.getPhoneNumber())) {
                        phoneCourierTextField.setText("Такой номер уже есть");
                        find = true;
                        break;
                    }
                }
                if (!find) {
                    Courier courier;

                    if (patronymicCourierTextField.getText().trim().equals("")) {
                        // курьер без отчества
                        courier = new Courier(nameCourierTextField.getText().trim(),
                                surnameCourierTextField.getText().trim(),
                                phoneCourierTextField.getText().trim());
                    } else {
                        // курьер с отчеством
                        courier = new Courier(nameCourierTextField.getText().trim(),
                                patronymicCourierTextField.getText().trim(),
                                surnameCourierTextField.getText().trim(),
                                phoneCourierTextField.getText().trim());
                    }
                    Company.getInstance().getCouriers().add(courier);
                    couriersTextArea.setText("Успешно добавлен следующий курьер:\n");
                    courier.print("small", couriersTextArea);
                    patronymicCourierTextField.clear();
                    nameCourierTextField.clear();
                    surnameCourierTextField.clear();
                    phoneCourierTextField.clear();
                }
            }
        });

        // кнопка Удаление курьера
        deleteCourierButton.setOnAction(event -> {

            if (!searchCourierTextField.getText().trim().isEmpty()) {

                RadioButton button = (RadioButton) group.getSelectedToggle();
                if (button.getText().equals(idRadioButton.getText())) {
                    try {
                        int ID = Integer.parseInt(searchCourierTextField.getText().trim());

                        Company c = Company.getInstance();
                        for (int i = 0; i < c.getCouriers().size(); i++) {
                            if (c.getCouriers().get(i).getCourierId() == ID) {
                                couriersTextArea.setText("Удален курьер по ID: " + ID + "\n");
                                c.getCouriers().get(i).print("small", couriersTextArea);
                                c.getCouriers().remove(i);
                                searchCourierTextField.clear();
                                return;
                            }
                        }
                        couriersTextArea.setText("Курьер по ID: " + ID + " не найден");
                    } catch (Exception ex) {
                        searchCourierTextField.setText("Неверный ввод (не цифры)");
                        return;
                    }
                } else {
                    searchCourierTextField.setText("Удаление только по ID");
                    return;
                }
                searchCourierTextField.clear();
            }
        });

        // кнопка Изменение статуса клиента
        changeClientStatusButton.setOnAction(event -> {

            boolean find = false;

            if (!clientLoginTextField.getText().trim().isEmpty()) {
                String login = clientLoginTextField.getText().trim();
                for (Client c : admin.getClients()) {
                    if (c.getLogin().equals(login)) {
                        // изменить статус
                        c.setStatus(stringToClientStatus(statusChangeChoiceBox.getValue().trim()));
                        // почистить поле и вывести клиента
                        clientsTextArea.clear();
                        c.print("small", clientsTextArea);
                        clientLoginTextField.clear();
                        find = true;
                        break;
                    }
                }
            }
            if (!find)
                clientLoginTextField.setText("Неверный логин");
        });

        // кнопка найти заказ
        findOrderButton.setOnAction(event -> {

            try {
                int ID = Integer.parseInt(searchOrderTextField.getText().trim());
                boolean find = false;
                // поиск заказа по ID в файле
                try {
                    Scanner in = new Scanner(new File(sample.Main.passOrdersDB), "UTF-8");
                    String s;
                    while (in.hasNextLine()) {
                        s = in.nextLine();
                        if (s.contains("\"orderId\":" + ID)) {
                            ordersTextArea.setText("Найден заказ по ID: " + ID + "\n");
                            MyJSON.fromJSON(s, Order.class).print(ordersTextArea);
                            find = true;
                            break;
                        }
                    }
                    if (!find)
                        ordersTextArea.setText("Заказ по ID: " + ID + "\nНе найдено");
                    searchOrderTextField.clear();
                    in.close();
                } catch (FileNotFoundException ex) {
                    System.out.println(ex);
                    System.out.println("WRONG IN OrdersDB.txt FROM AdministratorController");
                }

            } catch (Exception ex) {
                searchOrderTextField.setText("Неверный ввод (не цифры)");
            }
        });

        // кнопка найти клиента(ов)
        findClientButton.setOnAction(event -> {

            RadioButton button = (RadioButton) groupCl.getSelectedToggle();
            if (button.getText().equals(surnameClientRadioButton.getText())) {
                searchClientBySurnameClicked(admin.getClients());
            } else {
                searchClientByStatusClicked(admin.getClients());
            }
        });

        // кнопка найти курьера(ов)
        findCourierButton.setOnAction(event -> {

            if (!searchCourierTextField.getText().trim().isEmpty()) {

                RadioButton button = (RadioButton) group.getSelectedToggle();
                if (button.getText().equals(idRadioButton.getText())) {
                    searchCourierByIDClicked();
                } else {
                    searchCourierBySurnameClicked();
                }
            }
        });

        // кнопка показать
        showButton.setOnAction(event -> {

            if (clientsTab.isSelected()) {
                clientsTextArea.clear();
                admin.showClients(clientsTextArea);
            }
            else if (couriersTab.isSelected()){
                couriersTextArea.clear();
                admin.showCouriers(couriersTextArea);
            }
            else if (productsTab.isSelected()) {
                productsTextArea.clear();
                admin.showProducts(productsTextArea);
            }
            else if (ordersTab.isSelected()) {
                ordersTextArea.clear();
                admin.showOrders(ordersTextArea);
            }
            else if (reviewsTab.isSelected()) {
                reviewsTextArea.clear();
                admin.showReviews(reviewsTextArea);
            }
            else if (companyTab.isSelected()) {
                Company company = Company.getInstance();
                phoneTextField.setText(company.getPhoneNumber());
                addressTextField.setText(company.getAddress());
                workTimeTextField.setText(company.getWorkTime());
                aboutCompanyTextArea.clear();
                admin.showAboutCompanyInformation(aboutCompanyTextArea);
            }
        });

        // кнопка выход
        exitButton.setOnAction(event -> {

            // сохранить телефон, адрес и время работы компании в файл
            try {
                PrintWriter out = new PrintWriter(new FileWriter(Main.passCompany, false));
                out.println(Company.getInstance().getPhoneNumber());
                out.println(Company.getInstance().getAddress());
                out.print(Company.getInstance().getWorkTime());
                out.close();
            } catch (IOException ex) {
                System.out.println(ex);
                System.out.println("WRONG IN Company.txt FROM AdministratorController");
            }
            System.out.println("The file Company was updated from AdministratorController");

            // сохранить отзывы в файл
            try {
                PrintWriter out = new PrintWriter(new FileWriter(Main.passReviewsFile, false));
                for (String s : Company.getInstance().getReviews())
                    out.print(s);
                out.close();
            } catch (IOException ex) {
                System.out.println(ex);
                System.out.println("WRONG IN Reviews.txt FROM AdministratorController");
            }
            System.out.println("The file Reviews was updated from AdministratorController");

            // сохранить курьеров в файл
            ArrayList<String> sCouriers = new ArrayList<String>();
            ArrayList<Courier> couriers = Company.getInstance().getCouriers();
            int len = couriers.size();
            for (int i = 0; i < len; i++) {
                sCouriers.add(MyJSON.toJSON(couriers.get(i)));
            }
            try {
                PrintWriter out = new PrintWriter(new FileWriter(Main.passCouriersDB, false));
                for (String s : sCouriers)
                    out.println(s);
                out.close();
            } catch (IOException ex) {
                System.out.println(ex);
                System.out.println("WRONG IN CouriersDB.txt FROM AdministratorController");
            }
            System.out.println("The file CouriersDB was updated from AdministratorController");

            // сохранить клиентов в файл
            ArrayList<String> sClients = new ArrayList<String>();
            ArrayList<Client> clients = admin.getClients();
            len = clients.size();
            for (int i = 0; i < len; i++) {
                sClients.add(MyJSON.toJSON(clients.get(i)));
            }
            try {
                PrintWriter out = new PrintWriter(new FileWriter(Main.passClientsDB, false));
                for (String s : sClients)
                    out.println(s);
                out.close();
            } catch (IOException ex) {
                System.out.println(ex);
                System.out.println("WRONG IN ClientsDB.txt FROM AdministratorController");
            }
            System.out.println("The file ClientsDB was updated from AdministratorController");

            // сохранить продукты БД в файл
            ArrayList<String> sProducts = new ArrayList<String>();
            ArrayList<Product> products = Company.getInstance().getProducts();
            len = products.size();
            for (int i = 0; i < len; i++) {
                sProducts.add(MyJSON.toJSON(products.get(i)));
            }
            try {
                PrintWriter out = new PrintWriter(new FileWriter(Main.passProductsDB, false));
                for (String s : sProducts)
                    out.println(s);
                out.close();
            } catch (IOException ex) {
                System.out.println(ex);
                System.out.println("WRONG IN ProductsDB.txt FROM AdministratorController");
            }
            System.out.println("The file ProductsDB was updated from AdministratorController");

            // закрыть это окно и родителя
            exitButton.getScene().getWindow().hide();
        });
    }

    private ClientStatus stringToClientStatus(String status) {
        for (ClientStatus st:ClientStatus.values()){
            if (st.name().equals(status))
                return st;
        }
        return null;
    }

    private String defineProduct(String productName) {

        String kind;

        switch(productName){
            case "Огурец свежий":
                kind = "CUCUMBER";
                break;
            case "Томат свежий":
                kind = "TOMATO";
                break;
            case "Картофель свежий":
                kind = "POTATO";
                break;
            case "Яблоко свежее":
                kind = "APPLE";
                break;
            case "Груша свежая":
                kind = "PEAR";
                break;
            default:
                priceProductTextField.clear();
                aboutProductTextField.clear();
                saleProductTextField.clear();
                return null;
        }
        return kind;
    }

    private void searchClientByStatusClicked(ArrayList<Client> cl) {

        String status = (String) statusChoiceBox.getValue().trim();
        boolean find = false;

        clientsTextArea.setText("Клиент(ы) со статусом: " + status + "\n");
        for (Client c: cl) {
            if (c.getStatus().name().equals(status)){
                c.print("small", clientsTextArea);
                find = true;
            }
        }
        if(!find)
            clientsTextArea.appendText("Не найдено");
        searchClientTextField.clear();
    }

    private void searchClientBySurnameClicked(ArrayList<Client> cl) {

        String surname = searchClientTextField.getText().trim();
        boolean find = false;

        clientsTextArea.setText("Клиент(ы) по фамилии: " + surname + "\n");
        for (Client c: cl) {
            if (c.getSurname().equals(surname)){
                c.print("small", clientsTextArea);
                find = true;
            }
        }
        if(!find)
            clientsTextArea.appendText("Не найдено");
        searchClientTextField.clear();
    }

    private void searchCourierBySurnameClicked() {

        String surname = searchCourierTextField.getText().trim();
        ArrayList<Courier> co = Company.getInstance().getCouriers();
        boolean find = false;

        couriersTextArea.setText("Курьер(ы) по фамилии: " + surname + "\n");
        for (Courier c: co) {
            if (c.getSurname().equals(surname)){
                c.print("small", couriersTextArea);
                find = true;
            }
        }
        if(!find)
            couriersTextArea.appendText("Не найдено");
        searchCourierTextField.clear();
    }

    private void searchCourierByIDClicked() {

        int ID;
        try{
            ID = Integer.parseInt(searchCourierTextField.getText().trim());
        }
        catch (Exception ex) {
            searchCourierTextField.setText("Неверный ввод (не цифры)");
            return;
        }

        ArrayList<Courier> co = Company.getInstance().getCouriers();

        for (Courier c: co) {
            if (c.getCourierId() == ID){
                couriersTextArea.setText("Найден курьер по ID: " + ID + "\n");
                c.print("small", couriersTextArea);
                searchCourierTextField.clear();
                return;
            }
        }
        couriersTextArea.setText("Курьер по ID: " + ID + " не найден");
        searchCourierTextField.clear();
    }
}


