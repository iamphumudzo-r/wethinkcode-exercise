public class VirtualMouse {
    // Reference Type: This is technically a pointer, but we don't use '*'
    private String status; 
    private int clickCount; // Primitive Type: Stores the actual number

    // Constructor: Initializes the 'Reference'
    public VirtualMouse() {
        this.status = "Disconnected";
        this.clickCount = 0;
    }

    public void leftClick() {
        // In Java, we don't worry about manual 'delete' or 'CloseDisplay'
        // the JVM handles the memory cleanup for us.
        this.clickCount++;
        System.out.println("Click performed. Total: " + clickCount);
    }
}