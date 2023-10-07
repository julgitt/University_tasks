from decimal import Decimal 

# FLOAT
def vat_invoice(_list):
    return sum(_list) * 0.23


def vat_receipt(_list):
    multiplied_list = [element * 0.23 for element in _list]
    return sum(multiplied_list)


# DECIMAL
def vat_invoice_decimal(_list):
    return sum(_list) * Decimal('0.23')


def vat_receipt_decimal(_list):
    multiplied_list = [element * Decimal('0.23') for element in _list]
    return sum(multiplied_list)


input_list = ['0.2', '0.1']
shopping_list = [float(x) for x in input_list]
shopping_list_double = [Decimal(x) for x in input_list]

print("For float: " + str(vat_invoice(shopping_list) == vat_receipt(shopping_list)))
print("For Decimal: " + str(vat_invoice_decimal(shopping_list_double) == vat_receipt_decimal(shopping_list_double)))