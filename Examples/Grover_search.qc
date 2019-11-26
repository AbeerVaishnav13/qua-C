# Two qubit grover search to find the number '2' or '10' in binary representation

func grover_search {
	[H, H]
	[-, S]
	[-, H]
	[@, X]
	[-, H]
	[-, S]
	[H, H]
	[X, X]
	[-, H]
	[@, X]
	[-, H]
	[X, X]
	[H, H]
}

quReg a = new quReg[2] => 'quReg1'
a.setPrecision(6)

a.Pa()
a.grover_search()
a.Pa()
