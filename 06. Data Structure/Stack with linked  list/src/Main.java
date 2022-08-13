import java.util.Scanner;

class Node {
    int data;
    Node next;
}

class Stack {

    Node top;

    //****** Methods ******

    public boolean isEmpty() {
        return (top == null);
    }

    public void push(int data) {

        Node node = new Node();
        node.data = data;
        node.next = null;

        node.next = top;
        top = node;
    }
    public void pop() {

        if (isEmpty()) {
            System.out.println("Stack is Empty!");
            return;
        }
        top = top.next;
    }
    public void printList() {

        if (isEmpty()) {
            System.out.println("Stack is Empty!");
            return;
        }
        else {
            Node node = top;
            while (node.next != null) {

                System.out.print("[" + " " + node.data + " " + "]" + "   ------>   ");
                node = node.next;
            }
            System.out.print("[" + " " + node.data + " " + "]");
            System.out.print('\n');
        }
    }
    public void printTop() {

        if (isEmpty()) {
            System.out.println("Stack is Empty!");
        }
        else {

            System.out.println(top.data);
        }
    }
}

public class Main {

    public static void main(String[] args) {

        Stack stack = new Stack();

        Scanner input = new Scanner(System.in);
        //System.out.print("Please enter number requests: ");
        int n = input.nextInt();

        int counter = 0;

        while (counter != n) {
            int request = input.nextInt();

            switch (request) {

                case 1 :
                    int x = input.nextInt();
                    stack.push(x);
                    break;

                case 2 :
                    stack.pop();
                    break;
                case 3 :
                    stack.printTop();
                    break;
            }
            counter++;
        }
    }
}