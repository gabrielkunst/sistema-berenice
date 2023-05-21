#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PRODUCTS 100

struct Product {
    int id;
    char name[50];
    float price;
};

int main() {
    struct Product products[MAX_PRODUCTS];
    int numProducts;

    // Read the list of products
    printf("Enter the number of products: ");
    scanf("%d", &numProducts);

    for (int i = 0; i < numProducts; i++) {
        printf("Enter details of product %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &products[i].id);
        printf("Name: ");
        scanf("%s", products[i].name);
        printf("Price: ");
        scanf("%f", &products[i].price);
    }

    // Get the current date and time
    time_t now = time(NULL);
    struct tm *localTime = localtime(&now);

    // Create the filename based on the current date and time
    char filename[100];
    sprintf(filename, "%d-%02d-%02d-%02d-%02d-%02d.txt",
            localTime->tm_year + 1900, localTime->tm_mon + 1,
            localTime->tm_mday, localTime->tm_hour,
            localTime->tm_min, localTime->tm_sec);

    // Open the file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Write the list of products to the file
    for (int i = 0; i < numProducts; i++) {
        fprintf(file, "Product %d:\n", i + 1);
        fprintf(file, "ID: %d\n", products[i].id);
        fprintf(file, "Name: %s\n", products[i].name);
        fprintf(file, "Price: %.2f\n", products[i].price);
        fprintf(file, "\n");
    }

    // Close the file
    fclose(file);

    printf("Data written to file: %s\n", filename);

    return 0;
}
