#include "Elf.h"

int Elf::GetMagic()
{
    return magic;
}

void Elf::SetMagic(int _magic)
{
    magic = _magic;
}
