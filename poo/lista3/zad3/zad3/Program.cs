
class Program {
    public static void Main() {
        Old.Item[] items = new Old.Item[] {
            new Old.Item { Name = "Banany", Price =5 },
            new Old.Item { Name = "Jabłka", Price = 4 },
            new Old.Item { Name = "Marchewki", Price = 3 }
        };

        var register = new Old.CashRegister();
        register.PrintBill(items);


         New.CategorizedItem[] new_items = new New.CategorizedItem[] {
            new New.CategorizedItem { Name = "Banany", Price = 5, Category = "Owoc" },
            new New.CategorizedItem { Name = "Jabłka", Price = 4, Category = "Owoc"  },
            new New.CategorizedItem { Name = "Marchewki", Price = 3, Category = "Warzywo" }
        };

        var plRegister = new New.CashRegister(
            new New.PL_VATCalculator()
        );

        var duRegister  = new New.CashRegister(
            new New.DU_VATCalculator()
        );

        plRegister.PrintBill(new_items, new New.CategorySorter());

        duRegister.PrintBill(new_items, new New.AlphabeticSorter());

        Console.WriteLine("Cena: {0}\n", plRegister.CalculatePrice(new_items));

        Console.WriteLine("Cena: {0}\n", duRegister.CalculatePrice(new_items));
    }
     
}
