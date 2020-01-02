func shor {
	[X, -, -, -, H, H, H, H]

	[-, X, -, -, @, -, -, -]
	[-, -, X, -, @, -, -, -]

	[-, X, -, @, -, @, -, -]
	[-, @, -, X, -, @, -, -]
	[-, X, -, @, -, @, -, -]
	[X, -, @, -, -, @, -, -]
	[@, -, X, -, -, @, -, -]
	[X, -, @, -, -, @, -, -]

	[-, -, -, -, Q, Q, Q, Q]
}

quReg q = init [8]
q.name = "qr1: "
q.prec = 6

q.Pnz()
q.shor()
q.Pnz()

######################################
# Pauli-X: X
# Pauli-Y: Y
# Pauli-Z: Z
# Phase: S
# Rotation: R
# Hadamard: H
# Swap: x
# QFT: ~
# Control: @
# Inverse Control: o
