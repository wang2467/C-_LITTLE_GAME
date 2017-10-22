public class IntList implements MyList{

    private IntList next;
    private int data;

    public IntList(IntList n, int value){
        this.data = value;
        this.next = n;

    };

    public IntList(int value){
        this.data = 0;
        this.next = null;
    }

    public int getData(){
        return this.data;
    };

    public IntList next(){
        return this.next;
    };

    public void printNode(){
        System.out.print("IntList Node, data is: " + getData());
    };

}
