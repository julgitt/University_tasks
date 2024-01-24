animal(X) :- cat(X).
parent(jola, jola).
parent(jurek, julia).

children(X,Y) :- parent(Y, X).
human(tom).
cat(tom).
dog(jerry).
animal(X) :- dog(X).
furras(X) :- animal(X), human(X).