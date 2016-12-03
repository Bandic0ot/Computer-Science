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

	/**
	 * The width of the text field.
	 */
	private static final int FIELD_WIDTH = 10;

	/**
	 * A panel containing all the buttons.
	 */
	private JPanel buttonPanel;
	
	/**
	 * A button that opens an add flight window.
	 */
	private JButton addFlightButton;
	
	/**
	 * A button that opens an add passenger window.
	 */
	private JButton addPassButton;
	
	/**
	 * A button that opens a display passenger window.
	 */
	private JButton displayPassButton;
	
	/**
	 * A button that opens a display flight window.
	 */
	private JButton displayFlightButton;
	
	/**
	 * A button that quits the application.
	 */
	private JButton quitButton;


	// -------- Constructor --------
	/**
	 * A constructor that creates a window for
	 * the main menu of the application.
	 */
	public FlightAppMenu() {

		createButtons();
		createButtonPanel();
		createSearchPanel();

		setSize(FRAME_WIDTH, FRAME_HEIGHT);
	}

	// -------- Methods --------
	/**
	 * Creates a panel with a border layout which
	 * contains all the buttons.
	 */
	public void createButtonPanel() {

		buttonPanel = new JPanel();
		buttonPanel.setLayout(new GridLayout(5, 1));

		buttonPanel.add(addFlightButton);
		buttonPanel.add(addPassButton);
		buttonPanel.add(displayPassButton);
		buttonPanel.add(displayFlightButton);
		buttonPanel.add(quitButton);


		add(buttonPanel, BorderLayout.CENTER);
	}

	/**
	 * Creates a panel which contains a text field and
	 * label for handling searching up information on
	 * different flights.
	 */
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

	/**
	 * Creates all the buttons which handle opening up different
	 * windows throughout the application.
	 */
	public void createButtons() {

		// Creating the Add Flight button.
		addFlightButton = new JButton("Add Flight");

		class AddFlightItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				HandleAddFlightFrame newFlight = new HandleAddFlightFrame();
				newFlight.setVisible(true);
			}
		}

		ActionListener flightListener = new AddFlightItemListener();
		addFlightButton.addActionListener(flightListener);


		// Creating the Add Passenger button.
		addPassButton = new JButton("Add Passenger");

		class AddPassengerItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				HandleAddPassengerFrame newPassenger = new HandleAddPassengerFrame();
				newPassenger.setVisible(true);
			}
		}

		ActionListener passListener = new AddPassengerItemListener();
		addPassButton.addActionListener(passListener);


		// Creating the Display Passengers button.
		displayPassButton = new JButton("Display Passengers");

		class DisplayPassengerItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				HandlePassengerDisplayFrame newPassenger = new HandlePassengerDisplayFrame();
				newPassenger.setVisible(true);
			}
		}

		ActionListener passDisplayListener = new DisplayPassengerItemListener();
		displayPassButton.addActionListener(passDisplayListener);


		// Creating the Display Flights button.
		displayFlightButton = new JButton("Display Flights");

		class DisplayFlightItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				HandleFlightDisplayFrame flightDisplay = new HandleFlightDisplayFrame();
				flightDisplay.setVisible(true);
			}
		}

		ActionListener flightDisplayListener = new DisplayFlightItemListener();
		displayFlightButton.addActionListener(flightDisplayListener);

		// Creating the quit button
		quitButton = new JButton("Quit");

		class ExitItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {

				System.exit(0);

			}
		}

		ActionListener listener = new ExitItemListener();
		quitButton.addActionListener(listener);
	}

	/**
	 * Run the flight app menu.
	 * @param args not used
	 */
	public static void main(String args[]) {
		JFrame window = new FlightAppMenu();

		window.setTitle("Flight App");
		window.setDefaultCloseOperation(EXIT_ON_CLOSE);
		window.setVisible(true);

	}

}