/**
 * this class is represent a binary search tree.<br>
 * tree is also accept the duplicate values.<br>
 * the left subtree of a node contains nodes with keys lesser than  node.<br>
 * the right subtree of a node contains nodes with kys greater than or equal to node.<br>
 */
public class BinaryTree {
    //************** Class Property **************
    /**
     * this is root of the tree
     */
    private Node root;

    //************** Methods **************

    /**
     * a getter to return the root node.
     *
     * @return the root node of tree
     */
    public Node getRoot() { return root; }

    //************** insert **************
    /**
     * this method do the insertion operation for the key which is passed by the user.<br>
     * search for leaf node and insert the node left or right of that based on key value.<br>
     *
     * @param data the key value which is entered by the user.
     */
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
    /**
     * Traverses a tree in an in-order manner.<br>
     * visit all nodes and print their values.<br>
     *
     * @param node  this is starting node which is always root(we always pass root as a parameter of this method.)
     */
    public void traverseInOrder(Node node) {
        if (node != null) {
            traverseInOrder(node.getLeft());
            System.out.print(" " + node.getData());
            traverseInOrder(node.getRight());

        }
    }

    /**
     * Traverses a tree in a pre-order manner.<br>
     * visit all nodes and print their values.<br>
     *
     * @param node this is starting node which is always root(we always pass root as a parameter of this method)
     */
    public void traversePreOrder(Node node) {
        if (node != null) {
            System.out.print(" " + node.getData());
            traversePreOrder(node.getLeft());
            traversePreOrder(node.getRight());
        }
    }

    //************** count all the nodes of a tree **************
    /**
     * a method to traverse the tree in post order and count all nodes.<br>
     *
     * @param node this is starting node which is always root(we always pass root as a parameter of this method)
     * @return count of all nodes of the tree
     */
    public int countNode(Node node) {
        if (node == null) {
            return 0;

        } else if (node.getLeft() == null && node.getRight() == null) {
            return 1; // the node with no child is leaf

        }
        // recursive call to left child and right child and
        // add the result with 1 ( 1 for counting the root)
        return 1 + countNode(node.getLeft()) + countNode(node.getRight());

    }

    //************** count all the leaf nodes of a tree **************
    /**
     * a method to traverse the tree and count all leaf nodes.<br>
     *
     * @param node this is starting node which is always root(we always pass root as a parameter of this method)
     * @return count of all leaf nodes of the tree
     */
    private int countLeaf(Node node) {
        if (node == null) {
            return 0;

        } else if (node.getLeft() == null && node.getRight() == null) {
            return 1; //the node with no child is leaf

        }
        return countLeaf(node.getLeft()) + countLeaf(node.getRight());

    }

    //************** print count of leafs **************
    /**
     * call the {@link #countLeaf(Node)} and print return value of the method in output.
     *
     * @param node pass root node as parameter.
     */

    public void printLeaf(Node node) {
        int leafsCount = countLeaf(node);
        System.out.println("count of leaf nodes: " + leafsCount);

    }

    //************** print count of none leafs **************
    //all nodes - leaf nodes = none leaf nodes
    /**
     * this method prints the count of none leaf nodes in output.<br>
     *     none leaf nodes = {@link #countNode(Node)} - {@link #countLeaf(Node)}
     *
     * @param node pass root node as parameter.
     */
    public void printNoneLeaf(Node node) {
        int noneLeafsCount = countNode(node) - countLeaf(node);
        System.out.println("count of none leaf nodes: " + noneLeafsCount);

    }

    //************** delete **************

    /**
     * this is our interface which user will call in Main and in its body {@link #delete(Node, float)}
     * will be call to start deletion for asked data from root node.
     *
     * @param data user asked data.
     */
    public void delete(float data) {
        root = delete(root, data);
    }

