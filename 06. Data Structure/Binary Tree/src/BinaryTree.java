public class BinaryTree {
    //class property
    private Node root;

    //methods
    public Node getRoot() {
        return root;
    }

    //************** insert **************
    public void insert(float data) {
        if (root == null) {
            root = new Node(data); //tree is empty so create root node.

        } else {
            Node current = root;
            Node parent = null; //this object is null by default(just for readability)

            while (true) {
                parent = current;

                //goto left side
                if (data < parent.getData()) {
                    current = current.getLeft();

                    if (parent.getLeft() == null) {
                        parent.setLeft(data); //insert data
                        return;

                    }
                }

                //goto right side
                else {
                    current = current.getRight();

                    if (parent.getRight() == null) {
                        parent.setRight(data); //insert data
                        return;

                    }
                }
            }
        }
    }

    //************** traverse  tree **************
    public void traverseInOrder(Node node) {
        if (node != null) {
            traverseInOrder(node.getLeft());
            System.out.print(" " + node.getData());
            traverseInOrder(node.getRight());

        }
    }

    public void traversePreOrder(Node node) {
        if (node != null) {
            System.out.print(" " + node.getData());
            traversePreOrder(node.getLeft());
            traversePreOrder(node.getRight());
        }
    }

    //************** count all the nodes of a tree **************
    public int countNode(Node node) {
        if (node == null) {
            return 0;

        } else if (node.getLeft() == null && node.getRight() == null) {
            return 1;

        }
        return 1 + countNode(node.getLeft()) + countNode(node.getRight());

    }

    //************** count all the leaf nodes of a tree **************
    private int countLeaf(Node node) {
        if (node == null) {
            return 0;

        } else if (node.getLeft() == null && node.getRight() == null) {
            return 1; //the node with no child is leaf

        }
        return countLeaf(node.getLeft()) + countLeaf(node.getRight());

    }

    //************** print count of leafs **************
    public void printLeaf(Node node) {
        int leafsCount = countLeaf(node);
        System.out.println("count of leaf nodes: " + leafsCount);

    }

    //************** print count of none leafs **************
    //all nodes - leaf nodes = none leaf nodes
    public void printNoneLeaf(Node node) {
        int noneLeafsCount = countNode(node) - countLeaf(node);
        System.out.println("count of none leaf nodes: " + noneLeafsCount);

    }

    //************** recursive delete **************
    private Node delete(Node node, float data) {
        if (node == null) {
            return null;

        }
        //yaahh... node to be delete found.
        if (data == node.getData()) {
            //case1: no child
            if (node.getLeft() == null && node.getRight() == null) {
                return null;

            }
            //case2: one child
            else if (node.getRight() == null) {
                return node.getLeft();

            } else if (node.getLeft() == null) {
                return node.getRight();

            }
            //case3: two child
            else {
                float smallestData = findSmallestData(node.getRight());
                node.setData(smallestData);
                node.setRight(delete(node.getRight(), smallestData));
                return node;

            }
        }
        if (data < node.getData()) {
            node.setLeft(delete(node.getLeft(), data));
            return node;

        }
        node.setRight(delete(node.getRight(), data));
        return node;
    }

    //find the data of the node that will replace the deleted node.
    private float findSmallestData(Node root) {
        if (root.getLeft() == null) {
            return root.getData();

        }
        return findSmallestData(root.getLeft());

    }

    //************** delete **************
    public void delete(float data) {
        root = delete(root, data);
    }

    //************** remove duplicates **************
    private void removeDuplicate(Node node) {
        if (node != null) {
            boolean test = containsNode(node.getData(), node);

            if (test) {
                delete(node.getData());

            }
            removeDuplicate(node.getLeft());
            removeDuplicate(node.getRight());

        }
    }

    public void removeDuplicate() {
        removeDuplicate(root);
    }

    private boolean containsNode(float data, Node node) {
        if (data < node.getData()) {
            return containsNodeRecursive(node.getLeft(), data);

        } else {
            return containsNodeRecursive(node.getRight(), data);

        }
    }

    private boolean containsNodeRecursive(Node current, float data) {
        if (current == null) {
            return false;

        } else if (data == current.getData()) {
            return true;

        } else if (data < current.getData()) {
            return containsNodeRecursive(current.getLeft(), data);

        } else {
            return containsNodeRecursive(current.getRight(), data);

        }
    }
    //************** end remove operation **************

    //************** search tree for given data **************
    private boolean containsNode(float data) {
        return containsNodeRecursive(root, data);
    }

    //************** find the largest data in the tree **************
    private float findBiggestData(Node node) {
        Node current = node;

        while (current.getRight() != null) {
            current = current.getRight();

        }
        return (current.getData());

    }

    //************** compare given data with largest data if data is bigger:return 1 else: -1 **************
    private int isBiggestData(Node node, float data) {
        float biggestNode = findBiggestData(node);

        if (biggestNode < data) {
            return 1;

        }else {
            return -1;

        }
    }

    //************** traverse tree in pre order and store data in array **************
    private void storePreOrder(Node node, float[] array, int index) {
        if (node != null) {
            array[index++] = node.getData();
            storePreOrder(node.getLeft(), array, index);
            storePreOrder(node.getRight(), array, index);

        }
    }

    //************** sorting array **************
    private void bubbleSort(float[] array) {
        int size = array.length;

        for (int i = 0; i < size - 1; i++) {
            boolean swapped = true;

            for (int j = 0; j < size - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    float temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;

                    swapped = false;

                }
            }
            if (swapped == true)
                break;
        }
    }

    //************** find the smallest data bigger than given data **************
    private void lowerBound(float data, Node node) {
        boolean isDuplicate = containsNode(data);

        if (node == null) {
            System.out.println("root is null"); //root is null

        } else if (isBiggestData(node, data) == 1) {
            System.out.println("there is no data equal or bigger than this one!");  //the given data is bigger than all other nodes in the tree

        } else if (isDuplicate) {
            System.out.println(data);  // the given data is already exist in the tree so print that

        } else { // operation for find lower bound starts...
            float[] storeNode;

            //goto right side of the tree
            if (data > node.getData()) {
                int countOfRightNodes = countNode(node.getRight()); // number of nodes in the right subtree
                storeNode = new float[countOfRightNodes + 1]; // array of floats to store data & right subtree
                storeNode[0] = data;
                storePreOrder(node.getRight(), storeNode, 1); // store nodes in an array
                bubbleSort(storeNode); // sort the array

                for (int i = 0; i < storeNode.length; i++) { // search for given data, the data after this is lower bound
                    if (data == storeNode[i]) {
                        System.out.println("the lower bound is: " + storeNode[i + 1]);
                        break;

                    }
                }

            } else {
                int countOfLeftNodes = countNode(node.getLeft()); // number of nodes in the left subtree
                storeNode = new float[countOfLeftNodes + 2]; // array of floats to store data, root node & left subtree
                storeNode[0] = data;
                storeNode[1] = node.getData();
                storePreOrder(node.getLeft(), storeNode, 2); // store nodes in an array
                bubbleSort(storeNode); // sort the array

                for (int i = 0; i < storeNode.length; i++) { // search for given data, the data after this is lower bound
                    if (data == storeNode[i]) {
                        System.out.println("the lower bound is: " + storeNode[i + 1]);
                        break;
                    }
                }
            }
        }
    }

    public void lowerBound(float data) {
        lowerBound(data,root);
    }
}