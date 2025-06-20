package sample.classes;

public class Sale {

    private boolean haveSale;
    private int amount;

    public Sale(boolean haveSale, int amount){
        this.haveSale = haveSale;
        if (this.haveSale)
            this.amount = amount;
        else
            this.amount = 0;
    }

    public void setHaveSale(boolean haveSale) {
        this.haveSale = haveSale;
    }

    public boolean getHaveSale() {
        return haveSale;
    }

    public void setAmount(int amount) {
        this.amount = amount;
    }

    public int getAmount() {
        return amount;
    }
}