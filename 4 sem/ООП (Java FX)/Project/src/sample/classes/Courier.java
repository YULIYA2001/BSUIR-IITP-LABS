package sample.classes;

import javafx.scene.control.TextArea;

public class Courier extends Person{

    private int courierId;
    public static int ids;

    public Courier(String name, String surname, String phoneNumber, int courierId){
        super(name, surname, phoneNumber);
        this.courierId = courierId;
    }

    public Courier(String name, String patronymic, String surname, String phoneNumber, int courierId){
        super(name, patronymic, surname, phoneNumber);
        this.courierId = courierId;
    }

    public Courier(String name, String surname, String phoneNumber){
        super(name, surname, phoneNumber);
        this.courierId = ids;
        ids++;
    }

    public Courier(String name, String patronymic, String surname, String phoneNumber){
        super(name, patronymic, surname, phoneNumber);
        this.courierId = ids;
        ids++;
    }

    public int getCourierId() {
        return courierId;
    }

    public void setCourierId(int courierId){
        this.courierId = courierId;
    }

    @java.lang.Override
    public void print() {
        System.out.println("ID " + getCourierId() + "\nИмя " + getName() + "\nФамилия " + getSurname() +
                "\nОтчество " + getPatronymic() + "\nТелефон " + getPhoneNumber());
    }

    public void print(String small) {

        if (small.equals("small")) {
            System.out.println("ID " + getCourierId() + "   " + getSurname() + " " + getName() + " " +
                    getPatronymic() + "   Телефон: " + getPhoneNumber());
        }
    }

    // для вывода на форму
    public void print(String small, TextArea couriersTextArea) {

        if (small.equals("small")) {
            couriersTextArea.appendText("ID " + getCourierId() + "     " + getSurname() + " " + getName() +
                    " " + getPatronymic() + "     Телефон: " + getPhoneNumber() + "\n\n");
        }
    }
}
