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

public class HandleAddPassengerFrame extends JFrame {

	// -------- Instance Variables --------
	private static final int FRAME_WIDTH = 550;
	private static final int FRAME_HEIGHT = 350;
	private static final int FIELD_WIDTH = 10;

	private JPanel mainPanel;

	private JLabel errorLabel;

	private JTextField nameField;
	private JTextField numberField;

	private String name;
	private String number;

	// -------- Constructor --------
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
					System.out.print("Error");
					errorLabel.setText("Please enter a valid string in all fields.");

					mainPanel.revalidate();
				}
			}

		}

		ActionListener listener = new PanelItemListener();
		nameField.addActionListener(listener);

		return namePanel;
	}

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
					System.out.print("Error");
					errorLabel.setText("Please enter a valid string in all fields.");

					mainPanel.revalidate();
				}
			}

		}

		ActionListener listener = new PanelItemListener();
		numberField.addActionListener(listener);


		return numberPanel;
	}
	
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
