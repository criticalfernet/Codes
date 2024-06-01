from typing import Callable

class Term():
    def __init__(self, coeff:float, power:float):
        self.coeff = coeff
        self.power = power
        

def factorial(num:int) -> int:
    out:int =1
    for i in range(1,num+1):
        out *= i
    return out
 
def product(func:Callable[[int],float],b:int,a:int=0) -> float:
    out:float=1
    for i in range(a,b+1):
        i = int(i)
        out *= func(i)
    return out
    
def integrate(term:Term) -> Term:
    return Term(term.coeff/(term.power+1), term.power+1)

def exponent(base:float, power:float) -> float:
    out:float = pow(base,power)
    return out

def definateIntegrate(term:Term,a:float,b:float) -> float:
    integrated:Term = integrate(term)
    coeff:float = integrated.coeff
    power:float = integrated.power
    out:float = coeff * (exponent(b,power) - exponent(a,power)) 
    return out

def customfunc(x:int) -> float: return 0.5-float(x)

def makecoeff(index:int) -> float:
    return product(customfunc,index-1)/factorial(index)

def createterm(index:int,basepow:float=1,neg:bool=False) -> Term:
    return Term(
        makecoeff(index) * (1 - (index % 2)*2*neg)
        ,basepow*index)

# debug

iterations:int = 150

summition:float = 0
for i in range(iterations):
    summition+= definateIntegrate(createterm(i,2,True),0,0.5)

SQRT3:float = 1.732050807568877293527446

extraTerm:float  = SQRT3/8
print(12*(summition-extraTerm))

# integrate(-circle-)|0->0.5 = [ PI/12 - root(3)/8 ]    


# sqrt of 3 = 2* sqrt(1-1/4)




