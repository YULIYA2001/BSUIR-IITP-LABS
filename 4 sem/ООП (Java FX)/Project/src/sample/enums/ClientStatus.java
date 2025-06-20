package sample.enums;

public enum ClientStatus {
    NO(0),
    BRONZE(2),
    SILVER(3),
    GOLD(5),
    PLATINUM(10),
    DIAMOND(15);
    private int amount;

    ClientStatus(int amount) { this.amount = amount; }

    public int getAmount(){ return amount;}
}