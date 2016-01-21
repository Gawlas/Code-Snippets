void sincos(float angle, float* sine, float* cosine)
{
	__asm
	{
		mov eax, sine
		mov edx, cosine

		fld angle
		fsincos
		fstp dword ptr [edx]
		fstp dword ptr [eax]
	}
}