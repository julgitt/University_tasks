package com.company;
import java.io.*;

public class Main {

    public static void main(String[] args) throws Exception {
	  
        Stack<Integer> numbers= new Stack<>(4);
        numbers.Push(5);
        numbers.Push(6);
        numbers.Push(7);
        numbers.Push(5);
        numbers.Push(6);
        numbers.Push(6);
        System.out.println(numbers);


        // Serialization
        try
        {
            FileOutputStream file = new FileOutputStream("numbers.ser");
            ObjectOutputStream oos = new ObjectOutputStream(file);
            oos.writeObject(numbers);
            oos.close();
            file.close();
        }
        catch (IOException ioe)
        {
            ioe.printStackTrace();
            return;
        }

        Stack<Integer> numbers2= new Stack<>(3);

        //Deserialization

        try
        {
            FileInputStream file = new FileInputStream("numbers.ser");
           ObjectInputStream ois = new ObjectInputStream(file);

            numbers2 = (Stack) ois.readObject();

            ois.close();
            file.close();
        }
        catch (IOException ioe)
        {
            ioe.printStackTrace();
            return;
        }
        catch (ClassNotFoundException c)
        {
           System.out.println("Class not found");
           c.printStackTrace();
           return;
        }
        System.out.println(numbers2);

    }
}
