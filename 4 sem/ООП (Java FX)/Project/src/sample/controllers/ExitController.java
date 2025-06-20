package sample.controllers;

import java.io.*;
import java.util.ArrayList;

import com.alibaba.fastjson.JSON;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.stage.Stage;
import sample.Main;
import sample.classes.Company;
import sample.classes.Courier;
import sample.classes.Product;

public class ExitController {

    @FXML
    private Button exitOkButton;

    @FXML
    private Button exitNoButton;

    @FXML
    void initialize() {

        // кнопка Ок подтверждение выхода
        exitOkButton.setOnAction(event -> {

            // сохранить отзывы в файл
            try {
                PrintWriter out = new PrintWriter(new FileWriter(Main.passReviewsFile, false));
                for (String s : Company.getInstance().getReviews())
                    out.print(s);
                out.close();
            }
            catch (IOException ex){
                System.out.println(ex);
            }
            System.out.println("The file Reviews was updated from ExitController");

            /*TODO // сохранить курьеров в файл
            ArrayList<String> sCouriers = new ArrayList<String>();
            ArrayList<Courier> couriers = Company.getInstance().getCouriers();
            int len = couriers.size();
            for(int i = 0; i < len; i++){
                sCouriers.add(JSON.toJSONString(couriers.get(i)));
            }
            try {
                PrintWriter out = new PrintWriter(new FileWriter(Main.passCouriersDB, false));
                for (String s : sCouriers)
                    out.println(s);
                out.close();
            }
            catch (IOException ex){
                System.out.println(ex);
            }
            System.out.println("The file CouriersDB was updated from ExitController");

            // сохранить продукты БД в файл
            ArrayList<String> sProducts = new ArrayList<String>();
            ArrayList<Product> products = Company.getInstance().getProducts();
            for (Product product : products) {
                sProducts.add(JSON.toJSONString(product));
            }
            try {
                PrintWriter out = new PrintWriter(new FileWriter(Main.passProductsDB, false));
                for (String s : sProducts)
                    out.println(s);
                out.close();
            }
            catch (IOException ex){
                System.out.println(ex);
            }
            System.out.println("The file ProductsDB was updated from ExitController");*/

            // закрыть это окно и родителя
            Stage stage1 = (Stage) exitOkButton.getScene().getWindow();
            Stage parentStage = (Stage) stage1.getOwner();
            stage1.close();
            parentStage.close();
        });

        // кнопка No отмена выхода
        exitNoButton.setOnAction(event -> {
            // закрыть это окно
            exitNoButton.getScene().getWindow().hide();
        });
    }
}

