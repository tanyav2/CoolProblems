# CoolProblems

### Problem 1

`Problem1.md`

### Problem 2

`swap.py`

### Problem 3

`Problem3.md` 

### Problem 4

`128bit.c` contains C code for this problem. To test it, you can generate two 128 bit unsigned numbers, split them into their 64 most significant and least significant bits, and then use the `mult_128()` function to multiply two such numbers. The result will be a 256 bit number. The function prints out the number in 4 parts. 

So, for instance:

    x = 238540812838453508252297635959906447441
    y = 277823518802795137820834436446017355703`

Then, 

`xy = 66272248000858124060635517506625314532097283602457302379952476090895571106023`

To run the program with these values, you would split x and y up and input the following:

    uint128 x = {11964670763611140177, 12931323375295470054}
    uint128 y = {6177830468733435831, 15060843132677893917}

The output will be:

    prod.low.low = 13944326641725487335
    prod.low.high = 16827249728999320874
    prod.high.low = 2156870476339497494
    prod.high.high = 10557778222273090865

The above combined is indeed the number `66272248000858124060635517506625314532097283602457302379952476090895571106023`
