The avrdude.conf and hardware/ resources come directly from the Adafruit
Trinket tutorial here:

  http://learn.adafruit.com/introducing-trinket

The 10-USBtiny.rules udev rules is suggested by a page linked from the tutorial
but the page is out of date and shows deprecated (pre-2009) `SYSFS{...}` syntax
instead of the current `ATTR{...}`/`ATTRS{...}` udev syntax.

This setup still does not work directly from the Arduino IDE. Attempting to
upload directly from the IDE results in a cleared firmware (preserved
bootloader, thankfully) followed by a series of errors. Programming must be
done separately using avrdude commmands like this:

```bash
# Clears program space; fails with lots of errors
avrdude -c usbtiny -p attiny85 -U flash:w:trinketblink.hex
# Succeeds in programming chip (usually)
avrdude -c usbtiny -p attiny85 -D -U flash:w:trinketblink.hex
```

This appears to be a problem with the erase timing (something the Adafruit
provided avrdude.conf is specifically trying to address). The `-D` in the
second command skips the erase phase (the only part of the first command that
will succeed).

Programming must be done from the commandline using the above commands.  I
don't see a way to use the Ardquino IDE for more than compile. If using the
Arduino IDE for compiling, the output files will be left somewhere like this
(i.e. use instead of "trinketblink.hex" in the above):

```
/tmp/build2960098601916446287.tmp/feeder_sketch.cpp.hex
```

One thing further. At the time of this commit, the trinket tutorial provides
links to a Linux avr ld linker that is actually the Mac OS X avr ld. (i.e. The
ones provided for Linux and Mac have the same sha1sums and are Mach-o fat
binaries.) The modified ld is provided to handler larger sized object files.

For now the program size is small enough not to warrant an updated linker so we
skip the Adafruit suggested ld.

This project also leverages the PowerSwitch Tail II device. Documentation can
be found here:

  http://www.powerswitchtail.com/Pages/default.aspx
