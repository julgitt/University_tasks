animal(X) :- cat(X).
parent(malgosia, stasia).
parent(kasia, kasia).

children(X,Y) :- parent(Y, X).
human(stasia).
human(kasia).
cat(kasia).
cat(stasia).
human(tom).
cat(tom).
dog(jerry).
animal(X) :- dog(X).
furras(X) :- animal(X), human(X).

furrasy(X,Y) :- children(X,Y), furras(X).