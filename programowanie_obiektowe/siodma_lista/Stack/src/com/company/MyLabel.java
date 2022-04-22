package com.company;
import java.awt.event.*;
import java.io.*;
import javax.swing.*;

public class MyLabel {
    public  JTextField add(String name, String information, MyFrame my_frame){
        JLabel label = new JLabel(name);
        my_frame.container.add(label);
        JTextField figureInfo = new JTextField(information, 40);
        my_frame.container.add(figureInfo);
        return figureInfo;
    }
}
