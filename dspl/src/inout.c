/*
* Copyright (c) 2015-2019 Sergey Bakhurin
* Digital Signal Processing Library [http://dsplib.org]
*
* This file is part of DSPL.
*
* is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* DSPL is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar.    If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dspl.h"



#ifdef DOXYGEN_ENGLISH

#endif
#ifdef DOXYGEN_RUSSIAN

#endif
int DSPL_API addlog(char* str, char* fn)
{
    FILE* pFile = NULL;
    if(!str)
        return ERROR_PTR;

    pFile = fopen(fn, "a+");
    if(pFile == NULL)
        return ERROR_FOPEN;

    fprintf(pFile, "%s\n", str);

    fclose(pFile);
    return RES_OK;
}







#ifdef DOXYGEN_ENGLISH

#endif
#ifdef DOXYGEN_RUSSIAN

#endif
void DSPL_API dspl_info()
{
    printf("\n\n        D S P L - 2.0\n");
    printf("        version 2.20.01.09\n");
    printf("\n        Copyright (C) 2015-2020\n");
    printf("        Sergey Bakhurin                www.dsplib.org\n");
    printf("        ---------------------------------------------\n");
    printf("        BLAS and LAPACK ver.: 3.8.0    www.netlib.org\n");

}


#ifdef DOXYGEN_ENGLISH

#endif
#ifdef DOXYGEN_RUSSIAN

#endif
int DSPL_API readbin(char* fn, void** x, int* k, int* dtype)
{
    FILE* pFile = NULL;
    int n, m, t, err;

    if(!x)
        return ERROR_PTR;
    if(!fn)
        return ERROR_FNAME;

    pFile = fopen(fn, "rb");
    if(pFile == NULL)
            return ERROR_FOPEN;

    if(fread(&t, sizeof(int), 1, pFile) != 1)
    {
        err = ERROR_FREAD_SIZE;
        goto exit_label;
    }

    if(dtype)
        *dtype = t;

    if(fread(&n, sizeof(int), 1, pFile) != 1)
    {
        err = ERROR_FREAD_SIZE;
        goto exit_label;
    }

    if(fread(&m, sizeof(int), 1, pFile) != 1)
    {
        err = ERROR_FREAD_SIZE;
        goto exit_label;
    }

    if(k)
        *k = n*m;
    switch(t)
    {
        case DAT_DOUBLE:
            (*x) = (*x) ? realloc(*x, n*m*sizeof(double)) :
                          malloc(n*m*sizeof(double));
            if(fread(*x, sizeof(double), n*m, pFile) != n*m)
            {
                err = ERROR_FREAD_SIZE;
                goto exit_label;
            }

            break;
        case DAT_COMPLEX:
            (*x) = (*x) ? realloc(*x, n*m*sizeof(complex_t)) :
                          malloc(n*m*sizeof(complex_t));
            if(fread(*x, sizeof(complex_t), n*m, pFile) != n*m)
            {
                err = ERROR_FREAD_SIZE;
                goto exit_label;
            }
            break;
        default:
            err = ERROR_DAT_TYPE;
            goto exit_label;
    }
    err = RES_OK;
exit_label:
    if(pFile)
        fclose(pFile);
    return err;
}


#ifdef DOXYGEN_ENGLISH
/*! ****************************************************************************
\ingroup IN_OUT_GROUP
\fn    int writebin(void* x, int n, int dtype, char* fn)
\brief Save 1D vector to the binary file

Function saves real or complex 1D vector size `n` to the binary file `fn`. \n\n

File format supports 1D and 2D arrays and has follow format: \n\n

\verbatim
type     4 bytes type int.
         Can take on value:
         DAT_DOUBLE,  if x pointer to the real vector;
         DAT_COMPLEX, if x pointer to the complex vector;

n        4 bytes type int.
         Number of array rows.

m        4 bytes type int.
         Number of array columns.
         This parameter equals 1 because this function saves 1D vector.

data     Data in binary raw.
         Data size is:
         n * sizeof(double),    if dtype==DAT_DOUBLE;
         n * sizeof(complex_t), if dtype==DAT_COMPLEX.
\endverbatim

Binary file can be used for algorithms verification by external packages like
GNU Octave, Matlab, Python because the function writes to a file
without loss of accuracy. \n \n

\param[in] x
Pointer to the input vector. \n
Vector size is `[n x 1]`. \n \n

\param[in] n
Size of input vector. \n \n

\param[in] dtype
Type of data. \n

Can be one of follow: \n
`DAT_DOUBLE` -- real data; \n
`DAT_COMPLEX` -- complex data. \n \n

\param[in] fn
File name. \n \n

\return
`RES_OK` if file is saved successfully. \n
Else \ref ERROR_CODE_GROUP "code error".

Reading saved binary file from GNU Octave or Matlab:
\code{.m}
function [dat, n, m] = readbin(fn)
    fid = fopen(fn);
    if(~fid)
        error('cannot to open file');
    end
    type = fread(fid, 1, 'int32');
    n    = fread(fid, 1, 'int32');
    m    = fread(fid, 1, 'int32');

    if(type==0)
        dat = fread(fid, [n*m, 1], 'double');
    end

    if(type==1)
        y = fread(fid, [n*m*2, 1], 'double');
        dat = y(1:2:end) + 1i * y(2:2:end);
    end

    dat = reshape(dat, n, m);

    fclose(fid);
end
\endcode

\author Sergey Bakhurin www.dsplib.org
***************************************************************************** */
#endif
#ifdef DOXYGEN_RUSSIAN
/*! ****************************************************************************
\ingroup IN_OUT_GROUP
\fn    int writebin(void* x, int n, int dtype, char* fn)
\brief ��������� ������ � �������� ����

������� ��������� �������� ��� ����������� ������ ������
������� `[n x 1]` � �������� ���� `fn`.    \n \n

���� �������� ������������� ��� �������� ��� ����������,
��� � ��������� �������� � ����� ��������� ������:    \n \n
\verbatim

type     4 ����� ���� int.
         ����� ��������� ��������:
         DAT_DOUBLE,    ���� x ��������� �� ������ ������������ �����;
         DAT_COMPLEX, ���� x ��������� �� ������ ����������� �����.

n        4 ����� ���� int.
         ���������� ����� ������.

m        4 ����� ���� int.
         ���������� �������� ������.
         ��� ���������� ������� ������ ����� 1.

data     ������ � �������� ����.
         ������ ������:
         n * sizeof(double),    ���� dtype==DAT_DOUBLE;
         n * sizeof(complex_t), ���� dtype==DAT_COMPLEX.
\endverbatim

���� ����� ���� ����������� ��� ����������� ���������� ���������� ��������,
������ ��� GNU Octave, Matlab, Python � �.�. \n \n

\param[in] x
��������� �� ������ ������.    \n
������ ������� `[n x 1]`. \n
\n

\param[in] n
������ ������� ������. \n
\n

\param[in] dtype
��� ������. \n
����� ��������� ��������: \n
`DAT_DOUBLE`  -- ������������ ������; \n
`DAT_COMPLEX` -- ����������� ������. \n
\n

\param[in] fn
��� �����. \n
\n

\return
`RES_OK` --- ���� �������� �������. \n
� ��������� ������ \ref ERROR_CODE_GROUP "��� ������". \n

\note
������ ������� ���������� ������ � ���� ��� ������ ��������,
������� ������������� ������������ �� ��� ����������� ������ DSPL. \n
\n


������� ��� ������ ��������� ����� � GNU Octave � Matlab:
\code{.m}
function [dat, n, m] = readbin(fn)
    fid = fopen(fn);
    if(~fid)
        error('cannot to open file');
    end
    type = fread(fid, 1, 'int32');
    n    = fread(fid, 1, 'int32');
    m    = fread(fid, 1, 'int32');

    if(type==0)
        dat = fread(fid, [n*m, 1], 'double');
    end

    if(type==1)
        y = fread(fid, [n*m*2, 1], 'double');
        dat = y(1:2:end) + 1i * y(2:2:end);
    end

    dat = reshape(dat, n, m);

    fclose(fid);
end
\endcode

\author ������� ������ www.dsplib.org
***************************************************************************** */
#endif
int DSPL_API writebin(void* x, int n, int dtype, char* fn)
{
    int k, res;
    FILE* pFile = NULL;

    if(!x)
        return ERROR_PTR;
    if(n < 1)
        return ERROR_SIZE;
    if(!fn)
        return    ERROR_FNAME;

    pFile = fopen(fn, "wb");
    if(pFile == NULL)
            return ERROR_FOPEN;


    if(fwrite(&dtype, sizeof(int), 1, pFile) != 1)
    {
        res = ERROR_FWRITE_SIZE;
        goto exit_label;
    }



    if(fwrite(&n, sizeof(int), 1, pFile) != 1)
    {
        res = ERROR_FWRITE_SIZE;
        goto exit_label;
    }

    k = 1;
    if(fwrite(&k, sizeof(int), 1, pFile) != 1)
    {
        res = ERROR_FWRITE_SIZE;
        goto exit_label;
    };

    switch(dtype)
    {
        case DAT_DOUBLE:
            if(fwrite((double*)x, sizeof(double), n, pFile) != n)
            {
                res = ERROR_FWRITE_SIZE;
                goto exit_label;
            }
            break;
        case DAT_COMPLEX:
            if(fwrite((complex_t*)x,
                    sizeof(complex_t), n, pFile) != n)
            {
                res = ERROR_FWRITE_SIZE;
                goto exit_label;
            }
            break;
        default:
            res = ERROR_DAT_TYPE;
            goto exit_label;
    }
    res = RES_OK;
exit_label:
    if(pFile)
        fclose(pFile);
    return res;
}






