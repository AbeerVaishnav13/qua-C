# Hadamard Fever for 28 qubits!!! (only attempt to run if your system has a minimum of 8GB RAM)

func Hadamard_Fever {
	[H, H, H, H, H, H, H, H, H, H, H, H, H, H, -, -, -, -, -, -, -, -, -, -, -, -, -, -]
	Pnz()
	[-, -, -, -, -, -, -, -, -, -, -, -, -, -, H, H, H, H, H, H, H, H, H, H, H, H, H, H]
	
	[H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H]
}

quReg a = init [28]
a.name = "quReg1: "
a.prec = 6

a.Pnz()
a.Hadamard_Fever()
a.Pnz()
