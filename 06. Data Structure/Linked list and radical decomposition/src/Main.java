import java.util.*;
import java.lang.Math;

public class Main {

    public static void main(String[] args) {

        //read inputs from the user
        Scanner input = new Scanner(System.in);

        System.out.print("Please enter number of array's members & number of requests: ");
        int n = input.nextInt();
        int m = input.nextInt();

        System.out.println("Please enter array's members: ");
        int[] Array = new int[n];
        for (int i = 0; i < n; i++) {
            Array[i] = input.nextInt();
        }

        //lets segment
        int section = 0;//Number of members of each section in sqrt(n) & Number of members of each section in sqrt(n)+1
        int section1 = 0;//Number of remain members in sqrt(n)+1
        int partition = 0;// Number of segments
        LinkedList[] list; //array of linked lists
        double sqrt = Math.sqrt(n);

        //square root ex: 9, 16, 49, ...
        if ((int) sqrt == sqrt) {
            partition = section = (int) sqrt;

            //Creat array of objects
            list = new LinkedList[partition];
            for (int i = 0; i < partition; i++) {
                list[i] = new LinkedList();
            }

            //convert array to LinkedList
            int j = 0; // count array index
            for (int i = 0; i < partition; i++) {
                int counter = 0; // count Number of members of each section
                while (counter != section) {
                    if (j < n) {
                        list[i].insert(Array[j]);
                        counter++;
                        j++;
                    }
                }
            }

            //Print the whole list
            //for (int i = 0; i < partition; i++) {
            //    list[i].print();
            //}

        } else {

            section = (int) sqrt + 1;
            partition = n / section;

            section1 = n - (partition * section);
            if (section1 != 0) {
                partition += 1; //suppose u entered 20, so you don't need any extra segment. (case1)
                                //suppose u entered 11, so you need just 1 extra segment. (case 2)
            }

            //Creat array of objects
            list = new LinkedList[partition];
            for (int i = 0; i < partition; i++) {
                list[i] = new LinkedList();
            }

            //convert array to LinkedList
            int j = 0; // count array index
            int counter = 0; // count Number of segment which are full
            int counter1; // count Number of members of each section with square root
            for (int i = 0; i < partition; i++) {
                if (section1 != 0) { // case 2 based on what explained above.

                    if (counter < partition - 1) {
                        counter1 = 0;
                        while (counter1 != section) {

                            list[i].insert(Array[j]);
                            counter1++;
                            j++;
                        }
                        counter++;

                    } else {

                        for (int k = j; k < n; k++) {
                            list[i].insert(Array[k]);
                        }

                    }
                } else { // case 1 based on what explained above.
                    if (counter < partition) {
                        counter1 = 0;
                        while (counter1 != section) {

                            list[i].insert(Array[j]);
                            counter1++;
                            j++;
                        }
                        counter++;
                    }
                }
            }
            //Print the whole list
            //for (int i = 0; i < partition; i++) {
            //    list[i].print();
            //}
        }

        //start asking requests.
        System.out.println("Please enter your requests: ");
        int counter = 0;
        while (counter != m) {
            int userRequest = input.nextInt();
            int s, e, index;

            switch (userRequest) {
                case 1:
                    s = input.nextInt();
                    e = input.nextInt();

                    int sPosition = position(s, section);
                    int sIndex = index(s, section);

                    int ePosition = position(e, section);
                    int eIndex = index(e, section);
                    int eValue = list[ePosition].value(eIndex - 1);

                    list[sPosition].insertAt(sIndex, eValue);
                    list[ePosition].delete(eIndex);

                    if (sPosition != ePosition) {
                        int countShift = ePosition - sPosition;
                        int traverse = sPosition;
                        for (int i = 0; i < countShift; i++) {
                            int shiftValue = list[traverse].shiftValue();
                            list[traverse + 1].insertAtFirst(shiftValue);
                            list[traverse].delete(section + 1);
                            traverse++;
                        }
                    }

                    //Print the whole list
                    //for (int i = 0; i < partition; i++) {
                    //    list[i].print();
                    //}
                    break;
                case 2:
                    index = input.nextInt();
                    if (index <= section) {
                        list[0].display(index - 1);
                    }
                    if (index > section && index % section != 0) {
                        int devide = index / section;
                        index = (int) (index - devide * section);
                        list[devide].display(index - 1);

                    }
                    if (index > section && index % section == 0) {
                        int devide = index / section;
                        index = section;
                        list[devide - 1].display(index - 1);

                    }

                    break;
                default:
                    System.out.println("wrong input try again!");
                    counter--;
                    break;
            }
            counter++;

        }

    }

    // this method return the position of each node (specifies in which range it is located)
    public static int position(int index, int section) {
        int devide = 0;
        if (index <= section) {
            return (0);
        }

        else if (index > section && index % section != 0) {
            devide = index / section;
            return (devide);

        }

        else if (index > section && index % section == 0) {
            devide = index / section;
            return (devide - 1);

        } else
            return -1;

    }

    // this method return the index of each node (specifies index in range where it is located)
    public static int index(int index, int section) {
        int devide = 0;
        if (index <= section) {
            return (index);

        }

        else if (index > section && index % section != 0) {
            devide = index / section;
            index = index - devide * section;
            return (index);

        }

        else if (index > section && index % section == 0) {
            index = section;
            return (index);

        } else
            return -1;

    }

}

