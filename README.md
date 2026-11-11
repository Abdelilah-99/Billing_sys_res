# Restaurant billing system in C

A terminal application that generates **restaurant invoices** for "BCH. Restaurant".
Bills can be saved to a file and listed or searched later.

## Features
- Menu-driven interface: generate an invoice, show all invoices, search an invoice by customer name
- Each invoice has a customer name, date, time and up to 50 items (name, quantity, unit price)
- Computes the subtotal, a 10% discount and the net total
- Saves invoices to `RestaurantBill.txt` (binary records with `fwrite` / `fread`)

## Build and run
```bash
gcc 0_0X_BILLING_SYS.c -o billing
./billing
```

**Stack:** C · structs · file I/O
