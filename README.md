# Qua-C

Qua-C ( pronounced as /'kwɑ-si/) is a *domain specific programming language* for simulating **Quantum Computing Algorithms.**

Qua-C is a language under development to make the process of coding a Quantum Algorithm easy and in a visual syntax format.

Qua-C has a different ideology from conventional programming languages, which have a sequential syntax format to apply functions and gates to data. Instead of a sequential construct, Qua-C executes code pseudo-parallel fashion for the set of qubits in the quregister.

**The Qua-C Transpiler is developed completely in 'C' language currently.**

Also see the 'Examples' folder to know more about the functionality. The 'Examples' folder contains various examples like:-

1. CNOT Gate
2. Hadamard Gate
3. Rotation of qubits about X, Y, Z - Axes of Bloch Sphere
4. Quantum NOT Gate
5. Quantum Registers
6. Quantum Rotation about imaginary axis
7. Quantum swapping of two Qubits


## Quantum Registers

This feature allows the use to make registers consisting of multiple qubits at a time.

To make the coding of these gates easier, a functionality of short-hand gates is provided. The gates can be applied to the register as follows:-

	*** example.qc ***

	func test {
		Pa()
		[X, X]
		[Z, Y]
		[H, H]
		[X, Z]
		[Y, X]
	}

	quReg a = init(2)
	a.name = "quReg1: "
	a.prec = 6

	a.test()
	a.Pnz()


OUTPUT:

	./quacc example.qc

	quReg2 = 
	[0]:	{1.000000 + 0.000000 i} |00>	100.00 %
	[1]:	{0.000000 + 0.000000 i} |01>	0.00 %
	[2]:	{0.000000 + 0.000000 i} |10>	0.00 %
	[3]:	{0.000000 + 0.000000 i} |11>	0.00 %

	quReg2 = 
	[0]:	{-0.000000 - 0.500000 i} |00>	25.00 %
	[1]:	{-0.000000 + 0.500000 i} |01>	25.00 %
	[2]:	{-0.000000 - 0.500000 i} |10>	25.00 %
	[3]:	{-0.000000 + 0.500000 i} |11>	25.00 %


The above code segment has the following meaning:-
 - Initialize a new quRegister.
 - Display text for the quRegister is "quReg1: ".
 - Pa() -> Print all possible combinations of 'n' qubits in the quRegister.
 - Pauli gate 'X' is applied to [qubit[0], qubit[1]] respectively.
 - Pauli gate 'Z' is applied to qubit[0] and 'Y' to qubit[1] respectively, and so on.
 - Pnz() -> Print only non-zero magnitude values.

## List of short-hand gates
- Hadamard Gate: **H**
- Phase Gate: **S**
- Rotation Gate: **R(x)**

        x: Angle value (in degrees)(Int/Float)
- CNOT Gate:
    - Control gate: **Co**
    - NOT gate: **Cx**
- NOOP Gate: **-**
- Pauli Gates
    - Pauli X gate: **X**
    - Pauli Y gate: **Y**
    - Pauli Z gate: **Z**
- Swap Gate: **Sx**
- Quantum Fourier Transform (QFT) Gate: **Q**
- Inverse QFT Gate: **Qi**

 *For more info, see the examples: https://github.com/AbeerVaishnav13/qua-C/tree/master/Examples*

*\*Currently, the language supports registers upto 28-qubits with 8GB of memory.*

## Installation Instructions

### Dependncies
The dependencies for QuaC language is the **gcc** compiler and **cmake**. 

(i) For Ubuntu/Linux platform

	sudo apt-get install gcc cmake

(ii) For MacOS platform - With HomeBrew installed

	sudo brew install gcc cmake

(iii) For Windows platform - install MINGW GCC for windows or even better, install any Linux 			  		distribution of your choice :)


### Install the compiler
Go to the installations directory:-

	cd /path/to/download/location/qua-C-master

Run the following command after installing all the dependencies

	make

Run the basic example file

	./quacc ./Examples/basic.qc



More stuff on the way... Enjoy! :)

Regards

Abeer Vaishnav


