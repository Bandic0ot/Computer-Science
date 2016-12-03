package gui;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import commands.AddPassengerCommand;

/**
 * A frame which allows the user to add a Passenger to the
 * Passenger Dictionary using their name and telephone number.
 * @author Matthew Mulenga
 *
 */
public class HandleAddPassengerFrame extends JFrame {

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
	 * The field used for collecting the passenger's name.
	 */
	private JTextField nameField;
	
	/**
	 * The field used for collecting the passenger's telephone number.
	 */
	private JTextField numberField;

	/**
	 * Stores the passenger's name.
	 */
	private String name;
	
	/**
	 * Stores the passenger's telephone number.
	 */
	private String number;

	// -------- Constructor --------
	/**
	 * A constructor which creates the window which handles
	 * the adding of a passenger to the system.
	 */
	public HandleAddPassengerFrame() {
		mainPanel = new JPanel();
		mainPanel.setLayout(new BorderLayout());

		JPanel centerPanel = new JPanel();
		centerPanel.setLayout(new GridLayout(2,1));

		errorLabel = new JLabel("");

		JPanel namePanel = createNamePanel();
		JPanel numberPanel = createNumberPanel();

		centerPanel.add(namePanel);
		centerPanel.add(numberPanel);

		JButton closeButton = createButton();

		mainPanel.add(centerPanel, BorderLayout.CENTER);
		mainPanel.add(errorLabel, BorderLayout.NORTH);
		mainPanel.add(closeButton, BorderLayout.SOUTH);

		add(mainPanel);

		setSize(FRAME_WIDTH, FRAME_HEIGHT);
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		setTitle("Add Passenger");
		setVisible(false);
	}


	// -------- Methods --------
	/**
	 * Creates a panel which contains a text field and
	 * label for handling the addition of a passenger's
	 * name.
	 * @return The initialized panel.
	 */
	private JPanel createNamePanel() {

		JPanel namePanel = new JPanel();
		JLabel label = new JLabel("Enter the passenger's name: ");
		nameField = new JTextField(FIELD_WIDTH);

		nameField.setEditable(true);

		namePanel.add(label);
		namePanel.add(nameField);

		class PanelItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				name = nameField.getText();

				try {
					AddPassengerCommand passCommand = new AddPassengerCommand();

					passCommand.addPassenger(name, number);

					if(passCommand.wasSuccessful()) {
						nameField.setText("");
						numberField.setText("");
						
						mainPanel.revalidate();
					} else {
						errorLabel.setText(passCommand.getErrorMessage());
						mainPanel.revalidate();
					}
				} catch(Exception e) {
					errorLabel.setText("Please enter a valid string in all fields.");

					mainPanel.revalidate();
				}
			}

		}

		ActionListener listener = new PanelItemListener();
		nameField.addActionListener(listener);

		return namePanel;
	}

	/**
	 * Creates a panel which contains a text field and
	 * label for handling the addition of a passenger's
	 * telephone number.
	 * @return The initialized panel.
	 */
	private JPanel createNumberPanel() {

		JPanel numberPanel = new JPanel();
		JLabel label = new JLabel("Enter the passenger's telephone number: ");
		numberField = new JTextField(FIELD_WIDTH);

		numberField.setEditable(true);

		numberPanel.add(label);
		numberPanel.add(numberField);

		class PanelItemListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				number = numberField.getText();

				try {
					AddPassengerCommand passCommand = new AddPassengerCommand();

					passCommand.addPassenger(name, number);

					if(passCommand.wasSuccessful()) {
						nameField.setText("");
						numberField.setText("");
						
						mainPanel.revalidate();
					} else {
						errorLabel.setText(passCommand.getErrorMessage());
						mainPanel.revalidate();
					}
				} catch(Exception e) {
					errorLabel.setText("Please enter a valid string in all fields.");

					mainPanel.revalidate();
				}
			}

		}

		ActionListener listener = new PanelItemListener();
		numberField.addActionListener(listener);


		return numberPanel;
	}
	
	/**
	 * Creates a button which is used to close the
	 * window.
	 * @return The initialized button.
	 */
	private JButton createButton() {
		JButton closeButton = new JButton("Close");
		
		class CloseButtonListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				setVisible(false);
			}
		}
		
		ActionListener listener = new CloseButtonListener();
		closeButton.addActionListener(listener);
		
		return closeButton;
	}


}
