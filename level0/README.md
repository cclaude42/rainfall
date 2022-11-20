# level0

We find an executable named `level0`. Running it gives us a segfault, and running it with an argument (`./level0 arg`) prints `No !` to stdout.

We start by copying the executable to our local machine :

```
sudo scp -P 4242 level0@<RAINFALL_IP>:level0 .
```

We open the executable with **Cutter**, a reverse engineering tool. When Cutter's done processing it, it gives us a complex mesh of assembly code.

We select `main` on the left menu, then `Graph (main)` on the bottom. We get a simplified view, showing us how the program runs :

![Cutter graph (main)](https://i.imgur.com/N32mNLP.png)

What does this mean ?

The top block is the beginning of the program. It seems to split after a certain condition, running either :
- A block containing a `write` - likely, what prints `No !` (on the right)
- A block containing the classic `get*id`, `set*id` and `execve` functions - which elevate user privileges (on the left)

We examine the condition :

```
call    atoi                      ; sym.atoi ; int atoi(const char *str)
cmp     eax, 0x1a7                ; 423
jne     0x8048f58
```

A call to `atoi()`, followed by a comparison to the number `423`, and a conditional jump (`jne` standing for *Jump if Not-Equal*). It's clear the program expects that number as first argument.

## **The exploit**

We try :

```
./level0 423
```

It works ! The executable enters an interactive, privileged shell-like `execve` loop, prompting us with `$ `.

## **The flag**

We run :

```
cat /home/user/level1/.pass
```

We get the level0 flag (which is also the level1 password) :

```
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```