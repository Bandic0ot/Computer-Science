package gui;

import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

import commands.DisplayPassengersCommand;

public class HandlePassengerDisplayFrame extends JFrame {
	// -------- Instance Variables --------
	private static final int FRAME_WIDTH = 550;
	private static final int FRAME_HEIGHT = 350;

	// -------- Constructor ---------
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
