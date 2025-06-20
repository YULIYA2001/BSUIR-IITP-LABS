package sample.classes;

import javafx.scene.control.TextArea;

public class Cart {

    private Product product;
    private double amount;
    private double costWithSale;

    public Cart(Product product, double amount){
        this.product = product;
        this.amount = amount;
        this.costWithSale = product.getPrice() * amount * (1 - product.getSale().getAmount()/100.0);
    }

    public void setProduct(Product product) {
        this.product = product;
    }

    public Product getProduct() {
        return product;
    }

    public void setAmount(double amount) {
        this.amount = amount;
    }

    public double getAmount() {
        return amount;
    }

    public void setCostWithSale(double cost) {
        this.costWithSale = cost;
    }

    public double getCostWithSale() { return costWithSale; }

    public void print(TextArea ordersTextArea) {

        ordersTextArea.appendText(getAmount() + " кг      ");
        getProduct().print(ordersTextArea);
    }
}
