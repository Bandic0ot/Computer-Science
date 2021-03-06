package interfaces;

import java.util.InputMismatchException;
import java.util.Scanner;

/**
 * A class which handles all input and output for the application.
 * @author Matthew Mulenga
 *
 */
public class UserInterface {

	
	//-------- Instance Variables --------
	/**
	 * The scanner used to read input from the user.
	 */
	private Scanner consoleIn = new Scanner(System.in);
	
	
	
	//-------- Methods ---------
	/**
	 * Output the prompt to list the possible operations, 
	 * and read selection picked by the user.
	 * @return  the int corresponding to the operation selected
	 */
	public int readOpId() {
		int id;
		System.out.print("Please select an operation to do"
				+ "\n0: quit"
				+ "\n1: add a new passenger"
				+ "\n2: add a new flight"
				+ "\n3: display the empty seats of a flight"
				+ "\n4: book a passenger on a flight"
				+ "\n5: book a first-class passenger on a flight"
				+ "\n6: assign a passenger a seat"
				+ "\n7: display all the passengers"
				+ "\n8: display all the flights"
				+ "\nEnter the number of your selection: ");
		id = readInt();
		return id;
	}
	
	/**
	 * Read in an int value.  If a non-int value is entered, then issue another request.  
	 * @return the int value read in
	 */
	public int readInt()
	{
		int result = 0;    // must be initialized
		//Scanner consoleIn = new Scanner(System.in);
		boolean successful ;
		do
		{
			successful = true;
			try
			{
				result = consoleIn.nextInt();
			} catch (InputMismatchException e)
			{
				successful = false;
				String faultyInput = consoleIn.nextLine();
				System.out.print("You entered \"" + faultyInput + "\" which is not an int." 
	                               + "\nPlease try again: ");
			}
		}
		while (!successful);
		consoleIn.nextLine();  // discard the remainder of the line		
		return result;
	}
	
	/**
	 * Reads the passenger name in from the console.
	 * @return The passenger's name.
	 */
	public String getPassName() {
		System.out.print("Enter the name of the passenger: ");
		
		return consoleIn.nextLine();
	}
	
	/**
	 * Reads the passenger telephone number in from the console.
	 * @return The passenger's telephone number.
	 */
	public String getTelNumber() {
		System.out.print("Enter the telephone number of the passenger: ");
		
		return consoleIn.nextLine();
	}
	
	/**
	 * Reads the number of the flight in from the console.
	 * @return The number of the flight.
	 */
	public int getFlightNumber() {
		System.out.print("Enter the number of the flight: ");
		int number = readInt();
		
		return number;
	}
	
	/**
	 * Reads the width of the flight in from the console.
	 * @return The width of the flight.
	 */
	public int getFlightWidth() {
		System.out.print("Enter the width of the flight: ");
		int width = readInt();
		
		return width;
	}
	
	/**
	 * Reads the capacity of the flight in from the console.
	 * @return The capacity of the flight.
	 */
	public int getFLightCapacity() {
		System.out.print("Enter the capacity of the flight: ");
		int capacity = readInt();
		
		return capacity;
	}
	
	/**
	 * Reads the meal plan of the passenger in from the console.
	 * @return The meal plan of the passenger.
	 */
	public String getMealPlan() {
		System.out.print("Enter the meal plan of the passenger: ");
		
		return consoleIn.nextLine();
	}
	
	/**
	 * Reads the seat of the passenger in from the console.
	 * @return The seat of the passenger.
	 */
	public String getPassSeat() {
		System.out.print("Enter the seat for the passenger: ");
		
		return consoleIn.nextLine();
	}
	
	/**
	 * Takes a string as an argument and displays it on the console.
	 * @param message A string containing a message.
	 */
	public void sendMessage(String message) {
		System.out.println(message);
	}
}