    /**
     * method to recursively find and delete the asked node from the tree.<br>
     * there are three possible cases to consider deleting a node from the BST once we found the node to delete: <br>
     *     case 1: deleting a node with no children : remove the node from the tree. <br>
     *     case 2: deleting a node with one children : remove the node and replace it with its child. <br>
     *     case 3: deleting a node with two children : find the node that will replace the deleted node by call the <br>
     *     -{@link #findSmallestData(Node)} we search for the successor of the deleted node at it's right subtree. <br>
     *     Then we assign the smallest value to target node, and after that, we'll delete duplicate from the right sub-tree. <br>
     *     (we can also use the largest value of the left subtree for implementation.)
     *
     * @param node pass root node as parameter.
     * @param data user entered data to be delete.
     * @return a node based on each case.
     */
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
    /**
     * this method will find the value of smallest node in right subtree of the node which should be delete.
     *
     * @param node right child of the node which is going to be delete
     * @return value of the smallest node in the right subtree of the target node.
     */
    private float findSmallestData(Node node) {
        //check the left child of the right child of the target node
        //if its null so the right child of target node is the smallest.
        if (node.getLeft() == null) {
            return node.getData();

        }
        //if not continue to the left side of the right child of the target node until reach the smallest one
        return findSmallestData(node.getLeft());

    }

    //************** remove duplicates **************
    /**
     * this is our interface which user will call in Main and in its body {@link #removeDuplicate(Node)}
     * will be call for removing duplicates.
     */
    public void removeDuplicate() { removeDuplicate(root); }

    /**
     * this method removes duplicate values.<br>
     * traverse the tree in pre-order manner and call {@link #containsNode(float, Node)} <br>
     * If any duplicate node is found then pass the value of duplicate node to {@link #delete(float)} for deletion operation.
     *
     * @param node pass root node as parameter.
     */
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

    /**
     * this method is use specifically in {@link #removeDuplicate(Node)} and its similar to {@link #containsNode(float)} <br>
     * the difference is {@link #containsNode(float)} starts from the root node but this method start from left or right child <br>
     * -of the passed node because of not compare each node with itself.
     *
     * @param data value of all the nodes in the tree based on traversal.
     * @param node reference of all the nodes in the tree based on traversal.
     * @return if the tree contains the data return true else true false.
     */
    private boolean containsNode(float data, Node node) {
        // goto left side of the tree
        if (data < node.getData()) {
            return containsNodeRecursive(node.getLeft(), data);
        // goto right side of the tree
        } else {
            return containsNodeRecursive(node.getRight(), data);

        }
    }

    /**
     * search for the passed parameter by compare its value in the current node <br>
     * and go left or right based on which control structure will be execute.
     *
     * @param current tree's nodes.
     * @param data key value of the each node.
     * @return if find a data equal to passed parameter return true else false.
     */
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
    /**
     * search method to check if the given data is available in the tree or not.
     *
     * @param data the key value which is entered by the user.
     * @return if the tree contains the data return true else true false.
     */
    private boolean containsNode(float data) {
        return containsNodeRecursive(root, data);
    }

    //************** find the largest data in the tree **************
    /**
     * method to find the largest element of the BST.<br>
     * traversing the right child until we reach the rightmost node in the tree.
     *
     * @param node pass root node as parameter.
     * @return the largest data in the BST.
     */
    private float findBiggestData(Node node) {
        Node current = node;

        while (current.getRight() != null) {
            current = current.getRight();

        }
        return (current.getData());

    }

    //************** compare given data with largest data if data is bigger:return 1 else: -1 **************
    /**
     * this method check which node is the biggest node.<br>
     * the data returned by {@link #findBiggestData(Node)} <br>
     * or the data which is passed to method.
     *
     * @param node pass root node as parameter.
     * @param data the key value which is entered by the user.
     * @return  1 if user passed data be greater than largest node of tree else return -1.
     */
    private int isBiggestData(Node node, float data) {
        float biggestNode = findBiggestData(node);

        if (biggestNode < data) {
            return 1;

        } else {
            return -1;

        }
    }

