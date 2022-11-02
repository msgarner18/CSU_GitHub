public class Buffer {
    private int[] nums;
    private int front;//index of number to be consumed next
    private int rear;//index of number to be added next

    //initialize Buffer
    public Buffer(int size) {
        this.nums = new int[size];
        this.front = -1;
        this.rear = -1;
    }

    //returns index of number that was just added
    public int lastAdded() {
        return rear;
    }

    //returns index of number last removed
    public int lastRemoved() {
        return (front+1)%nums.length;
    }

    //returns true if buffer is full
    public boolean isFull() {
        return (rear+1)%nums.length == front;
    }

    //returns true if buffer is empty
    public boolean isEmpty() {
        return front == -1;
    }
    
    //adds a number to buffer
    public synchronized void enqueue(int n) {
        while(isFull()) {
            //if buffer is full don't allow producer to continue producing
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        if(isEmpty()) {
            front ++;
        }
        rear = (rear+1)%nums.length;
        nums[rear] = n;
        //if producer has produced, allow consumer to continue consuming
        notifyAll();
    }

    //removes number from buffer and returns value    
    public synchronized int dequeue() {
        while(isEmpty()) {
            //if consumer has no values to consume, don't allow consumer to continue consuming
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        int temp = nums[front];
        if(front == rear) {
            front = -1;
            rear = -1;
        }
        else {
            front = (front+1)%nums.length;
        }
        //if producer has finished consuming, allow producer to continue producing
        notifyAll();
        return temp;
    }
    
    //print all elements inside of buffer for debugging purposes
    public void print()
    {
        System.out.println("Buffer: ");
        for(int i = front; i <= rear; i++) {
            System.out.print(nums[i]+", ");
        }
        System.out.println();
        System.out.flush();
    }
}