// ten_byte_asm.cpp: определяет точку входа для консольного приложения.
//
//#include <cstdio>
//#include <tchar.h>
//#include <cstdlib>
//#include <iostream>
//#include <cstring>

class uDynamic
{
public:
	uDynamic(unsigned __int8 size);
	uDynamic(const uDynamic& a);
	~uDynamic();
	uDynamic& operator=(const uDynamic& a_src);

	unsigned __int8* data;
	unsigned __int8 size;
	//int numb = 0;
};



uDynamic sum(uDynamic a, uDynamic b);
uDynamic minus(uDynamic a, uDynamic b);
uDynamic and (uDynamic a, uDynamic b);
uDynamic or (uDynamic a, uDynamic b);
uDynamic neg(uDynamic a);
uDynamic inc(uDynamic a);
uDynamic inv(uDynamic a);

uDynamic::uDynamic(unsigned __int8 size)
{
	this->size = size;
	this->data = new unsigned __int8[size];
}

uDynamic::uDynamic(const uDynamic& a)
{
	this->size = a.size;
	//this->numb = a.numb + 1;
	this->data = new unsigned __int8[this->size];
	//memcpy(this->data, a.data, this->size);
	for (int i = 0; i < this->size; i++)
	{
		a.data[i] = this->data[i];
	}
}

uDynamic::~uDynamic()
{
	//std::cout << "term "<<numb;
	delete this->data;
}

uDynamic& uDynamic::operator=(const uDynamic& src)
{
	this->~uDynamic();
	this->size = src.size;
	//this->numb = src.numb + 1;
	this->data = new unsigned __int8[this->size];
	//memcpy(this->data, src.data, this->size);;
	for (int i = 0; i < this->size; i++)
	{
		src.data[i] = this->data[i];
	}
	return *this;
	// TODO: вставьте здесь оператор return

}

#define byteSize 20 
int test()
{
	unsigned __int8 a = 255, b = 2, of = 0;
	uDynamic s1(byteSize), s2(byteSize);
	for (int i = 0; i < s1.size; i++)
	{
		s1.data[i] = 0x86;//rand() + 0x20;
		s2.data[i] = 0x80;//rand();// +8;
	}
	s1.data[0] = 1;

	//s2.data[0] = 1;
	/*for (int i = s1.size - 1; i >= 0; i--)
		printf("%02X ", s1.data[i]);
	//putchar('\n');
	for (int i = s1.size - 1; i >= 0; i--)
		printf("%02X ", s2.data[i]);
	putchar('\n');*/
	//uDynamic res(0);// = new uDynamic(0);
	/*inc(s1);
	for (int i = s1.size - 1; i >= 0; i--)
		printf("%02X ", s1.data[i]);
	putchar('\n');*/
	//minus(s1, s2, res);

	uDynamic res(0);
	res = and (s1, s2);

	/*for (int i = s1.size - 1; i >= 0; i--)
		printf("%02X ", res.data[i]);
	putchar('\n');*/
	//system("pause");
	//delete res;
	return 0;
}

uDynamic sum(uDynamic a, uDynamic b)
{
	unsigned __int8 it4, it1;
	int len = (a.size > b.size ? a.size : b.size);
	void* ap = a.data, * rp, * a2p = b.data;
	void* bp = b.data;
	uDynamic res(len);

	res.data = new unsigned __int8[len];
	rp = res.data;
	_asm {
		movzx ax, len
		mov bl, 4
		div bl
		mov it4, al
		mov it1, ah

		mov bl, ah
		movzx ecx, al
		cmp ecx, 0
		JZ esum4
		pushf
		sum4 :
		mov ebx, ap
			mov eax, DWORD PTR[ebx];
		mov ebx, a2p
			mov ebx, DWORD PTR[ebx]
			popf
			adc eax, ebx
			pushf
			mov ebx, rp
			mov DWORD PTR[ebx], eax

			add ap, 4
			add a2p, 4
			add rp, 4
			LOOP sum4
			esum4 :

		movzx ecx, it1
			cmp ecx, 0
			JZ esum1
			sum1 :
		mov ebx, ap
			mov al, BYTE PTR[ebx];
		mov ebx, a2p
			mov bl, BYTE PTR[ebx]
			popf
			adc al, bl
			pushf
			mov ebx, rp
			mov BYTE PTR[ebx], al
			add ap, 1
			add a2p, 1
			add rp, 1
			LOOP sum1
			esum1 :

		popf
	}

	return res;
}

uDynamic and (uDynamic a, uDynamic b)
{
	unsigned __int8 it4, it1;
	int len = (a.size > b.size ? a.size : b.size);
	void* ap = a.data, * rp, * a2p = b.data;
	void* bp = b.data;
	uDynamic res(len);

	res.data = new unsigned __int8[len];
	rp = res.data;
	_asm {
		movzx ax, len
		mov bl, 4
		div bl
		mov it4, al
		mov it1, ah

		mov bl, ah
		movzx ecx, al
		cmp ecx, 0
		JZ esum4
		pushf
		sum4 :
		mov ebx, ap
			mov eax, DWORD PTR[ebx];
		mov ebx, a2p
			mov ebx, DWORD PTR[ebx]

			and eax, ebx

			mov ebx, rp
			mov DWORD PTR[ebx], eax

			add ap, 4
			add a2p, 4
			add rp, 4
			LOOP sum4
			esum4 :

		movzx ecx, it1
			cmp ecx, 0
			JZ esum1
			sum1 :
		mov ebx, ap
			mov al, BYTE PTR[ebx];
		mov ebx, a2p
			mov bl, BYTE PTR[ebx]
			and al, bl
			mov ebx, rp
			mov BYTE PTR[ebx], al
			add ap, 1
			add a2p, 1
			add rp, 1
			LOOP sum1
			esum1 :

		popf
	}

	return res;
}

