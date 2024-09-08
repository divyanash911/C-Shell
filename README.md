# Description
<h1>DivyaShell</h1>
This is a simple representation of the Bash shell coded in the C Programming language as a part of the Operating Systems and Networks course at IIIT-Hyderabad Monsoon 2023 semester.
This branch is for the Final-Submission of the project.It supports basic bash functionalities like cd , ls , history , ps , sleep , echo , git , jobs and many more.
It supports input output redirection as well as piping , signals , foreground , background processes and keyboard interrupts.
To run the shell you can either run the makefile, if it doesn't respond you can run the command 

```bash
make
```
Alternate -

```bash
gcc -g main.c color.c pastevents.c peek.c proclore.c prompt.c searchfile.c stringhelper.c iman.c pipe.c fg.c neonate.c ping.c
```

# Assumptions
<ul>
  <li>Assumed that bash-oriented commands and shell specific commands won't be given as a single multi-command thread</li>
  <li>The size of relevant commands are constrained to size of MACROS defined to store them.</li>
  <li>Since the shell is a first-time project , it may throw some bugs at the user.</li>
  <li>Excessive care has been taken to handle all sorts of edge-cases but any if any such ambiguity still remains , it will be covered up later on in the final commit.</li>
  <li>Commands like seek , neonate are not handled in I/O redirection because of technical difficulties to the shell environment.</li>
  <li>Error handling is a part of the project but any unprecdented command-flow which hasn't been taken care of can render the shell unresponding or even dead due
  to segmentation faults. Most of it has been taken care of.</li>
  <li>Input redirection to user commands is not supported.</li>
  <li>A control + \ keyboard interrupt is added to kill the shell immediately.</li>
  
</li>
</ul>
