#pragma once


enum class registers{
	// 8 bit registers
	al = 0,
	cl,
	dl,
	bl,
	ah,
	ch,
	dh,
	bh,

	// 16 bit registers
	ax,
	cx,
	dx,
	bx,
	sp,
	bp,
	si,
	di,

	// 32 bit registers

	eax,
	ecx,
	edx,
	ebx,
	esp,
	ebp,
	esi,
	edi,

	// 64 bit registers

	rax,
	rcx,
	rdx,
	rbx,
	rsp,
	rbp,
	rsi,
	rdi,

	// 16 bit segment registers
	es,
	cs,
	ss,
	ds,
	fs,
	gs

};



struct register_info{
    unsigned char reg: 3;
    unsigned int size;
    bool is_segment;
}__attribute((packed));


extern "C" struct register_info registers_table[];