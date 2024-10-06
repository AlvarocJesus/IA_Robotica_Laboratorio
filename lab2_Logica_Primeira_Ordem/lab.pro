/* Notas sobre as relacoes
casal -> Pedro e Antonia
1 filho -> joao
2 filho -> clara
3 filho -> francisco
4 filho -> ana

Ana -> 2 filhos
1 filho - Helena
2 filho - joana

Joao -> 1 filho
1 filho -> Mario

casal -> Mario e Helena
1 filho -> Carlos

casal -> Francisco e Milena
0 filho

Clara -> 2 filho
1 filho -> Pietro
2 filho -> enzo

casal -> Pietro e Francisca

casal -> Enzo e Antonia
*/

progenitor(pedro,joao).
progenitor(pedro,clara).
progenitor(pedro,francisco).
progenitor(pedro,ana).
progenitor(antonia,joao).
progenitor(antonia,clara).
progenitor(antonia,francisco).
progenitor(antonia,ana).

progenitor(ana,helena).
progenitor(ana,joana).

progenitor(joao,mario).

progenitor(helena,carlos).
progenitor(mario,carlos).

progenitor(clara,pietro).
progenitor(clara,enzo).

sexo(ana,feminino).
sexo(maria,feminino).
sexo(joana,feminino).
sexo(helena,feminino).
sexo(clara,feminino).
sexo(antonia,feminino).
sexo(mario,masculino).
sexo(joao,masculino).
sexo(jose,masculino).
sexo(carlos,masculino).
sexo(pedro,masculino).
sexo(francisco,masculino).
sexo(pietro,masculino).
sexo(enzo,masculino).

irma(X,Y) :- progenitor(A,X), progenitor(A,Y), X\==Y, sexo(X,feminino).
irmao(X,Y) :- progenitor(A,X), progenitor(A,Y), X\==Y, sexo(X,masculino).

descendente(X,Y) :- progenitor(X,Y).
descendente(X,Y) :- progenitor(X,A), descendente(A,Y).

avô(X,Y) :- progenitor(X,A), progenitor(A,Y), sexo(X,masculino).
avó(X,Y) :- progenitor(X,A), progenitor(A,Y), sexo(X,feminino).

ascendente(X,Y) :- progenitor(X,Y).
ascendente(X,Y) :- progenitor(A,X), ascendente(Y,A).

tio(X,Y) :- progenitor(A, Y), irmao(A,X), X\==Y, sexo(X,masculino).
tio(X,Y) :- progenitor(A, Y), irma(A,X), X\==Y, sexo(X,masculino).
tia(X,Y) :- progenitor(A,Y), irma(A,X), X\==Y, sexo(X,feminino).
tia(X,Y) :- progenitor(A,Y), irmao(A,X), X\==Y, sexo(X,feminino).

primo(X,Y) :- progenitor(A,X), (irmao(A,B) ; irma(A,B)), progenitor(B,Y), sexo(X,masculino).
prima(X,Y) :- progenitor(A,X), (irmao(A,B) ; irma(A,B)), progenitor(B,Y), sexo(X,feminino).
