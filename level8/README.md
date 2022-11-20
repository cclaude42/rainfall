# level8

The executable is an interactive loops with commands :

- `auth ` runs `_auth = malloc(4)` (don't forget the space)
- `reset` runs `free(_auth)`
- `service` runs `_service = strdup(servbuf)`
- `login` runs `system("/bin/sh")` IF `_auth[8] != 0`

## **The allocation**

`_auth` is an `int` table ; this means addresses are 4 bytes long, so `_auth[8]` is at `_auth + 32`.

The mallocs are successive, meaning each new `auth ` or `service` will allocate a new address 16 bytes after the previous one.

## **The buffers**

There are three successive buffers : `cmd[5]`, `authbuf[2]` and `servbuf[137]`.

`cmd` is passed to `fgets` and filled with our `stdin` prompt, meaning more than 5 characters will overwrite `authbuf`, and more than 7 will write in `servbuf`.

Running "service", for example, will yield the following :

```
cmd     : s  e  r  v  i
authbuf : c  e
servbuf : \n \0 \0 \0 ...
```

This means, by the way, that running service automatically initializes its value to non-zero (since `serv = strdup(servbuf)` and `servbuf` contains a `\n`).

## **The exploit**

We run **`auth `** : `_auth` is set to `0x804a008`. 

We run **`service`** : `_service` is set to `0x804a018`.

We run **`service`** again : `_service` is set to `0x804a028`.

Now `_auth+32` (or `_auth[8]`) is `_service`, which is initialized to non-zero.

We run **`login`** to get the interactive shell.

## **The flag**

It works ! In our interactive shell, we run :

```
cat /home/user/level9/.pass
```

... and get the flag for `level8` :

```
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```