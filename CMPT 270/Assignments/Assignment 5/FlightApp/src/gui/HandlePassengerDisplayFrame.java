package gui;

import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

import commands.DisplayPassengersCommand;

public class HandlePassengerDisplayFrame extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

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
	 * the displaying a list of the passengers in the system.
	 */
	public HandlePassengerDisplayFrame() {
		DisplayPassengersCommand display = new DisplayPassengersCommand();

		JTextArea myTextArea = new JTextArea(display.getPassengersString());
		myTextArea.setEditable(false); // the user is not allowed to edit the text area
		JScrollPane myPane = new JScrollPane(myTextArea);

		add(myPane);

		setSize(FRAME_WIDTH, FRAME_HEIGHT);
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		setTitle("Display Passengers");
		setVisible(false);
	}
}
