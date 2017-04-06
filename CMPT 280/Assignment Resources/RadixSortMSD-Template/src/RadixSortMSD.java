import lib280.list.ArrayedList280;
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
	public static void MSDRadixSort(String[] keys, int R) {
		sortByDigit(keys, R, 0);
	}

	/**
	 *
	 * @param keys
	 * @param R
	 * @param i
	 */
	public static void sortByDigit(String[] keys, int R, int i) {
		ArrayedList280<String>[] list = new ArrayedList280[R];

		for(int k = 0; k < R; k++) {
			list[k] = new ArrayedList280<>(R);
		}

		for(int j = 0; j < keys.length; j++) {

			if(keys[j].length() > i) {
				// Check to see if the character at the index matches any
				// letters using their ASCII decimal values.
				switch (keys[j].charAt(i)) {
					case 'A':
						list[0].insert(keys[j]);
						break;

					case 'B':
						list[1].insert(keys[j]);
						break;

					case 'C':
						list[2].insert(keys[j]);
						break;

					case 'D':
						list[3].insert(keys[j]);
						break;

					case 'E':
						list[4].insert(keys[j]);
						break;

					case 'F':
						list[5].insert(keys[j]);
						break;

					case 'G':
						list[6].insert(keys[j]);
						break;

					case 'H':
						list[7].insert(keys[j]);
						break;

					case 'I':
						list[8].insert(keys[j]);
						break;

					case 'J':
						list[9].insert(keys[j]);
						break;

					case 'K':
						list[10].insert(keys[j]);
						break;

					case 'L':
						list[11].insert(keys[j]);
						break;

					case 'M':
						list[12].insert(keys[j]);
						break;

					case 'N':
						list[13].insert(keys[j]);
						break;

					case 'O':
						list[14].insert(keys[j]);
						break;

					case 'P':
						list[15].insert(keys[j]);
						break;

					case 'Q':
						list[16].insert(keys[j]);
						break;

					case 'R':
						list[17].insert(keys[j]);
						break;

					case 'S':
						list[18].insert(keys[j]);
						break;

					case 'T':
						list[19].insert(keys[j]);
						break;

					case 'U':
						list[20].insert(keys[j]);
						break;

					case 'V':
						list[21].insert(keys[j]);
						break;

					case 'W':
						list[22].insert(keys[j]);
						break;

					case 'X':
						list[23].insert(keys[j]);
						break;

					case 'Y':
						list[24].insert(keys[j]);
						break;

					case 'Z':
						list[25].insert(keys[j]);
						break;
				}
			}
		}

		// Check to see if the string has more characters compared to i
		// if it does we need to sort all the remaining characters
		// recursively.
		for(int k = 0; k < keys.length; k++) {
			if(i < keys[k].length() - 1) {

				String[] tempArray = new String[list[k].count()];

				list[k].goFirst();
				for(int j = 0; j < tempArray.length; j++) {
					tempArray[j] = list[k].item();
					list[k].goForth();
				}

				sortByDigit(tempArray, R, i + 1);
			}
		}

//		for(int k = 0; k < keys.length; k++) {
//			keys[k] = null;
//		}


	}

	// The list passed in corresponds to a single character, but filled with multiple words
//	public void sortByDigitHelper(LinkedList280<String> keys, int i) {
//		for(int k = 0; k < 26; k++) {
//
//		}
//
//	}
	

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

		MSDRadixSort(items, 26);

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
