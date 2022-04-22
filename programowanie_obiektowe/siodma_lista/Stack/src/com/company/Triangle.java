package com.company;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Triangle extends Figure {
    private int side1;
    private int side2;
    private int side3;
    JTextField figureSide1;
    JTextField figureSide2;
    JTextField figureSide3;

    public Triangle() {
        super("",0,0);
        this.side1 = 0;
        this.side2 = 0;
        this.side3 = 0;
    }
    public Triangle(String s, int p, int a, int s1, int s2, int s3) {
        super(s, p, a);
        this.side1 = s1;
        this.side2 = s2;
        this.side3 = s3;
    }

    public String toString() {
        return  this.name + " " + this.perimeter + " " + this.area
                + " " + this.side1 + " " + this.side2 + " " + this.side3 + "\n";
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
            side1 =Integer.parseInt(figureSide1.getText());
            side2 =Integer.parseInt(figureSide2.getText());
            side3 =Integer.parseInt(figureSide3.getText());
            Save(file_name);
        }
    }

    public void Edit(MyFrame my_frame, String file_name) {
        MyLabel label = new MyLabel();
        figureArea = label.add("Area", Integer.toString(this.area), my_frame);

        //name
        figureName = label.add("Name", this.name, my_frame);

        //perimeter
        figurePerimeter = label.add("Perimeter", Integer.toString(this.perimeter), my_frame);

        //side1
        figureSide1 = label.add("First side", Integer.toString(this.side1), my_frame);

        //side2
        figureSide2 = label.add("Second side", Integer.toString(this.side2), my_frame);

        //side3
        figureSide3 = label.add("Third side", Integer.toString(this.side3), my_frame);

        save_button.addActionListener(new MyListener(file_name));

        my_frame.container.add(save_button);
        my_frame.frame.pack();
        my_frame.frame.setVisible(true);
    }
}
