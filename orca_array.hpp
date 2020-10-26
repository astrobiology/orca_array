///////////////////////////////////////////////////////////////////////////
//
// File: orca_array.hpp
// Author: Pramod Gupta, Department of Astronomy, University of Washington
// Last Modified: 2020 Oct 26
//
// Multi-dimensional array template classes array1d<T> to array7d<T>
// Compile time option for array bounds checking and
// for accessing array elements via Fortran order or C order.
//
// See orca_array_readme for usage.
///////////////////////////////////////////////////////////////////////////

#ifndef ORCA_ARRAY
#define ORCA_ARRAY

// Choose 0 or 1 for below options
#define ARRAY_BOUNDS_CHECK 0
#define FORTRAN_ORDER 0

//////////////////////////////////////////////////////////////////////////////
// Notes:
// Copy constructor and assignment operator are private.
// Hence pass all orca_arrays to a function by reference .

// All member functions are defined within the class so they are inline
// by default. However, we still label the at() function inline as a
// reminder.
///////////////////////////////////////////////////////////////////////////////

#include <new>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

namespace orca_array {

//////////////// start class array1d /////////////////////
template <class array_element_type> class array1d {

  private:
    int size1;
    array_element_type *internal_array;

  public:
    inline int length1(void) const { return size1; }

    inline array_element_type &at(int x1) {
#if ARRAY_BOUNDS_CHECK == 1

        if ((x1 < 0) || (x1 >= size1)) {

            printf("index x1 is less than 0 or  equal to size1 or greater than "
                   "size1\n");
            printf("x1=%d \n", x1);
            printf("size1=%d \n", size1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }
#endif

        return internal_array[x1];
    }

    // overloaded at() const
    inline const array_element_type &at(int x1) const {
#if ARRAY_BOUNDS_CHECK == 1

        if ((x1 < 0) || (x1 >= size1)) {

            printf("index x1 is less than 0 or  equal to size1 or greater than "
                   "size1\n");
            printf("x1=%d \n", x1);
            printf("size1=%d \n", size1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }
#endif

        return internal_array[x1];
    }

    // constructor
    array1d(int dim1) {

        if (dim1 <= 0) {
            printf("dim1 is less than or equal to 0\n");
            printf("dim1=%d \n", dim1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else {
            size1 = dim1;
            internal_array = new array_element_type[size1];
        }
    }

    // destructor
    ~array1d() { delete[] internal_array; }

    // note that even though array1d is a template, inside defintion of array1d
    // array1d means same as array1d<array_element_type>
  private:
    // prohibit copy constructor
    array1d(array1d &);

    // prohibit assignment operator
    array1d &operator=(array1d &);
};

////////////// end class array1d /////////////////////

//////////////// start class array2d /////////////////////

template <class array_element_type> class array2d {

  private:
    // number of rows
    int size1;
    // number of columns
    int size2;

    array_element_type *internal_array;

  public:
    inline int length1(void) const { return size1; }

    inline int length2(void) const { return size2; }

    inline array_element_type &at(int x1, int x2) {

#if ARRAY_BOUNDS_CHECK == 1

        if ((x1 < 0) || (x1 >= size1)) {

            printf("index x1 is less than 0 or  equal to size1 or greater than "
                   "size1\n");
            printf("x1=%d \n", x1);
            printf("size1=%d \n", size1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x2 < 0) || (x2 >= size2)) {

            printf("index x2 is less than 0 or  equal to size2 or greater than "
                   "size2\n");
            printf("x2=%d \n", x2);
            printf("size2=%d \n", size2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

#endif

        // x1 is row number and x2 is column number

#if FORTRAN_ORDER == 1
        // fortran convention
        // first index changes fastest
        return internal_array[x2 * size1 + x1];
#else
        // C convention
        // last index changes fastest
        return internal_array[x1 * size2 + x2];
#endif
    }

    // overloaded at() const
    inline const array_element_type &at(int x1, int x2) const {

#if ARRAY_BOUNDS_CHECK == 1

        if ((x1 < 0) || (x1 >= size1)) {

            printf("index x1 is less than 0 or  equal to size1 or greater than "
                   "size1\n");
            printf("x1=%d \n", x1);
            printf("size1=%d \n", size1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x2 < 0) || (x2 >= size2)) {

            printf("index x2 is less than 0 or  equal to size2 or greater than "
                   "size2\n");
            printf("x2=%d \n", x2);
            printf("size2=%d \n", size2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

#endif

        // x1 is row number and x2 is column number

#if FORTRAN_ORDER == 1
        // fortran convention
        // first index changes fastest
        return internal_array[x2 * size1 + x1];
#else
        // C convention
        // last index changes fastest
        return internal_array[x1 * size2 + x2];
#endif
    }

    // constructor
    array2d(int dim1, int dim2) {

        if (dim1 <= 0) {
            printf("dim1 is less than or  equal to 0\n");
            printf("dim1=%d \n", dim1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim2 <= 0) {
            printf("dim2 is less than or equal to 0\n");
            printf("dim2=%d \n", dim2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else {
            size1 = dim1;
            size2 = dim2;
            internal_array = new array_element_type[size1 * size2];
        }
    }

    // destructor
    ~array2d() { delete[] internal_array; }

    // note that even though array2d is a template, inside defintion of array2d
    // array2d means same as array2d<array_element_type>
  private:
    // prohibit copy constructor
    array2d(array2d &);

    // prohibit assignment operator
    array2d &operator=(array2d &);
};

////////////// end class array2d /////////////////////

//////////////// start class array3d /////////////////////
template <class array_element_type> class array3d {

  private:
    // x-axis
    int size1;
    // y-axis
    int size2;
    // z-axis (think of like floor in a building)
    int size3;

    // size2size1 and size2size3 did not improve performance
    ////but this approach may improve performance for higher dimensions
    // size2size1=size2*size1 in constructor
    //  int size2size1;

    // size2size3=size2*size3 in constructor
    //  int size2size3;

    array_element_type *internal_array;

    // factors for Fortran order
    int F1, F2, F3;

    // factors for C order
    int C1, C2, C3;

  public:
    inline int length1(void) const { return size1; }

    inline int length2(void) const { return size2; }

    inline int length3(void) const { return size3; }

    inline array_element_type &at(int x1, int x2, int x3) {

#if ARRAY_BOUNDS_CHECK == 1

        if ((x1 < 0) || (x1 >= size1)) {

            printf("index x1 is less than 0 or  equal to size1 or greater than "
                   "size1\n");
            printf("x1=%d \n", x1);
            printf("size1=%d \n", size1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x2 < 0) || (x2 >= size2)) {

            printf("index x2 is less than 0 or  equal to size2 or greater than "
                   "size2\n");
            printf("x2=%d \n", x2);
            printf("size2=%d \n", size2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x3 < 0) || (x3 >= size3)) {

            printf("index x3 is less than 0 or  equal to size3 or greater than "
                   "size3\n");
            printf("x3=%d \n", x3);
            printf("size3=%d \n", size3);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

#endif

#if FORTRAN_ORDER == 1
        // fortran convention
        // first index changes fastest
        //   return  internal_array[x3*size2*size1 + x2*size1 + x1];
        return internal_array[x3 * F3 + x2 * F2 + x1 * F1];
#else
        // C convention
        // last index changes fastest
        //  return  internal_array[x1*size2*size3 + x2*size3 + x3];
        return internal_array[x1 * C1 + x2 * C2 + x3 * C3];

#endif
    }

    // overloaded at() const
    inline const array_element_type &at(int x1, int x2, int x3) const {

#if ARRAY_BOUNDS_CHECK == 1

        if ((x1 < 0) || (x1 >= size1)) {

            printf("index x1 is less than 0 or  equal to size1 or greater than "
                   "size1\n");
            printf("x1=%d \n", x1);
            printf("size1=%d \n", size1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x2 < 0) || (x2 >= size2)) {

            printf("index x2 is less than 0 or  equal to size2 or greater than "
                   "size2\n");
            printf("x2=%d \n", x2);
            printf("size2=%d \n", size2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x3 < 0) || (x3 >= size3)) {

            printf("index x3 is less than 0 or  equal to size3 or greater than "
                   "size3\n");
            printf("x3=%d \n", x3);
            printf("size3=%d \n", size3);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

#endif

#if FORTRAN_ORDER == 1
        // fortran convention
        // first index changes fastest
        //   return  internal_array[x3*size2*size1 + x2*size1 + x1];
        return internal_array[x3 * F3 + x2 * F2 + x1 * F1];
#else
        // C convention
        // last index changes fastest
        //  return  internal_array[x1*size2*size3 + x2*size3 + x3];
        return internal_array[x1 * C1 + x2 * C2 + x3 * C3];

#endif
    }

    // constructor
    array3d(int dim1, int dim2, int dim3) {

        if (dim1 <= 0) {
            printf("dim1 is less than or  equal to 0\n");
            printf("dim1=%d \n", dim1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim2 <= 0) {
            printf("dim2 is less than or equal to 0\n");
            printf("dim2=%d \n", dim2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim3 <= 0) {
            printf("dim3 is less than or equal to 0\n");
            printf("dim3=%d \n", dim3);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else {
            size1 = dim1;
            size2 = dim2;
            size3 = dim3;

            F3 = size2 * size1;
            F2 = size1;
            F1 = 1;

            C1 = size2 * size3;
            C2 = size3;
            C3 = 1;

            internal_array = new array_element_type[size1 * size2 * size3];
        }
    }

    // destructor
    ~array3d() { delete[] internal_array; }

    // note that even though array3d is a template, inside defintion of array3d
    // array3d means same as array3d<array_element_type>
  private:
    // prohibit copy constructor
    array3d(array3d &);

    // prohibit assignment operator
    array3d &operator=(array3d &);
};

////////////// end class array3d /////////////////////

//////////////// start class array4d /////////////////////
template <class array_element_type> class array4d {

  private:
    // x-axis
    int size1;
    // y-axis
    int size2;
    // z-axis (think of like floor in a building)
    int size3;
    // t-axis
    int size4;

    array_element_type *internal_array;

    // factors for Fortran order
    int F1, F2, F3, F4;

    // factors for C order
    int C1, C2, C3, C4;

  public:
    inline int length1(void) const { return size1; }

    inline int length2(void) const { return size2; }

    inline int length3(void) const { return size3; }

    inline int length4(void) const { return size4; }

    inline array_element_type &at(int x1, int x2, int x3, int x4) {

#if ARRAY_BOUNDS_CHECK == 1

        if ((x1 < 0) || (x1 >= size1)) {

            printf("index x1 is less than 0 or  equal to size1 or greater than "
                   "size1\n");
            printf("x1=%d \n", x1);
            printf("size1=%d \n", size1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x2 < 0) || (x2 >= size2)) {

            printf("index x2 is less than 0 or  equal to size2 or greater than "
                   "size2\n");
            printf("x2=%d \n", x2);
            printf("size2=%d \n", size2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x3 < 0) || (x3 >= size3)) {

            printf("index x3 is less than 0 or  equal to size3 or greater than "
                   "size3\n");
            printf("x3=%d \n", x3);
            printf("size3=%d \n", size3);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x4 < 0) || (x4 >= size4)) {

            printf("index x4 is less than 0 or  equal to size4 or greater than "
                   "size4\n");
            printf("x4=%d \n", x4);
            printf("size4=%d \n", size4);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
            exit(1);
        }

#endif

#if FORTRAN_ORDER == 1
        // fortran convention
        // first index changes fastest
        //   return  internal_array[x4*size3*size2*size1 + x3*size2*size1 +
        //   x2*size1 + x1];

        return internal_array[x4 * F4 + x3 * F3 + x2 * F2 + x1 * F1];
#else
        // C convention
        // last index changes fastest
        //  return  internal_array[x1*size2*size3*size4 + x2*size3*size4
        //  +x3*size4 + x4];

        return internal_array[x1 * C1 + x2 * C2 + x3 * C3 + x4 * C4];
#endif
    }

    // overloaded at() const
    inline const array_element_type &at(int x1, int x2, int x3, int x4) const {

#if ARRAY_BOUNDS_CHECK == 1

        if ((x1 < 0) || (x1 >= size1)) {

            printf("index x1 is less than 0 or  equal to size1 or greater than "
                   "size1\n");
            printf("x1=%d \n", x1);
            printf("size1=%d \n", size1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x2 < 0) || (x2 >= size2)) {

            printf("index x2 is less than 0 or  equal to size2 or greater than "
                   "size2\n");
            printf("x2=%d \n", x2);
            printf("size2=%d \n", size2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x3 < 0) || (x3 >= size3)) {

            printf("index x3 is less than 0 or  equal to size3 or greater than "
                   "size3\n");
            printf("x3=%d \n", x3);
            printf("size3=%d \n", size3);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x4 < 0) || (x4 >= size4)) {

            printf("index x4 is less than 0 or  equal to size4 or greater than "
                   "size4\n");
            printf("x4=%d \n", x4);
            printf("size4=%d \n", size4);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
            exit(1);
        }

#endif

#if FORTRAN_ORDER == 1
        // fortran convention
        // first index changes fastest
        //   return  internal_array[x4*size3*size2*size1 + x3*size2*size1 +
        //   x2*size1 + x1];

        return internal_array[x4 * F4 + x3 * F3 + x2 * F2 + x1 * F1];
#else
        // C convention
        // last index changes fastest
        //  return  internal_array[x1*size2*size3*size4 + x2*size3*size4
        //  +x3*size4 + x4];

        return internal_array[x1 * C1 + x2 * C2 + x3 * C3 + x4 * C4];
#endif
    }

    // constructor
    array4d(int dim1, int dim2, int dim3, int dim4) {

        if (dim1 <= 0) {
            printf("dim1 is less than or  equal to 0\n");
            printf("dim1=%d \n", dim1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim2 <= 0) {
            printf("dim2 is less than or equal to 0\n");
            printf("dim2=%d \n", dim2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim3 <= 0) {
            printf("dim3 is less than or equal to 0\n");
            printf("dim3=%d \n", dim3);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim4 <= 0) {
            printf("dim4 is less than or equal to 0\n");
            printf("dim4=%d \n", dim4);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else {
            size1 = dim1;
            size2 = dim2;
            size3 = dim3;
            size4 = dim4;

            internal_array =
                new array_element_type[size1 * size2 * size3 * size4];

            F4 = size3 * size2 * size1;
            F3 = size2 * size1;
            F2 = size1;
            F1 = 1;

            C1 = size2 * size3 * size4;
            C2 = size3 * size4;
            C3 = size4;
            C4 = 1;
        }
    }

    // destructor
    ~array4d() { delete[] internal_array; }

    // note that even though array4d is a template, inside defintion of array4d
    // array4d means same as array4d<array_element_type>
  private:
    // prohibit copy constructor
    array4d(array4d &);

    // prohibit assignment operator
    array4d &operator=(array4d &);
};

////////////// end class array4d /////////////////////

//////////////// start class array5d /////////////////////
template <class array_element_type> class array5d {

  private:
    // x-axis
    int size1;
    // y-axis
    int size2;
    // z-axis (think of like floor in a building)
    int size3;
    // t-axis
    int size4;
    //
    int size5;

    array_element_type *internal_array;

    // factors for Fortran order
    int F1, F2, F3, F4, F5;

    // factors for C order
    int C1, C2, C3, C4, C5;

  public:
    inline int length1(void) const { return size1; }

    inline int length2(void) const { return size2; }

    inline int length3(void) const { return size3; }

    inline int length4(void) const { return size4; }

    inline int length5(void) const { return size5; }

    inline array_element_type &at(int x1, int x2, int x3, int x4, int x5) {

#if ARRAY_BOUNDS_CHECK == 1

        if ((x1 < 0) || (x1 >= size1)) {

            printf("index x1 is less than 0 or  equal to size1 or greater than "
                   "size1\n");
            printf("x1=%d \n", x1);
            printf("size1=%d \n", size1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x2 < 0) || (x2 >= size2)) {

            printf("index x2 is less than 0 or  equal to size2 or greater than "
                   "size2\n");
            printf("x2=%d \n", x2);
            printf("size2=%d \n", size2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x3 < 0) || (x3 >= size3)) {

            printf("index x3 is less than 0 or  equal to size3 or greater than "
                   "size3\n");
            printf("x3=%d \n", x3);
            printf("size3=%d \n", size3);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x4 < 0) || (x4 >= size4)) {

            printf("index x4 is less than 0 or  equal to size4 or greater than "
                   "size4\n");
            printf("x4=%d \n", x4);
            printf("size4=%d \n", size4);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x5 < 0) || (x5 >= size5)) {

            printf("index x5 is less than 0 or  equal to size5 or greater than "
                   "size5\n");
            printf("x5=%d \n", x5);
            printf("size5=%d \n", size5);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }
#endif

#if FORTRAN_ORDER == 1
        // fortran convention
        // first index changes fastest
        //   return  internal_array[x5*size4*size3*size2*size1 +
        //   x4*size3*size2*size1 + x3*size2*size1 + x2*size1 + x1];

        return internal_array[x5 * F5 + x4 * F4 + x3 * F3 + x2 * F2 + x1 * F1];

#else
        // C convention
        // last index changes fastest
        //  return  internal_array[x1*size2*size3*size4*size5 +
        //                               x2*size3*size4*size5 +
        //                                     x3*size4*size5 +
        //                                           x4*size5 + x5];

        return internal_array[x1 * C1 + x2 * C2 + x3 * C3 + x4 * C4 + x5 * C5];

#endif
    }

    // overloaded at() const
    inline const array_element_type &at(int x1, int x2, int x3, int x4,
                                        int x5) const {

#if ARRAY_BOUNDS_CHECK == 1

        if ((x1 < 0) || (x1 >= size1)) {

            printf("index x1 is less than 0 or  equal to size1 or greater than "
                   "size1\n");
            printf("x1=%d \n", x1);
            printf("size1=%d \n", size1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x2 < 0) || (x2 >= size2)) {

            printf("index x2 is less than 0 or  equal to size2 or greater than "
                   "size2\n");
            printf("x2=%d \n", x2);
            printf("size2=%d \n", size2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x3 < 0) || (x3 >= size3)) {

            printf("index x3 is less than 0 or  equal to size3 or greater than "
                   "size3\n");
            printf("x3=%d \n", x3);
            printf("size3=%d \n", size3);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x4 < 0) || (x4 >= size4)) {

            printf("index x4 is less than 0 or  equal to size4 or greater than "
                   "size4\n");
            printf("x4=%d \n", x4);
            printf("size4=%d \n", size4);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x5 < 0) || (x5 >= size5)) {

            printf("index x5 is less than 0 or  equal to size5 or greater than "
                   "size5\n");
            printf("x5=%d \n", x5);
            printf("size5=%d \n", size5);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }
#endif

#if FORTRAN_ORDER == 1
        // fortran convention
        // first index changes fastest
        //   return  internal_array[x5*size4*size3*size2*size1 +
        //   x4*size3*size2*size1 + x3*size2*size1 + x2*size1 + x1];

        return internal_array[x5 * F5 + x4 * F4 + x3 * F3 + x2 * F2 + x1 * F1];

#else
        // C convention
        // last index changes fastest
        //  return  internal_array[x1*size2*size3*size4*size5 +
        //                               x2*size3*size4*size5 +
        //                                     x3*size4*size5 +
        //                                           x4*size5 + x5];

        return internal_array[x1 * C1 + x2 * C2 + x3 * C3 + x4 * C4 + x5 * C5];

#endif
    }

    // constructor
    array5d(int dim1, int dim2, int dim3, int dim4, int dim5) {

        if (dim1 <= 0) {
            printf("dim1 is less than or  equal to 0\n");
            printf("dim1=%d \n", dim1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim2 <= 0) {
            printf("dim2 is less than or equal to 0\n");
            printf("dim2=%d \n", dim2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim3 <= 0) {
            printf("dim3 is less than or equal to 0\n");
            printf("dim3=%d \n", dim3);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim4 <= 0) {
            printf("dim4 is less than or equal to 0\n");
            printf("dim4=%d \n", dim4);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim5 <= 0) {
            printf("dim5 is less than or equal to 0\n");
            printf("dim5=%d \n", dim5);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else {
            size1 = dim1;
            size2 = dim2;
            size3 = dim3;
            size4 = dim4;
            size5 = dim5;

            internal_array =
                new array_element_type[size1 * size2 * size3 * size4 * size5];

            F5 = size4 * size3 * size2 * size1;
            F4 = size3 * size2 * size1;
            F3 = size2 * size1;
            F2 = size1;
            F1 = 1;

            C1 = size2 * size3 * size4 * size5;
            C2 = size3 * size4 * size5;
            C3 = size4 * size5;
            C4 = size5;
            C5 = 1;
        }
    }
    // destructor
    ~array5d() { delete[] internal_array; }

    // note that even though array5d is a template, inside defintion of array5d
    // array5d means same as array5d<array_element_type>
  private:
    // prohibit copy constructor
    array5d(array5d &);

    // prohibit assignment operator
    array5d &operator=(array5d &);
};

////////////// end class array5d /////////////////////

//////////////// start class array6d /////////////////////
template <class array_element_type> class array6d {

  private:
    // x-axis
    int size1;
    // y-axis
    int size2;
    // z-axis (think of like floor in a building)
    int size3;
    // t-axis
    int size4;
    //
    int size5;

    int size6;

    array_element_type *internal_array;

    // factors for Fortran order
    int F1, F2, F3, F4, F5, F6;

    // factors for C order
    int C1, C2, C3, C4, C5, C6;

  public:
    inline int length1(void) const { return size1; }

    inline int length2(void) const { return size2; }

    inline int length3(void) const { return size3; }

    inline int length4(void) const { return size4; }

    inline int length5(void) const { return size5; }

    inline int length6(void) const { return size6; }

    inline array_element_type &at(int x1, int x2, int x3, int x4, int x5,
                                  int x6) {

#if ARRAY_BOUNDS_CHECK == 1

        if ((x1 < 0) || (x1 >= size1)) {

            printf("index x1 is less than 0 or  equal to size1 or greater than "
                   "size1\n");
            printf("x1=%d \n", x1);
            printf("size1=%d \n", size1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x2 < 0) || (x2 >= size2)) {

            printf("index x2 is less than 0 or  equal to size2 or greater than "
                   "size2\n");
            printf("x2=%d \n", x2);
            printf("size2=%d \n", size2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x3 < 0) || (x3 >= size3)) {

            printf("index x3 is less than 0 or  equal to size3 or greater than "
                   "size3\n");
            printf("x3=%d \n", x3);
            printf("size3=%d \n", size3);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x4 < 0) || (x4 >= size4)) {

            printf("index x4 is less than 0 or  equal to size4 or greater than "
                   "size4\n");
            printf("x4=%d \n", x4);
            printf("size4=%d \n", size4);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x5 < 0) || (x5 >= size5)) {

            printf("index x5 is less than 0 or  equal to size5 or greater than "
                   "size5\n");
            printf("x5=%d \n", x5);
            printf("size5=%d \n", size5);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x6 < 0) || (x6 >= size6)) {

            printf("index x6 is less than 0 or  equal to size6 or greater than "
                   "size6\n");
            printf("x6=%d \n", x6);
            printf("size6=%d \n", size6);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

#endif

#if FORTRAN_ORDER == 1
        // fortran convention
        // first index changes fastest
        //   return  internal_array[x6*size5*size4*size3*size2*size1 +
        //   x5*size4*size3*size2*size1 +
        //                          x4*size3*size2*size1 + x3*size2*size1 +
        //                          x2*size1 + x1];

        return internal_array[x6 * F6 + x5 * F5 + x4 * F4 + x3 * F3 + x2 * F2 +
                              x1 * F1];

#else
        // C convention
        // last index changes fastest
        //  return  internal_array[x1*size2*size3*size4*size5*size6 +
        //                               x2*size3*size4*size5*size6 +
        //                                     x3*size4*size5*size6 +
        //                                           x4*size5*size6 +
        //                                                 x5*size6 + x6];

        return internal_array[x1 * C1 + x2 * C2 + x3 * C3 + x4 * C4 + x5 * C5 +
                              x6 * C6];

#endif
    }

    // overloaded at() const
    inline const array_element_type &at(int x1, int x2, int x3, int x4, int x5,
                                        int x6) const {

#if ARRAY_BOUNDS_CHECK == 1

        if ((x1 < 0) || (x1 >= size1)) {

            printf("index x1 is less than 0 or  equal to size1 or greater than "
                   "size1\n");
            printf("x1=%d \n", x1);
            printf("size1=%d \n", size1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x2 < 0) || (x2 >= size2)) {

            printf("index x2 is less than 0 or  equal to size2 or greater than "
                   "size2\n");
            printf("x2=%d \n", x2);
            printf("size2=%d \n", size2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x3 < 0) || (x3 >= size3)) {

            printf("index x3 is less than 0 or  equal to size3 or greater than "
                   "size3\n");
            printf("x3=%d \n", x3);
            printf("size3=%d \n", size3);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x4 < 0) || (x4 >= size4)) {

            printf("index x4 is less than 0 or  equal to size4 or greater than "
                   "size4\n");
            printf("x4=%d \n", x4);
            printf("size4=%d \n", size4);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x5 < 0) || (x5 >= size5)) {

            printf("index x5 is less than 0 or  equal to size5 or greater than "
                   "size5\n");
            printf("x5=%d \n", x5);
            printf("size5=%d \n", size5);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x6 < 0) || (x6 >= size6)) {

            printf("index x6 is less than 0 or  equal to size6 or greater than "
                   "size6\n");
            printf("x6=%d \n", x6);
            printf("size6=%d \n", size6);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

#endif

#if FORTRAN_ORDER == 1
        // fortran convention
        // first index changes fastest
        //   return  internal_array[x6*size5*size4*size3*size2*size1 +
        //   x5*size4*size3*size2*size1 +
        //                          x4*size3*size2*size1 + x3*size2*size1 +
        //                          x2*size1 + x1];

        return internal_array[x6 * F6 + x5 * F5 + x4 * F4 + x3 * F3 + x2 * F2 +
                              x1 * F1];

#else
        // C convention
        // last index changes fastest
        //  return  internal_array[x1*size2*size3*size4*size5*size6 +
        //                               x2*size3*size4*size5*size6 +
        //                                     x3*size4*size5*size6 +
        //                                           x4*size5*size6 +
        //                                                 x5*size6 + x6];

        return internal_array[x1 * C1 + x2 * C2 + x3 * C3 + x4 * C4 + x5 * C5 +
                              x6 * C6];

#endif
    }

    // constructor
    array6d(int dim1, int dim2, int dim3, int dim4, int dim5, int dim6) {

        if (dim1 <= 0) {
            printf("dim1 is less than or  equal to 0\n");
            printf("dim1=%d \n", dim1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim2 <= 0) {
            printf("dim2 is less than or equal to 0\n");
            printf("dim2=%d \n", dim2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim3 <= 0) {
            printf("dim3 is less than or equal to 0\n");
            printf("dim3=%d \n", dim3);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim4 <= 0) {
            printf("dim4 is less than or equal to 0\n");
            printf("dim4=%d \n", dim4);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim5 <= 0) {
            printf("dim5 is less than or equal to 0\n");
            printf("dim5=%d \n", dim5);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim6 <= 0) {
            printf("dim6 is less than or equal to 0\n");
            printf("dim6=%d \n", dim6);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else {
            size1 = dim1;
            size2 = dim2;
            size3 = dim3;
            size4 = dim4;
            size5 = dim5;
            size6 = dim6;

            internal_array = new array_element_type[size1 * size2 * size3 *
                                                    size4 * size5 * size6];

            F6 = size5 * size4 * size3 * size2 * size1;
            F5 = size4 * size3 * size2 * size1;
            F4 = size3 * size2 * size1;
            F3 = size2 * size1;
            F2 = size1;
            F1 = 1;

            C1 = size2 * size3 * size4 * size5 * size6;
            C2 = size3 * size4 * size5 * size6;
            C3 = size4 * size5 * size6;
            C4 = size5 * size6;
            C5 = size6;
            C6 = 1;
        }
    }

    // destructor
    ~array6d() { delete[] internal_array; }

    // note that even though array6d is a template, inside defintion of array6d
    // array6d means same as array6d<array_element_type>
  private:
    // prohibit copy constructor
    array6d(array6d &);

    // prohibit assignment operator
    array6d &operator=(array6d &);
};

////////////// end class array6d /////////////////////

//////////////// start class array7d /////////////////////
template <class array_element_type> class array7d {

  private:
    // x-axis
    int size1;
    // y-axis
    int size2;
    // z-axis (think of like floor in a building)
    int size3;
    // t-axis
    int size4;
    //
    int size5;

    int size6;

    int size7;

    array_element_type *internal_array;

    // factors for Fortran order
    int F1, F2, F3, F4, F5, F6, F7;

    // factors for C order
    int C1, C2, C3, C4, C5, C6, C7;

  public:
    inline int length1(void) const { return size1; }

    inline int length2(void) const { return size2; }

    inline int length3(void) const { return size3; }

    inline int length4(void) const { return size4; }

    inline int length5(void) const { return size5; }

    inline int length6(void) const { return size6; }

    inline int length7(void) const { return size7; }

    inline array_element_type &at(int x1, int x2, int x3, int x4, int x5,
                                  int x6, int x7) {

#if ARRAY_BOUNDS_CHECK == 1

        if ((x1 < 0) || (x1 >= size1)) {

            printf("index x1 is less than 0 or  equal to size1 or greater than "
                   "size1\n");
            printf("x1=%d \n", x1);
            printf("size1=%d \n", size1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x2 < 0) || (x2 >= size2)) {

            printf("index x2 is less than 0 or  equal to size2 or greater than "
                   "size2\n");
            printf("x2=%d \n", x2);
            printf("size2=%d \n", size2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x3 < 0) || (x3 >= size3)) {

            printf("index x3 is less than 0 or  equal to size3 or greater than "
                   "size3\n");
            printf("x3=%d \n", x3);
            printf("size3=%d \n", size3);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x4 < 0) || (x4 >= size4)) {

            printf("index x4 is less than 0 or  equal to size4 or greater than "
                   "size4\n");
            printf("x4=%d \n", x4);
            printf("size4=%d \n", size4);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x5 < 0) || (x5 >= size5)) {

            printf("index x5 is less than 0 or  equal to size5 or greater than "
                   "size5\n");
            printf("x5=%d \n", x5);
            printf("size5=%d \n", size5);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x6 < 0) || (x6 >= size6)) {

            printf("index x6 is less than 0 or  equal to size6 or greater than "
                   "size6\n");
            printf("x6=%d \n", x6);
            printf("size6=%d \n", size6);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x7 < 0) || (x7 >= size7)) {

            printf("index x7 is less than 0 or  equal to size7 or greater than "
                   "size7\n");
            printf("x7=%d \n", x7);
            printf("size7=%d \n", size7);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

#endif

#if FORTRAN_ORDER == 1
        // fortran convention
        // first index changes fastest
        //   return  internal_array[x7*size6*size5*size4*size3*size2*size1 +
        //   x6*size5*size4*size3*size2*size1 +
        //                          x5*size4*size3*size2*size1 +
        //                          x4*size3*size2*size1 + x3*size2*size1 +
        //                          x2*size1 + x1];

        return internal_array[x7 * F7 + x6 * F6 + x5 * F5 + x4 * F4 + x3 * F3 +
                              x2 * F2 + x1 * F1];
#else
        // C convention
        // last index changes fastest
        //  return  internal_array[x1*size2*size3*size4*size5*size6*size7 +
        //                               x2*size3*size4*size5*size6*size7 +
        //                                     x3*size4*size5*size6*size7 +
        //                                           x4*size5*size6*size7 +
        //                                                 x5*size6*size7 +
        //                                                       x6*size7 + x7];

        return internal_array[x1 * C1 + x2 * C2 + x3 * C3 + x4 * C4 + x5 * C5 +
                              x6 * C6 + x7 * C7];
#endif
    }

    // overloaded at() const
    inline const array_element_type &at(int x1, int x2, int x3, int x4, int x5,
                                        int x6, int x7) const {

#if ARRAY_BOUNDS_CHECK == 1

        if ((x1 < 0) || (x1 >= size1)) {

            printf("index x1 is less than 0 or  equal to size1 or greater than "
                   "size1\n");
            printf("x1=%d \n", x1);
            printf("size1=%d \n", size1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x2 < 0) || (x2 >= size2)) {

            printf("index x2 is less than 0 or  equal to size2 or greater than "
                   "size2\n");
            printf("x2=%d \n", x2);
            printf("size2=%d \n", size2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x3 < 0) || (x3 >= size3)) {

            printf("index x3 is less than 0 or  equal to size3 or greater than "
                   "size3\n");
            printf("x3=%d \n", x3);
            printf("size3=%d \n", size3);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x4 < 0) || (x4 >= size4)) {

            printf("index x4 is less than 0 or  equal to size4 or greater than "
                   "size4\n");
            printf("x4=%d \n", x4);
            printf("size4=%d \n", size4);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x5 < 0) || (x5 >= size5)) {

            printf("index x5 is less than 0 or  equal to size5 or greater than "
                   "size5\n");
            printf("x5=%d \n", x5);
            printf("size5=%d \n", size5);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x6 < 0) || (x6 >= size6)) {

            printf("index x6 is less than 0 or  equal to size6 or greater than "
                   "size6\n");
            printf("x6=%d \n", x6);
            printf("size6=%d \n", size6);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

        if ((x7 < 0) || (x7 >= size7)) {

            printf("index x7 is less than 0 or  equal to size7 or greater than "
                   "size7\n");
            printf("x7=%d \n", x7);
            printf("size7=%d \n", size7);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        }

#endif

#if FORTRAN_ORDER == 1
        // fortran convention
        // first index changes fastest
        //   return  internal_array[x7*size6*size5*size4*size3*size2*size1 +
        //   x6*size5*size4*size3*size2*size1 +
        //                          x5*size4*size3*size2*size1 +
        //                          x4*size3*size2*size1 + x3*size2*size1 +
        //                          x2*size1 + x1];

        return internal_array[x7 * F7 + x6 * F6 + x5 * F5 + x4 * F4 + x3 * F3 +
                              x2 * F2 + x1 * F1];
#else
        // C convention
        // last index changes fastest
        //  return  internal_array[x1*size2*size3*size4*size5*size6*size7 +
        //                               x2*size3*size4*size5*size6*size7 +
        //                                     x3*size4*size5*size6*size7 +
        //                                           x4*size5*size6*size7 +
        //                                                 x5*size6*size7 +
        //                                                       x6*size7 + x7];

        return internal_array[x1 * C1 + x2 * C2 + x3 * C3 + x4 * C4 + x5 * C5 +
                              x6 * C6 + x7 * C7];
#endif
    }

    // constructor
    array7d(int dim1, int dim2, int dim3, int dim4, int dim5, int dim6,
            int dim7) {

        if (dim1 <= 0) {
            printf("dim1 is less than or  equal to 0\n");
            printf("dim1=%d \n", dim1);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim2 <= 0) {
            printf("dim2 is less than or equal to 0\n");
            printf("dim2=%d \n", dim2);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim3 <= 0) {
            printf("dim3 is less than or equal to 0\n");
            printf("dim3=%d \n", dim3);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim4 <= 0) {
            printf("dim4 is less than or equal to 0\n");
            printf("dim4=%d \n", dim4);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim5 <= 0) {
            printf("dim5 is less than or equal to 0\n");
            printf("dim5=%d \n", dim5);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim6 <= 0) {
            printf("dim6 is less than or equal to 0\n");
            printf("dim6=%d \n", dim6);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else if (dim7 <= 0) {
            printf("dim7 is less than or equal to 0\n");
            printf("dim7=%d \n", dim7);
            printf("file %s, line %d.\n", __FILE__, __LINE__);
            raise(SIGSEGV);
        } else {
            size1 = dim1;
            size2 = dim2;
            size3 = dim3;
            size4 = dim4;
            size5 = dim5;
            size6 = dim6;
            size7 = dim7;

            // Fortran convention
            F7 = size6 * size5 * size4 * size3 * size2 * size1;
            F6 = size5 * size4 * size3 * size2 * size1;
            F5 = size4 * size3 * size2 * size1;
            F4 = size3 * size2 * size1;
            F3 = size2 * size1;
            F2 = size1;
            F1 = 1;

            // C convention
            // last index changes fastest
            C1 = size2 * size3 * size4 * size5 * size6 * size7;
            C2 = size3 * size4 * size5 * size6 * size7;
            C3 = size4 * size5 * size6 * size7;
            C4 = size5 * size6 * size7;
            C5 = size6 * size7;
            C6 = size7;
            C7 = 1;

            internal_array =
                new array_element_type[size1 * size2 * size3 * size4 * size5 *
                                       size6 * size7];
        }
    }

    // destructor
    ~array7d() { delete[] internal_array; }

    // note that even though array7d is a template, inside defintion of array7d
    // array7d means same as array7d<array_element_type>
  private:
    // prohibit copy constructor
    array7d(array7d &);

    // prohibit assignment operator
    array7d &operator=(array7d &);
};

////////////// end class array7d /////////////////////

} // namespace orca_array

// endif ORCA_ARRAY
#endif
