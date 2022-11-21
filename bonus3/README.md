# bonus3

The executable does the following :

- Open the `end` flag
- Read the contents into a buffer
- Set `*(buf + atoi(av[1])` to `0`
- Compare the buffer and `av[1]`
- If they're the same, run `/bin/sh`

The number we put in `av[1]` will define the length of our buffer ; if we set it to `5`, for example, there will be `\0` after 5 chars, so our buffer's contents will be the 5 first characters of the `end` flag.

## **The exploit**

There's a very simple way to solve this.

The only way we can know the contents of the buffer is if we set `av[1]` to `0` ; in this case, the buffer will always be `""`, since the first byte is a null-termination.

`atoi` returns `0` by default, so as long as we don't start with any digits, any input will return `0` - including an empty string.

We run :

```
./bonus3 ""
```

## **The flag**

It works ! In the interactive shell, we run :

```
cat /home/user/end/.pass
```

We get the final flag :

```
3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
```