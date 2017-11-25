#ifndef MAIN
#define MAIN
#include <Python.h>
#include <string.h>
#include "monty.h"
#include "alphabeta.h"
#include "connect4.h"

static PyObject * getBestMovePython(PyObject *self, PyObject *args) {
    char * moves; int width, height, numTrials, type;
    if (!PyArg_Parse(args, "(siiii)", &moves, &width, &height, &numTrials, &type)) /* convert Python -> C */
        return NULL;                            /* null=raise exception */
    std::string str = std::string(moves);
    Game g = Game(width, height);
    for (auto c : str)
    {
        g.makeMove(c - '0');
    }
    
    if (type == 0) {
        Monty ai(numTrials);
        return Py_BuildValue("i", ai.getBestMove(g));
    }
    AlphaBeta ai(numTrials);
    return Py_BuildValue("i", ai.getBestMove(g));

}

/* registration table */
static PyMethodDef ai_methods[] = {
    /* name, &func, fmt, doc */
    {"get_best_move", getBestMovePython, METH_VARARGS, "func doc"},
    {NULL, NULL, 0, NULL}                           /* end of table marker */
};

/* module definition structure */
static struct PyModuleDef ai_module = {
    PyModuleDef_HEAD_INIT, "connect4_ai", /* name of module */
    "mod doc",      /* module documentation, may be NULL */
    -1,             /* size of per-interpreter module state, -1=in global vars */
    ai_methods   /* link to methods table */
};

/* module initializer */
PyMODINIT_FUNC PyInit_connect4_ai()         /* called on first import */
{                                     /* name matters if loaded dynamically */
  return PyModule_Create(&ai_module);
}

#endif