    //************** traverse tree in pre order and store data in array **************
    /**
     * method to traverse the tree in pre-order manner and store the value of each node in an array. <br>
     *
     * @param node left or right child of  the root  node based on data which is passing to {@link #lowerBound(float, Node)}
     * @param array array of floats to store the value of nodes.
     * @param index index of array based on which control structure will be executed in {@link #lowerBound(float, Node)}
     */
    private void storePreOrder(Node node, float[] array, int index) {
        if (node != null) {
            array[index++] = node.getData();
            storePreOrder(node.getLeft(), array, index);
            storePreOrder(node.getRight(), array, index);

        }
    }

    //************** sorting array **************
    /**
     * sorting method which use bubble sort for sorting the array.
     *
     * @param array array of floats which contains the keys of the tree's nodes.
     */
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

    //************** find the smallest data bigger than or equal to given data **************

    /**
     * this is our interface which user will call in Main and in its body {@link #lowerBound(float, Node)}
     * will be call for finding the smallest data bigger than or equal to given data .
     * @param data user asked data.
     */
    public void lowerBound(float data) {
        lowerBound(data, root);
    }

    /**
     * the method will find the smallest data bigger than or equal to given data. <br>
     * the algorithm is as follows: <br>
     *     1. if the node be null print proper message in output. <br>
     *
     *     2. call {@link #isBiggestData(Node, float)} to check if there is any data equal or bigger than this one. <br>
     *      *     if no print proper message in output. <br>
     *
     *     3. call {@link #containsNode(float)} to check if there is any data <br>
     *     -in the tree which is equal to the data which is passed by the user.<br>
     *     if yes print that.<br>
     *
     *     4. the main algorithm is as follows: <br>
     *         1. declare an array of float and new that based on which control structure will be execute. <br>
     *         2. call the {@link #storePreOrder(Node, float[], int)} and store the key value of each node while traversing a subtree. <br>
     *         3. using {@link #bubbleSort(float[])} to sort array. <br>
     *         4. finally the element after the user passed data is our answer.
     *
     * @param data user entered data to be compare and find the smallest data bigger than or equal to it.
     * @param node pass root node as parameter.
     */
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

    //************** AVL TREE **************

    /**
     * this method use to set height for each node in our BST before start balancing.
     *
     * @param node  pass root node as parameter.
     */
    private void setHeight(Node node) {
        if (node == null) {
            return;
        }
        setHeight(node.getLeft());
        setHeight(node.getRight());
        int height = 1 + Math.max(height(node.getLeft()), height(node.getRight())); //
        node.setHeight(height);

    }

    /**
     * update the height of nodes in process of rotation and balancing. <br>
     * The height of a node in a binary tree is the largest number of edges in a path from a leaf node to a target node. <br>
     * if the target node doesn’t have any other nodes connected to it, the height of that node would be 0. <br>
     *
     * @param node each node in in process of rotation and balancing.
     */
    private void updateHeight(Node node) {
        if (node == null) {
            return;
        }
        //1 for counting the root
        int height = 1 + Math.max(height(node.getLeft()), height(node.getRight()));
        node.setHeight(height);

    }

    /**
     * method to return the height of the node
     *
     * @param node any node of the tree
     * @return height of a node.
     */
    private int height(Node node) {

        if (node == null) {
            return -1;
        } else {
            return node.getHeight();
        }

    }

    /**
     * method to calculate the balance factor with decrease the height of the left child from the height of the right child.
     * @param node any node of the tree
     * @return an integer which is the balance factor of the node.
     */
    public int getBalanceFactor(Node node) {
        if (node == null) {
            return 0;
        } else {
            return height(node.getLeft()) - height(node.getRight()); // calculate the balance factor of the node
        }
    }

