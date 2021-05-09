#include <stdio.h>
#include <string.h>

//print the rows, cols, cells in the vending machine
void print_vending_machine(int rows, int cols, int cells, 
    int arr3d[rows][cols][cells])
{
    int slotNumber = 0;
    for (int i = 0; i < rows; i++)
    {   
        printf("%*s", 1, " ");
        for (int j = 0; j < cols; j++)
        {
            printf("<%d>", ++slotNumber);
            printf("%*s", 11, " ");
        }
        printf("\n");

        for (int j = 0; j < cols; j++)
        {            
            for (int k = 0; k < cells; k++)
            {
                printf(" %2d,", arr3d[i][j][k]);
            }
            printf("\b");
            printf("%*s", 3, " ");
        }
        printf("\n");
    }
}


//zero for every element in the array
//i.e. fill empty cells with zeros
void zero_vending_machine(int rows, int cols, int cells, 
    int arr3d[rows][cols][cells])
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            for (int k = 0; k < cells; k++)
                arr3d[i][j][k] = 0;
}


//checks if vending machine is empty
int is_empty_vending_machine(int rows, int cols, int cells, 
    int arr3d[rows][cols][cells])
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            for (int k = 0; k < cells; k++)
                if (arr3d[i][j][k] != 0)
                    return 0;
    return 1;
}

//copy float arrays from src to dest
void copy_float_array(float *src, float *dest, int len)
{
    for (int i = 0; i < len; i++)
    {
        dest[i] = src[i];
    }
}


//find index of given element in float array
int index_of_f(float *arr, int len, float value)
{
    for (int i = 0; i< len; i++)
    {
        if (value == arr[i])
        {
            return i;
        }
    }

    return -1;
}


//find index of given element in int array
int index_of_i(int *arr, int len, int value)
{
    for (int i = 0; i< len; i++)
    {
        if (value == arr[i])
        {
            return i;
        }
    }

    return -1;
}


//sort weights array by descending
void sort_by_weight(float *weights, int len, int *switchArr)
{
    //need to make a copy of unsorted weights
    //to create switchArr
    float copy[len];
    copy_float_array(weights, copy, len);


    //selection sort
    for (int i = 0; i < len; i++)
    {
        float max = weights[i]; 
        int index = i;

        for (int j = i+1; j < len; j++) 
        {
            if (max < weights[j])
            {
                max = weights[j];
                index = j;
            }    
        }

        weights[index] = weights[i];
        weights[i] = max;
    }


    //show difference in indexes after sort
    //in switchArr
    for (int i = 0; i< len; i++)
    {
        switchArr[index_of_f(weights, len, copy[i])] = i;
    }
}


