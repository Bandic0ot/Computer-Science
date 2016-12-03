package gui;

import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;

import commands.DisplayFlightsCommand;

public class HandleFlightDisplayFrame extends JFrame {
	
	// -------- Instance Variables --------
	/**
	 * The width of the frame.
	 */
	private static final int FRAME_WIDTH = 550;
	
	/**
	 * The height of the frame.
	 */
	private static final int FRAME_HEIGHT = 350;
	
	// -------- Constructor ---------
	/**
	 * A constructor which creates a window that handles
	 * the displaying a list of the flights in the system.
	 */
	public HandleFlightDisplayFrame() {
		DisplayFlightsCommand display = new DisplayFlightsCommand();
		
		JTextArea myTextArea = new JTextArea(display.getFlightsString());
		myTextArea.setEditable(false); // the user is not allowed to edit the text area
		JScrollPane myPane = new JScrollPane(myTextArea);
		
		add(myPane);
		
		setSize(FRAME_WIDTH, FRAME_HEIGHT);
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		setTitle("Display Flights");
		setVisible(false);
	}

}
