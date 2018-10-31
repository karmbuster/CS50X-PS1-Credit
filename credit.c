#include <stdio.h>
#include <cs50.h>


int getValidLength(long long num)
{
    // check length of 13
    if ((num > 999999999999) && (num < 10000000000000))
    {
        return 13;
    }
    // check length of 15
    else if ((num > 99999999999999) && (num < 1000000000000000))
    {
        return 15;
    }
    // check length of 16
    else if ((num > 999999999999999) && (num < 10000000000000000))
    {
        return 16;
    }
    // for any length not 13, 15, or 16 return
    return 0;
}

bool valid(int length, long long card)
{
    // store card number in temp variable
    // I didn't want to change the value of card
    long long temp = card;
    // variable to hold the current last digit as we take them off one by one
    int lastDigit = 0;
    // this sum is the sum for the digits that get multiplied by 2
    int sumMultiplied = 0;
    // this sum is the sum for the digits that do not get multiplied
    // this sum is added to sumMultiplied at the end
    int sumSingle = 0;

    for (int i = 0; i < length; i++)
    {
        if ((i % 2) != 0)
        {
            lastDigit = (temp % 10) * 2;

            if (lastDigit > 9)
            {
                int ones = lastDigit % 10;
                lastDigit = lastDigit / 10;
                int tens = lastDigit % 10;
                sumMultiplied = sumMultiplied + ones + tens;
            }
            else
            {
                sumMultiplied = sumMultiplied + lastDigit;
            }
        }
        else
        {
            lastDigit = temp % 10;
            sumSingle =  sumSingle + lastDigit;
        }
        temp = temp / 10;
    }
    if ((sumMultiplied + sumSingle) % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(void)
{
    // Valid Conditions
    //AMEX - Start with: 34, 37; 15 Digits
    //MASTERCARD - Starts with: 51, 52, 53, 54, 55; 16 Digits
    //VISA - Start with: 4; 13 or 16 Digits
    // Luhn's Algorithm
    // 1. Multiply every other digit by 2, starting with second-to-last digit and add those products' digits together
    // 2. Add the sum to the sum of the digits that weren't multiplied by 2
    // 3. If the total's last digit is 0, the number is valid

    // get a card number from the user
    long long cardNum = get_long_long("Enter Card Number: ");
    // check if length is 13, 15, or 16 digits
    int length = getValidLength(cardNum);
    long long startsWith;
    bool isValid;



    switch (length)
    {
        case 13:
            // get first digit of card number
            startsWith = (cardNum / 1000000000000) % 10;

            // VISA cards need to start with 4 as first digit
            if (startsWith == 4)
            {
                // check to see if the card number is valid via Luhn's Algorithm
                isValid = valid(length, cardNum);
                if (isValid)
                {
                    // if number is 13 digits, starts with 4, and is valid, then it is a VISA
                    printf("VISA\n");
                    // exit program, skipping the breaks
                    return 0;
                }
                // break if card number is not valid per the algorithm
                break;
            }
            else
            {
                // break if the number does not start with 4
                break;
            }
        case 15:
            // get first digit of card number
            // 15 digits can only be AMEX
            // can only be AMEX if start with 34, 37

            startsWith = (cardNum / 100000000000000) % 10;

            if (startsWith == 3)
            {
                // must start with 3 to continue
                // get the digit after the 3
                startsWith = (cardNum / 10000000000000) % 10;

                if ((startsWith == 4) || (startsWith == 7))
                {
                    // digit after the 3 must be either 4 or 7
                    // then check for validity
                    isValid = valid(length, cardNum);
                    if (isValid)
                    {
                        printf("AMEX\n");
                        // exit program, skipping the breaks
                        return 0;
                    }
                    else
                    {
                        // if number is not valiid, then break
                        break;
                    }
                }
                else
                {
                    // if digit after 3 is not 4 or 7, then break
                    break;
                }

            }
            else
            {
                // if card number doesnt start with 3 then break
                break;
            }


            break;
        case 16:
            //MASTERCARD - Starts with: 51, 52, 53, 54, 55; 16 Digits
            //VISA - Start with: 4; 13 or 16 Digits

            // get first digit of card number
            startsWith = (cardNum / 1000000000000000) % 10;

            if (startsWith == 4)
            {
                isValid = valid(length, cardNum);
                if (isValid)
                {
                    // if number is 16 digits, starts with 4, and is valid, then it is a VISA
                    printf("VISA\n");
                    // exit program, skipping the breaks
                    return 0;
                }
                // break if card number is not valid per the algorithm
                break;
            }
            else if (startsWith == 5)
            {
                // get next digit
                startsWith = (cardNum / 100000000000000) % 10;

                // if next digit is 1, 2, 3, 4, or 5, check validity
                if ((startsWith > 0) && (startsWith < 6))
                {
                    isValid = valid(length, cardNum);
                    if (isValid)
                    {
                        // if the card is 16 digits, first digit is 5, second is between 1 and 5, and is valid, then it is MC
                        printf("MASTERCARD\n");
                        return 0;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            else
            {
                // if first digit is not 4 or 5 then break
                break;
            }
        // if length is not 13, 15, or 16, then it is an invalid number
        default:
            printf("INVALID\n");
    }
    // all correct paths return 0, exiting the program, so if the program ever gets to this line, the number is invald
    printf("INVALID\n");

}