    /**
     * the main method to re-balance the tree and covert BST to AVL tree. <br>
     *  recursively goto end of the tree and balance the tree. <br>
     * algorithm is as follows: <br>
     *     1.left-heavy: 1.right rotation 2. left-right rotation <br>
     *         if height of the left child of the z node's left child <br>
     *         be greater than or equal to height of the right child of <br>
     *         -the z node's left child so we can re balance the tree just <br>
     *         -by a  simple right rotation. <br>
     *         if not we need combination of two rotation : <br>
     *         first : rotate left second : rotate right (left-right rotation) <br>
     *         to maintain the bst structure. <br> <br>

     *     2.right-heavy: 1.left rotation 2. right-left rotation <br>
     *         if height of the right child of the z node's right child <br>
     *         be greater than or equal to height of the right child of <br>
     *         -the z node's left child so we can re balance the tree just <br>
     *         -by a  simple left rotation. <br>
     *         if not we need combination of two rotation : <br>
     *         first : rotate right second : rotate left (right-left rotation) <br>
     *         to maintain the bst structure. <br> <br>
     *
     * @param z pass root node as parameter.
     * @return its based on which control structure is execute.
     */

    private Node balance(Node z) {
        if (z == null) {
            return null;
        }

        z.setLeft(balance(z.getLeft()));
        z.setRight(balance(z.getRight()));

        updateHeight(z);
        int balance = getBalanceFactor(z);
        if (balance > 1) {  // left heavy : if the balance factor be + so left side is heavier than right side.

            if (height(z.getLeft().getLeft()) >= height(z.getLeft().getRight())) {
                z = rotateRight(z);
            } else {
                z.setLeft(rotateLeft(z.getLeft()));
                z = rotateRight(z);
            }
        } else if (balance < -1) {  // right heavy : if the balance factor be - so right side is heavier than left side.
            if (height(z.getRight().getRight()) >= height(z.getRight().getLeft())) {
                z = rotateLeft(z);
            } else {
                z.setRight(rotateRight(z.getRight()));
                z = rotateLeft(z);
            }
        }

        return z;
    }

    /**
     * rotate to the right with respect to maintaining the bst structure <br>
     * and update the height of the nodes after rotation
     *
     * @param y node to be rotate
     * @return left child of y which will be the parent node after rotation.
     */
    private Node rotateRight(Node y) {
        Node x = y.getLeft();
        Node z = x.getRight();
        x.setRight(y);
        y.setLeft(z);
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    /**
     * rotate to the left with respect to maintaining the bst structure <br>
     * and update the height of the nodes after rotation
     *
     * @param y node to be rotate
     * @return right child of y which will be the parent node after rotation.
     */
    private Node rotateLeft(Node y) {
        Node x = y.getRight();
        Node z = x.getLeft();
        x.setLeft(y);
        y.setRight(z);
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    /**
     * everything start from here  first we set a height for each nod by calling <br>
     * {@link #setHeight(Node)} and the start convert BST to AVL.
     */

    public void bstToAVL() {
        setHeight(root);

        root = balance(root);

    }

    /**
     * traverse the tree in a pre-order manner and if an unbalanced node found <br>
     * then call {@link #bstToAVL()} to re balance again. <br>
     * do this until the balance factor of each node be -1,0 or 1.
     *
     * @param node pass root node as parameter.
     */
    public void isBalanced(Node node) {
        if (node != null) {
            int balanceFactor = getBalanceFactor(node);

            if (balanceFactor != -1 || balanceFactor != 0 || balanceFactor != 1) {
                bstToAVL();
            }
            isBalanced(node.getLeft());
            isBalanced(node.getRight());

        }
    }

    /**
     * traverse the tree in a pre order manner and print the balance factor of each node in output.
     *
     * @param node pass root node as parameter.
     */
    public void printBalanceFactor(Node node) {
        setHeight(root);
        if (node != null) {
            System.out.println(" balance of node " + node.getData() + "is: " + getBalanceFactor(node) + "  ");
            printBalanceFactor(node.getLeft());
            printBalanceFactor(node.getRight());
        }
    }

}

