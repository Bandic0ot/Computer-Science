package commands;

import containers.FlightDictionary;
import containers.PassengerDictionary;

import entities.Flight;
import entities.Passenger;

public class BookPassengerCommand extends CommandStatus {

	public void addPassToFlight(String name, Flight flight) {
		Passenger p = PassengerDictionary.dictionary().get(name);
		
		if(p == null) {
			throw new RuntimeException("There is no passenger with name " + name);
		}
	}

}
