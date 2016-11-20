package interfaces;

import java.util.InputMismatchException;
import java.util.Scanner;

public class UserInterface {

	
	//-------- Instance Variables --------
	
	private Scanner consoleIn;
	
	
	
	//-------- Methods ---------
	/**
	 * Initialize the system by creating the input scanner.
	 */
	public UserInterface(Scanner in) {
		consoleIn = in;
	}

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

}
