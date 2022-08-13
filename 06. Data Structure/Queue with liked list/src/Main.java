import java.util.Scanner;

class Node {
    int data;
    Node next;
}

class Queue {
    Node front;
    Node rear;

    //****** Methods ******

    public void enqueue(int data) {
        Node node = new Node();
        node.data = data;
        node.next = null;

        if (rear == null && front == null) {
            rear = front = node;
        } else {
            rear.next = node;
            rear = node;
        }
    }

    public void dequeue() {
        Node garbage = front;

        if (front == null) {
            System.out.println("the queue is empty!");
        } else if (rear == front) {
            rear = front = null;
        } else {
            front = front.next;
        }
    }

    public void frontPrint() {
        if (front == null) {
            System.out.println("the queue is empty!");
        } else {
            System.out.println(front.data);
        }

    }

    public void rearPrint() {
        if (rear == null) {
            System.out.println("the queue is empty!");
        } else {
            System.out.println(rear.data);
        }
    }
}

public class Main {

    public static void main(String[] args) {

        Queue queue = new Queue();

        Scanner input = new Scanner(System.in);
        //System.out.print("Please enter number requests: ");
        int n = input.nextInt();

        int counter = 0;

        while (counter != n) {
            int request = input.nextInt();

            switch (request) {

                case 1:
                    int x = input.nextInt();
                    queue.enqueue(x);
                    break;

                case 2:
                    queue.dequeue();
                    break;
                case 3:
                    queue.frontPrint();
                    break;
                case 4:
                    queue.rearPrint();
            }
            counter++;
        }
    }
}