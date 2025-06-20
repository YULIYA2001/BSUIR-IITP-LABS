package sample.classes;

import javafx.scene.control.TextArea;
import java.util.ArrayList;

public class Order implements Printable{

    private Client client;
    private Delivery delivery;
    private int orderId;
    private  OrderStatus orderStatus;
    private double cost;
    private ArrayList<Cart> carts = new ArrayList<Cart>();

    public Order(Client client, Delivery delivery, int orderId, OrderStatus orderStatus, double cost,
                 ArrayList<Cart> carts) {
        this.client = client;
        this.delivery = delivery;
        this.orderId = orderId;
        this.orderStatus = orderStatus;
        this.cost = cost;
        for (int i = 0; i < carts.size(); i++) {
            this.carts.add(carts.get(i));
        }
    }

    public void setClient(Client client) {
        this.client = client;
    }

    public Client getClient() {
        return client;
    }

    public void setDelivery(Delivery delivery) {
        this.delivery = delivery;
    }

    public Delivery getDelivery() {
        return delivery;
    }

    public void setOrderId(int orderId) {
        this.orderId = orderId;
    }

    public int getOrderId() {
        return orderId;
    }

    public double getCost() {
        return cost;
    }

    public void addCart(Cart cart) {
        this.carts.add(cart);
    }

    public ArrayList<Cart> getCarts() {
        return carts;
    }


    @Override
    public void print() {

        double cost = (int)Math.round(getCost()*100) / 100.0;
        System.out.println("ID " + getOrderId() + "\nДоставка: " +
                (getDelivery().getKind() == Delivery.KindOfDelivery.PICKUP ? "Самовывоз" : "Курьером")
                + "   Стоимость с доставкой: " + cost + " p.");
        client.print("for order");
        System.out.println("Продукты: ");
        for (int i = 0; i < carts.size(); i++) {
            carts.get(i).getProduct().print();
        }
        System.out.println();
    }

    public void print(TextArea ordersTextArea) {

        double cost = (int)Math.round(getCost()*100) / 100.0;
        ordersTextArea.appendText("ID " + getOrderId() + "\nДоставка: " +
                (getDelivery().getKind() == Delivery.KindOfDelivery.PICKUP ? "Самовывоз" : "Курьером")
                + "     Стоимость с доставкой: " + cost + " p.\n");
        client.print("for order", ordersTextArea);
        ordersTextArea.appendText("Продукты: \n");
        for (int i = 0; i < carts.size(); i++) {
            carts.get(i).print(ordersTextArea);
        }
    }
}
