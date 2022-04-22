package com.company;

public abstract class Cards implements Comparable<Cards> {

    String Figure;
    int value;

    public int compareTo(Cards other) {
        try {
            if (other.value > value){
                return 1;
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }
    @Override
    public String toString() {
        return this.Figure;
    }
}
