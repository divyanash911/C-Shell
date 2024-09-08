# Description
This is an implementation of the Linux shell in C shell. It supports basic terminal commands and some couple commands. It also uses networking and piping concepts to make the terminal more diverse and robust to commands from the user. This project was taken up as a part of the Operating Systems and Networks course at IIITH Monsoon '23 semester. The documentation for the shell is given below


## Table of Contents
- [warp Command](#warp-command)
- [peek Command](#peek-command)
- [pastevents Command](#pastevents-command)
- [proclore Command](#proclore-command)
- [I/O Redirection](#io-redirection)
- [Pipes](#pipes)
- [Redirection along with Pipes](#redirection-along-with-pipes)
- [activities Command](#activities-command)
- [ping Command](#ping-command)
- [fg and bg Commands](#fg-and-bg-commands)
- [neonate Command](#neonate-command)
- [iMan Command](#iman-command)

---

### warp Command
**Syntax:**
```bash
warp [flags] [directory]
```
**Flags:**
- `.`: Current directory
- `..`: Parent directory
- `~`: Home directory
- `-`: Previous directory

**Description:**
Changes the shell's working directory. Supports both absolute and relative paths.

**Examples:**
```bash
warp test          # Changes to /home/user/test
warp ../tutorial   # Changes to /home/user/tutorial
warp ~             # Changes to /home/user
warp -             # Changes to the previous directory
```

---

### peek Command
**Syntax:**
```bash
peek [flags] [path]
```
**Flags:**
- `-a`: Show hidden files
- `-l`: Display extra information

**Description:**
Lists files and directories in the specified directory. Supports flags for additional details and color-coded output.

**Examples:**
```bash
peek test              # Lists files and directories in /home/user/test
peek -a /usr/bin       # Lists hidden files in /usr/bin
peek -l ~              # Displays extra information in /home/user
```

---

### pastevents Command
**Syntax:**
```bash
pastevents
pastevents purge
pastevents execute <index>
```
**Description:**
Stores and retrieves the 15 most recent commands. 'purge' clears stored commands. 'execute' runs a command from the history.

**Examples:**
```bash
pastevents            # Displays the command history
pastevents purge      # Clears the command history
pastevents execute 3  # Executes the command at index 3
```

---

### proclore Command
**Syntax:**
```bash
proclore [pid]
```
**Description:**
Provides information about a process, including PID, status, process group, virtual memory, and executable path.

**Examples:**
```bash
proclore             # Displays information about the shell process
proclore 123         # Displays information about the process with PID 123
```

---

### I/O Redirection
**Syntax:**
```bash
command > output_file
command >> output_file
command < input_file
```
**Description:**
Redirects command output to a file using `>`, appends with `>>`, and takes input from a file using `<`.

**Examples:**
```bash
echo "Hello" > greeting.txt   # Writes "Hello" to greeting.txt
wc < textfile.txt            # Counts words from textfile.txt
```

---

### Pipes
**Syntax:**
```bash
command1 | command2 | command3
```
**Description:**
Passes output from `command1` as input to `command2`, and so on.

**Examples:**
```bash
echo "Lorem Ipsum" | wc | sed 's/ //g'   # Processes output through multiple commands
```

---

### Redirection along with Pipes
**Syntax:**
```bash
command1 | command2 > output_file
command1 < input_file | command2
```
**Description:**
Combines I/O redirection with pipes for more advanced command sequences.

**Examples:**
```bash
cat file.txt | wc > stats.txt   # Counts words in file.txt and writes to stats.txt
```

---

### activities Command
**Syntax:**
```bash
activities
```
**Description:**
Prints a list of all processes spawned by the shell, including command name, PID, and state.

**Examples:**
```bash
activities   # Displays information about currently running processes
```

---

### ping Command
**Syntax:**
```bash
ping <pid> <signal_number>
```
**Description:**
Sends signals to processes based on PID and signal number.

**Examples:**
```bash
ping 123 9    # Sends SIGKILL signal to process with PID 123
ping 456 41   # Sends signal 9 to process with PID 456
```

---

### fg and bg Commands
**Syntax:**
```bash
fg <pid>
bg <pid>
```
**Description:**
`fg` brings a background process to the foreground, and `bg` changes a stopped background process to running.

**Examples:**
```bash
fg 789    # Brings the background process with PID 789 to the foreground
bg 789    # Changes the state of process with PID 789 to running (in the background)
```

---

### neonate Command
**Syntax:**
```bash
neonate -n <time_arg>
```
**Description:**
Prints the Process-ID of the most recently created process every `<time_arg>` seconds until the key 'x' is pressed.

**Examples:**
```bash
neonate -n 4   # Prints the PID every 4 seconds until 'x' is pressed
```

---

### iMan Command
**Syntax:**
```bash
iMan <command_name>
```
**Description:**
Fetches man pages from http://man.he.net/ for the given command.

**Examples:**
```bash
iMan sleep            # Retrieves the man page for the 'sleep' command
iMan invalid_command  # Displays an error for a non-existing command
```

This detailed documentation provides users with clear information on each command's syntax, available flags, and usage examples. Include these details in your README file for user reference.