package sample.classes;

import java.time.LocalDate;

public class Delivery {

    private KindOfDelivery kind;
    private double price;
    private LocalDate time;              //крайнее время привоза
    private String address;
    private Courier courier;

    public Delivery(KindOfDelivery kind, double price, LocalDate time, String address, Courier courier){
        this.kind = kind;
        this.price = price;
        this.time = time;
        this.address = address;
        this.courier = courier;
    }

    public void setKind(KindOfDelivery kind) {
        this.kind = kind;
    }

    public KindOfDelivery getKind() {
        return kind;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public double getPrice() {
        return price;
    }

    public void setTime(LocalDate time) {
        this.time = time;
    }

    public LocalDate getTime() {
        return time;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getAddress() {
        return address;
    }

    public void setCourier(Courier courier) {
        this.courier = courier;
    }

    public Courier getCourier() {
        return courier;
    }

    public enum KindOfDelivery{
        COURIER,
        PICKUP
    }
}

/*
Date date = new Date();
String dat = new SimpleDateFormat("dd-MM-yyyy").format(date);*/
