using System;
using System.Linq.Expressions;

public class Person
{
    public string Name { get; set; }
    public int Age { get; set; }
}

class Program
{
    static void Main(string[] args)
    {
        Person person = new Person();
        person.Age = 22;
        person.Name = "Julia";

        Expression<Func<int, int>> f = n => 4 * (7 + n);

        Expression<Func<int>> constantExpr = () => 42;
        Expression<Func<int, string>> conditionalExpr = n => n > 0 ? "Positive" : "Non-Positive";

        Expression<Func<Person, int>> memberExpr = p => p.Age;

        PrintExpressionVisitor v = new PrintExpressionVisitor();
        Console.WriteLine("\n");
        v.Visit(f);
        Console.WriteLine("\n");
        v.Visit(constantExpr);
        Console.WriteLine("\n");
        v.Visit(conditionalExpr);
        Console.WriteLine("\n");
        v.Visit(memberExpr);
        Console.WriteLine("\n");
        
        var compiledExpr = memberExpr.Compile();
        var result = compiledExpr(person);
        Console.WriteLine("Value: " + result);

        Console.ReadLine();
    }
}
public class PrintExpressionVisitor : ExpressionVisitor
{
    protected override Expression VisitBinary(BinaryExpression expression)
    {
        Console.WriteLine("{0} {1} {2}",
        expression.Left, expression.NodeType, expression.Right);
        return base.VisitBinary(expression);
    }
    protected override Expression VisitLambda<T>(Expression<T> expression)
    {
        Console.WriteLine("{0} -> {1}",
        expression.Parameters.Aggregate(string.Empty, (a, e) => a += e),
        expression.Body);
        return base.VisitLambda<T>(expression);
    }
    // dodane:
    protected override Expression VisitConstant(ConstantExpression expression)
    {
        Console.WriteLine("Constant: {0}", expression.Value);
        return base.VisitConstant(expression);
    }
    protected override Expression VisitConditional(ConditionalExpression expression)
    {
        Console.WriteLine("Conditional: {0} ? {1} : {2}",
            expression.Test, expression.IfTrue, expression.IfFalse);
        return base.VisitConditional(expression);
    }
    protected override Expression VisitMember(MemberExpression expression)
    {
        Console.WriteLine("Member Access: {0}", expression.Member.Name, expression.Member);
        return base.VisitMember(expression);
    }

}
