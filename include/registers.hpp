#pragma once


enum class registers{
	AL,AX,EAX,

	CL,CX,ECX,

	DL,DX,EDX,

	BL,BX,EBX,

	AH,SP,ESP,

	CH,BP,EBP,

 	DH,SI,ESI,

	BH,DI,EDI
};





#define AX_REGISTERS_WL 0b000

#define CX_REGISTERS_WL 0b001

#define DX_REGISTERS_WL 0b010

#define BX_REGISTERS_WL 0b011

#define SP_REGISTERS_W_AH 0b100

#define BP_REGISTERS_W_CH 0b101

#define SI_REGISTERS_W_DH 0b110

#define DI_REGISTERS_W_BH 0b111