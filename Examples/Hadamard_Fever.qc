# Hadamard Fever for 28 qubits!!! (only attempt to run if your system has a minimum of 8GB RAM)

func Hadamard_Fever {
	[H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H]	
	[H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H]
}

quReg a = new quReg[28] => 'quReg1'
a.setPrecision(6)

a.Pnz()
a.Hadamard_Fever()
a.Pnz()
