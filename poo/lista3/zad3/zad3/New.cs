using System;
using System.Collections.Generic;
using System.Linq;

namespace New {
    public interface ITaxCalculator {
        Decimal CalculateTax(Decimal price);
    }

    public abstract class Item {
        public Decimal Price {get; set;}
        public string Name   {get; set;}
    }

    public interface IItemSorter<I> where I : Item {
        IEnumerable<I> SortItems(IEnumerable<I> items);
    }

    public class CashRegister {
        private ITaxCalculator taxCalc;

        public CashRegister(ITaxCalculator calc) {
            this.taxCalc = calc;
        }

        public Decimal CalculatePrice(IEnumerable<Item> items) {
            Decimal _price = 0;
            foreach (var item in items) {
                _price += item.Price + taxCalc.CalculateTax(item.Price);
            }
            return _price;
        }

        public void PrintBill<I>(IEnumerable<I> items, IItemSorter<I> sorter) where I : Item {
            foreach (var item in sorter.SortItems(items)) {
                Console.WriteLine("towar {0} : cena {1} + podatek {2}\n",
                    item.Name, item.Price, taxCalc.CalculateTax(item.Price));
            }
        }
    }

    //_____________________________________________________________

    public class PL_VATCalculator : ITaxCalculator {
        public Decimal CalculateTax(Decimal price) {
            return price * 0.23m;
        }
    }

    public class DU_VATCalculator : ITaxCalculator {
        public Decimal CalculateTax(Decimal price) {
            return price * 0.19m;
        }
    }

    public class CategorizedItem : Item {
        public string Category {get; set;}
    }

    public class CategorySorter : IItemSorter<CategorizedItem> {
        public IEnumerable<CategorizedItem> SortItems(
            IEnumerable<CategorizedItem> items) {
            return items.OrderBy(item => item.Category);
        }
    }

    public class AlphabeticSorter : IItemSorter<Item> {
        public IEnumerable<Item> SortItems(IEnumerable<Item> items) {
            return items.OrderBy(item => item.Name);
        }
    }
}
