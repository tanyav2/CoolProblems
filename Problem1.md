
## Problem 1

### How many times will this for loop execute?
#### Answer: Signed - `2^(sizeof(type)*8 - 1) - 10` and for unsigned: `2^(sizeof(type)*8) - 10`

There are a few points I need to make about the solution that I came up with.


1. I was blatantly wrong with the way I calculated the number of times it would run. I forgot to raise the number of bits to a power of 2.


2. Even then, there were certain things I encountered that led me to realize what I was doing wrong. For starters, running `for (char i = 0; i < i + 10; i++) {...}` ran way more times than `2^8 - 10`. This is because of something called [integer promotions](https://www.geeksforgeeks.org/integer-promotions-in-c/). So, what was happening was that `i` was getting converted to `int` because of the use of the operator `+` in `i + 10`. That's why it ran till much larger values than `2^8 - 10`.


3. So, to get rid of the typecasting problem, I tried the code `for (char i = 0; i < (char)(i + 10); i++)`. This ran `118` times. Looking closely, I realized that `118` is equal to `2^7 - 10`. Then, I tried `for (uint8_t i = 0; i < (uint8_t)(i + 10); i++)`. This ran `246` times, which is `2^8 - 10`. This was happening because in signed data types like char, the most significant bit was reserved for the sign. This piece of information somehow completely slipped my mind earlier. 


4. I further proved this by running the following code, which outputted 1 and 0 respectively, solidifying the fact that `char i = 255` was indeed being treated as `-1`.

```
    char i = 255;
    char j = 127;
    printf("%d\n", i < j);
    
    unsigned char k = 255;
    unsigned char l = 127;
    printf("%d\n", k < l);
```



4. Given these observations, I realized that the answer would certainly depend on whether the data type was signed or unsigned. For signed datatypes, **the answer would be: `2^(sizeof(type)*8 - 1) - 10` and for unsigned, it would be: `2^(sizeof(type)*8) - 10`**

