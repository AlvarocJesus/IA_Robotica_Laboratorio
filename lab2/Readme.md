# Atividade Laboratório 2

Considere o conhecimento sobre a familia Machado:

Pouco se sabe da história passada da família Machado. Existem alguns registros antigos que indicam que o casal Pedro e Antonia criou quatro filhos, o João, a Clara, o Francisco e a Ana. Que a Ana teve duas filhas, a Helena e a Joana, também parece ser verdade, segundo os mesmos registos. Além disso, o Mário é filho do João, pois muito se orgulha ele disso. Estranho também, foi constatar que o Carlos nasceu da relação entre a Helena, muito formosa, e o Mário. Francisco não teve filhos, mas casou-se com Milene e Clara era mãe de Pietro a Enzo, que casaram com as irmãs Francisca e Antonia

Faça um programa em PROLOG capaz de identificar as seguintes relações de parentesco na familia: avó, avô, tio, tia, primo, prima, descedente, ascendente.

## Ferramenta para usar PROLOG online

[Prolog online](http://swish.swi-prolog.org/)

## Exemplos de codigo

[Falam a mesma lingua](./exemplo.pro) <br>
[Arvore Genealogica](./exeArvoreGenealogica.pro)

## Exemplo com Python

[Github do exemplo](https://github.com/ArtificialIntelligenceToolkit/)

```python
# pip install aima3
from aima3.logic import expr, FolKB, fol_fc_ask

clauses = []

clauses.append(expr("Progenitor(Maria, Joao)"))
clauses. append(expr("Progenitor(x,y) == > Pessoa(x)"))
clauses.append(expr("Progenitor(x,y) == > Pessoa(y)"))
clauses.append(expr("Sexo(Ana,Feminino)"))
clauses.append(expr("Progenitor(x,y) & Sexo(x,Feminino) == > Mae(x,y) "))
clauses. append(expr("Progenitor(x,y) & Progenitor(x,z) & Sexo(y,Masculino) \
== > Irmao(y,z)"))

Genealogia = FolKB(clauses)

perguntas = ["Sexo(x, Masculino)",
"Sexo(Maria,x)",
"Irmao(x, Ana)",
"Irma(x, Joao)",
"Descendente(x,Maria)",
"Descendente(Joao,x)",
"Pessoa(x)",
"Mae(x,y)",
"Pai(x,y)"]

for i in perguntas:
resposta = fol_fc_ask(Genealogia, expr(i))
print("%s -> %s" %(i, (list(resposta))))
```

## Resolucao do lab

casal -> Pedro e Antonia <br>
1 filho -> joao
2 filho -> clara
3 filho -> francisco
4 filho -> ana

Ana -> 2 filhos <br>
1 filho - Helena
2 filho - joana

Joao -> 1 filho <br>
1 filho -> Mario

casal -> Mario e Helena <br>
1 filho -> Carlos

casal -> Francisco e Milena <br>
0 filho

Clara -> 2 filho <br>
1 filho -> Pietro
2 filho -> enzo

casal -> Pietro e Francisco

casal -> Enzo e Antonia

Funcoes a fazer

- [x] avó
- [x] avô
- [x] tio
- [x] tia
- [x] primo
- [x] prima
- [x] descendente
- [x] ascendente
