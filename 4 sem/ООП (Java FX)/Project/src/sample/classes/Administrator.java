package sample.classes;

import com.alibaba.fastjson.JSON;
import javafx.scene.control.TextArea;
import sample.Main;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Administrator {

    public static final String adminLogin = "0";//TODO "administrator";
    public static final String adminPassword = "0";//"rotartsinimda";
    private ArrayList<Client> clients = Administrator.takeClients();

    public ArrayList<Client> getClients(){
        return this.clients;
    }

    private static ArrayList<Client> takeClients(){

        ArrayList<Client> clients = new ArrayList<Client>();
        try {
            Scanner in = new Scanner(new File(Main.passClientsDB), "UTF-8");
            String s;
            while (in.hasNextLine()) {
                s = in.nextLine();
                // обработка на пустоту файла
                try {
                    clients.add(JSON.parseObject(s, Client.class));
                }catch (Exception ex) {}
            }
            in.close();
        }
        catch(FileNotFoundException ex) {
            System.out.println(ex);
            System.out.println("WRONG IN ClientsDB.txt FROM Administrator");
        }

        return clients;
    }

    public void showClients(){

        System.out.println("\nClients: ");

        // считывание клиентов из файла
        for (Client c: this.clients) {
            c.print("small");
        }
    }

    // для вывода клиентов на форму
    public void showClients(TextArea clientsTextArea){

        // считывание клиентов из файла
        for (Client c: this.clients) {
            c.print("small", clientsTextArea);
        }
    }

    public void showCouriers(){

        Company company = Company.getInstance();

        System.out.println("\nCouriers: ");
        for (Courier courier: company.getCouriers()) {
            courier.print("small");
        }
    }

    // для вывода курьеров на форму
    public void showCouriers(TextArea couriersTextArea){

        Company company = Company.getInstance();

        for (Courier courier: company.getCouriers()) {
            courier.print("small", couriersTextArea);
        }
    }

    public void showProducts(){

        Company company = Company.getInstance();

        System.out.println("\nProducts: ");
        for (Product product: company.getProducts()) {
            product.print();
        }
    }

    // для вывода продуктов на форму
    public void showProducts(TextArea productsTextArea){

        Company company = Company.getInstance();

        for (Product product: company.getProducts()) {
            product.print(productsTextArea);
        }
    }

    public void showOrders(){

        System.out.println("\nOrders: ");
        // считывание заказов из файла
        try {
            Scanner in = new Scanner(new File(Main.passOrdersDB), "UTF-8");
            String s;
            while (in.hasNextLine()) {
                s = in.nextLine();
                // обработка на пустоту файла
                try {
                    JSON.parseObject(s, Order.class).print();
                }catch (Exception ex) {
                    s = null;
                }
            }
            in.close();
        }
        catch(FileNotFoundException ex) {
            System.out.println(ex);
            System.out.println("WRONG IN OrdersDB.txt FROM Administrator (showOrders)");
        }
    }

    // для вывода на форму
    public void showOrders(TextArea ordersTextArea){

        // считывание заказов из файла
        try {
            Scanner in = new Scanner(new File(Main.passOrdersDB), "UTF-8");
            String s;
            while (in.hasNextLine()) {
                s = in.nextLine();
                // обработка на пустоту файла
                try {
                    JSON.parseObject(s, Order.class).print(ordersTextArea);
                }catch (Exception ex) {
                    s = null;
                }
            }
            in.close();
        }
        catch(FileNotFoundException ex) {
            System.out.println(ex);
            System.out.println("WRONG IN OrdersDB.txt FROM Administrator (showOrders)");
        }
    }

    public void showReviews(){

        Company company = Company.getInstance();

        System.out.println("\nReviews: ");
        for (String review: company.getReviews()) {
            System.out.println(review);
        }
    }

    // для вывода на форму
    public void showReviews(TextArea ordersTextArea){

        Company company = Company.getInstance();

        for (String review: company.getReviews()) {
            ordersTextArea.appendText(review);
        }
    }

    // для вывода на форму
    public void showAboutCompanyInformation(TextArea aboutCompanyTextArea){

        aboutCompanyTextArea.setWrapText(true);
        File file = new File(Main.passAboutCompany);
        try (Scanner input = new Scanner(file)) {
            while (input.hasNextLine()) {
                aboutCompanyTextArea.appendText(input.nextLine());
            }
        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
            System.out.print("WRONG WITH FILE О_нас.txt FROM Adminstrator");
        }
        aboutCompanyTextArea.positionCaret(0);
    }

    public double returnProfit(){

        double profit = 0;

        // считывание заказов из файла
        try {
            Scanner in = new Scanner(new File(Main.passOrdersDB), "UTF-8");
            String s;
            while (in.hasNextLine()) {
                s = in.nextLine();
                // обработка на пустоту файла
                try {
                    profit += JSON.parseObject(s, Order.class).getCost();
                }catch (Exception ex) {
                    s = null;
                }
            }
            in.close();
        }
        catch(FileNotFoundException ex) {
            System.out.println("WRONG IN OrdersDB.txt FROM Administrator (showProfit)");
            System.out.println(ex);
        }
        // округление до сотых
        profit = (int)Math.round(profit*100) / 100.0;

        return profit;
    }
}

