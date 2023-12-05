# Description
<h1>DivyaShell</h1>
This is a simple representation of the Bash shell coded in the C Programming language as a part of the Operating Systems and Networks course at IIIT-Hyderabad Monsoon 2023 semester.
This branch is for the Mid-Submission of the project.It supports basic bash functionalities like cd , ls , history and more. The final submission would also include piping , redirection , file management and networking.
To run the shell you can either run the makefile, if it doesn't respond you can run the command 

```bash
gcc -g main.c prompt.c color.c peek.c proclore.c pastevents.c searchfile.c stringhelper.c 
```

# Assumptions
<ul>
  <li>Assumed that bash-oriented commands and shell specific commands won't be given as a single multi-command thread</li>
  <li>The size of relevant commands are constrained to size of MACROS defined to store them.</li>
  <li>Since the shell is under construction , it may throw some bugs at the user but that's what I'll be doing!Fixing them.</li>
  <li>The codebase is not completely modularized as of now and is still under modularization.</li>
  <li>Excessive care has been taken to handle all sorts of edge-cases but any if any such ambiguity still remains , it will be covered up later on in the final commit.</li>
</ul>