uDynamic or (uDynamic a, uDynamic b)
{
	unsigned __int8 it4, it1;
	int len = (a.size > b.size ? a.size : b.size);
	void* ap = a.data, * rp, * a2p = b.data;
	void* bp = b.data;
	uDynamic res(len);

	res.data = new unsigned __int8[len];
	rp = res.data;
	_asm {
		movzx ax, len
		mov bl, 4
		div bl
		mov it4, al
		mov it1, ah

		mov bl, ah
		movzx ecx, al
		cmp ecx, 0
		JZ esum4
		pushf
		sum4 :
		mov ebx, ap
			mov eax, DWORD PTR[ebx];
		mov ebx, a2p
			mov ebx, DWORD PTR[ebx]

			or eax, ebx

			mov ebx, rp
			mov DWORD PTR[ebx], eax

			add ap, 4
			add a2p, 4
			add rp, 4
			LOOP sum4
			esum4 :

		movzx ecx, it1
			cmp ecx, 0
			JZ esum1
			sum1 :
		mov ebx, ap
			mov al, BYTE PTR[ebx];
		mov ebx, a2p
			mov bl, BYTE PTR[ebx]
			or al, bl
			mov ebx, rp
			mov BYTE PTR[ebx], al
			add ap, 1
			add a2p, 1
			add rp, 1
			LOOP sum1
			esum1 :

		popf
	}

	return res;
}

uDynamic minus(uDynamic a, uDynamic b)
{
	b = neg(b);
	return sum(a, b);
}

uDynamic neg(uDynamic a)
{
	unsigned __int8 it4, it1;
	int len = a.size;
	void* ap = a.data;

	_asm {
		movzx ax, len
		mov bl, 4
		div bl
		mov it4, al
		mov it1, ah
		//inv
		mov ebx, ap//inv pointer

		movzx ecx, al//4byte inv
		cmp ecx, 0
		JZ einv4
		inv4 :
		mov eax, DWORD PTR[ebx];
		not eax
			mov DWORD PTR[ebx], eax
			add ebx, 4
			LOOP inv4
			einv4 :

		movzx ecx, it1//1byte inv
			cmp ecx, 0
			JZ einv1
			inv1 :
		mov al, BYTE PTR[ebx]
			not al
			mov BYTE PTR[ebx], al
			add ebx, 1
			LOOP inv1
			einv1 :


		//inv end
		//inc beg

		mov ebx, ap

			movzx ecx, it4
			cmp ecx, 0
			JZ esum4
			sub ebx, 4
			sum4 :
		add ebx, 4
			mov eax, DWORD PTR[ebx];
		add eax, 1
			mov DWORD PTR[ebx], eax
			JC sum4

			esum4 :
		movzx ecx, it1
			cmp ecx, 0
			JZ esum1
			sub ebx, 1
			sum1 :
			mov al, BYTE PTR[ebx];
		add al, 1
			mov BYTE PTR[ebx], al
			JC sum1
			esum1 :


		//inc end
	}

	return a;
}

uDynamic inc(uDynamic a)
{
	unsigned __int8 it4, it1;
	int len = a.size;
	void* ap = a.data;

	_asm {
		movzx ax, len
		mov bl, 4
		div bl
		mov it4, al
		mov it1, ah

		//inc beg
		mov ebx, ap

		movzx ecx, it4
		cmp ecx, 0
		JZ esum4
		sub ebx, 4
		sum4 :
		add ebx, 4
			mov eax, DWORD PTR[ebx];
		add eax, 1
			mov DWORD PTR[ebx], eax
			JC sum4

			esum4 :
		movzx ecx, it1
			cmp ecx, 0
			JZ esum1
			sub ebx, 1
			sum1 :
			mov al, BYTE PTR[ebx];
		add al, 1
			mov BYTE PTR[ebx], al
			JC sum1
			esum1 :
		//inc end
	}
	return a;
}

uDynamic inv(uDynamic a)
{
	unsigned __int8 it4, it1;
	int len = a.size;
	void* ap = a.data;

	_asm {
		movzx ax, len
		mov bl, 4
		div bl
		mov it4, al
		mov it1, ah
		mov ebx, ap//inv pointer

		movzx ecx, al//4byte inv
		cmp ecx, 0
		JZ einv4
		inv4 :
		mov eax, DWORD PTR[ebx];
		not eax
			mov DWORD PTR[ebx], eax
			add ebx, 4
			LOOP inv4
			einv4 :

		movzx ecx, it1//1byte inv
			cmp ecx, 0
			JZ einv1
			inv1 :
		mov al, BYTE PTR[ebx]
			not al
			mov BYTE PTR[ebx], al
			add ebx, 1
			LOOP inv1
			einv1 :
		//inv end
	}
	return a;
}