#ifdef DOXYGEN_ENGLISH
/*! ****************************************************************************
\ingroup IN_OUT_GROUP
\fn int writetxt(double* x, double* y, int n, char* fn)
\brief Save real data \f$y(x)\f$ to the text file `fn`. \n

File format is:

\verbatim
x[0]        y[0]
x[1]        y[1]
...         ...
x[n-1]    y[n-1]
\endverbatim

Text file can be used to plotting data with a third-party program
for example, the GNUPLOT package (see \ref PLOT_GROUP). \n

\param[in] x
Pointer to the vector `x`.    \n
Vector size is `[n x 1]`. \n \n

\param[in] y
Pointer to the vector `y`. \n
Vector size is    `[n x 1]`. \n
This pointer can be `NULL`.
File will have only one column corresponds to `x` vector in this case. \n \n

\param[in] n
Size of vectors `x` and `y`. \n \n

\param[in] fn
File name. \n \n


\return
`RES_OK` if file is saved successfully. \n
Else \ref ERROR_CODE_GROUP "code error".

\note
This function rounds data when writing to a file.
So, it is not recommended to use it to verify algorithms.

\author Sergey Bakhurin www.dsplib.org
***************************************************************************** */
#endif
#ifdef DOXYGEN_RUSSIAN
/*! ****************************************************************************
\ingroup IN_OUT_GROUP
\fn    int writetxt(double* x, double* y, int n, char* fn)
\brief ��������� ������������ ������ � ��������� ����

������� ��������� ������������ ������ � ��������� ���� `fn`. \n
���� ����� ��������� ������: \n
\verbatim
x[0]        y[0]
x[1]        y[1]
...         ...
x[n-1]    y[n-1]
\endverbatim

���� ����� ���� ����������� ��� ���������� ������� ��������� ����������,
�������� ������� GNUPLOT (��. ������ \ref PLOT_GROUP). \n

\param[in] x
��������� �� ������ ������. \n
������ ������� `[n x 1]`. \n \n

\param[in] y
��������� �� ������ ������. \n
������ ������� `[n x 1]`. \n
����� ���� `NULL`. \n
���� ����� ��������� ������ ���� ������� ���������������
������� `x` ���� `y == NULL`. \n \n

\param[in] n
������ ������� ��������. \n \n

\param[in] fn
��� �����. \n \n

\return
`RES_OK` --- ���� �������� �������. \n
� ��������� ������ \ref ERROR_CODE_GROUP "��� ������": \n

\note
������ ������� ���������� ���������� ������ ��� ������ � ����.
������� �� ������������� ������������ �� ��� ����������� ������ DSPL.

\author ������� ������ www.dsplib.org
***************************************************************************** */
#endif
int DSPL_API writetxt(double* x, double* y, int n, char* fn)
{
    int k, err;
    FILE* pFile = NULL;
    if(!x)
        return ERROR_PTR;
    if(n < 1)
        return ERROR_SIZE;
    if(!fn)
        return ERROR_FNAME;

    pFile = fopen(fn, "w+");
    if(pFile == NULL)
        return ERROR_FOPEN;

    if(y)
    {
        for(k = 0; k < n; k++)
        {
            if(isnan(x[k]) || isnan(y[k]))
            {
                err = ERROR_NAN;
                goto exit_label;
            }
            if(isinf(x[k]) || isinf(y[k]))
            {
                err = ERROR_INF;
                goto exit_label;
            }
            fprintf(pFile, "%+.12E\t%+.12E\n", x[k], y[k]);
        }
    }
    else
    {
        for(k = 0; k < n; k++)
        {
            if(isnan(x[k]))
            {
                err = ERROR_NAN;
                goto exit_label;
            }
            if(isinf(x[k]))
            {
                err = ERROR_INF;
                goto exit_label;
            }
            fprintf(pFile, "%+.12E\n", x[k]);
        }
    }
    err = RES_OK;
exit_label:
    fclose(pFile);
    return err;
}


