package com.company;

import java.io.*;

public class Stack<T extends Serializable> implements Serializable{
    T element;
    Stack<T> next;
    boolean empty;

    public Stack(T elem) {
        element = elem;
        empty = false;
    }

    public void Push(T element) {
        Stack<T> temp = this;
        while (temp.next != null) {
            temp = temp.next;
        }

        temp.next = new Stack<T>(element);
        empty = false;
    }

    public T Pop() throws Exception {
        Stack<T> temp = this;
        Stack<T> previous = temp;

        if (IsEmpty()) {
            throw new Exception("there is nothing to delete");
        }
        if (this.next == null) {
            empty = true;
            return this.element;
        }
        while (temp.next != null) {
            previous = temp;
            temp = temp.next;
        }
        T deleted = temp.element;
        previous.next = null;
        return deleted;
    }

    @Override
    public String toString() {
        String result = "";
        Stack<T> temp = this;

        if (IsEmpty()) {
            try {
                throw new Exception("the Stack is empty");
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        while (temp != null) {
            result += " " + temp.element;
            temp = temp.next;
        }

        return result;
    }
    public T GetFirst(){
        return element;
    }

    public boolean IsEmpty() {
        if (element == null && next == null)
            return true;
        return empty;
    }
}

