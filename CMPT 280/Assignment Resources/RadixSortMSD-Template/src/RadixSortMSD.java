import lib280.list.LinkedList280;
import sun.awt.image.ImageWatched;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.LinkedList;
import java.util.Scanner;

public class RadixSortMSD<I> {

	// *************************************************************
	// TODO Write YOUR RADIX SORT HERE
	// *************************************************************

	/**
	 *
	 * @param keys
	 * @param R
	 */
	public void MSDRadixSort(I[] keys, int R) {
		sortByDigit(keys, R, 0);
	}

	/**
	 *
	 * @param keys
	 * @param R
	 * @param i
	 */
	public void sortByDigit(I[] keys, int R, int i) {
		LinkedList280<I>[] list = new LinkedList280[R];

		for(int k = 0; k < R - 1; k++) {
			list[k] = new LinkedList280<I>();
		}

		for(int k = 0; k < keys.length; k++) {
			if(keys[k].charAt(i) == k) {
				list[k].insert(keys[k]);
			}
		}

		for(int k = 0; k < R - 1; k++) {
			if(k < keys[k].length()) {
				MSDRadixSort(list[k], i + 1);
			}
		}
	}
	

	public static void main(String args[]) {
		
		// *************************************************************
		// Change the input file by changing the line below.
		// *************************************************************
		String inputFile = "words-basictest.txt";
		
		// Initialize a scanner to read the input file.
		Scanner S = null;
		try {
			S = new Scanner(new File(inputFile));  
		} catch (FileNotFoundException e) {
			System.out.println("Error: " + inputFile + "was not found.");
			return;
		}
		
		// Read the first line of the file and convert it to an integer to see how many
		// words are in the file.
		int numWords = Integer.valueOf(S.nextLine());
		
		// Initialize an array large enough to store numWords words.
		String items[] = new String[numWords];
		
		// Read each word from the input file and store it in the next free element of 
		// the items array.
		int j=0;
		while(S.hasNextLine()) {
			items[j++] = S.nextLine().toUpperCase();
		}
		S.close();
		System.out.println("Done reading " + numWords + " words.");
		

		// Test and time your radix sort.
		long startTime = System.nanoTime();
		
		// *************************************************************
		// TODO CALL YOUR RADIX SORT TO SORT THE 'items' ARRAY HERE
		// *************************************************************

		long stopTime = System.nanoTime();
		
		// Uncomment this section if you want the sorted list to be printed to the console.
		// (Good idea for testing with words-basictest.txt; leave it commented out though
		// for testing files with more than 50 words).

		for(int i=0; i < items.length; i++) {
			System.out.println(items[i]);
		}

		
		// Print out how long the sort took in milliseconds.
		System.out.println("Sorted " + items.length + " strings in " + (stopTime-startTime)/1000000.0 + "ms");
	
	}
	
}
