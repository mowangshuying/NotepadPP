#pragma once


enum class CodeId {
	Unknown,
	Ansi,
	Utf8,
	Utf8Bom,
	Utf16LE,
	Utf16LEBom,
	Utf16BE,
    Utf16BEBom,
	GBK,
	EucJp,
	ShiftJis,
	EucKr,
	Koi8R,
	Tis620,
	Big5,
	__End,
};

enum class LineEnd
{
	Unknown,
	Dos,//
	Unix,
	Mac,
}; 