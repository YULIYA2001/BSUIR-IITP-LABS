package sample.classes;

public abstract class Person implements Printable{

    private String name;
    private String patronymic = "-";
    private String surname;
    private String phoneNumber;

    Person(String name, String surname, String phoneNumber){
        this.name = name;
        this.surname = surname;
        this.phoneNumber = phoneNumber;
    }

    Person(String name, String patronymic, String surname, String phoneNumber){
        this.name = name;
        this.patronymic = patronymic;
        this.surname = surname;
        this.phoneNumber = phoneNumber;
    }

    public String getName(){
        return this.name;
    }

    public String getPatronymic(){
        return this.patronymic;
    }

    public String getSurname(){
        return this.surname;
    }

    public String getPhoneNumber(){
        return this.phoneNumber;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setPatronymic(String patronymic) {
        this.patronymic = patronymic;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }
}
