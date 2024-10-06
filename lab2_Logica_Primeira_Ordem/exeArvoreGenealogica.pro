progenitor(maria,joao).
progenitor(jose,joao).
progenitor(maria,ana).
progenitor(jose,ana).
progenitor(jose,mario).
progenitor(ana,helena).
progenitor(ana,joana).
progenitor(helena,carlos).
progenitor(mario,carlos).
sexo(ana,feminino).
sexo(maria,feminino).
sexo(joana,feminino).
sexo(helena,feminino).
sexo(mario,masculino).
sexo(joao,masculino).
sexo(jose,masculino).
sexo(carlos,masculino).

irma(X,Y) :- progenitor(A,X), progenitor(A,Y), X\==Y, sexo(X,feminino).
irmao(X,Y) :- progenitor(A,X), progenitor(A,Y), X\==Y, sexo(X,masculino).

descendente(X,Y) :- progenitor(X,Y).
descendente(X,Y) :- progenitor(X,A), descendente(A,Y).

avo(X,Y) :- progenitor(X,A), progenitor(A,Y), sexo(X,masculino).
