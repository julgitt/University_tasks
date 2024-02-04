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

    def __mul__(self, other):
        return And(self, other)

    def tautology(self, variables):
        permutations = itertools.product([False, True], repeat=len(variables))
        for perm in permutations:
            var_assignment = dict(zip(variables, perm))
            if not self.eval(var_assignment):
                return False
        return True


    def simplify(self):
       pass
    


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
    
    def simplify(self):
        return self 
    

class Constant(Formula):
    def __init__(self, value):
        if type(value) != bool:
            raise typeException("boolean")
        self.value = value

    def __str__(self):
        return str(self.value)

    def eval(self, variables):
        return self.value
    
    def simplify(self):
        return self
         

class Not(Formula):
    def __init__(self, expression):
        self.expression = expression

    def __str__(self):
        return '¬' + str(self.expression)
    
    def eval(self, variables):
        return not self.expression.eval(variables)
    
    def simplify(self):
        var = self.expression.simplify()
        if isinstance(var, Variable):
            return Not(var)
        if isinstance(var, Constant):
            return Constant(not var.value)
        if isinstance(var, Not):
            return var
        return Not(var)
      
         


class And(Formula):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def __str__(self):
        return f"( {str(self.left)}  ∧  {str(self.right)} )"
    
    def eval(self, variables):
        return self.left.eval(variables) and self.right.eval(variables)
    
    def simplify(self):
        if isinstance(self.left, Constant):
            if self.left.value == False:
                return self.left
            return self.right.simplify()
        elif isinstance(self.right, Constant):
            if self.right.value == False:
                return self.right
            return self.left.simplify()
        else:
            return self.right.simplify().__mul__(self.left.simplify())
              
    

class Or(Formula):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def __str__(self):
        return f"( {str(self.left)}  v  {str(self.right)} )"
    
    def eval(self, variables):
        return self.left.eval(variables) or self.right.eval(variables)
    
    def simplify(self):
        if isinstance(self.left, Constant):
            if self.left.value == True:
                return self.left
            return self.right.simplify()
        elif isinstance(self.right, Constant):
            if self.left.value == True:
                return self.right
            return self.left.simplify()
        else:
            return self.left.simplify().__add__ (self.right.simplify())
         
    

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



y = And(Constant(True), And(Constant(True),  Not(Constant(False))))
x = And(Constant(True), And(Constant(True),  Not(Variable('x'))))
f = Or(Constant(True), And(Constant(True), Not(Variable('x'))))
val = f.eval({'x' : True})
print(str(f))
print(f"for: {str({'x' : True})}, in: {str(f)}, val: {str(val)}")

taut = Or(Variable('p'), Not(Variable('p')))
if taut.tautology(['p']):
    print(f"Formula:  {str(taut)} is tautology.")
else:
    print(f"Formula: {str(taut)} is not tautology.")

print(f"for: {str(x)}, simplify():  {str(x.simplify())}")
print(f"for: {str(y)}, simplify():  {str(y.simplify())}")
print(f"for: {str(f)}, simplify():  {str(f.simplify())}")
