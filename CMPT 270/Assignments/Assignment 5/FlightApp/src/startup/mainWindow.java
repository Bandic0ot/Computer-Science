package startup;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JButton;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class mainWindow {
	
	
	public static void main(String args[]) {
		class ClickListener implements ActionListener {
			public void actionPerformed(ActionEvent event) {
				System.out.println("Click.");
			}
		}
		
		JFrame frame = new JFrame();
		
		JButton button = new JButton("Click me!");
		JLabel label = new JLabel("Hello World!");
		JPanel panel = new JPanel();
		
		ActionListener listener = new ClickListener();
		button.addActionListener(listener);
		
		panel.add(button);
		panel.add(label);
		frame.add(panel);
		
		frame.setSize(400, 400);
		frame.setTitle("Hello World");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		
		//System.exit(0);
	}

}
