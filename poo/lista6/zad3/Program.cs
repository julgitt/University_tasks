public class MainClass
{
    public static void Main()
    {
        Tree root = new TreeNode()
        {
            Left = new TreeNode()
            {
                Left = new TreeNode() 
                {
                    Left = new TreeNode()
                    {
                        Left = new TreeLeaf() { Value = 4 },
                        Right = new TreeLeaf() { Value = 4 }
                    },
                    Right = new TreeLeaf() { Value = 3 }
                },
                Right = new TreeLeaf() { Value = 2 }
            },
            Right = new TreeLeaf() { Value = 1 }
        };
        DepthTreeVisitor visitor = new DepthTreeVisitor();
        visitor.Visit(root);

        Console.WriteLine("Głębokość drzewa to {0}", visitor.Depth);
        Console.ReadLine();
    }
}

public abstract class Tree
{
}

public class TreeNode : Tree
{
    public Tree Left { get; set; }
    public Tree Right { get; set; }
}

public class TreeLeaf : Tree
{
    public int Value { get; set; }
}

public abstract class TreeVisitor
{
    // ta metoda nie jest potrzebna ale ułatwia korzystanie z Visitora
    public void Visit(Tree tree)
    {
        if (tree is TreeNode)
            this.VisitNode((TreeNode)tree);
        if (tree is TreeLeaf)
            this.VisitLeaf((TreeLeaf)tree);
    }

    public virtual void VisitNode(TreeNode node)
    {
        // tu wiedza o odwiedzaniu struktury
        if (node != null)
        {
            this.Visit(node.Left);
            this.Visit(node.Right);
        }
    }

    public virtual void VisitLeaf(TreeLeaf leaf)
    {
    }
}
public class DepthTreeVisitor : TreeVisitor
{
    private int currentDepth;
    public int Depth;

    public DepthTreeVisitor()
    {
        this.currentDepth = 0;
        this.Depth = 0;
    }

    public override void VisitNode(TreeNode node)
    {
        this.currentDepth++;
        base.VisitNode(node);
        this.currentDepth--;
    }

    public override void VisitLeaf(TreeLeaf leaf)
    {
        this.Depth = Math.Max(Depth, currentDepth);
    }
}