package startup;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JButton;

public class mainWindow {
	
	public static void main(String args[]) {
		JFrame frame = new JFrame();
		
		JButton button = new JButton("Click me!");
		JLabel label = new JLabel("Hello World!");
		JPanel panel = new JPanel();
		
		panel.add(button);
		panel.add(label);
		//frame.add(panel);
		
		frame.setSize(400, 400);
		frame.setTitle("Hello World");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		
		System.out.println("Heya!");
		
		//System.exit(0);
	}

}
