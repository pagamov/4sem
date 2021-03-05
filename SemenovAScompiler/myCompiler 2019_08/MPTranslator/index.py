# some code to understand problem
from copy import copy

class Tree:
    def __init__(self,word,SY_table):
        pass

class Vertex:
    def __init__(self,data,nterm,term):
        self.data = data
        self.nterm = nterm
        self.term = term
        self.child = []
    def log(self,dep):
        print('\t'*dep, self.data)
        for ch in self.child:
            ch.log(dep+1)
class SY_table:
    def __init__(self,alphabet,nonterm,term,rules,start):
        self.alphabet = alphabet
        self.nonterm = nonterm
        self.term = term
        self.rules = rules
        self.start = start
    def make_tree(self, word):
        print(word)
        i = 0
        self.root = Vertex(self.start,True,False)
        while i < len(word):
            i+=1 
    def log(self):
        print("tree")
        self.root.log(0)

# main segment
R1 = {'S':['0','A','S'],
      'A':['0','S','A'],
      'S':['1'],
      'A':['1']
     }
R2 = {'S':['S','A','a'],
      'A':['A','S','a'],
      'S':['b'],
      'A':['b']
     }

table = SY_table(['0','1'],['S', 'A'],['a','b'],[R1,R2],'S')
table.make_tree("00111")
