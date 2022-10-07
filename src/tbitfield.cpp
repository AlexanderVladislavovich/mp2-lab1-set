// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
  BitLen = len;
  if (BitLen < 32)
  {
    MemLen = 1;
  }
  else 
  {
    MemLen = (BitLen >> 5) + 1;
  }
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
  {
    pMem[i] = 0;
  }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
  {
    pMem[i] = bf.pMem[i];
  }
}

TBitField::~TBitField()
{
  delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return ((n-1) / sizeof(int) * 8); 
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  return MemLen -  (1 << ((n - 1) % (sizeof(int) * 8)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  int a = GetMemMask(n);
  int b = GetMemIndex(n);
  pMem[b] = pMem[b] | a;
}

void TBitField::ClrBit(const int n) // очистить бит
{
  int a = GetMemMask(n);
  int b = GetMemIndex(n);
  pMem[b] = pMem[b] & ~a;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  int a = GetMemMask(n);
  int b = GetMemIndex(n);
  return (pMem[b] & a);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this == &bf)
  {
    return *this;
  }
  delete[] pMem;
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  pMem = new TELEM[BitLen];
  for (int i = 0; i < BitLen; i++)
  {
    pMem = bf.pMem;
  }
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (BitLen != bf.BitLen)
  {
    cout << "sizes don't match" << endl;
    return 0;
  }
  else
  {
    for (int i = 0; i < MemLen; i++)
    {
      if (pMem[i] != bf.pMem[i])
      {
        return 0;
      }
      else
      {
        if (i == MemLen - 1)
        {
          return 1;
        }
      }
    }
  }
  return FAKE_INT;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{

  if (BitLen != bf.BitLen)
  {
    cout << "sizes don't match" << endl;
    return 1;
  }
  else
  {
    for (int i = 0; i < MemLen; i++)
    {
      if (pMem[i] != bf.pMem[i])
      {
        return 1;
      }
      else
      {
        if (i == MemLen - 1)
        {
          return 0;
        }
      }
    }
  }
  return FAKE_INT;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int copy1, copy2;
  if (BitLen > bf.BitLen)
  {
    copy1 = BitLen;
    copy2 = MemLen;
  }
  else
  {
    copy1 = bf.BitLen;
    copy2 = bf.MemLen;
  }

  TBitField f(copy1);

  for (int i = 0; i < copy2; i++)
  {
    f.pMem[i] = pMem[i] | bf.pMem[i];
  }

  return f;
    return FAKE_BITFIELD;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{

  int copy1, copy2;
  if (BitLen > bf.BitLen)
  {
    copy1 = BitLen;
    copy2 = MemLen;
  }
  else
  {
    copy1 = bf.BitLen;
    copy2 = bf.MemLen;
  }

  TBitField f(copy1);

  for (int i = 0; i < copy2; i++)
  {
    f.pMem[i] = pMem[i] & bf.pMem[i];
  }

  return f;
    return FAKE_BITFIELD;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField f(BitLen);
  for (int i = 0; i < MemLen; i++)
  {
    f.pMem[i] = ~(pMem[i]);
  }
    return FAKE_BITFIELD;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  for (int i = 0; i < bf.GetLength(); i++)
  {
    int a = bf.GetBit(i);
    istr >> a;
  }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.GetLength(); i++)
  {
    ostr << bf.GetBit(i);
  }
  ostr << "\n";

    return ostr;
}
