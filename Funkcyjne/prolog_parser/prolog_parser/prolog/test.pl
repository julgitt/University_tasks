animal(X) :- cat(X).
parent(jurek, julia).
parent(jola, jola).

children(X,Y) :- parent(Y, X).
human(julia).
human(jola).
cat(jola).
cat(julia).
human(tom).
cat(tom).
dog(jerry).
animal(X) :- dog(X).
furras(X) :- animal(X), human(X).

furrasy(X,Y) :- children(X,Y), furras(X).