package startup;

import containers.PassengerDictionary;
import containers.FlightDictionary;

import entities.Flight;
import entities.Passenger;

import commands.AddPassengerCommand;
import commands.DisplayEmptySeatCommand;
import commands.BookPassengerCommand;

import interfaces.UserInterface;

//import java.util.Scanner;

/**
 * A simple flight reservation system whereby passengers can be created, flights created,
 * and passengers booked on the flights.  First class passengers are initially given a seat
 * and a meal plan.  Regular passengers are booked on a flight with no seat and can later 
 * be given a seat.
 * @author Matthew Mulenga
 */
public class FlightReservationSystem 
{
	//-------- Instance Variables --------
	/**
	 * The user interface, handles all I/O.
	 */
	private UserInterface userInterface;
	
	
	//-------- Methods --------
	/**
	 * Constructor that initializes the userInterface.
	 */
	public FlightReservationSystem()
	{
		userInterface = new UserInterface();
	}
	
	/**
	 * Run the reservation system: initialize, and then accept and carry out
	 * operations.  Output the passenger and flight dictionaries when finishing.
	 */
	public void run()
	{
		int opId = userInterface.readOpId();
		while (opId != 0)
		{
			try
			{
				switch (opId)
				{
				case 1:
					addPassenger();
					break;
				case 2:
					addFlight();
					break;
				case 3:
					displayEmptySeats();
					break;
				case 4:
					bookPassenger();
					break;
				case 5:
					bookFirstClassPassenger();
					break;
				case 6:
					assignSeatForPassenger();
					break;
				case 7:
					userInterface.sendMessage("\nThe passengers in the system are \n" + PassengerDictionary.dictionary());
					break;
				case 8:
					userInterface.sendMessage("\nThe flights in the system are \n" + FlightDictionary.dictionary());
					break;
				default:
					userInterface.sendMessage("Invalid int value; try again");
				}
			} catch (RuntimeException e)
			{
				userInterface.sendMessage(e.getMessage());
			}

			opId = userInterface.readOpId();
		}
		
		userInterface.sendMessage("The system at shutdown is as follows: " + toString());
	}
	
	/**
	 * Read the information for a new passenger and then add the passenger 
	 * to the dictionary of all passengers.
	 */
	public void addPassenger()
	{
		String name = userInterface.getPassName();
		String telNumber = userInterface.getTelNumber();
		
		AddPassengerCommand passCommand = new AddPassengerCommand();
		passCommand.addPassToDict(name, telNumber);
		
		if(!passCommand.wasSuccessful()) {
			userInterface.sendMessage(passCommand.getErrorMessage());
		}
	}

	/**
	 * Read the information for a new flight and then add the flight 
	 * to the dictionary of all flights.
	 */
	public void addFlight()
	{
		int number = userInterface.getFlightNumber();
		if (FlightDictionary.dictionary().containsKey(number)) {
			throw new RuntimeException("Flight not added as there already "
					+ "is a flight with the number " + number);
		}
		int width = userInterface.getFlightWidth();
		int capacity = userInterface.getFLightCapacity();
		
		Flight f = new Flight(number, width, capacity);
		Flight sameNumberFlight = FlightDictionary.dictionary().put(number, f);
		if (sameNumberFlight != null)
		{
			FlightDictionary.dictionary().put(number, sameNumberFlight); // put the original flight back
			throw new RuntimeException("Number in the dictionary even though " +
					"containsKey failed.  Flight "  + number + " not entered.");
		}
	}
	
	/**
	 * Read the number for a flight, and then display its empty seats.
	 */
	public void displayEmptySeats()
	{
		int number = userInterface.getFlightNumber();
		DisplayEmptySeatCommand seatCommand = new DisplayEmptySeatCommand();
		seatCommand.emptySeat(number);
		
		if(seatCommand.wasSuccessful()) {
			userInterface.sendMessage(seatCommand.getAvailableSeatString());
		} else {
			userInterface.sendMessage(seatCommand.getErrorMessage());
		}
			
	}
	
	/**
	 * Read the name for a passenger, the number for a flight, and then book
	 * the passenger on the flight as a regular passenger.
	 */
	public void bookPassenger()
	{
		String name = userInterface.getPassName();
		int number = userInterface.getFlightNumber();
		BookPassengerCommand bookCommand = new BookPassengerCommand();
		
		bookCommand.addPassToFlight(name, number);
		
		if(!bookCommand.wasSuccessful()) {
			userInterface.sendMessage(bookCommand.getErrorMessage());
		}
	}

	/**
	 * Read the name for a passenger, the number for a flight, the seat for the passenger,
	 * and the meal plan for the passenger, and then book
	 * the passenger on the flight as a first class passenger.
	 */
	public void bookFirstClassPassenger()
	{
		String name = userInterface.getPassName();
		Passenger p = PassengerDictionary.dictionary().get(name);
		if (p == null)
			throw new RuntimeException("There is no passenger with name " + name);
		int number = userInterface.getFlightNumber();
		Flight f = FlightDictionary.dictionary().get(number);
		if (f == null)
			throw new RuntimeException("There is no flight with number " + number);
		String seat = userInterface.getPassSeat();
		String meal = userInterface.getMealPlan();
		f.makeFirstClassBooking(p, seat, meal);
	}
	
	/** 
	 * Read the name for a passenger, the number for a flight, and the seat for the
	 * passenger on the flight, and then assign the passenger the seat on the flight.
	 */
	public void assignSeatForPassenger()
	{
		String name = userInterface.getPassName();
		Passenger p = PassengerDictionary.dictionary().get(name);
		if (p == null)
			throw new RuntimeException("There is no passenger with name " + name);
		int number = userInterface.getFlightNumber();
		Flight f = FlightDictionary.dictionary().get(number);
		if (f == null)
			throw new RuntimeException("There is no flight with number " + number);
		String seat = userInterface.getPassSeat();
		f.assignSeat(p, seat);
	}
	
	/**
	 * @return a String that contains all the passengers and flights in the system.
	 */
	public String toString()
	{
		/* The output should be formatted much better, 
		 * but show the format from a Map. */
		String result = "\nThe passengers in the system are \n" + PassengerDictionary.dictionary();
		result = result + "\n\nThe flights in the system are \n" + FlightDictionary.dictionary();
		
		return result + "\n";
	}
	
	/**
	 * Run the flight reservation system.
	 * @param args not used
	 */
	public static void main(String[] args) 
	{
		FlightReservationSystem sys = new FlightReservationSystem();
		sys.run();
		
	}
}
