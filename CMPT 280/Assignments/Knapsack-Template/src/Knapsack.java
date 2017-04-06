import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


/**
 * A non-public class that stores an item's value and weight
 */
class Item implements Comparable<Item> {

	protected Double value;
	protected Double weight;
	
	Item(Double v, Double w) {
		value = v;
		weight = w;
	}

	@Override
	public int compareTo(Item o) {
		return this.value.compareTo(o.value);
	}
	
	/**
	 * @return the value
	 */
	public Double value() {
		return value;
	}

	/**
	 * @return the weight
	 */
	public Double weight() {
		return weight;
	}
	
}

/**
 * A non-public class that stores an instance of Knapsack.
 */
class KnapsackInstance {
	/**
	 * The number of items in the problem instance.
	 */
	protected Integer numItems;
	
	/**
	 * The items to be considered.
	 */
	Item items[];
	
	/**
	 * The capacity of the knapsack in the problem instance.
	 */
	protected Double W;
	
	/**
	 * Initialize a knapsack instance.
	 * @param numItems Number of items in the problem instance
	 * @param W Capacity of the backpack.
	 */
	KnapsackInstance(Integer numItems, Double W) {
		this.numItems = numItems;
		this.W = W;
		this.items = new Item[this.numItems];
	}
	
	/** 
	 * @return The number of items in the problem instance.
	 */
	public Integer numItems() { return this.numItems; }
	
	/**
	 * Set the value and weight of the id-th item.
	 */
	public void setItem(Double value, Double weight, Integer id) {
		this.items[id] = new Item(value, weight);
	}
	
	/**
	 * Obtain an item's value
	 */
	public Double value(int i) { return this.items[i].value(); }
	
	/**
	 * Obtain and item's weight
	 */
	public Double weight(int i) { return this.items[i].weight(); }

	/**
	 * Obtain the knapsack's capacity
	 */
	public Double capacity() { return this.W; }
	
	/** 
	 * Obtain the array of items.
	 */
	public Item[] items() { return this.items; }

	/**
	 * Printable representation of the problem instance.
	 */
	public String toString() {
		StringBuffer result = new StringBuffer();
		
		result.append("W = " + this.W + "\n");
		for(int i=0; i < this.numItems; i++) {
			result.append(this.items[i].value + ", " + this.items[i].weight + "\n");
		}
		return result.toString();
	}
	
}


public class Knapsack {

	public static KnapsackInstance readKnapsackInstance(String filename) {
		
		Scanner infile = null;
		try {
			infile = new Scanner(new File(filename));
		} catch (FileNotFoundException e) {
			System.out.println("Error: " + filename + " could not be opened.");			
		}
		
		// Try to read the knapsack capacity and the number of items.
		if (!infile.hasNextDouble()) 
			throw new RuntimeException("Error: expected knapsack weight as a real number");
		Double W = infile.nextDouble();
		
		if (!infile.hasNextInt()) 
			throw new RuntimeException("Error: expected integer number of items.");
		Integer numItems = infile.nextInt();
		
		// Create a knapsack instance for the given number of items.
		KnapsackInstance K = new KnapsackInstance(numItems, W);
		
		// Read each value-weight pair.
		for(int i=0; i < numItems; i++) {
			if(!infile.hasNextDouble()) 
				throw new RuntimeException("Error: expected a value while reading item " + i +".");
			Double v = infile.nextDouble();
			if(!infile.hasNextDouble()) 
				throw new RuntimeException("Error: expected a weight while reading item " + i +".");
			Double w = infile.nextDouble();
			
			// Store the value-weight pair in the problem instance.
			K.setItem(v,w,i);				
		}
		
		infile.close();
		
		return K;
	}

	// TODO Write your backtracking and greedy solutions to Knapsack here.
	

	public static void main(String args[]) {
		KnapsackInstance K = readKnapsackInstance("Knapsack-Template/knapsack-basictest.dat");
		
		// this line is mostly just to prevent a warning that K is unused.  You can
		// delete it when you're ready.  It has the added bonus of letting you see
		// the problem instance.
		System.out.println(K);
		
		// TODO Call your algorithms to solve the knapsack instance K here.
	}
}
