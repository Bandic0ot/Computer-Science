/**
 * Created by Matthew Mulenga on 2017-01-17.
 */

import lib280.base.Cursor280;
import lib280.exception.NoCurrentItem280Exception;
import lib280.list.LinkedIterator280;
import lib280.list.LinkedList280;
import sun.awt.image.ImageWatched;

import java.util.Random;

public class A1Q1 {

    public static Sack [] generatePlunder ( int howMany ) {
        Random generator = new Random ();
        Sack grain [] = new Sack [ howMany ];
        for (int i = 0; i < howMany ; i ++) {
            grain[i] = new Sack(
                    Grain.values()[generator.nextInt(Grain.values().length)] ,
                    generator.nextDouble() * 100);
        }
        return grain ;
    }

    @SuppressWarnings("unchecked")
    public static void main(String args[]) {

        int capacity = Grain.values().length;

        Sack[] sackArray = generatePlunder(8);

        // Create an array that holds a linked list for each type of Sack item.
        LinkedList280<Sack>[] listArray = new LinkedList280[capacity];

        // Initialize the lists within the newly created array.
        for(int i = 0; i < capacity; i++) {
            listArray[i] = new LinkedList280<Sack>();
        }


        // Loop through each item in the randomly generated sack.
        for(int i = 0; i < sackArray.length; i++) {
            // Loop through each sack item list
            for(int j = 0; j < capacity; j++) {
                // If the index of the list matches the ordinal of the grain type
                // add the grain to the list
                if(j == sackArray[i].getType().ordinal()) {
                    listArray[j].insert(sackArray[i]);
                }
            }
        }



    }

}