int main()
{
    //define rows, cols, cells of the machine
    int rows;       //x
    int cols;       //y
    int cells = 3;  //z
    do
    {
        printf("Rows: ");
        scanf("%d", &rows);

        if (rows <= 0)
            printf("Rows can't be negative or zero!\n");

    } while (rows <= 0);

    do
    {
        printf("Cols: ");
        scanf("%d", &cols);

         if (cols <= 0)
            printf("Cols can't be negative or zero!\n");

    } while (cols <= 0);
    

    int capacity = rows*cols*cells;
    printf("Vending Machine Capacity: %d products\n", capacity);


    //init vending machine && fill empty cells with zeros
    int vendMachine[cols][rows][cells];
    zero_vending_machine(rows, cols, cells, vendMachine);
    

    //init helping structures
    char  foodsNames[capacity][100], drinksNames[capacity][100];
    float foodsWeights[capacity],    drinksWeights[capacity];
    float foodsPrices[capacity],     drinksPrices[capacity];
    int   foodsAmounts[capacity],    drinksAmounts[capacity];
    int   foodProducts = 0,          drinkProducts = 0;
    

    //input drinks amount
    do
    {
        printf("\nDrink Brands (Number): ");
        scanf("%d", &drinkProducts);

        if (drinkProducts < 0)
            printf("Value can't be negative!\n");

    } while (drinkProducts < 0);


    //the drinks themselves
    for (int i = 0; i < drinkProducts; i++)
    {
        char tempName[100];
        float tempWeight;
        float tempPrice;
        int tempAmount;
        
        printf(" drink brand #%d\n", i + 1);
        printf(" name / liters / price / amount: "); 
        scanf("%s %f %f %d", //name separator is "-"
                 tempName,  
                &tempWeight, 
                &tempPrice, 
                &tempAmount);
        
        if (tempAmount <= 0 || tempPrice <= 0 || tempWeight <= 0)
        {
            printf("Values can't be negative or zero!\n");
            i--;
            continue;
        }

        strcpy(drinksNames[i], tempName);
        drinksWeights[i] = tempWeight;
        drinksPrices[i] = tempPrice;
        drinksAmounts[i] = tempAmount;
    }


    //input foods amount
    do
    {
        printf("\nFood Brands (Number): ");
        scanf("%d", &foodProducts);

        if (foodProducts < 0)
            printf("Value can't be negative!\n");

    } while (foodProducts < 0);
    
        

    //the foods themselves
    for (int i = 0; i < foodProducts; i++)
    {
        char tempName[100];
        float tempWeight;
        float tempPrice;
        int tempAmount;
        
        printf(" food brand #%d\n", i + 1);
        printf(" name / weight / price / amount: "); 
        scanf("%s %f %f %d", //name separator is "-"
                 tempName,  
                &tempWeight, 
                &tempPrice, 
                &tempAmount);
        
        if (tempAmount <= 0 || tempPrice <= 0 || tempWeight <= 0)
        {
            printf("Values can't be negative or zero!\n");
            i--;
            continue;
        }

        strcpy(foodsNames[i], tempName);
        foodsWeights[i] = tempWeight;
        foodsPrices[i] = tempPrice;
        foodsAmounts[i] = tempAmount;
    }


    //helping structure to handle data after weights sort;
    //switchArr contains the indexing diffenrence between
    //unsorted and sorted state
    int switchArr[capacity];
    if (foodProducts > 0)
    {
        sort_by_weight(foodsWeights, foodProducts, switchArr);
    }

    
   /*
    *    1, 2, 3 - id of drink > 0
	*    -1, -2, -3 - id of food < 0
	*    0 - empty cell
    */
    //THE FILLING PROCESS
	//fills form the bottom to the top;
    //first are drinks in the order they were typed in,
    //then are foods ordered by weight;
    //!every slot (3 cells) has 1 type of product;
    int drinksIndex = 0;
    int foodsIndex = 0;
    int nextSlot = 0;
    for (int row = rows - 1; row >= 0; row--)
    {
        for (int col = cols - 1; col >= 0; col--)
        {
            nextSlot = 0;

            for (int cell = 0; cell < cells; cell++)
            {
                if (nextSlot)
                    break;
                
                if (drinksIndex < drinkProducts)
                {

                    vendMachine[row][col][cell] = drinksIndex + 1;
                    drinksAmounts[drinksIndex]--;
                    
                    if(drinksAmounts[drinksIndex] == 0)
                    {
                        drinksIndex++;
                        nextSlot = 1;
                    }    

                    continue;
                }
                
                if (foodsIndex < foodProducts)
                {
                    vendMachine[row][col][cell] = -(switchArr[foodsIndex] + 1);
                    foodsAmounts[switchArr[foodsIndex]]--;
                    
                    if(foodsAmounts[switchArr[foodsIndex]] == 0)
                    {
                        foodsIndex++;
                        nextSlot = 1;
                    }  
                }

            }
        }
    }


    //printing info message;
    //print the rest of the products - if there are any; 
    printf("\n");
    if (drinksIndex < drinkProducts || foodsIndex < foodProducts)
    {
        printf("*****************************************************\n");
        printf("  VENDING MACHINE IS FULL!\n");
        printf("  There are some products left!\n");
        printf("\n");

        if (drinksIndex < drinkProducts)
        {
            printf("  Drinks left:\n");

            for (int i = drinksIndex; i < drinkProducts; i++)
            {
                printf("    %d x %s %.2fl $%.2f left\n", 
                    drinksAmounts[i], 
                    drinksNames[i],
                    drinksWeights[i], 
                    drinksPrices[i]);
            }
        }
        
        if (foodsIndex < foodProducts)
        {
            printf("  Foods left:\n");

            for (int i = foodsIndex; i < foodProducts; i++)
            {
                printf("    %d x %s %.2fg $%.2f left\n", 
                    foodsAmounts[switchArr[i]], 
                    foodsNames[switchArr[i]],
                    foodsWeights[i], 
                    foodsPrices[switchArr[i]]);
            }

        }
        
        printf("*****************************************************\n");
    }
    else if (drinkProducts == 0 && foodProducts == 0)
    {
        printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        printf("   No products to fill with!\n");
    }
    else
    {
        printf("-----------------------------------------------------\n");
        printf("   Vending Machine Filled!\n");
    }
    

    //THE BUYING PROCESS
    do 
    {
        //print vending machine with the products in it
        printf("\n-----------------------------------------------------\n");
        printf("Vending Machine:\n");
        print_vending_machine(rows, cols, cells, vendMachine);
        printf("\n");

        printf(" Table of content:\n");
        printf("    0 = empty cell\n");
        
        //print and stop the program if the vending machine is empty
        if (is_empty_vending_machine(rows, cols, cells, vendMachine))
        {
            printf("\nSORRY! No items to buy!\n");
            printf("Come back next time!\n");
            printf("Bye!\n");
            break;
        }

        //print id <-> product
        if (drinkProducts > 0)
            printf("  Drinks:\n");
        for (int i = 0; i < drinkProducts; i++)
        {
            printf("  %3d = %s %.2fl $%.2f\n", 
                i+1, 
                drinksNames[i], 
                drinksWeights[i], 
                drinksPrices[i]);
        }

        if (foodProducts > 0)
            printf("  Foods:\n");
        for (int i = 0; i < foodProducts; i++)
        {
            printf("  %3d = %s %.2fg $%.2f\n", 
                -(i+1), 
                foodsNames[i], 
                foodsWeights
                    [index_of_i(switchArr,foodProducts, i)],
                foodsPrices[i]);
        }
   
        //from here customer can buy products
        printf("\n");
        printf("Do you want to buy something? (y/n) ");
        
        getchar();
        char buy = getchar();
        
        if (buy == 'y' || buy == 'Y')
        {
            float money = 0, cost = 0;
            int index = 0, isFood = 0;
            int slot;
            int row, col, cell;
            int notReady = 1;

            do
            {
                printf("Insert money $: ");
                scanf("%f", &money);

                if (money < 0)
                    printf("Money can't be nagative value!\n");
                else if (money < 0.50)
                    printf("Money have to be at least $0.50!\n");

            } while (money <= 0);
            
            
            printf("Enter slot <number>: ");
            do
            {
                scanf("%d", &slot);

                if (slot <= 0)
                {
                    printf("Value can't be negative or zero!\n");
                    printf("Enter slot <number>: ");
                    continue;
                }

                col = (slot-1) % cols;
                row = (slot-1) / cols;
                cell = cells - 1;


                while (cell > 0 && vendMachine[row][col][cell] == 0)
                {
                    cell--;
                }

                index = vendMachine[row][col][cell];

                if (index < 0)
                {
                    index = (-1)*index - 1;
                    cost = foodsPrices[index];
                    isFood = 1;
                    notReady = 0;
                }
                else if (index > 0)
                {
                    index = index - 1;
                    cost = drinksPrices[index];
                    isFood = 0;
                    notReady = 0;
                }
                else
                {
                    printf("No items on slot <%d>!\n", slot);
                    printf("Enter another slot <number>: ");
                    continue;
                }
        
                while (money < cost)
                {
                    printf("Not enough money to buy this product!\n");
                    printf("(You have $%.2f. Selected product is $%.2f)\n", 
                        money, 
                        cost);
                    printf("Do you want to add more money? (y/n) ");
                    
                    getchar();
                    char more = getchar();
                    if (more == 'y' || more == 'Y')
                    {
                        float addMoney;

                        printf("Insert more money $: ");
                        scanf("%f", &addMoney);

                        money += addMoney;
                        
                        notReady = 0;
                    }
                    else if (more == 'n' || more == 'N')
                    {
                        printf("Than enter another slot <number>: ");
                        notReady = 1;
                        break;
                    }
                }

            } while (notReady);

            if (isFood)
            {
                printf("\n");
                printf("Buying... %s %.2fg for $%.2f\n",
                    foodsNames[index],
                    foodsWeights[switchArr[index]],
                    foodsPrices[index]);

                foodsAmounts[index]--;
            }
            else
            {
                printf("\n");
                printf("Buying... %s %.2fl for $%.2f\n",
                    drinksNames[index],
                    drinksWeights[index],
                    drinksPrices[index]);

                drinksAmounts[index]--;
            }

            money -= cost;
            printf("Change: $%.2f\n", money);
            printf("YOU CAN GET YOUR PRODUCT!");

            vendMachine[row][col][cell] = 0;
        }
        else if (buy == 'n' || buy == 'N')
        {
            printf("Bye...\n");
            break;
        }

    } while (1);

    return 0;
}
