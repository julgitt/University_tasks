mother(ania, basia).
mother(basia, piotr).
father(olek, ania).
father(olek, kacper).
parent(X, Y) :- mother(X, Y).
parent(X, Y) :- father(X, Y).
ancestor(X, Y) :- parent(X, Y).
ancestor(X, Y) :- parent(X, Z), ancestor(Z, Y).