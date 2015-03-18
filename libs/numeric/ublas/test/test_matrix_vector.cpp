//
//  Copyright (c) 2013 Joaquim Duran
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/numeric/ublas/assignment.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_vector.hpp>

#include "utils.hpp"

using namespace boost::numeric::ublas;

namespace tans {
template <class AE>
typename AE::value_type mean_square(const matrix_expression<AE> &me) {
    typename AE::value_type s(0);
    typename AE::size_type i, j;
    for (i=0; i!= me().size1(); i++) {
        for (j=0; j!= me().size2(); j++) {
          s+= scalar_traits<typename AE::value_type>::type_abs(me()(i,j));
        }
    }
    return s/me().size1()*me().size2();
}

template <class AE>
typename AE::value_type mean_square(const vector_expression<AE> &ve) {
    // We could have use norm2 here, but ublas' ABS does not support unsigned types.
    typename AE::value_type s(0);
    typename AE::size_type i;
    for (i=0; i!= ve().size(); i++) {
            s+=scalar_traits<typename AE::value_type>::type_abs(ve()(i));
        }
    return s/ve().size();
}
const double TOL=0.0;

}

template <class Vector, class StorageCategory>
void guardSparsePreserveResize( Vector &vec, typename Vector::size_type new_size, StorageCategory) // Because sparse matrices don't have preserve data implemented
{
    vec.resize( new_size );
}


template <class Vector>
void guardSparsePreserveResize( Vector &vec, typename Vector::size_type new_size, sparse_tag) // Because sparse matrices don't have preserve data implemented
{
    vec.resize( new_size, false );
}

template <class Matrix>
bool test_matrix_row_facade() {
    bool pass = true;
    using namespace tans;

    typedef matrix_row_vector<Matrix> RowVector;

    { // Testing resize
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_row_facade: resize" );

    typename Matrix::size_type num_rows = 3;
    typename Matrix::size_type num_cols = 5;
		
    Matrix matrix(num_rows, num_cols);
    RowVector rows(matrix);
    pass &= (matrix.size1() == num_rows);
    pass &= (rows.size() == num_rows);
    pass &= (matrix.size2() == num_cols);
	
    typename Matrix::size_type new_num_rows = 6;
    guardSparsePreserveResize( rows, new_num_rows, typename Matrix::storage_category());
    //rows.resize(new_num_rows);

    pass &= (matrix.size1() == new_num_rows);
    pass &= (rows.size() == new_num_rows);
    pass &= (matrix.size2() == num_cols);
    }

    { // Testing operator()
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_row_facade: operator()" );

    Matrix A(3,3), RA(3,3);
    RowVector rows(A);

    RA <<=  1, 2, 3,
            4, 5, 6,
            7, 8, 9;

    for(typename Matrix::size_type i = 0; i < A.size1(); i++) {
        rows(i) = matrix_row<Matrix>(RA, i);
    }
    
    pass &= (mean_square(A-RA)<=TOL);
    }

    { // Testing operator[]
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_row_facade: operator[]" );

    Matrix A(3,3), RA(3,3);
    RowVector rows(A);

    RA <<=  1, 2, 3,
            4, 5, 6,
            7, 8, 9;
		
    for(typename Matrix::size_type i = 0; i < A.size1(); i++) {
        rows[i] = matrix_row<Matrix>(RA, i);
    }
    
    pass &= (mean_square(A-RA)<=TOL);
    }
    
    { // Testing operator[] const
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_row_facade: operator[] const" );

    Matrix RA(3,3);
    RowVector rows(RA);

    RA <<=  1, 2, 3,
            4, 5, 6,
            7, 8, 9;

    for(typename Matrix::size_type i = 0; i < RA.size1(); i++) {
      pass &= (mean_square(rows[i]-matrix_row<Matrix>(RA, i))<=TOL);
    }
    }

    { // Testing const iterator
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_row_facade: const iterator" );

    Matrix RA(3,3);
    RowVector rows(RA);

    RA <<=  1, 2, 3,
            4, 5, 6,
            7, 8, 9;

    typename RowVector::size_type i = 0;
    for(typename RowVector::const_iterator iter = rows.begin();
	iter != rows.end();
	iter++) {
      pass &= (mean_square(*iter-matrix_row<Matrix>(RA, i++))<=TOL);
    }
    }

    { // Testing iterator
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_row_facade: iterator" );

    Matrix A(3,3), RA(3,3);
    RowVector rows(A);

    RA <<=  1, 2, 3,
            4, 5, 6,
            7, 8, 9;

    typename RowVector::size_type i = 0;
    for(typename RowVector::iterator iter = rows.begin();
	iter != rows.end();
	iter++) {
      *iter = matrix_row<Matrix>(RA, i++);
    }

    pass &= (mean_square(A-RA)<=TOL);
    }

    { // Testing reserse iterator
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_row_facade: reverse iterator" );

    Matrix A(3,3), RA(3,3);
    RowVector rows(A);

    RA <<=  1, 2, 3,
            4, 5, 6,
            7, 8, 9;

    typename RowVector::size_type i = rows.size();
    for(typename RowVector::reverse_iterator iter = rows.rbegin();
	iter != rows.rend();
	iter++) {
      *iter = matrix_row<Matrix>(RA, --i);
    }

    pass &= (mean_square(A-RA)<=TOL);
    }

    { // Testing const reverse iterator
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_row_facade: const reverse iterator" );

    Matrix RA(3,3);
    RowVector rows(RA);

    RA <<=  1, 2, 3,
            4, 5, 6,
            7, 8, 9;

    typename RowVector::size_type i = rows.size();
    for(typename RowVector::const_reverse_iterator iter = rows.rbegin();
	iter != rows.rend();
	iter++) {
      pass &= (mean_square(*iter-matrix_row<Matrix>(RA, --i))<=TOL);
    }
    }

    return pass;
}


