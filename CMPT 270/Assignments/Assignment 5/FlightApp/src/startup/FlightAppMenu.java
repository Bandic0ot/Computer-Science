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

public class FlightAppMenu extends JFrame {
	
	// -------- Instance Variables --------
	private static final int FRAME_WIDTH = 550;
	private static final int FRAME_HEIGHT = 350;
	
	private JPanel buttonPanel;
	private JButton button1, button2, button3, button4, button5, button6;
	
	
	// -------- Constructor --------
	public FlightAppMenu() {
		
		createButtons();
		createComponents();
		
		setSize(FRAME_WIDTH, FRAME_HEIGHT);
	}
	
	public void createComponents() {
		
		buttonPanel = new JPanel();
		buttonPanel.setLayout(new GridLayout(6, 1));
		
		buttonPanel.add(button1);
		buttonPanel.add(button2);
		buttonPanel.add(button3);
		buttonPanel.add(button4);
		buttonPanel.add(button5);
		buttonPanel.add(button6);
		
		add(buttonPanel, BorderLayout.CENTER);
	}
	
	public void createButtons() {
		button1 = new JButton("Add Flight");
		button2 = new JButton("Add Passenger");
		button3 = new JButton("Display Passengers");
		button4 = new JButton("Display Flights");
		button5 = new JButton("Quit");
		button6 = new JButton("");
	}
	
	
	// -------- Methods --------
	public static void main(String args[]) {
		JFrame window = new FlightAppMenu();
		
		window.setTitle("Flight App");
		window.setDefaultCloseOperation(EXIT_ON_CLOSE);
		window.setVisible(true);
		
	}

}