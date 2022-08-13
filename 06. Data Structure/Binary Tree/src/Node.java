public class Node {
    //class properties
    private float data;
    private Node right;
    private Node left;

    //constructor
    public Node(float data) {
        this.data = data;
        right = left = null;
    }

    //methods
    public void setData(float data) {
        this.data = data;
    }

    public float getData() {
        return data;
    }

    public void setRight(float data) {
        this.right = new Node(data);
    }

    public void setRight(Node node) {
        this.right = node;
    }

    public Node getRight() {
        return right;
    }

    public void setLeft(float data) {
        this.left = new Node(data);
    }

    public void setLeft(Node node) {
        this.left = node;
    }


    public Node getLeft() {
        return left;
    }
}
