public class LinkedList {
    Node head;

    //****** Methods ******

    public void insert(int data) {

        Node node = new Node();
        node.data = data;
        node.next = null;

        if (head == null) {
            head = node;
        } else {
            Node temp = head;
            while (temp.next != null) {
                temp = temp.next;
            }
            temp.next = node;
        }

    }

    public void insertAtFirst(int data) {

        Node node = new Node();
        node.data = data;
        node.next = null;

        node.next = head;
        head = node;
    }

    public void insertAt(int index, int data) {

        Node node = new Node();
        node.data = data;
        node.next = null;

        if (index == 1) {
            insertAtFirst(data);
        } else {
            Node temp = head;
            for (int i = 0; i < index - 2; i++) {
                temp = temp.next;
            }
            node.next = temp.next;
            temp.next = node;
        }
    }

    public void delete(int index) {

        if (index == 1) {
            head = head.next;
        } else {
            Node temp = head;
            Node temp1 = null;
            for (int i = 0; i < index - 2; i++) {
                temp = temp.next;
            }
            temp1 = temp.next;
            temp.next = temp1.next;
        }
    }

    public void print() {

        Node node = head;
        while (node.next != null) {

            System.out.print("[" + " " + node.data + " " + "]" + "   ------>   ");
            node = node.next;
        }
        System.out.print("[" + " " + node.data + " " + "]");
        System.out.print('\n');
    }

    public void display(long index) {

        int counter = 0;
        Node node = head;
        if (index == counter)
            System.out.println(node.data);
        else {
            while (index != counter) {
                node = node.next;
                counter++;
            }
            System.out.println(node.data);
        }
    }

    public int value(int index) {

        int counter = 0;
        Node node = head;
        if (index == counter)
            return (node.data);
        else {
            while (index != counter) {
                node = node.next;
                counter++;
            }
            return (node.data);
        }
    }

    public int shiftValue() {

        Node node = head;
        while (node.next != null) {
            node = node.next;
        }
        return (node.data);
    }


}

