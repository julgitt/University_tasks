package com.company;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.Objects;

public class Main {

    public static void main(String[] args) throws Exception {
        if (args.length == 2) {
            Figure figure;

            if (Objects.equals(args[1], "Figure"))
                figure = new Figure();
            else if (Objects.equals(args[1], "Circle"))
                figure = new Circle();
            else if (Objects.equals(args[1], "Triangle"))
                figure = new Triangle();
            else
                throw new Exception("Wrong class name in argument");


            MyFrame frame = new MyFrame();
            File file = new File(args[0]);
            if (file.isFile() && file.canRead()) {
                try {
                    FileInputStream input = new FileInputStream(args[0]);
                    ObjectInputStream objInput = new ObjectInputStream(input);

                    figure = (Figure) objInput.readObject();

                    objInput.close();
                    input.close();
                } catch (IOException | ClassNotFoundException ioe) {
                    ioe.printStackTrace();
                }
            } else if (file.createNewFile())
                System.out.println("File has been created");
            figure.Edit(frame, args[0]);
        } else
            System.out.println(args.length);
    }
}




