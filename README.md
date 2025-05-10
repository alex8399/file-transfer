# Linux utility for transferring files within a Local Area Network (LAN)

Linux utility for sending and receiving files within a Local Area Network (LAN). The sender needs only the receiver's IP address and port to initiate the transfer, while the receiver only needs to know the file number being sent.

Connections between users are established using sockets.

## Content

[Example](#example)

[UML Class Diagram](#uml-class-diagram)

[Valgrind: Detecting Memory Leaks](#valgrind-detecting-memory-leaks)

[How to run](#how-to-run)


## Example

Sending files `text.txt` and `bin_file.exe` to a receiver at IP address `192.168.0.114` on port `8080`.

### Sending files

```bash
allex-nik@allex-nik:~/Programming/linux_network_util/src$  ./app.exe send 192.168.0.114 8080 ./text.txt ./bin_file.exe
Command 'send' is set.
---------------------------------------------------------------------------
File sender is waiting response from file receiver.
Connection is established.
The file transfer has started.
---------------------------------------------------------------------------
The transfer of file ./text.txt has started.
The transfer of file ./text.txt has finished. The size of ./text.txt is 16342 bytes.
---------------------------------------------------------------------------
The transfer of file ./bin_file.exe has started.
The transfer of file ./bin_file.exe has finished. The size of ./bin_file.exe is 82856 bytes.
---------------------------------------------------------------------------
The file transfer has finished.
Connection was closed.
allex-nik@allex-nik:~/Programming/linux_network_util/src$ 
```


### Receiving files

```bash
alex@alex-VirtualBox:~/Desktop/linux_network_util/src$ ./app.exe receive 8080 2
Command 'receive' is set.
---------------------------------------------------------------------------
File receiver is waiting for response from file sender.
Connection is established.
The file downloading has started.
---------------------------------------------------------------------------
The downloading of 1 file has started.
The downloading of file ./text.txt has finished. The size of ./text.txt is 16342 bytes.
---------------------------------------------------------------------------
The downloading of 2 file has started.
The downloading of file ./bin_file.exe has finished. The size of ./bin_file.exe is 82856 bytes.
---------------------------------------------------------------------------
The file downloading has finished.
Connection was closed.
alex@alex-VirtualBox:~/Desktop/linux_network_util/src$
```


## UML Class Diagram
![images](/docs/diagram/UMLClassDiagram.drawio.svg)

## Valgrind: Detecting Memory Leaks

### Sending files

```bash
allex-nik@allex-nik:~/Programming/linux_network_util/src$ valgrind ./app.exe send 192.168.0.114 8080 ./LinuxSockets.cpp ./Console.o
==274== Memcheck, a memory error detector
==274== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==274== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==274== Command: ./app.exe send 192.168.0.114 8080 ./LinuxSockets.cpp ./Console.o
==274==
...
...

...
==274== 
==274== HEAP SUMMARY:
==274==     in use at exit: 0 bytes in 0 blocks
==274==   total heap usage: 40 allocs, 40 frees, 97,054 bytes allocated
==274==
==274== All heap blocks were freed -- no leaks are possible
==274==
==274== For lists of detected and suppressed errors, rerun with: -s
==274== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
allex-nik@allex-nik:~/Programming/linux_network_util/src$ 
```

### Receiving files

```bash
alex@alex-VirtualBox:~/Desktop/linux_network_util/src$ valgrind ./app.exe receive 8080 2
==3172== Memcheck, a memory error detector
==3172== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==3172== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==3172== Command: ./app.exe receive 8080 2
==3172==
...
...

...
==3172== 
==3172== HEAP SUMMARY:
==3172==     in use at exit: 0 bytes in 0 blocks
==3172==   total heap usage: 36 allocs, 36 frees, 94,715 bytes allocated
==3172== 
==3172== All heap blocks were freed -- no leaks are possible
==3172== 
==3172== For lists of detected and suppressed errors, rerun with: -s
==3172== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
alex@alex-VirtualBox:~/Desktop/linux_network_util/src$
```

### Summary
As a result of Valgrind testing, no memory leaks were detected in the program. This outcome was achieved with the help of smart pointers, such as ```std::unique_ptr``` and ```std::shared_ptr```.


## How to run

### Prerequisites
1. Clang with C++20 support.
2. Linux OS.
3. Two devices connected to the same Local Area Network (LAN), each assigned an IP address within the 192.168.X.X range.


### Installation

1. **Clone the repository**:
    ```bash
    git clone https://github.com/alex8399/file-transfer.git
    cd file-transfer/src
    ```

2. **Compile the executable file**:
    ```bash
    make dirs
    make app.exe
    ```

### Manual

**usage:**

```bash
./app.exe <option> [progs-and-agrs]
```

**Options:**

- **send <receiver-ip> <receiver-port> [file1] ... [fileN]**

  Send `file1`, ..., `fileN` to the specified receiver.

  ```bash
  ./app.exe send <receiver-ip> <receiver-port> [file1] ... [fileN]
  ```

- **receive <port> <number-of-files>**

  Receive the indicated number of files from the sender.

  ```bash
  ./app.exe receive <port> <number-of-files>
  ```

- **--help**

  Show manual.

  ```bash
  ./app.exe --help
  ```

**Examples:**

- To send files `file1.txt` and `file2.txt` to a receiver at IP `192.168.0.114` on port `8080`:

  ```bash
  ./app.exe send 192.168.0.114 8080 file1.txt file2.txt
  ```

- To receive 2 files on port `8080`:

  ```bash
  ./app.exe receive 8080 2
  ```
