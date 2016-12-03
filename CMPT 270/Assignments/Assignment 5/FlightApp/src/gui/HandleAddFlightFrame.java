package gui;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JButton;
import javax.swing.JTextField;

import java.awt.GridLayout;
import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import commands.AddFlightCommand;

/**
 * A frame which allows the user to add a Flight to the
 * Flight Dictionary using the number of the flight.
 * @author Matthew Mulenga
 *
 */
public class HandleAddFlightFrame extends JFrame {


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
	 * The main panel which has a Border Layout.
	 */
	private JPanel mainPanel;

	/**
	 * A label used for displaying errors.
	 */
	private JLabel errorLabel;

	/**
	 * The number of the flight.
	 */
	private String number;
	
	/**
	 * The width of the flight.
	 */
	private String width;
	
	/**
	 * The capacity of the flight.
	 */
	private String capacity;

	// -------- Constructor --------
	/**
	 * A constructor which creates the window which
	 * handles the addition of a flight to the system.
	 */
	public HandleAddFlightFrame() {

		mainPanel = new JPanel();
		mainPanel.setLayout(new BorderLayout());

		JPanel centerPanel = new JPanel();
		centerPanel.setLayout(new GridLayout(3,1));

		errorLabel = new JLabel("");

		JPanel numberPanel = createNumberPanel();
		JPanel widthPanel = createWidthPanel();
		JPanel capacityPanel = createCapacityPanel();

		centerPanel.add(numberPanel);
		centerPanel.add(widthPanel);
		centerPanel.add(capacityPanel);

		JButton submitButton = createButton();

		mainPanel.add(centerPanel, BorderLayout.CENTER);
		mainPanel.add(errorLabel, BorderLayout.NORTH);
		mainPanel.add(submitButton, BorderLayout.SOUTH);

		add(mainPanel);

		setSize(FRAME_WIDTH, FRAME_HEIGHT);
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		setTitle("Add Flight");
		setVisible(false);
	}

	// -------- Methods --------
	/**
	 * Creates a panel which contains a text field and
	 * label for handling the addition of a flight's
	 * number.
	 * @return The initialized panel.
	 */
	private JPanel createNumberPanel() {

		JPanel numberPanel = new JPanel();
		JLabel label = new JLabel("Enter the flight number: ");
		JTextField numberField = new JTextField(FIELD_WIDTH);

		numberField.setEditable(true);

		numberPanel.add(label);
		numberPanel.add(numberField);

		class PanelItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				number = numberField.getText();
			}

		}

		ActionListener listener = new PanelItemListener();
		numberField.addActionListener(listener);

		return numberPanel;
	}
	
	/**
	 * Creates a panel which contains a text field and
	 * label for handling the addition of a flight's
	 * width.
	 * @return The initialized panel.
	 */
	private JPanel createWidthPanel() {

		JPanel widthPanel = new JPanel();
		JLabel label = new JLabel("Enter the width of the flight: ");
		JTextField widthField = new JTextField(FIELD_WIDTH);

		widthField.setEditable(true);

		widthPanel.add(label);
		widthPanel.add(widthField);

		class PanelItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				width = widthField.getText();
			}

		}

		ActionListener listener = new PanelItemListener();
		widthField.addActionListener(listener);

		return widthPanel;
	}

	/**
	 * Creates a panel which contains a text field and
	 * label for handling the addition of a flight's
	 * capacity.
	 * @return The initialized panel.
	 */
	private JPanel createCapacityPanel() {

		JPanel capacityPanel = new JPanel();
		JLabel label = new JLabel("Enter the capacity of the flight: ");
		JTextField capacityField = new JTextField(FIELD_WIDTH);

		capacityField.setEditable(true);
		capacityField.setText("");

		capacityPanel.add(label);
		capacityPanel.add(capacityField);

		class PanelItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				capacity = capacityField.getText();
			}

		}

		ActionListener listener = new PanelItemListener();
		capacityField.addActionListener(listener);

		return capacityPanel;
	}

	/**
	 * Creates a button which submits the data when pressed.
	 * @return The initialized button.
	 */
	private JButton createButton() {
		JButton submitButton = new JButton("Submit");
		ActionListener listener = new submitButtonListener();

		submitButton.addActionListener(listener);

		return submitButton;
	}

	class submitButtonListener implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			try {
				AddFlightCommand flightCommand = new AddFlightCommand();

				flightCommand.addFlight(Integer.parseInt(number), Integer.parseInt(width), Integer.parseInt(capacity));

				if(flightCommand.wasSuccessful()) {
					setVisible(false);
				} else {
					errorLabel.setText(flightCommand.getErrorMessage());
					mainPanel.revalidate();
				}
			} catch(Exception e) {

				errorLabel.setText("Please enter a valid integer in all fields.");

				mainPanel.revalidate();
			}
		}

	}
}
