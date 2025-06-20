package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.scene.image.Image;

import sample.classes.*;

import java.io.*;
import java.util.Scanner;

public class Main extends Application {

    public static final String passClientsDB = "C:\\YCHEBA\\4сем\\ООП\\Project\\ClientsDB.txt";
    public static final String passCouriersDB = "C:\\YCHEBA\\4сем\\ООП\\Project\\CouriersDB.txt";
    public static final String passReviewsFile = "C:\\YCHEBA\\4сем\\ООП\\Project\\Reviews.txt";
    public static final String passProductsDB = "C:\\YCHEBA\\4сем\\ООП\\Project\\ProductsDB.txt";
    public static final String passCartsFolder = "C:\\YCHEBA\\4сем\\ООП\\Project\\Carts";
    public static final String passOrdersDB = "C:\\YCHEBA\\4сем\\ООП\\Project\\OrdersDB.txt";
    public static final String passCompany = "C:\\YCHEBA\\4сем\\ООП\\Project\\CompanyInf.txt";
    public static final String passAboutCompany = "C:\\YCHEBA\\4сем\\ООП\\Project\\О_нас.txt";
    // клиент, который осуществил вход в приложение
    public static Client currentClient;
    public static int ordersCount_ID = 0;

    @Override
    public void start(Stage primaryStage) throws Exception{

        // Singleton-паттерн
        Company company = Company.getInstance();
        company.initCompany();

        // подсчет количества заказов (для id следующего заказа)
        try {
            Scanner in = new Scanner(new File(Main.passOrdersDB), "UTF-8");
            int count = 0;
            String s;
            while (in.hasNextLine()) {
                s = in.nextLine().trim();
                // обработка на пустоту файла
                if (s.indexOf("orderId") != -1)
                    count++;
            }
            ordersCount_ID = count;
            in.close();
        }
        catch(FileNotFoundException ex) {
            System.out.println(ex);
            System.out.println("WRONG IN " + Main.passCouriersDB + "FROM Main");
        }

        // определение следующего ID для курьера (по максимальному имеющемуся)
        int max = 0;
        if(company.getCouriers().size() != 0) {
            max = company.getCouriers().get(0).getCourierId();
            for (int i = 1; i < company.getCouriers().size(); i++) {
                if(max < company.getCouriers().get(i).getCourierId())
                    max = company.getCouriers().get(i).getCourierId();
            }
        }
        Courier.ids = ++max;



        // объект в json и обратно
        //String jsonStringClient = JSON.toJSONString(c);
        //Client c = JSON.parseObject(jsonStringClient, Client.class);

        Parent root = FXMLLoader.load(getClass().getResource("fxml/sample.fxml"));
        primaryStage.setTitle("Магазин свежих фруктов и овощей");
        primaryStage.getIcons().add(new Image("file:C:\\YCHEBA\\4сем\\ООП\\Project\\src\\sample\\images\\onion.png"));
        primaryStage.setScene(new Scene(root, 700, 400));
        // невозможно менять размеры окна
        primaryStage.setResizable(false);
        primaryStage.show();
        }

        public static void main(String[] args) {
            launch(args);
        }
    }
