package com.company;

public class Main {

    public static void main(String[] args) throws Exception {
	    Cards king = new King();
        Cards queen = new Queen();
        Cards jack = new Jack();
        Cards jack2 = new Jack();
        Cards ace = new Ace();
        Cards ace2 = new Ace();
        OrderedList<Cards> cards= new OrderedList<>();
        cards.Add(king);
        cards.Add(queen);
        cards.Add(ace2);
        cards.Add(jack);
        cards.Add(ace);
        cards.Add(jack);
        System.out.println(cards);
    }
}
