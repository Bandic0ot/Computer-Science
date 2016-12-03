package startup;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JButton;
import javax.swing.JTextField;

import java.awt.GridLayout;
import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import gui.HandleAddFlightFrame;
import gui.HandleFlightFrame;
import gui.HandleAddPassengerFrame;
import gui.HandlePassengerDisplayFrame;
import gui.HandleFlightDisplayFrame;

public class FlightAppMenu extends JFrame {

	// -------- Instance Variables --------
	/**
	 * The width of the frame.
	 */
	private static final int FRAME_WIDTH = 550;
	
	/**
	 * The height of the frame.
	 */
	private static final int FRAME_HEIGHT = 350;

	/**
	 * The width of the text field.
	 */
	private static final int FIELD_WIDTH = 10;

	/**
	 * A panel containing all the buttons.
	 */
	private JPanel buttonPanel;
	
	/**
	 * 
	 */
	private JButton button1, button2, button3, button4, button5;


	// -------- Constructor --------
	public FlightAppMenu() {

		createButtons();
		createButtonPanel();
		createSearchPanel();

		setSize(FRAME_WIDTH, FRAME_HEIGHT);
	}

	public void createButtonPanel() {

		buttonPanel = new JPanel();
		buttonPanel.setLayout(new GridLayout(5, 1));

		buttonPanel.add(button1);
		buttonPanel.add(button2);
		buttonPanel.add(button3);
		buttonPanel.add(button4);
		buttonPanel.add(button5);


		add(buttonPanel, BorderLayout.CENTER);
	}

	public void createSearchPanel() {
		JPanel searchPanel = new JPanel();
		JLabel prompt = new JLabel("Search flight #: ");
		JTextField field = new JTextField(FIELD_WIDTH);

		searchPanel.add(prompt);
		searchPanel.add(field);

		add(searchPanel, BorderLayout.SOUTH);

		//Create a listener for the text field
		class TextFieldItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				HandleFlightFrame newFrame = new HandleFlightFrame(Integer.parseInt(field.getText()));
				newFrame.setVisible(true);
			}
		}

		ActionListener listener = new TextFieldItemListener();
		field.addActionListener(listener);
	}

	public void createButtons() {

		// Creating the Add Flight button.
		button1 = new JButton("Add Flight");

		class AddFlightItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				HandleAddFlightFrame newFlight = new HandleAddFlightFrame();
				newFlight.setVisible(true);
			}
		}

		ActionListener flightListener = new AddFlightItemListener();
		button1.addActionListener(flightListener);


		// Creating the Add Passenger button.
		button2 = new JButton("Add Passenger");

		class AddPassengerItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				HandleAddPassengerFrame newPassenger = new HandleAddPassengerFrame();
				newPassenger.setVisible(true);
			}
		}

		ActionListener passListener = new AddPassengerItemListener();
		button2.addActionListener(passListener);


		// Creating the Display Passengers button.
		button3 = new JButton("Display Passengers");

		class DisplayPassengerItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				HandlePassengerDisplayFrame newPassenger = new HandlePassengerDisplayFrame();
				newPassenger.setVisible(true);
			}
		}

		ActionListener passDisplayListener = new DisplayPassengerItemListener();
		button3.addActionListener(passDisplayListener);


		// Creating the Display Flights button.
		button4 = new JButton("Display Flights");

		class DisplayFlightItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				HandleFlightDisplayFrame flightDisplay = new HandleFlightDisplayFrame();
				flightDisplay.setVisible(true);
			}
		}

		ActionListener flightDisplayListener = new DisplayFlightItemListener();
		button4.addActionListener(flightDisplayListener);

		// Creating the quit button
		button5 = new JButton("Quit");

		class ExitItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {

				System.exit(0);

			}
		}

		ActionListener listener = new ExitItemListener();
		button5.addActionListener(listener);
	}


	// -------- Methods --------
	public static void main(String args[]) {
		JFrame window = new FlightAppMenu();

		window.setTitle("Flight App");
		window.setDefaultCloseOperation(EXIT_ON_CLOSE);
		window.setVisible(true);

	}

}