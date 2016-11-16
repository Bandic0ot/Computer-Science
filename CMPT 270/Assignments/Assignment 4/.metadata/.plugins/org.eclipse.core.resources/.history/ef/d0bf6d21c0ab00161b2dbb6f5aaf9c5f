package commands;

import containers.FlightDictionary;
import entities.Flight;


public class DisplayEmptySeatCommand extends CommandStatus {
	
	private String availableSeatString;
	
	public void displayEmptySeat(int number) {
		Flight f = FlightDictionary.dictionary().get(number);
		
		try {
			if(f == null) {
				throw new RuntimeException("There is no flight with number " + number);
			} else {
				availableSeatString = f.availableSeats();
				successful = true;
			}
		}
		catch(RuntimeException e) {
			successful = false;
			errorMessage = e.getMessage();
		}
	}
	
	public String getAvailableSeatString() {
		return availableSeatString;
	}

}
