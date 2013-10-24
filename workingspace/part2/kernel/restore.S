.file "restore.S"

.text
.global restore

restore:
	LDMFD sp!, {r8, pc}
