import itertools

class Formula:
    def __init__(self):
        pass

    def eval(self, variables):
        pass
    
    def __str__(self):
        pass
    
    def __add__(self, other):
        return Or(self, other)

    def __mul__(self, f1, f2):
        return And(f1, f2)

    def tautology(self, variables):
        permutations = itertools.product([False, True], repeat=len(variables))
        for perm in permutations:
            var_assignment = dict(zip(variables, perm))
            if not self.eval(var_assignment):
                return False
        return True


    def simplify(self):
        if isinstance(self, Not):
            return Not(self.f.simplify())
    
        if isinstance(self, Or):
            if self.left == Constant(True) or self.right == Constant(True):
                return Constant(True)
            if self.left == Constant(False):
                return self.right.simplify()
            if self.right == Constant(False):
                return self.left.simplify()
    
        if isinstance(self, And):
            if self.left == Constant(False) or self.right == Constant(False):
                return Constant(False)
            if self.left == Constant(True):
                return self.right.simplify()
            if self.right == Constant(True):
                return self.left.simplify()
    
        return self

class Variable(Formula):
    def __init__(self, name):
        self.name = name

    def eval(self, variables):
        if self.name not in variables:
            raise noValException(self.name)
        return variables[self.name]

    def __str__(self):
        return self.name
    
    def tautology(self):
        return False
    

class Constant(Formula):
    def __init__(self, value):
        if type(value) != bool:
            raise typeException("boolean")
        self.value = value

    def __str__(self):
        return str(self.value)

    def eval(self, variables):
        return self.value
    

class Not(Formula):
    def __init__(self, f):
        self.f = f

    def __str__(self):
        return '¬' + str(self.f)
    
    def eval(self, variables):
        return not self.f.eval(variables)


class And(Formula):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def __str__(self):
        return f"( {str(self.left)}  ∧  {str(self.right)} )"
    
    def eval(self, zmienne):
        return self.left.eval(zmienne) and self.right.eval(zmienne)
    

class Or(Formula):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def __str__(self):
        return f"( {str(self.left)}  v  {str(self.right)} )"
    
    def eval(self, zmienne):
        return self.left.eval(zmienne) or self.right.eval(zmienne)
    

class typeException(Exception):
    def __init__(self, expected_type):
        self.expected_type = expected_type

    def __str__(self):
        return f"Value must be a {self.expected_type}"


class noValException(Exception):
    def __init__(self, variable):
        self.variable = variable

    def __str__(self):
        return f"No value for variable {self.variable}"




f = Or(Constant(False), And(Constant(True), Not(Variable('x'))))
val = f.eval({'x' : True})
print(str(f))
print(f"for: {str({'x' : True})}, in: {str(f)}, val: {str(val)}")

taut = Or(Variable('p'), Not(Variable('p')))
if taut.tautology(['p']):
    print(f"Formula:  {str(taut)} is tautology.")
else:
    print(f"Formula: {str(taut)} is not tautology.")

print(f"for: {str(f)}, simplify():  {str(f.simplify())}")
