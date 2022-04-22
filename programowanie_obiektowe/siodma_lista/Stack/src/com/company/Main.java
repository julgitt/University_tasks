package com.company;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;

public class Main {

    public static void main(String[] args) throws IOException, ClassNotFoundException, NoSuchMethodException {
        if (args.length == 2) {
            Class<?> figure = Class.forName(args[1]);
            Class<?>[] classes = {args[1].getClass()};

            MyFrame frame = new MyFrame();
            File file = new File(args[0]);
            if (file.isFile() && file.canRead()) {
                try {
                    FileInputStream input = new FileInputStream(args[0]);
                    ObjectInputStream objInput = new ObjectInputStream(input);

                    figure = (Class<?>) objInput.readObject();

                    objInput.close();
                    input.close();
                } catch (IOException | ClassNotFoundException ioe) {
                    ioe.printStackTrace();
                }
            }
            else if(file.createNewFile())
                System.out.println("File has been created");
            figure.getMethod("Edit", classes);
        }
        else
            System.out.println(args.length);
    }
}

  /*  public static void main(String[] args) throws IOException {

        MyFrame frame = new MyFrame();
        Circle figure = new Circle();
        File file = new File("Circle.ser");
        if (file.isFile() && file.canRead()) {
            try {
                FileInputStream input = new FileInputStream("Circle.ser");
                ObjectInputStream objInput = new ObjectInputStream(input);

                figure = (Circle) objInput.readObject();

                objInput.close();
                input.close();
            } catch (IOException | ClassNotFoundException ioe) {
                ioe.printStackTrace();
            }
        }
        else if(file.createNewFile())
            System.out.println("File has been created");

        figure.Edit(frame,"Circle.ser");
    }*/