#ifdef DOXYGEN_ENGLISH

#endif
#ifdef DOXYGEN_RUSSIAN

#endif
int DSPL_API writetxt_cmplx(complex_t* x, int n, char* fn)
{
    int k;
    FILE* pFile = NULL;
    if(!x)
        return ERROR_PTR;
    if(n < 1)
        return ERROR_SIZE;
    if(!fn)
        return ERROR_FNAME;

    pFile = fopen(fn, "w+");
    if(pFile == NULL)
        return ERROR_FOPEN;

    for(k = 0; k < n; k++)
        fprintf(pFile, "%+.12E  %+.12E\n", RE(x[k]), IM(x[k]));


    fclose(pFile);
    return RES_OK;
}



#ifdef DOXYGEN_ENGLISH
/*! ****************************************************************************
\ingroup IN_OUT_GROUP
\fn int writetxt_int(int* x, int* y, int n, char* fn)

\brief Save interger data \f$y(x)\f$ to the text file `fn`. \n

File format

\verbatim
x[0]        y[0]
x[1]        y[1]
...         ...
x[n-1]    y[n-1]
\endverbatim

Text file can be used to plotting data with a third-party program
for example, the GNUPLOT package (see \ref PLOT_GROUP). \n

\param[in] x
Pointer to the interger vector `x`. \n
Vector size is `[n x 1]`. \n \n

\param[in] y
Pointer to the interger vector `y`. \n
Vector size is    `[n x 1]`. \n
This pointer can be `NULL`.
File will have only one column corresponds to `x` vector in this case. \n \n

\param[in] n
Size of vectors `x` and `y`. \n \n

\param[in] fn
File name. \n \n

\return
`RES_OK` if file is saved successfully. \n
Else \ref ERROR_CODE_GROUP "code error".

\author Sergey Bakhurin www.dsplib.org
***************************************************************************** */
#endif
#ifdef DOXYGEN_RUSSIAN
/*! ****************************************************************************
\ingroup IN_OUT_GROUP
\fn    int writetxt_int(int* x, int* y, int n, char* fn)

\brief ��������� ������������� ������ � ��������� ����

������� ��������� ������������� ������ � ��������� ���� `fn`. \n
���� ����� ��������� ������: \n

\verbatim
x[0]        y[0]
x[1]        y[1]
...         ...
x[n-1]    y[n-1]
\endverbatim

���� ����� ���� ����������� ��� ���������� ������� ��������� ����������,
�������� ������� GNUPLOT (��. ������ \ref PLOT_GROUP). \n

\param[in] x
��������� �� ������ ������.    \n
������ ������� `[n x 1]`. \n \n

\param[in] y
��������� �� ������ ������.    \n
������ �������    `[n x 1]`.    \n
����� ���� `NULL`.    \n
���� ����� ��������� ������ ���� ������� ���������������
������� `x` ���� `y == NULL`. \n \n

\param[in] n
������ ������� ��������. \n \n

\param[in] fn
��� �����. \n \n

\return
`RES_OK` --- ���� �������� �������. \n
� ��������� ������ \ref ERROR_CODE_GROUP "��� ������": \n

\author ������� ������ www.dsplib.org
***************************************************************************** */
#endif
int DSPL_API writetxt_int(int* x, int* y, int n, char* fn)
{
    int k;
    FILE* pFile = NULL;
    if(!x)
        return ERROR_PTR;
    if(n < 1)
        return ERROR_SIZE;
    if(!fn)
        return ERROR_FNAME;

    pFile = fopen(fn, "w+");
    if(pFile == NULL)
        return ERROR_FOPEN;

    if(y)
        for(k = 0; k < n; k++)
            fprintf(pFile, "% -14d\t% -14d\n", x[k], y[k]);

    else
        for(k = 0; k < n; k++)
            fprintf(pFile, "% -.14d\n", x[k]);

    fclose(pFile);
    return RES_OK;
}




