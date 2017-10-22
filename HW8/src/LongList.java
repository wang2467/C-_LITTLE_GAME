public class LongList implements MyList{

    private LongList next;
    private long data;

    public LongList(LongList n, long value){
        data = value;
        this.next = n;

    };

    public LongList(int value){
        this.data = 0;
        this.next = null;
    }

    public long getData(){
        return this.data;
    };

    public LongList next(){
        return this.next;
    };

    public void printNode(){
        System.out.print("LongList Node, data is: " + getData());
    };

}
