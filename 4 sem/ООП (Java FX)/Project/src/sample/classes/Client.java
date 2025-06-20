package sample.classes;

import javafx.scene.control.TextArea;
import  sample.enums.ClientStatus;

public class Client extends Person{

    private String login;
    private String password;
    private String address;
    private ClientStatus status;

    public Client(String name, String patronymic, String surname, String phoneNumber, String address,
           String login, String password, ClientStatus status){
        super(name, patronymic, surname, phoneNumber);
        this.address = address;
        this.login = login;
        this.password = password;
        this.status = status;
    }

    public Client(String name, String surname, String phoneNumber, String address,
           String login, String password, ClientStatus status){
        super(name, surname, phoneNumber);
        this.address = address;
        this.login = login;
        this.password = password;
        this.status = status;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getAddress(){
        return this.address;
    }

    public void setStatus(ClientStatus status){
        this.status = status;
    }

    public ClientStatus getStatus(){
        return this.status;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public String getLogin() {
        return login;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getPassword() {
        return password;
    }

    @java.lang.Override
    public void print() {
        System.out.println("Имя: " + getName() + "\nФамилия: " + getSurname() + "\nОтчество: " + getPatronymic() +
                "\nТелефон: " + getPhoneNumber() + "\nАдрес доставки: " + getAddress() + "\nЛогин: " + getLogin() +
                "\nПароль: " + getPassword() + "\n" + getStatus());
    }

    public void print(String type) {

        if (type.equals("small")) {
            System.out.println(getSurname() + " " + getName() + " " + getPatronymic() + "\nТелефон: " +
                    getPhoneNumber() + "   Адрес доставки: " + getAddress() + "   Логин: " + getLogin() + "\n");
        }
        else if (type.equals("for order")){
            System.out.println("Клиент: " + getSurname() + " " + getName() + " " + getPatronymic() +
                    "   Телефон: " + getPhoneNumber() + "   Адрес доставки: " + getAddress() +
                    "   Логин: " + getLogin() + "\n");
        }
    }

    // для вывода на форму
    public void print(String type, TextArea clientsTextArea) {

        if (type.equals("small")) {
            clientsTextArea.appendText(getSurname() + " " + getName() + " " + getPatronymic() +
                    "\nТелефон: " + getPhoneNumber() + "     Адрес доставки: " + getAddress() + "     Логин: " +
                    getLogin() + "     Статус: " + getStatus().name() + "\n\n");
        }
        else if (type.equals("for order")){
            clientsTextArea.appendText("Клиент: " + getSurname() + " " + getName() + " " + getPatronymic() +
                    "     Телефон: " + getPhoneNumber() + "     Адрес доставки: " + getAddress() +
                    "     Логин: " + getLogin() + "\n");
        }
    }
}