package gui;

import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;

import commands.DisplayFlightsCommand;

public class HandleFlightDisplayFrame extends JFrame {
	
	// -------- Instance Variables --------
	private static final int FRAME_WIDTH = 550;
	private static final int FRAME_HEIGHT = 350;
	
	// -------- Constructor ---------
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
