package sample.classes;

import javafx.scene.control.TextArea;
import sample.enums.FruitVegetable;

public class Product implements Printable{

    private FruitVegetable name;
    private double price;
    private String referenceInformation;
    private boolean availability;
    private Sale sale;

    public Product(FruitVegetable name, double price,
                   String referenceInformation, boolean availability, Sale sale){
        this.name = name;
        this.price = price;
        this.referenceInformation = referenceInformation;
        this.availability = availability;
        this.sale = sale;
    }

    public void setName(FruitVegetable name) {
        this.name = name;
    }

    public FruitVegetable getName() {
        return name;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public double getPrice() {
        return price;
    }

    public void setReferenceInformation(String referenceInformation) {
        this.referenceInformation = referenceInformation;
    }

    public String getReferenceInformation() {
        return referenceInformation;
    }

    public void setAvailability(boolean available) {
        this.availability = available;
    }

    public boolean getAvailability() {
        return availability;
    }

    public void setSale(Sale sale) {
        this.sale = sale;
    }

    public Sale getSale() {
        return sale;
    }

    @java.lang.Override
    public void print() {

        String name = "";
        switch (getName()){
            case CUCUMBER:
                name = "Огурец свежий";
                break;
            case TOMATO:
                name = "Томат свежий";
                break;
            case POTATO:
                name = "Картофель свежий";
                break;
            case APPLE:
                name = "Яблоко свежее";
                break;
            case PEAR:
                name = "Груша свежая";
        }

        System.out.println(name + " Цена: " + getPrice() + " p/кг   Справка: " +
                getReferenceInformation() + "   Наличие: " + (this.availability ? "Да" : "Нет") +
                "   Скидка: " + (this.sale.getHaveSale() ? this.sale.getAmount() + "%" : "Нет"));
    }

    public void print(TextArea productTextArea) {

        String name = "";
        switch (getName()){
            case CUCUMBER:
                name = "Огурец свежий";
                break;
            case TOMATO:
                name = "Томат свежий";
                break;
            case POTATO:
                name = "Картофель свежий";
                break;
            case APPLE:
                name = "Яблоко свежее";
                break;
            case PEAR:
                name = "Груша свежая";
        }

        productTextArea.appendText(name + "\nЦена: " + getPrice() + " p/кг     Справка: " +
                getReferenceInformation() + "     Наличие: " + (this.availability ? "Да" : "Нет") +
                "     Скидка: " + (this.sale.getHaveSale() ? this.sale.getAmount() + "%" : "Нет") + "\n\n");
    }
}
