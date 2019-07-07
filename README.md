# Qua-C 
Qua-C ( pronounced as /'kwɑ-si/) is a *domain specific programming language* for simulating **Quantum Computing Algorithms.**

Qua-C is a language under development to make the process of coding a Quantum Algorithm easy and in a visual syntax format.

Qua-C has a different ideology from conventional programming languages, which have a sequential syntax format to apply functions and gates to data. Instead of a sequential construct, Qua-C executes code pseudo-parallel fashion for the set of qubits in the quregister.

**The Qua-C Transpiler is developed completely in 'C' language currently.*

## Specifications
- Automatic datatype assignment through minimal keywords.

        var, val    # variable and value types

        # Examples
        val a = 10;
        var b = 15;
        var c = "Hello";


- Support for specifying conventional datatype explicitly for variables and floating point handling.

        Int, Char, Bool, Void, Float        # Datatypes

- New datatypes for providing quantum computiong simulation support.

        Qubit

- Support for multiple qubit calculations using quregisters.

        Qureg qr[] <- new Qureg[10];
        # qr[0] : Qubit_0
        # qr[1] : Qubit_1
        # qr[2] : Qubit_2
        # qr[3] : Qubit_3
        # qr[4] : Qubit_4
        # qr[5] : Qubit_5
        # qr[6] : Qubit_6
        # qr[7] : Qubit_7
        # qr[8] : Qubit_8
        # qr[9] : Qubit_9

- Implementation of short-hand Quantum Gates

    - Hadamard Gate: **H**
    - Phase Gate: **S**
    - Rotation Gate: **R(x)**
    
            x: Angle value (in degrees)(Int/Float)
    - CNOT Gate:
        - Control gate: **Co**
        - NOT gate: **Cx**
    - NOOP Gate: **~**
    - Pauli Gates
        - Pauli X gate: **X**
        - Pauli Y gate: **Y**
        - Pauli Z gate: **Z**
    - Swap Gate: **Sx**
    - Quantum Fourier Transform (QFT) Gate: **Q**
    - Inverse QFT Gate: **Qi**

- Easy to understand syntax, oriented towards ease of visualisation of operations on qubits using quantum gates.

        Qureg qr[] = new Qureg[2];

        qr[0] -> ( H | S | ~ | Co | ~ | R(10.25) | H | X | ~ | Co | ~ | H | X );
		qr[1] -> ( H | S | H | Cx | H |    S     | H | X | H | Cx | H | H | X );

        # OR #

        qr = {
            [0] -> ( H | S | ~ | Co | ~ | R(10.25) | H | X | ~ | Co | ~ | H | X );
		    [1] -> ( H | S | H | Cx | H |    S     | H | X | H | Cx | H | H | X );
        };


## Example syntax

        # file: example.quaC

        func Grover_search => (qr @ Qureg) @ Void {
            qr = {
                # Grover search for quregister of 2 qubits
                [0] -> ( H | ~ | ~ | Co | ~ | ~ | H | X | ~ | Co | ~ | H | X );
                [1] -> ( H | S | H | Cx | H | S | H | X | H | Cx | H | H | X );
            }

            for (var i in [2 :: qr.size]) {
                qr[i] -> ( ~ );
            }
        }

        func main => () @ Int {
            var n = input("Enter register size: ");
            Qureg qr[] = new Qureg[n];

            print("Qureg1:" + qr) @ ALL;

            Grover_search <- qr;    # Calling the function
            print("Calling Grover_Search()\n\n");

            print("Qureg1: " + qr) @ NONZERO;
        }

## OUTPUT
        $ qcc example.quaC
            Enter register size: 3

            Qureg1: [0] => {1.000000 + i0.000000} |000>   100.00 %
                    [1] => {0.000000 + i0.000000} |001>   0.00 %
                    [2] => {0.000000 + i0.000000} |010>   0.00 %
                    [3] => {0.000000 + i0.000000} |011>   0.00 %
                    [4] => {1.000000 + i0.000000} |100>   0.00 %
                    [5] => {0.000000 + i0.000000} |101>   0.00 %
                    [6] => {0.000000 + i0.000000} |110>   0.00 %
                    [7] => {0.000000 + i0.000000} |111>   0.00 %

            Calling Grover_Search()

            Qureg1: [1] => {-1.000000 + i0.000000} |001>   100.00%

** **NOTE: Qua-C is still under developement stage...**