#ifdef DOXYGEN_ENGLISH
/*! ****************************************************************************
\ingroup IN_OUT_GROUP
\fn    int writetxt_3d(double* x, int nx, double* y, int ny,
                       double* z, char* fn)

\brief Save data \f$ z(x,y)\f$    to the text file `fn` for 3D surface plotting.

Function \f$ z(x,y)\f$ describes as matrix `z[x[n], y[n]]` as it showed on the
follow figure:

\image html writetxt_3d_matrix.png

Matrix `z` writen in the memory by columns as it it showed on the figure by
red arrow. \n

Text file fas follow format: \n

\verbatim
x[0]        y[0]        z[0, 0]
x[1]        y[0]        z[1, 0]
x[2]        y[0]        z[2, 0]
...         ...         ...
x[nx-1] y[0]        z[nx-1, 0]

x[0]        y[1]        z[0, 1]
x[1]        y[1]        z[1, 1]
x[2]        y[1]        z[2, 1]
...         ...         ...
x[nx-1] y[1]        z[nx-1, 1]

...         ...         ...
...         ...         ...
...         ...         ...

x[0]        y[ny-1] z[0, ny-1]
x[1]        y[ny-1] z[1, ny-1]
x[2]        y[ny-1] z[2, ny-1]
...         ...         ...
x[nx-1] y[ny-1] z[nx-1, ny-1]
\endverbatim
Each `z` matrix value is writen on individual line corresponds to `x`
and `y` values. Matrix columns are separated from each other by an empty line.

The file can be used to build a 3D surface with a third-party program
for example, the GNUPLOT package (see \ref PLOT_GROUP). Also this format
supported by pgfplot3d packages of the Latex system. \n

\param[in] x
Pointer to the vector `x`. \n
Vector size is `[nx x 1]`. \n \n

\param[in] nx
Size of vector `x`. \n \n


\param[in] y
Pointer to the vector `y`. \n
Vector size is    `[ny x 1]`. \n\n

\param[in] ny
Size of vector `y`. \n\n

\param[in] z
Pointer to the matrix `z(x, y)`. \n
Size of matrix is    `[nx x ny]`. \n\n

\param[in] fn
3D data file name. \n\n


\return
`RES_OK` if file is saved successfully. \n
Else \ref ERROR_CODE_GROUP "code error".

Example of 3D surface plotting:

\include writetxt_3d_test.c

Program calcultes function

\f[
z(x,y) = x \exp(-x^2 -y^2)
\f]

and save data to the `dat/data3d.txt` file.\n
In addition, GNUPLOT built a 3D surface by data
 saved to the `dat/data3d.txt` file:

\image html writetxt_3d.png

\author Sergey Bakhurin www.dsplib.org
***************************************************************************** */
#endif
#ifdef DOXYGEN_RUSSIAN
/*! ****************************************************************************
\ingroup IN_OUT_GROUP
\fn int writetxt_3d(double* x, int nx, double* y, int ny, double* z, char* fn)

\brief ��������� ������ ��� ���������� 3D �������

������� ��������� ������������ ������ � ��������� ���� `fn`
��� ���������� 3D �����������. \n
������� \f$ z(x,y)\f$ ����������� �������� �������� `z[x[n], y[n]]`
��� ��� �������� �� �������

\image html writetxt_3d_matrix.png

������� `z` �������� � ������ �� ��������, ��� ��� �������� ������� ��������. \n
���� ����� ��������� ������: \n

\verbatim
x[0]        y[0]        z[0, 0]
x[1]        y[0]        z[1, 0]
x[2]        y[0]        z[2, 0]
...         ...         ...
x[nx-1] y[0]        z[nx-1, 0]

x[0]        y[1]        z[0, 1]
x[1]        y[1]        z[1, 1]
x[2]        y[1]        z[2, 1]
...         ...         ...
x[nx-1] y[1]        z[nx-1, 1]

...         ...         ...
...         ...         ...
...         ...         ...

x[0]        y[ny-1] z[0, ny-1]
x[1]        y[ny-1] z[1, ny-1]
x[2]        y[ny-1] z[2, ny-1]
...         ...         ...
x[nx-1] y[ny-1] z[nx-1, ny-1]
\endverbatim
����� �������, ������ �������� ������� `z` �������� ��������� ������� ��
���������������� ���������� `x` � `y`. ������� ������� �������� ������ �������.

���� ����� ���� ����������� ��� ���������� ������� ��������� ����������,
�������� ������� GNUPLOT (��. ������ \ref PLOT_GROUP). ����� ������ ������
�������������� �������� pgfplot3d ������������ ������� Latex. \n

\param[in] x
��������� �� ������ �������� ��� `x`. \n
������ ������� `[nx x 1]`. \n \n

\param[in] nx
������ ������� ��� `x`. \n \n


\param[in] y
��������� �� ������ ������ �������� ��� `y`. \n
������ �������    `[ny x 1]`. \n

\param[in] ny
������ ������� ��� `y`. \n \n

\param[in] z
��������� �� ������� �������� ������� `z(x, y)`. \n \n

\param[in] fn
��� �����. \n \n

\return
`RES_OK` --- ���� �������� �������. \n
� ��������� ������ \ref ERROR_CODE_GROUP "��� ������": \n

������ ������������� ������� � ���������� 3D ����������� ��������
� ��������� ��������:

\include writetxt_3d_test.c

������ ��������� ������������ � ������ ����������� �������

\f[
z(x,y) = x \exp(-x^2 -y^2)
\f]

� �������� `dat` ����� ������ ���� `data3d.txt`.\n
����� ���� ��������� GNUPLOT ���������� ���������� 3D �����������
�� ����������� � ���� ������:

\image html writetxt_3d.png

\author ������� ������ www.dsplib.org
***************************************************************************** */
#endif
int DSPL_API writetxt_3d(double* x, int nx, double* y, int ny,
                         double* z, char* fn)
{
    int k, n;
    FILE* pFile = NULL;

    if(!x || !y || !z)
        return ERROR_PTR;
    if(nx < 1 || ny < 1)
        return ERROR_SIZE;
    if(!fn)
        return ERROR_FNAME;

    pFile = fopen(fn, "w+");
    if(pFile == NULL)
        return ERROR_FOPEN;

    for(k = 0; k < ny; k++)
    {
        for(n = 0; n < nx; n++)
        {
            if(!isnan(z[n+k*nx]))
            {
                fprintf(pFile, "%+.12E\t%+.12E\t%+.12E\n",
                               x[n], y[k], z[n+k*nx]);

            }
        }
        fprintf(pFile, "\n");

    }
    fclose(pFile);
    return RES_OK;
}





