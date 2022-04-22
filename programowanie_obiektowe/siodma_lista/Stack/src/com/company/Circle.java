package com.company;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Circle extends Figure {
    private int radius;
    private int x_centre;
    private int y_centre;
    JTextField figureRadius;
    JTextField figure_x_centre;
    JTextField figure_y_centre;

    public Circle() {
        super("",0,0);
        this.radius = 0;
        this.x_centre = 0;
        this.y_centre = 0;
    }

    public Circle(String s, int p, int a, int r, int x, int y) {
        super(s, p, a);
        this.radius = r;
        this.x_centre = x;
        this.y_centre = y;
    }

    public String toString() {
        return this.name + " " + this.perimeter + " " + this.area
                + " " + this.radius + " " + this.x_centre + " "+ this.y_centre + "\n";
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
            radius =Integer.parseInt(figureRadius.getText());
            x_centre =Integer.parseInt(figure_x_centre.getText());
            y_centre =Integer.parseInt(figure_y_centre.getText());
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
        figureRadius = label.add("Radius", Integer.toString(this.radius), my_frame);

        //side2
        figure_x_centre = label.add("x coordinate", Integer.toString(this.x_centre), my_frame);

        //side3
        figure_y_centre = label.add("y coordinate", Integer.toString(this.y_centre), my_frame);

        save_button.addActionListener(new MyListener(file_name));

        my_frame.container.add(save_button);
        my_frame.frame.pack();
        my_frame.frame.setVisible(true);
    }
}