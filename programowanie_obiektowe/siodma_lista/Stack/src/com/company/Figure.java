package com.company;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Scanner;

public class Figure implements Serializable {
    protected String name;
    protected int perimeter;
    protected int area;

    JTextField figureName;
    JTextField figurePerimeter;
    JTextField figureArea;

    protected final JButton save_button = new JButton("Save");

    //constructor
    public Figure() {
        name = "";
        perimeter = 0;
        area = 0;
    }
    public Figure(String s, int p, int a) {
        name = s;
        perimeter = p;
        area = a;
    }

    //save to file/restore from file
    void Save(String name) {
        try {
            FileOutputStream file = new FileOutputStream(name);
            ObjectOutputStream oos = new ObjectOutputStream(file);
            oos.writeObject(this);
            oos.close();
            file.close();
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
    }


    @Override
    public String toString() {
        return this.name + " " + this.perimeter + " " + this.area + "\n";
    }


    class MyListener implements ActionListener {
        String file_name;
        MyListener(String name){
            super();
            file_name = name;
        }

        public void actionPerformed(ActionEvent e) {
            name = figureName.getText();
            perimeter = Integer.parseInt(figurePerimeter.getText());
            area = Integer.parseInt(figureArea.getText());
            Save(file_name);
        }
    }

    public void Edit(MyFrame my_frame, String file_name) {
        //area
        MyLabel label = new MyLabel();
        figureArea = label.add("Area", Integer.toString(this.area), my_frame);

        //name
        figureName = label.add("Name", this.name, my_frame);

        //perimeter
        figurePerimeter = label.add("Perimeter", Integer.toString(this.perimeter), my_frame);

        save_button.addActionListener(new MyListener(file_name));

        my_frame.container.add(save_button);
        my_frame.frame.pack();
        my_frame.frame.setVisible(true);
    }
}
