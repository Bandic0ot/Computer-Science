
import java.util.InputMismatchException;
import java.util.TreeMap;
import java.util.Scanner;

/**
 * A simple flight reservation system whereby passengers can be created, flights created,
 * and passengers booked on the flights.  First class passengers are initially given a seat
 * and a meal plan.  Regular passengers are booked on a flight with no seat and can later 
 * be given a seat.
 */
public class FlightReservationSystem 
{
	/**
	 * The dictionary of all flights.
	 */
	private TreeMap<Integer, Flight> flights;
	
	/** 
	 * The dictionary of all passengers.
	 */
	private TreeMap<String, Passenger> passengers;
	
	/**
	 * The scanner used to read input from the user.
	 */
	private Scanner consoleIn; //This is not necessary, but makes code a little cleaner
	
	/**
	 * Initialize the system by creating the dictionaries and input scanner.
	 */
	public FlightReservationSystem(Scanner in)
	{
		flights = new TreeMap<Integer, Flight>();
		passengers = new TreeMap<String, Passenger>();
		consoleIn = in;
	}
	
	/**
	 * Run the reservation system: initialize, and then accept and carry out
	 * operations.  Output the passenger and flight dictionaries when finishing.
	 */
	public void run()
	{
		int opId = readOpId();
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
					System.out.println("\nThe passengers in the system are \n" + passengers);
					break;
				case 8:
					System.out.println("\nThe flights in the system are \n" + flights);
					break;
				default:
					System.out.println("Invalid int value; try again");
				}
			} catch (RuntimeException e)
			{
				System.out.println(e.getMessage());
			}

			opId = readOpId();
		}
		
		System.out.println("The system at shutdown is as follows: " + toString());
	}
	
	/**
	 * Output the prompt to list the possible operations, 
	 * and read selection picked by the user.
	 * @return  the int corresponding to the operation selected
	 */
	public int readOpId()
	{
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
	 * Read the information for a new passenger and then add the passenger 
	 * to the dictionary of all passengers.
	 */
	public void addPassenger()
	{
		System.out.print("Enter the name of the passenger: ");
		String name = consoleIn.nextLine();
		System.out.print("Enter the telephone number of the passenger: ");
		String telNumber = consoleIn.nextLine();
		if (passengers.containsKey(name))
		{
			throw new RuntimeException("Person not added as there already "
								+ "is a person by the name " + name);
		}
		else
		{
			Passenger p = new Passenger(name, telNumber);
			Passenger sameNamePerson = passengers.put(name, p);
			if (sameNamePerson != null)
			{
				passengers.put(name, sameNamePerson);  // put the original person back
				throw new RuntimeException("Name in the dictionary even though " +
						"containsKey failed.  Passenger " + name + " not entered.");
			}
		}	
	}

	/**
	 * Read the information for a new flight and then add the flight 
	 * to the dictionary of all flights.
	 */
	public void addFlight()
	{
		System.out.print("Enter the number of the flight: ");
		int number = readInt();
		if (flights.containsKey(number))
			throw new RuntimeException("Flight not added as there already "
					+ "is a flight with the number " + number);
		System.out.print("Enter the width of the flight: ");
		int width = readInt();
		System.out.print("Enter the capacity of the flight: ");
		int capacity = readInt();
		Flight f = new Flight(number, width, capacity);
		Flight sameNumberFlight = flights.put(number, f);
		if (sameNumberFlight != null)
		{
			flights.put(number, sameNumberFlight); // put the original flight back
			throw new RuntimeException("Number in the dictionary even though " +
					"containsKey failed.  Flight "  + number + " not entered.");
		}
	}
	
	/**
	 * Read the number for a flight, and then display its empty seats.
	 */
	public void displayEmptySeats()
	{
		System.out.print("Enter the number of the flight: ");
		int number = readInt();
		Flight f = flights.get(number);
		if (f == null)
			throw new RuntimeException("There is no flight with number " + number);
		else 
			System.out.println(f.availableSeats());
	}
	
	/**
	 * Read the name for a passenger, the number for a flight, and then book
	 * the passenger on the flight as a regular passenger.
	 */
	public void bookPassenger()
	{
		System.out.print("Enter the name of the passenger: ");
		String name = consoleIn.nextLine();
		Passenger p = passengers.get(name);
		if (p == null)
			throw new RuntimeException("There is no passenger with name " + name);
		System.out.print("Enter the number of the flight: ");
		int number = readInt();
		Flight f = flights.get(number);
		if (f == null)
			throw new RuntimeException("There is no flight with number " + number);
		else f.makeBooking(p);
	}

	/**
	 * Read the name for a passenger, the number for a flight, the seat for the passenger,
	 * and the meal plan for the passenger, and then book
	 * the passenger on the flight as a first class passenger.
	 */
	public void bookFirstClassPassenger()
	{
		System.out.print("Enter the name of the passenger: ");
		String name = consoleIn.nextLine();
		Passenger p = passengers.get(name);
		if (p == null)
			throw new RuntimeException("There is no passenger with name " + name);
		System.out.print("Enter the number of the flight: ");
		int number = readInt();
		Flight f = flights.get(number);
		if (f == null)
			throw new RuntimeException("There is no flight with number " + number);
		System.out.print("Enter the seat for the passenger: ");
		String seat = consoleIn.nextLine();
		System.out.print("Enter the meal plan of the passenger: ");
		String meal = consoleIn.nextLine();
		f.makeFirstClassBooking(p, seat, meal);
	}
	
	/** 
	 * Read the name for a passenger, the number for a flight, and the seat for the
	 * passenger on the flight, and then assign the passenger the seat on the flight.
	 */
	public void assignSeatForPassenger()
	{
		System.out.print("Enter the name of the passenger: ");
		String name = consoleIn.nextLine();
		Passenger p = passengers.get(name);
		if (p == null)
			throw new RuntimeException("There is no passenger with name " + name);
		System.out.print("Enter the number of the flight: ");
		int number = readInt();
		Flight f = flights.get(number);
		if (f == null)
			throw new RuntimeException("There is no flight with number " + number);
		System.out.print("Enter the seat for the passenger: ");
		String seat = consoleIn.nextLine();
		f.assignSeat(p, seat);
	}
	
	/**
	 * @return a String that contains all the passengers and flights in the system.
	 */
	public String toString()
	{
		/* The output should be formatted much better, 
		 * but show the format from a Map. */
		String result = "\nThe passengers in the system are \n" + passengers;
		result = result + "\n\nThe flights in the system are \n" + flights;

		

		
		
		return result + "\n";
	}
	
	/**
	 * Run the flight reservation system.
	 * @param args not used
	 */
	public static void main(String[] args) 
	{
		Scanner in = new Scanner(System.in);
		FlightReservationSystem sys = new FlightReservationSystem(in);
		sys.run();
		in.close();
		
	}
}
