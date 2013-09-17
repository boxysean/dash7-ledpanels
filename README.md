Tectiles
========

There are two lighting modes in this repo.

- The first is called *Chinese Fire Drill*, referring to the game of everybody getting out of the car at once and changing places. These are how the LEDs behave: at one moment, a subset of panels are turned on, and the next moment (typically 2s later, adjustable) a different subset of panels are turned on.

- The second is plainly called *random*. Every moment a panel turns off and another turns on (typically 200ms, adjustable). There's a base parameter of how many panels are on at once (tested 10 if there are 24 panels). The distribution of randomess is nice, in fact here's a typical histogram of how often a panel lights up after 100 reptitions.

        histogram of # times a panel lights up over 100 moments
         0
         1
         2
         3 ******
         4 *********
         5 ********
         6 *
         7
         8
         9

How to adjust the parameters
----------------------------

The light sequences are pre-computed using python. They generate arrays that are meant to be copied and pasted into the Arduino code. It's easier. :)

So, for example, open up `gen-random.py` and adjust the parameters. Run the code and take the standard output and paste it into the appropriate place in the corresponding random Arduino sketch.

By Dash 7
---------

                           .------,
                           =\      \
          .------.          =\      \
          | DASH7 \          =\      \
          |        `----------'------'----------,
         .'        LI.-.LI LI LI LI LI LI LI.-.LI`-.
         \ _/._______|_|______.------,______|_|_____)
                             /      /
                           =/      /
                          =/      /
                         =/      /
                         /_____,'

