package sample.classes;

import java.time.LocalDate;
import sample.enums.OStatus;

public class OrderStatus {

    private OStatus orderStatus;
    // время начала
    private LocalDate time;

    public OrderStatus(OStatus orderStatus, LocalDate time){
        this.orderStatus = orderStatus;
        this.time = time;
    }

    public void setOrderStatus(OStatus orderStatus) {
        this.orderStatus = orderStatus;
    }

    public OStatus getOrderStatus() {
        return orderStatus;
    }

    public void setTime(LocalDate time) {
        this.time = time;
    }

    public LocalDate getTime() {
        return time;
    }
}