template <class Matrix>
bool test_matrix_column_facade() {
    bool pass = true;
    using namespace tans;

    typedef matrix_column_vector<Matrix> ColumnVector;

    { // Testing resize
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_column_facade: resize" );
    typename Matrix::size_type num_rows = 5;
    typename Matrix::size_type num_cols = 3;
    
    Matrix matrix(num_rows, num_cols);
    ColumnVector columns(matrix);
    pass &= (matrix.size2() == num_cols);
    pass &= (columns.size() == num_cols);
    pass &= (matrix.size1() == num_rows);
	
    typename Matrix::size_type new_num_cols = 6;
    guardSparsePreserveResize( columns, new_num_cols, typename Matrix::storage_category());
    //columns.resize(new_num_cols);
    pass &= (matrix.size2() == new_num_cols);
    pass &= (columns.size() == new_num_cols);
    pass &= (matrix.size1() == num_rows);
    }

    { // Testing operator ()
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_column_facade: operator()" );

    Matrix A(3,3), RA(3,3);
    ColumnVector columns(A);

    RA <<=  1, 2, 3,
            4, 5, 6,
            7, 8, 9;
		
    for(typename Matrix::size_type i = 0; i < A.size2(); i++) {
        columns(i) = matrix_column<Matrix>(RA, i);
    }
    
    pass &= (mean_square(A-RA)<=TOL);	
    }

    { // Testing operator[]
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_column_facade: operator[]" );

    Matrix A(3,3), RA(3,3);
    ColumnVector columns(A);

    RA <<=  1, 2, 3,
            4, 5, 6,
            7, 8, 9;
		
    for(typename Matrix::size_type i = 0; i < A.size2(); i++) {
        columns[i] = matrix_column<Matrix>(RA, i);
    }
    
    pass &= (mean_square(A-RA)<=TOL);
    }
    
    { // Testing operator[] const
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_column_facade: operator[] const" );

    Matrix RA(3,3);
    ColumnVector columns(RA);

    RA <<=  1, 2, 3,
            4, 5, 6,
            7, 8, 9;

    for(typename Matrix::size_type i = 0; i < RA.size2(); i++) {
      pass &= (mean_square(columns[i]-matrix_column<Matrix>(RA, i))<=TOL);
    }
    }

    { // Testing iterator
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_column_facade: iterator" );

     Matrix A(3,3), RA(3,3);
    ColumnVector columns(A);

    RA <<=  1, 2, 3,
            4, 5, 6,
            7, 8, 9;

    typename ColumnVector::size_type i = 0;
    for(typename ColumnVector::iterator iter = columns.begin();
	iter != columns.end();
	iter++) {
      *iter = matrix_column<Matrix>(RA, i++);
    }

    pass &= (mean_square(A-RA)<=TOL);
    }

    { // Testing const iterator
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_column_facade: const iterator" );

    Matrix RA(3,3);
    ColumnVector columns(RA);

    RA <<=  1, 2, 3,
            4, 5, 6,
            7, 8, 9;

    typename ColumnVector::size_type i = 0;
    for(typename ColumnVector::const_iterator iter = columns.begin();
	iter != columns.end();
	iter++) {
      pass &= (mean_square(*iter-matrix_column<Matrix>(RA, i++))<=TOL);
    }
    }

    { // Testing reserse iterator
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_column_facade: reverese iterator" );

    Matrix A(3,3), RA(3,3);
    ColumnVector columns(A);

    RA <<=  1, 2, 3,
            4, 5, 6,
            7, 8, 9;

    typename ColumnVector::size_type i = columns.size();
    for(typename ColumnVector::reverse_iterator iter = columns.rbegin();
	iter != columns.rend();
	iter++) {
      *iter = matrix_column<Matrix>(RA, --i);
    }

    pass &= (mean_square(A-RA)<=TOL);
    }

    { // Testing const reverse iterator
    BOOST_UBLAS_DEBUG_TRACE( "test_matrix_column_facade: const reverese iterator" );

    Matrix RA(3,3);
    ColumnVector columns(RA);

    RA <<=  1, 2, 3,
            4, 5, 6,
            7, 8, 9;

    typename ColumnVector::size_type i = columns.size();
    for(typename ColumnVector::const_reverse_iterator iter = columns.rbegin();
	iter != columns.rend();
	iter++) {
      pass &= (mean_square(*iter-matrix_column<Matrix>(RA, --i))<=TOL);
    }
    }

    return pass;
}