#ifdef DOXYGEN_ENGLISH

#endif
#ifdef DOXYGEN_RUSSIAN

#endif
int DSPL_API writetxt_3dline(double* x, double *y, double* z, int n, char* fn)
{
    int k;
    FILE* pFile = NULL;

    if(!x || !y || !z)
        return ERROR_PTR;
    if(n < 1)
        return ERROR_SIZE;
    if(!fn)
        return ERROR_FNAME;

    pFile = fopen(fn, "w+");
    if(pFile == NULL)
        return ERROR_FOPEN;

    for(k = 0; k < n; k++)
        fprintf(pFile, "%+.12E\t%+.12E\t%+.12E\n", x[k], y[k], z[k]);
    fprintf(pFile, "\n");
    fclose(pFile);
    return RES_OK;
}



#ifdef DOXYGEN_ENGLISH

#endif
#ifdef DOXYGEN_RUSSIAN

#endif
int DSPL_API writetxt_cmplx_re(double* x, complex_t *y, int n, char* fn)
{
    int k;
    FILE* pFile = NULL;

    if(!x)
        return ERROR_PTR;
    if(n < 1)
        return ERROR_SIZE;
    if(!fn)
        return ERROR_FNAME;

    pFile = fopen(fn, "w+");
    if(pFile == NULL)
        return ERROR_FOPEN;

    if(x)
        for(k = 0; k < n; k++)
            fprintf(pFile, "%+.12E\t%+.12E\n", x[k], RE(y[k]));
    else
        for(k = 0; k < n; k++)
            fprintf(pFile, "%+.12E\n", RE(y[k]));

    fclose(pFile);
    return RES_OK;
}


#ifdef DOXYGEN_ENGLISH

#endif
#ifdef DOXYGEN_RUSSIAN

#endif
int DSPL_API writetxt_cmplx_im(double* x, complex_t *y, int n, char* fn)
{
    int k;
    FILE* pFile = NULL;

    if(!x)
        return ERROR_PTR;
    if(n < 1)
        return ERROR_SIZE;
    if(!fn)
        return ERROR_FNAME;

    pFile = fopen(fn, "w+");
    if(pFile == NULL)
        return ERROR_FOPEN;

    if(x)
        for(k = 0; k < n; k++)
            fprintf(pFile, "%+.12E\t%+.12E\n", x[k], IM(y[k]));
    else
        for(k = 0; k < n; k++)
            fprintf(pFile, "%+.12E\n", IM(y[k]));

    fclose(pFile);
    return RES_OK;
}

