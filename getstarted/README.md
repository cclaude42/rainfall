# Getting started

## Setting up VirtualBox

In VirtualBox, go to `File > Host Network Manager`. If you see a `VirtualBox Host-Only Ethernet Adapter` listed, or a `vboxnet0`, you're set. Otherwise, make one using the `Create` button.

Create a new VM with `New`. Give it a name, select `Type: Linux` and `Version: Ubuntu`, leave the default settings.

Select your new VM, click `Settings`, and go to `Network`. If it's not already done, enable `Enable Network Adapter`, select `Attached-to: Host-Only Adapter` and make sure `Name:` points to the network you made earlier (probably `VirtualBox Host-Only Ethernet Adapter` or `vboxnet0`)

## Starting the VM

**Download the .iso file** from the [intranet's project page](https://projects.intra.42.fr/projects/42cursus-rainfall).

Now, `Start` the VM. It'll prompt you for an image to boot from. Import the ISO with the folder button, select it, and start the VM.

## Connecting

RainFall should now boot and display ASCII art, an IP address and prompt you for a login.

Now, **disregard that** entirely, and **copy the IP address displayed**. If you've correctly setup the network, you should be able to SSH into RainFall - without using VirtualBox's terrible interface.

Now pick a nice, comfortable terminal - one that actually knows your keyboard and lets you do a Ctrl-C - and log in remotely using :

```
ssh level0@<IP_ADDRESS> -p 4242
```

Congratulations! You are now ready to keep driving down the XP road.