public class PriceTracker {
    // Primitive: Stores the value directly on the stack
    private double currentPrice; 
    
    // Reference: Stores a pointer to a String object on the heap
    private String cryptoName;

    public PriceTracker(String name, double initialPrice) {
        this.cryptoName = name;
        this.currentPrice = initialPrice;
    }

    public void updatePrice(double newPrice) {
        this.currentPrice = newPrice;
        System.out.println(cryptoName + " updated to: $" + currentPrice);
    }
}