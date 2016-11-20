package commands;

import containers.PassengerDictionary;
import entities.Passenger;

/**
 * A class which handles the adding of a passenger to the 
 * passenger dictionary.
 * @author Matthew Mulenga
 *
 */
public class AddPassengerCommand extends CommandStatus {
	//-------- Methods --------
	/**
	 * A method which adds a passenger to the list of passengers.
	 * @precond name != null
	 * @param name The name of the passenger.
	 * @param telNumber The telephone number of the passenger.
	 */
	public void addPassToDict(String name, String telNumber) {
		
		if(name == null) {
			successful = false;
			errorMessage = "Error, the name was null.";
			return;
		} 
		else if(PassengerDictionary.dictionary().containsKey(name)) {
			successful = false;
			errorMessage = "Person not added as there already " 
					+ "is a person by the name " + name;

		}
		else {
			try {
				Passenger p = new Passenger(name, telNumber);
				
				PassengerDictionary.dictionary().put(name, p);
				
				successful = true;
			}
			catch(RuntimeException e) {
				successful = false;
				errorMessage = e.getMessage();
			}
		}
	}
	
	
	//-------- Testing --------
	public static void main(String[] args) {
		System.out.println("Testing AddPassengerCommand class");
		
		AddPassengerCommand command = new AddPassengerCommand();
		int testFailed = 0;
		
		try {
			command.addPassToDict("Matthew Mulenga", "555-1234");
			if(PassengerDictionary.dictionary().size() != 1) {
				testFailed++;
				throw new RuntimeException("Something is wrong with the addPassToDict method.");
			} 

			PassengerDictionary.dictionary().remove("Matthew Mulenga");
			if(PassengerDictionary.dictionary().size() != 0) {
				testFailed++;
				throw new RuntimeException("Something is wrong with the addPassToDict method.");
			}
		} catch(RuntimeException e) {
			System.out.println(e.getMessage());
		}
		
		System.out.println("Number of tests failed: " + testFailed);
	}
}

