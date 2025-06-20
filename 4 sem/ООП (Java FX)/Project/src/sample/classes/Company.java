package sample.classes;

import com.alibaba.fastjson.JSON;
import sample.Main;

import java.io.*;
import java.util.ArrayList;
import java.util.NoSuchElementException;
import java.util.Scanner;

// паттерн Singleton (порождающий паттерн, у класса только 1 экземпляр с глобальной точкой доступа)
public class Company {

    private static Company instance = null;
    private String name = "ООО \"Чиполлино\"";
    private String phoneNumber = "+375 (17) 123-45-68";
    private String address = "г.Минск, ул.Овощная, д.35";
    private String workTime = "пн-пт 9.00 - 18.00";
    private ArrayList<String> reviews = new ArrayList<String>();
    private ArrayList<Courier> couriers = new ArrayList<Courier>();
    private ArrayList<Product> products = new ArrayList<Product>();

    private Company() {
    }

    public static synchronized Company getInstance() {
        if (instance == null) {
            instance = new Company();
        }
        return instance;
    }

    public void initCompany(){
        //this.name = name;
        // считывание телефона и адреса компании из файла
        try {
            Scanner in = new Scanner(new File(Main.passCompany), "UTF-8");
            this.phoneNumber = in.nextLine();
            this.address = in.nextLine();
            this.workTime = in.nextLine();
            in.close();
        }
        catch(FileNotFoundException ex) {
            System.out.println("WRONG IN " + Main.passCompany + "FROM Company");
            System.out.println(ex);
        }
        catch(NoSuchElementException ex) {
            System.out.println("WRONG IN " + Main.passCompany + "FROM Company");
            System.out.println(ex);
        }

        // считывание отзывов из файла
        try {
            Scanner in = new Scanner(new File(Main.passReviewsFile), "UTF-8");
            String check;
            while (in.hasNextLine()) {
                check = in.nextLine().trim();
                this.reviews.add(check + "\n");
            }
            in.close();
        }
        catch(FileNotFoundException ex) {
            System.out.println("WRONG IN " + Main.passReviewsFile + "FROM Company");
            System.out.println(ex);
        }

        // считывание курьеров из файла в массив
        try {
            Scanner in = new Scanner(new File(Main.passCouriersDB), "UTF-8");
            String s;
            while (in.hasNextLine()) {
                s = in.nextLine().trim();
                // обработка на пустоту файла
                try {
                    this.couriers.add(JSON.parseObject(s, Courier.class));
                }catch (Exception ex) {}
            }
            in.close();
        }
        catch(FileNotFoundException ex) {
            System.out.println("WRONG IN " + Main.passCouriersDB + "FROM Company");
            System.out.println(ex);
        }

        // считываем продукты из файла БД в массив продуктов
        try {
            Scanner in = new Scanner(new File(Main.passProductsDB), "UTF-8");
            String s;
            while (in.hasNextLine()) {
                s = in.nextLine().trim();
                // обработка на пустоту файла
                try {
                    this.products.add(JSON.parseObject(s, Product.class));
                }catch (Exception ex) {}
            }
            in.close();
        }
        catch (FileNotFoundException ex){
            System.out.println("WRONG IN " + Main.passProductsDB + "FROM Company");
            System.out.println(ex);
        }
    }

    public String getWorkTime() { return workTime; }

    public void setWorkTime(String s){ this.workTime = s;}

    public void setProducts(ArrayList<Product> products) {
        this.products = products;
    }

    public ArrayList<Product> getProducts() {
        return this.products;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setAddress(String address) { this.address = address; }

    public String getAddress() { return address; }

    public ArrayList<Courier> getCouriers() {
        return this.couriers;
    }

    public void setReviews(String review) { this.reviews.add(review); }

    public ArrayList<String> getReviews() {
        return reviews;
    }

    public void setCourier(Courier courier) {
        this.couriers.add(courier);
    }
}