BOOST_UBLAS_TEST_DEF (test_matrix_row_facade) {

    BOOST_UBLAS_DEBUG_TRACE( "Starting matrix row vector facade" );

    BOOST_UBLAS_DEBUG_TRACE( "Testing matrix..." );
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<matrix<double> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<matrix<float> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<matrix<long> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<matrix<unsigned long> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<matrix<int> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<matrix<unsigned int> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<matrix<std::size_t> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<matrix<char> >());

    BOOST_UBLAS_DEBUG_TRACE( "Testing bounded_matrix..." );
    BOOST_UBLAS_TEST_CHECK((test_matrix_row_facade<bounded_matrix<double,7, 7> >()));
    BOOST_UBLAS_TEST_CHECK((test_matrix_row_facade<bounded_matrix<float,7, 7> >()));
    BOOST_UBLAS_TEST_CHECK((test_matrix_row_facade<bounded_matrix<long,7, 7> >()));
    BOOST_UBLAS_TEST_CHECK((test_matrix_row_facade<bounded_matrix<unsigned long,7, 7> >()));
    BOOST_UBLAS_TEST_CHECK((test_matrix_row_facade<bounded_matrix<int,7,7 > >()));
    BOOST_UBLAS_TEST_CHECK((test_matrix_row_facade<bounded_matrix<unsigned int,7, 7> >()));
    BOOST_UBLAS_TEST_CHECK((test_matrix_row_facade<bounded_matrix<char,7, 7> >()));
    BOOST_UBLAS_TEST_CHECK((test_matrix_row_facade<bounded_matrix<std::size_t,7, 7> >()));

    BOOST_UBLAS_DEBUG_TRACE( "Testing mapped_matrix..." );
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<mapped_matrix<double> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<mapped_matrix<float> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<mapped_matrix<long> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<mapped_matrix<unsigned long> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<mapped_matrix<int> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<mapped_matrix<unsigned int> >())
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<mapped_matrix<std::size_t> >())
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<mapped_matrix<char> >());

    BOOST_UBLAS_DEBUG_TRACE( "Testing compressed_matrix..." );
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<compressed_matrix<double> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<compressed_matrix<float> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<compressed_matrix<long> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<compressed_matrix<unsigned long> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<compressed_matrix<int> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<compressed_matrix<unsigned int> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<compressed_matrix<std::size_t> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<compressed_matrix<char> >());

    BOOST_UBLAS_DEBUG_TRACE( "Testing coordinate_matrix..." );
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<coordinate_matrix<double> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<coordinate_matrix<float> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<coordinate_matrix<long> >())
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<coordinate_matrix<unsigned long> >())
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<coordinate_matrix<int> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<coordinate_matrix<unsigned int> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<coordinate_matrix<std::size_t> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_row_facade<coordinate_matrix<char> >());
}


