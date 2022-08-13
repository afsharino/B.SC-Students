/**
 * Node class is an auxiliary class that will store float values, and keep a reference to each child and also its height.
 *
 * @author Mohammad Afshari
 */
public class Node {
    //************** Class Properties **************
    private float data;
    private Node right;
    private Node left;
    private int height;

    /**
     * Constructs and initializes a node with given data and null children with 0 height.
     *
     * @param data data is represent the key value of the node
     */
    public Node(float data) {
        this.data = data;
        this.height = 0;
        right = left = null;

    }

    //************** Methods **************

    public void setData(float data) {
        this.data = data;
    }
    public float getData() {
        return data;
    }


    public void setHeight(int height) {
        this.height = height;
    }
    public int getHeight() {
        return height;
    }


    public void setRight(float data) { this.right = new Node(data); }
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
