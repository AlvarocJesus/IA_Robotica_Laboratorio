a(angela,portugues).
a(jose,ingles).
a(viola,portugues).
a(viola,espanhol).
a(carlos,ingles).
a(sonia,ingles).
a(wilson,ingles).
am_a_mesma_lingua(X,Y) :- a(X,Z), a(Y,Z), not(X=Y).