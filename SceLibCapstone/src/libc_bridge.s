

	.align 2
	.balign 4
	.text
	.cpu cortex-a9
	.arch armv7-a
	.syntax unified
	.arm
	.fpu neon


	.global memset
	.type   memset, %function
memset:
	b sceClibMemset

	.global memcpy
	.type   memcpy, %function
memcpy:
	b sceClibMemcpy

	.global memmove
	.type   memmove, %function
memmove:
	b sceClibMemmove

	.global strstr
	.type   strstr, %function
strstr:
	b sceClibStrstr

	.global strlen
	.type   strlen, %function
strlen:
	mvn r1, #0
	b sceClibStrnlen

	.global strncat
	.type   strncat, %function
strncat:
	b sceClibStrncat

	.global strcmp
	.type   strcmp, %function
strcmp:
	b sceClibStrcmp

	.global strncpy
	.type   strncpy, %function
strncpy:
	b sceClibStrncpy

	.global strchr
	.type   strchr, %function
strchr:
	b sceClibStrchr

	.global printf
	.type   printf, %function
printf:
	b sceClibPrintf

	.global snprintf
	.type   snprintf, %function
snprintf:
	b sceClibSnprintf
