LADS - Freeware version 4.00
(C) Copyright 1998-2004 Frank Heyne Software (http://www.heysoft.de)

LADS lists the name and size of every alternate data stream (ADS) 
it finds in the specified directory (with or without subdirectories).

This software is provided "as is", without warranty of any kind!
Use it on your own risk!

Usage: LADS [Directory] [/S] [/D] [/A] [/Xname]

  Directory: directory to scan, current if ommitted

  /S     include Subdirectories

  /D     Debug LADS (I hope you never need to use this option ;-)

  /V     Verbose error reports

  /A     give a summary of All bytes used in the scanned directories
         (All files and directories are considered as uncompressed
         and all security decriptions are skipped for calculating 
         this number!)

  /Xname eXclude any ADS "name"

  /Pfile read Parameters from "file"

The /X switch allows to eXclude ADSs which have a name of your choice.
It is useful if you run some kind of AV software, which adds an ADS to 
every scanned file. The output of LADS is difficult to handle if it lists 
tens of thousands of ADSs with the same name.
Therefore you now can, for instance, run

  LADS C:\ /s /xCA_INOCULATEIT

and get only a list of those ADSs which have not been created by
the AV software.

Since version 3.20 of LADS you can exclude as many ADSs as you want from scanning.
To not need to write the parameters for every scan again and again, you can put
all or a part of them into a parameter file. The parameter file is a simple text 
file, each line contains a parameter and no white space. For the example above, 
you could create a parameter file LADSparam.txt with the following 3 lines:

C:\ 
/s 
/xCA_INOCULATEIT

and call the program this way:

  LADS /pLADSparam.txt


Since version 4.0 of LADS you can scan remote drives by their UNC names:

LADS \\Server\C$\temp



To learn more about alternate data streams, have a look at the
ADS FAQ at http://www.heysoft.de/

Pleas send bug reports and queries regarding LADS to
Frank Heyne (fh@heysoft.de)

Guarantee and responsibility
----------------------------
This program was developed with largest care. However, the author can
not guarantee, that the program runs under each version of Windows NT
on each computer flawlessly.
There is no warranty for the program, to the extent permitted by
applicable law. The copyright holder provides the program "as is"
without warranty of any kind, either expressed or implied, including,
but not limited to, the implied warranties of merchantability and
fitness for a particular purpose.  The entire risk as to the quality
and performance of the program is with you.  Should the program prove
defective, you assume the cost of all necessary servicing, repair or
correction. In no event unless required by applicable law will the
copyright holder be liable to you for damages, including any general,
special, incidental or consequential damages arising out of the use or
inability to use the program (including but not limited to loss of
data or data being rendered inaccurate or losses sustained by you or
third parties or a failure of the program to operate with any other
programs), even if such holder or other party has been advised of the
possibility of such damages.
