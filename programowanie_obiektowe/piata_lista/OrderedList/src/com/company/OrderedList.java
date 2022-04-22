package com.company;

public class OrderedList<T extends Comparable<T>> {
    Node<T> head;
    Node<T> tail;

    //constructor
    public OrderedList () {
        head = null;
        tail = null;
    }

    public void Add(T elem) throws Exception {
        Node<T> new_node = new Node<T>(elem);
        if (IsEmpty())
        {
            head = new_node;
            tail = head;
        }
        else
        {
            if (GetFirst().compareTo(elem)!=0){
                new_node.next = head;
                head.prev = new_node;
                head = new_node;
                return;
            }
            Node<T> temp = head;
            Node<T> prev_node = head;
            while (temp != null && temp.element.compareTo(elem)==0) {
                prev_node = temp;
                temp = temp.next;
            }
            if (temp != null) {
                new_node.next = temp;
                temp.prev = new_node;
            }
            new_node.prev = prev_node;
            prev_node.next = new_node;
        }
    }

    public T GetFirst() throws Exception {
        if (IsEmpty())
            throw new Exception ("List is empty");
        return head.element;
    }
    @Override
    public String toString() {
        Node<T> temp = head;
        String result = "";
        while (temp != null){
            result += " " + temp.element;
            temp = temp.next;
        }
        return result;
    }
    public Boolean IsEmpty()
    {
        return head == null || tail == null;
    }

}
