package commands;

import containers.FlightDictionary;
import containers.PassengerDictionary;

import entities.Flight;
import entities.Passenger;

/**
 * A class which handles the booking of a passenger
 * on a flight.
 * @author Matthew Mulenga
 *
 */
public class BookPassengerCommand extends CommandStatus {
	//-------- Methods --------
	/**
	 * Books the given passenger into the given flight.
	 * @precond p != null
	 * @precond f != null
	 * @param name The name of the passenger.
	 * @param number The flight number.
	 */
	public void addPassToFlight(String name, int number) {
		Passenger p = PassengerDictionary.dictionary().get(name);
		Flight f = FlightDictionary.dictionary().get(number);

		try {
			if(p == null) {
				throw new RuntimeException("There is no passenger with name " + name);
			} else if(f == null) {
				throw new RuntimeException("There is no flight with number " + number);
			} else {
				f.makeBooking(p);
				successful = true;
			}
		}
		catch(RuntimeException e) {
			successful = false;
			errorMessage = e.getMessage();
		}
	}
	
	

	//-------- Testing --------
	public static void main(String[] args) {
		System.out.println("Testing BookPassengerCommand class");
		int testFailed = 0;
		
		Flight f = new Flight(320, 3, 30);
		Passenger p = new Passenger("Matthew Mulenga", "555-1234");
		BookPassengerCommand command = new BookPassengerCommand();
		
		PassengerDictionary.dictionary().put("Matthew Mulenga", p);
		FlightDictionary.dictionary().put(320, f);
		
		try {
			command.addPassToFlight("Matthew Mulenga", 320);
			if(!p.hasBookingOn(f)) {
				testFailed++;
				throw new RuntimeException("Something is wrong with the addPassToFlight method.");
			}

		} catch(RuntimeException e) {
			System.out.println(e.getMessage());
		}
		
		System.out.println("Number of tests failed: " + testFailed);
	}
}
