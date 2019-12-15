#include <Python.h>
#include <iostream>
//#include "Source.cpp"
/*
 * Implements an example function.
 */
PyDoc_STRVAR(module2_example_doc, "example(obj, number)\
\
Example function");


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
		s1.data[i] = rand() + 0x20;
		s2.data[i] = rand();// +8;
	}
	s1.data[0] = 1;

	//s2.data[0] = 1;
	for (int i = s1.size - 1; i >= 0; i--)
		printf("%02X ", s1.data[i]);
	//putchar('\n');
	for (int i = s1.size - 1; i >= 0; i--)
		printf("%02X ", s2.data[i]);
	putchar('\n');
	//uDynamic res(0);// = new uDynamic(0);
	/*inc(s1);
	for (int i = s1.size - 1; i >= 0; i--)
		printf("%02X ", s1.data[i]);
	putchar('\n');*/
	//minus(s1, s2, res);

	uDynamic res(0);
	res = and (s1, s2);

	for (int i = s1.size - 1; i >= 0; i--)
		printf("%02X ", res.data[i]);
	putchar('\n');
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



PyObject *module2_example(PyObject *self, PyObject *args, PyObject *kwargs) {
    /* Shared references that do not need Py_DECREF before returning. */
    /*PyObject *obj = NULL;
    int number = 0;
	*/
    /* Parse positional and keyword arguments */
	/*
    static char* keywords[] = { "obj", "number", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi", keywords, &obj, &number)) {
        return NULL;
    }
	*/
    /* Function implementation starts here */
	/*
    if (number < 0) {
        PyErr_SetObject(PyExc_ValueError, obj);
        return NULL;   
    }
	*/
    test();

    Py_RETURN_NONE;
}

/*
 * List of functions to add to module2 in exec_module2().
 */
static PyMethodDef module2Methods[] = {
    { "example", (PyCFunction)module2_example, METH_VARARGS | METH_KEYWORDS, module2_example_doc },
    { NULL, NULL, 0, NULL } /* marks end of array */
};

/*
 * Initialize module2. May be called multiple times, so avoid
 * using static state.
 */
int exec_module2(PyObject *module) {
    //PyModule_AddFunctions(module, module2_functions);
	PyModule_AddFunctions(module, module2Methods);
    PyModule_AddStringConstant(module, "__author__", "Oleg");
    PyModule_AddStringConstant(module, "__version__", "1.0.0");
    PyModule_AddIntConstant(module, "year", 2019);

    return 0; /* success */
}

/*
 * Documentation for module2.
 */
PyDoc_STRVAR(module2_doc, "The module2 module");


static PyModuleDef_Slot module2_slots[] = {
    { Py_mod_exec, exec_module2 },
    { 0, NULL }
};

static struct PyModuleDef module2_def = {
    PyModuleDef_HEAD_INIT,
    "module2",
    module2_doc,
    0,              /* m_size */
	module2Methods,           /* m_methods */
	
};

PyMODINIT_FUNC PyInit_module2() {
    return PyModuleDef_Init(&module2_def);
}
