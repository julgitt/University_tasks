// Kod po zmianach:

using System;

namespace Old {
    public class TaxCalculator {
        public Decimal CalculateTax(Decimal price) { 
            return price * 0.22m;
        }
    }

    public class Item {
        public Decimal Price { get; set; }
        public string Name { get; set; }
    }

    public class CashRegister {
        public TaxCalculator taxCalc = new TaxCalculator();

        public Decimal CalculatePrice(Item[] items) {
            Decimal _price = 0;
            foreach (var item in items) {
                _price += item.Price + taxCalc.CalculateTax(item.Price);
            }
            return _price;
        }

        public void PrintBill(Item[] items) {
           foreach (var item in items) {
                Console.WriteLine("towar {0} : cena {1} + podatek {2}\n",
                    item.Name, item.Price, taxCalc.CalculateTax(item.Price));
            }
        }
    }
}