BOOST_UBLAS_TEST_DEF (test_matrix_column_facade) {

    BOOST_UBLAS_DEBUG_TRACE( "Starting matrix row column facade" );

    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<matrix<double> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<matrix<float> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<matrix<long> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<matrix<unsigned long> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<matrix<int> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<matrix<unsigned int> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<matrix<std::size_t> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<matrix<char> >());

    BOOST_UBLAS_TEST_CHECK((test_matrix_column_facade<bounded_matrix<double,7, 7> >()));
    BOOST_UBLAS_TEST_CHECK((test_matrix_column_facade<bounded_matrix<float,7, 7> >()));
    BOOST_UBLAS_TEST_CHECK((test_matrix_column_facade<bounded_matrix<long,7, 7> >()));
    BOOST_UBLAS_TEST_CHECK((test_matrix_column_facade<bounded_matrix<unsigned long,7, 7> >()));
    BOOST_UBLAS_TEST_CHECK((test_matrix_column_facade<bounded_matrix<int,7,7 > >()));
    BOOST_UBLAS_TEST_CHECK((test_matrix_column_facade<bounded_matrix<unsigned int,7, 7> >()));
    BOOST_UBLAS_TEST_CHECK((test_matrix_column_facade<bounded_matrix<char,7, 7> >()));
    BOOST_UBLAS_TEST_CHECK((test_matrix_column_facade<bounded_matrix<std::size_t,7, 7> >()));

    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<mapped_matrix<double> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<mapped_matrix<float> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<mapped_matrix<long> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<mapped_matrix<unsigned long> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<mapped_matrix<int> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<mapped_matrix<unsigned int> >())
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<mapped_matrix<std::size_t> >())
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<mapped_matrix<char> >());

    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<compressed_matrix<double> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<compressed_matrix<float> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<compressed_matrix<long> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<compressed_matrix<unsigned long> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<compressed_matrix<int> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<compressed_matrix<unsigned int> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<compressed_matrix<std::size_t> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<compressed_matrix<char> >());

    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<coordinate_matrix<double> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<coordinate_matrix<float> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<coordinate_matrix<long> >())
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<coordinate_matrix<unsigned long> >())
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<coordinate_matrix<int> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<coordinate_matrix<unsigned int> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<coordinate_matrix<std::size_t> >());
    BOOST_UBLAS_TEST_CHECK(test_matrix_column_facade<coordinate_matrix<char> >());
}


int main () {
    BOOST_UBLAS_TEST_BEGIN();

    BOOST_UBLAS_TEST_DO( test_matrix_row_facade );
    BOOST_UBLAS_TEST_DO( test_matrix_column_facade );

    BOOST_UBLAS_TEST_END();

    return EXIT_SUCCESS;;
}
