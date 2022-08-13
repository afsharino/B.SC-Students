import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        BinaryTree binarytree = new BinaryTree();
        Scanner input = new Scanner(System.in);
        System.out.print("How many requests do you have? ");
        int request = input.nextInt();

        int i = 0;
        while (i < request) {
            System.out.print("what do you want to do? ");
            int statement = input.nextInt();
            switch (statement) {
                case 1:
                    System.out.print("please enter \"x\" to insert: ");
                    int x = input.nextInt();
                    binarytree.insert(x);
                    break;
                case 2:
                    System.out.println("*** traverse in order ***");
                    binarytree.traverseInOrder(binarytree.getRoot());
                    System.out.print("\n");
                    System.out.println("*** traverse pre order ***");
                    binarytree.traversePreOrder(binarytree.getRoot());
                    System.out.print("\n");
                    break;
                case 3:
                    binarytree.printLeaf(binarytree.getRoot());
                    break;
                case 4:
                    binarytree.printNoneLeaf(binarytree.getRoot());
                    break;
                case 5:
                    System.out.print("please enter \"y\" to delete: ");
                    int y = input.nextInt();
                    int nodeCountBefore1 = binarytree.countNode(binarytree.getRoot());
                    binarytree.delete(y);
                    int nodeCountAfter1 = binarytree.countNode(binarytree.getRoot());
                    if (nodeCountBefore1 == nodeCountAfter1) {
                        System.out.println("There is no such node in this tree!!!");
                    } else {

                        System.out.println("Node deleted successfully!!!");
                    }
                    break;
                case 6:
                    int nodeCountBefore = binarytree.countNode(binarytree.getRoot());
                    binarytree.removeDuplicate();
                    int nodeCountAfter = binarytree.countNode(binarytree.getRoot());
                    if (nodeCountBefore == nodeCountAfter) {
                        System.out.println("There is no Duplicate node in this tree!!!");
                    } else {

                        System.out.println("Duplicate nodes removed successfully!!!");
                    }
                    break;
                case 7:
                    System.out.print("please enter \"z\" to find lower bound: ");
                    int z = input.nextInt();
                    binarytree.lowerBound(z);
                    break;
                default:
                    System.out.println("wrong input!!!");
            }
            i++;
        }

    }
}
