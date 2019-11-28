# Qua-C

Qua-C (pronounced as /'kwɑ-si/) is a *domain specific programming language* for simulating **Quantum Computing Algorithms.**

Qua-C is a language under development to make the process of coding a Quantum Algorithm easy and in a visual syntax format.

Qua-C has a different ideology from conventional programming languages, which have a sequential syntax format to apply functions and gates to data. Instead of a sequential construct, Qua-C executes code column-wise manner for a set of qubits in the quregister.

**The Qua-C Transpiler is developed completely in 'C' language currently.**

Also see the 'Examples' folder to know more about the functionality. The 'Examples' folder contains various examples like:-

1. Basic Example
2. **Grover search** for 2 qubits
3. Hadamard Gate mania
4. **Shor's period finding** algorithm
5. **Grover Search** for 5 qubits with **custom gates**


## Quantum Registers

This feature allows the use to make registers consisting of multiple qubits at a time.

To make the coding of these gates easier, a functionality of short-hand gates is provided. The gates can be applied to the register as follows:-

	### example.qc ###

	gate MyOwnGate[2] {
		[H, H]
	}

	func test {
	    [X, X] Pa()
		[Z, Y] Pa()
		[H, H] Pa()
		[X, Z] Pa()
		[Y, X] Pa()
		[MyOwnGate]
	}

	#### Initialize ####
	quReg a = new quReg[2] => 'myqureg1'
	a.setPrecision(6)

	#### Simulate ####
	a.Pnz()
	a.test()
	a.Pnz()


OUTPUT:

	./quacc example.qc

	[+] Parsing Successful...!!!

	Executing program...
	myqureg1 = 	
	[0] =>	{1.000000 + 0.000000 i} |00>	100.000000 %


	myqureg1 = 	
	[0] =>	{0.000000 + 0.000000 i} |00>	0.000000 %
	[1] =>	{0.000000 + 0.000000 i} |01>	0.000000 %
	[2] =>	{0.000000 + 0.000000 i} |10>	0.000000 %
	[3] =>	{1.000000 + 0.000000 i} |11>	100.000000 %


	myqureg1 = 	
	[0] =>	{0.000000 + 0.000000 i} |00>	0.000000 %
	[1] =>	{-0.000000 + 1.000000 i} |01>	100.000000 %
	[2] =>	{-0.000000 + 0.000000 i} |10>	0.000000 %
	[3] =>	{0.000000 + 0.000000 i} |11>	0.000000 %


	myqureg1 = 	
	[0] =>	{0.000000 + 0.500000 i} |00>	25.000000 %
	[1] =>	{0.000000 - 0.500000 i} |01>	25.000000 %
	[2] =>	{0.000000 + 0.500000 i} |10>	25.000000 %
	[3] =>	{0.000000 - 0.500000 i} |11>	25.000000 %


	myqureg1 = 	
	[0] =>	{0.000000 - 0.500000 i} |00>	25.000000 %
	[1] =>	{0.000000 + 0.500000 i} |01>	25.000000 %
	[2] =>	{-0.000000 + 0.500000 i} |10>	25.000000 %
	[3] =>	{-0.000000 - 0.500000 i} |11>	25.000000 %


	myqureg1 = 	
	[0] =>	{-0.500000 + 0.000000 i} |00>	25.000000 %
	[1] =>	{-0.500000 + 0.000000 i} |01>	25.000000 %
	[2] =>	{0.500000 + 0.000000 i} |10>	25.000000 %
	[3] =>	{0.500000 + 0.000000 i} |11>	25.000000 %


	myqureg1 = 	
	[2] =>	{-1.000000 + 0.000000 i} |10>	100.000000 %


	Time taken: 0 min, 0.000124 sec


The above code segment has the following meaning:-
 - Initialize a new quRegister.
 - Display text for the quRegister is "quReg1".
 - Pnz() -> Print only non-zero magnitude values of the 2 qubit quRegister.
 - Pauli gate 'X' is applied to [qubit[0], qubit[1]] respectively.
 - Print all states in the quRegister.
 - Pauli gate 'Z' is applied to qubit[0] and 'Y' to qubit[1] respectively, and so on.
 - Pnz() -> Print only non-zero magnitude values.

## List of short-hand gates
- Hadamard Gate: **H**
- Phase Gate: **S**
- Rotation Gate: **R_k**

        k: power of n'th root of unity (w)
- Control gate: **@**
- Inverse Control gate: **o**
- Identity Gate: **-**
- Pauli Gates
    - Pauli X gate: **X**
    - Pauli Y gate: **Y**
    - Pauli Z gate: **Z**
- Swap Gate: **x**
- Quantum Fourier Transform (QFT) Gate: **~**


**For more info, see the examples:** *https://github.com/AbeerVaishnav13/qua-C/tree/master/Examples*

**Currently, the language supports registers upto 29-qubits with 8GB of memory.**

## Installation Instructions

### Dependncies
The dependencies for QuaC language is the **gcc** compiler and **cmake**. 

(i) For Ubuntu/Linux platform

	sudo apt-get install gcc cmake

(ii) For MacOS platform - With HomeBrew installed

	sudo brew install gcc cmake

(iii) For Windows platform - install MINGW GCC for windows or even better, install any Linux distribution of your choice :)


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


