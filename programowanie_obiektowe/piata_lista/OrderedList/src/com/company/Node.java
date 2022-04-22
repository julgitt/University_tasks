package com.company;

public class Node<T extends Comparable<T>> {
    public Node<T> prev;
    public Node<T> next;
    public T element;

    //constructors
    public Node(T element)
    {
        this.element = element;
        prev = null;
        next = null;
    }
}
