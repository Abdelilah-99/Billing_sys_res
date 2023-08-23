#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct items
{
	char item[20];
	float price;
	int qty;
};
struct order
{
	char customer[50];
	char date[50];
	int numOfItem;
	struct items itm[50];
};
void generateBillHeader(char name[50], char date[30])
{
	printf("\n\n");
	printf("\t    BCH. Restaurant");
	printf("\n\t   -----------------");
	printf("\nDate: %s", date);
	printf("\nInvoice To: %s", name);
	printf("\n");
	printf("---------------------------------------\n");
	printf("Items\t\t");
	printf("Qty\t\t");
	printf("Total\t\t");
	printf("\n---------------------------------------");
	printf("\n\n");
}
void generateBillBody(char item[30], int qty, float price)
{
	printf("%s\t\t", item);
	printf("%d\t\t", qty);
	printf("%.2f\t\t", qty * price);
	printf("\n");
}

void generateBillFooter(float total)
{
	printf("\n");
	float dis = 0.1 * total;
	float netTotal = total - dis;
	printf("---------------------------------------\n");
	printf("Sub Total\t\t\t%.2f", total);
	printf("\nDiscount @10%s\t\t\t%.2f", "%", dis);
	printf("\n\t\t\t\t-------");
	printf("\nNet Total\t\t\t%.2f", netTotal);
	printf("\n---------------------------------------");
	printf("\nTotal\t\t\t%.2f", netTotal);
	printf("\n---------------------------------------\n");
}
int main()
{
	char savebill = 'y', name[50], flag = 'y';
	float total;
	int opt, n, valid = 0;
	FILE *fp;
	struct order ord;

	while (flag == 'y')
	{
		printf("\t\t==============BCH. RESTAURANT==============");
		printf("\n\n1-Generate Invoice");
		printf("\n2-Show all Invoices");
		printf("\n3-Search Invoice");
		printf("\n4-Exit");

		printf("\n\nPlease select option: ");
		scanf("%d", &opt);
		fgetc(stdin);
		switch (opt)
		{
		case 1:
			system("clear");
			printf("\nPlease enter the name of the customer: ");
			fgets(ord.customer, 50, stdin);
			ord.customer[strlen(ord.customer) - 1] = 0;
			strcpy(ord.date, __DATE__);
			printf("\nPlease the number of item: ");
			scanf("%d", &n);
			ord.numOfItem = n;
			for (int i = 0; i < n; i++)
			{
				fgetc(stdin);
				printf("\n\n");
				printf("Please enter the item %d : ", i + 1);
				fgets(ord.itm[i].item, 10, stdin);
				ord.itm[i].item[(strlen(ord.itm[i].item)) - 1] = 0;
				printf("Please enter the quantity: ");
				scanf("%d", &ord.itm[i].qty);
				printf("Please enter the price: ");
				scanf("%f", &ord.itm[i].price);
				total += ord.itm[i].price * ord.itm[i].qty;
			}
			generateBillHeader(ord.customer, ord.date);
			for (int i = 0; i < ord.numOfItem; i++)
			{
				generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
			}
			generateBillFooter(total);
			printf("\nDo you want to save the order [Y/N] : ");
			scanf("%s", &savebill);
			if (savebill == 'y')
			{
				fp = fopen("RestaurantBill.txt", "a+");
				fwrite(&ord, sizeof(struct order), 1, fp);
				if (fwrite != 0)
					printf("\nSuccessfully saved");
				else
					printf("\nError saving");
				fclose(fp);
			}
			break;
		case 2:
			system("clear");
			fp = fopen("RestaurantBill.txt", "r");
			printf("\n==============Your Prv Order==============");
			while (fread(&ord, sizeof(struct order), 1, fp))
			{
				float T = 0;
				generateBillHeader(ord.customer, ord.date);
				for (int i = 0; i < ord.numOfItem; i++)
				{
					generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
					T += ord.itm[i].qty * ord.itm[i].price;
				}
				generateBillFooter(T);
			}
			fclose(fp);
			break;
		case 3:
			printf("\nEnter the name you looking for : ");
			fgets(name, 50, stdin);
			name[strlen(name) - 1] = 0;
			system("clear");
			fp = fopen("RestaurantBill.txt", "r");
			while (fread(&ord, sizeof(struct order), 1, fp))
			{
				float T = 0;
				if (!strcmp(ord.customer, name))
				{
					printf("\n============== %s's Order ==============", name);
					generateBillHeader(ord.customer, ord.date);
					for (int i = 0; i < ord.numOfItem; i++)
					{
						generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
						T += ord.itm[i].qty * ord.itm[i].price;
					}
					generateBillFooter(T);
					valid = 1;
				}
			}
			if (!valid)
				printf("\n%s not found", name);

			fclose(fp);
			break;
		case 4:
			printf("Exiting...\n");
			exit(0);
			break;
		default:
			printf("Invalide option: %d", opt);
			break;
		}
		printf("\nDo you want to add an other item [Y/N]: ");
		scanf("%s", &flag);
	}
	printf("Exiting...");
	printf("\n");
	return 0;
}