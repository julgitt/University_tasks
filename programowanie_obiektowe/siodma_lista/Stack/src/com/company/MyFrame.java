package com.company;
import javax.swing.*;
import java.awt.*;

public class MyFrame extends JFrame{
    JFrame frame;
    Container container;
    GridLayout layout;
    // constructor
    public MyFrame() {
        frame = new JFrame("Figure edition");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        container = frame.getContentPane();
        layout = new GridLayout(4, 2);
        container.setLayout(layout);
    }
}
