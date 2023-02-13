# sh_shell

# Purpose

sh_shell is a simple Unix shell that supports:



* running simple commands
* redirecting stdin, stdout, and stderr


# Intended Users

This guide is intended for users who have basic experience with the POSIX system.



* Users who can run a program using a terminal on a POSIX system
* Users who know what the command line arguments and flags are
* Users who know how to use cmake.


# Software Requirements



* Clang-tidy
* Cmake
* Dot (This is used by Doxygen)
* Doxygen (Although this is not necessary to run the program, it is intended to be used when building this program, so if you want to build without creating a Doxygen file, edit CMakeLists.txt)
* Standard C17 compiler (e.g. GCC, Clang)
* Cgreen (cgreen is a framework for unit testing. It's not essential for running sh_shell, so if you don't have it installed or don't want the unit testing program, edit the CMakeLists.txt files.)
* libasan, libubsan (for Fedora)


# Platform



* macOS 13.2 (Ventura)
* Fedora 37

I tested programs on macOS and Fedora Linux (Fedora 37).


# Installing


## Obtaining

Clone this repo by running following command.

```
git clone https://github.com/hurshik7/sh_shell.git
```


Then, you can see the `source` directory.


## Building & Installing

go into the `source/` directory and build the sh_shell with the following commands.


```
cd source
cmake -S . -B build
cmake --build build
```


The compiler can be specified by passing one of the following to cmake:



* `-DCMAKE_C_COMPILER="gcc"`
* `-DCMAKE_C_COMPILER="clang"`

(For example, `cmake -S . -B build -DCMAKE_C_COMPILER="gcc")`


## Running


```
./build/sh_shell
```



## Environment Variables

The following environment variables alter the behaviour of sh_shell:


<table>
  <tr>
   <td><strong>Variable</strong>
   </td>
   <td><strong>Purpose</strong>
   </td>
  </tr>
  <tr>
   <td>PATH
   </td>
   <td>The directories to search for commands
   </td>
  </tr>
  <tr>
   <td>PS1
   </td>
   <td>The prompt to display, if not set, defaults to ‘$.’
   </td>
  </tr>
</table>



# Features



* sh_shell only supports executing simple commands with optional I/O redirection
* The PATH environment variable is searched for each command
* After a command completes, the exit status is displayed.


## Built-in Commands

sh_shell supports the following built-in commands:


<table>
  <tr>
   <td><strong>Command</strong>
   </td>
   <td><strong>Purpose</strong>
   </td>
  </tr>
  <tr>
   <td>cd
   </td>
   <td>Change working directory
   </td>
  </tr>
  <tr>
   <td>exit
   </td>
   <td>Exit the shell
   </td>
  </tr>
  <tr>
   <td>which
   </td>
   <td>locate a program file in the user's path
   </td>
  </tr>
</table>



## Limitations



* A program name has a space it cannot be run
* Tab completion is not implemented
* Command history is not implemented

The following command types are not supported:



* Pipelines (|)
* Lists (;, &, &,&, ||)
* Compound (if, case, until, while, for, ())
* Functions
