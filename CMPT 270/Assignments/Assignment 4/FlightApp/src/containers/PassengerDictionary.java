package containers;

import java.util.TreeMap;
import entities.Passenger;

/**
 * A class that follows the singleton pattern and stores the
 * passenger list for the rest of the program to access.
 * @author Matthew Mulenga
 *
 */
public class PassengerDictionary {

	// -------- Constructor --------
	/**
	 * A private constructor to ensure only one instance is created.
	 */
	private PassengerDictionary() {}

	
	
	// -------- Instance Variables --------
	/**
	 * A dictionary which stores passengers and uses their names as keys.
	 */
	private static TreeMap<String, Passenger> dictionary;
	
	
	
	// -------- Methods --------
	/**
	 * A method which is used to reference the dictionary.
	 * @precond dictionary != null
	 * @return Returns the dictionary.
	 */
	public static TreeMap<String, Passenger> dictionary() {
		if(dictionary == null) {
			dictionary = new TreeMap<String, Passenger>();
		}
		
		return dictionary;
	}
	
	
	
	// -------- Testing --------
	public static void main(String args[]) {
		System.out.println("Testing PassengerDictionary class");

		Passenger p = new Passenger("Matthew Mulenga", "555-1234");
		int testFailed = 0;

		try {
			dictionary().put("Matthew", p);
			if(dictionary.size() != 1) {
				testFailed++;
				throw new RuntimeException("Something is wrong with the dictionary.");
			}

			dictionary().remove("Matthew");
			if(dictionary.size() != 0) {
				testFailed++;
				throw new RuntimeException("Something is wrong with the dictionary.");
			}
		} catch(RuntimeException e) {
			System.out.println(e.getMessage());
		}
		
		System.out.println("Number of tests failed: " + testFailed);
	}
}
