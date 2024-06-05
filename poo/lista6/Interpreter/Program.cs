public class Context
{
    private Dictionary<string, bool> _localVariables =
        new Dictionary<string, bool>();

    public bool GetValue(string VariableName) 
    {
        if (_localVariables.ContainsKey(VariableName))
        {
            return _localVariables[VariableName];
        }
        else
        {
            throw new ArgumentException();
        }
    }

    public void SetValue(string VariableName, bool Value) 
    {
        if (_localVariables.ContainsKey(VariableName))
        {
            _localVariables.Remove(VariableName);
        }
        _localVariables.Add(VariableName, Value);
    }
}

public abstract class AbstractExpression
{
    public abstract bool Interpret(Context context);
}

public class ConstExpression : AbstractExpression 
{
    public bool Value;

    public ConstExpression(bool Value)
    { 
        this.Value = Value; 
    } 

    public override bool Interpret(Context context)
    {
        return Value;
    }
}

public class VariableExpression : AbstractExpression
{
    public string VariableName;

    public VariableExpression(string VariableName)
    {
        this.VariableName = VariableName;
    }

    public override bool Interpret(Context context)
    {
        return context.GetValue(this.VariableName);
    }
}

public class BinaryExpression : AbstractExpression 
{
    public AbstractExpression Left;
    public AbstractExpression Right;
    public string Operator;

    public BinaryExpression(AbstractExpression Left, AbstractExpression Right, string   Operator)
    {
        this.Left = Left;
        this.Right = Right; 
        this.Operator = Operator;
    }

    public override bool Interpret(Context context)
    {
        switch(this.Operator)
        {
            case "|":
                return 
                    this.Left.Interpret(context) | 
                    this.Right.Interpret(context);
            case "&":
                return
                   this.Left.Interpret(context) &
                   this.Right.Interpret(context);
            default:
                throw new ArgumentException();
        }
    }
}

public class UnaryExpression : AbstractExpression 
{
    public AbstractExpression Exp;
    public string Operator;

    public UnaryExpression(AbstractExpression Exp, string Operator)
    {
        this.Exp = Exp;
        this.Operator = Operator;
    }

    public override bool Interpret(Context context)
    {
        switch (this.Operator)
        {
            case "!":
                return
                    !this.Exp.Interpret(context);
            default:
                throw new ArgumentException();
        }
    }
}

public class Program
{
    public static void Main()
    {
        // klient
        Context ctx = new Context();
        ctx.SetValue("x", false);
        ctx.SetValue("y", true);
        AbstractExpression exp = new BinaryExpression(
            new UnaryExpression( new ConstExpression(true), "!"),
            new BinaryExpression(new VariableExpression("x"), new VariableExpression("y"), "&"),
            "|"
            );
        bool Value = exp.Interpret(ctx);
        Console.WriteLine(Value);
    }
}
