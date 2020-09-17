//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#include <iostream>

#include <boost/multiprecision/cpp_modular.hpp>
#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/modular/modular_adaptor.hpp>

#include <nil/algebra/fields/fp2.hpp>
#include <nil/algebra/fields/alt_bn128/base_field.hpp>
#include <nil/algebra/fields/alt_bn128/scalar_field.hpp>
#include <nil/algebra/fields/bls12/base_field.hpp>
#include <nil/algebra/fields/bls12/scalar_field.hpp>
#include <nil/algebra/fields/bn128/base_field.hpp>
#include <nil/algebra/fields/bn128/scalar_field.hpp>
#include <nil/algebra/fields/dsa_botan.hpp>
#include <nil/algebra/fields/dsa_jce.hpp>
//#include <nil/algebra/fields/ed25519_fe.hpp>
//#include <nil/algebra/fields/ffdhe_ietf.hpp>
//#include <nil/algebra/fields/modp_ietf.hpp>
//#include <nil/algebra/fields/modp_srp.hpp>

#include <nil/algebra/fields/detail/element/fp.hpp>
#include <nil/algebra/fields/detail/element/fp2.hpp>
#include <nil/algebra/multiexp/default.hpp>

using namespace nil::algebra;

template<typename FieldParams>
void print_field_element(typename fields::detail::element_fp<FieldParams> e) {
    std::cout << e.data << std::endl;
}

template<typename FieldParams>
void print_field_element(typename fields::detail::element_fp2<FieldParams> e) {
    std::cout << e.data[0].data << " " << e.data[1].data << std::endl;
}

template<typename FpField>
void fields_fp_basic_math_examples() {
    using policy_type = FpField;
    using value_type = typename policy_type::value_type;

    std::cout << "Field module value: " << policy_type::modulus << std::endl;

    value_type e1 = value_type(76749407), e2(44410867), e3 = value_type::one(), e4(121160274);

    std::cout << "Field element values: " << std::endl;
    std::cout << "e1 value: ";
    print_field_element(e1);

    std::cout << "e2 value: ";
    print_field_element(e2);

    std::cout << "e3 value: ";
    print_field_element(e3);

    value_type e1e2 = e1 * e2, e1sqr = e1.squared();

    value_type e1sqrt = e1.sqrt();

    std::cout << "e1sqrt value: ";
    print_field_element(e1sqrt);

    std::cout << "e1sqrt * e1sqrt \n";
    print_field_element(e1sqrt * e1sqrt);

    value_type e1inv = e1.inversed();

    std::cout << "e1 inversed value: ";
    print_field_element(e1inv);

    std::cout << "e1 * e1^(-1) \n";
    print_field_element(e1 * e1inv);

    std::cout << "e1 * e2 value: ";
    print_field_element(e1e2);

    std::cout << "e1 square value: ";
    print_field_element(e1sqr);

    std::cout << "e1 square square value: ";

    print_field_element(e1.squared().squared());

    std::cout << "e1 pow 4 value: ";

    print_field_element(e1.pow(4));

    std::cout << "e1 pow 11 value: ";

    print_field_element(e1.pow(11));

    std::cout << "e1 pow 44410867 value: ";

    print_field_element(e1.pow(44410867));

    std::cout << "e1 pow 1024 value: " ;
    print_field_element(e1.pow(1024));
    value_type e1_pow1024 = e1;
    for (int i = 1; i < 1024; i++) {
        e1_pow1024 = e1_pow1024 * e1;
    }
    std::cout<< "e1 * e1 (1024 times): ";
    print_field_element(e1_pow1024);
    std::cout << "Two previous values comparision: " << (e1.pow(1024) == e1_pow1024) << std::endl;


    value_type complex_eq = e1 * e3 + e1 * e4 + e2 * e3 + e2 * e4;
    value_type complex_eq1 = (e1 + e2) * (e3 + e4);

    std::cout << "e1 * e3 + e1 * e4 + e2 * e3 + e2 * e4 value: ";

    print_field_element(complex_eq);

    std::cout << "(e1 + e2) * (e3 + e4) value: ";

    print_field_element(complex_eq1);

    std::cout << "Doubled e1 value: ";

    print_field_element(e1.doubled());

    e1 += e2;

    std::cout << "e1 += e2 value: ";

    print_field_element(e1);
}

template<typename Fp2Field>
void fields_fp2_basic_math_examples() {
    using policy_type = Fp2Field;
    using value_type = typename policy_type::value_type;

    std::cout << "Field module value: " << policy_type::modulus << std::endl;

    value_type e1 = value_type(76749407, 44410867), e2(44410867, 1), e3 = value_type::one(), e4(121160274, 7);

    value_type ee(e1);

    std::cout << "ee value: ";
    print_field_element(ee);

    std::cout << "Non residue: " << e1.non_residue.data << std::endl;

    std::cout << "Field element values: " << std::endl;
    std::cout << "e1 value: ";
    print_field_element(e1);

    e1 += e2;

    std::cout << "e1 value: ";
    print_field_element(e1);
    std::cout << "ee value: ";
    print_field_element(ee);

    std::cout << "e2 value: ";
    print_field_element(e2);

    std::cout << "e3 value: ";
    print_field_element(e3);

    value_type e1inv = e1.inversed();

    std::cout << "e1 inversed value: ";
    print_field_element(e1inv);

    std::cout << "e1 * e1^(-1) \n";
    print_field_element(e1 * e1inv);

    value_type e1e2 = e1 * e2, e1sqr = e1.squared();

    std::cout << "e1 * e2 value: ";
    print_field_element(e1e2);

    std::cout << "e1 square value: ";
    print_field_element(e1sqr);

    std::cout << "e1 square square value: ";

    print_field_element(e1.squared().squared());

    std::cout << "e1 pow 4 value: ";

    print_field_element(e1.pow(4));

    std::cout << "e1 pow 11 value: ";

    print_field_element(e1.pow(11));

    std::cout << "e1 pow 44410867 value: ";

    print_field_element(e1.pow(44410867));

    value_type complex_eq = e1 * e3 + e1 * e4 + e2 * e3 + e2 * e4;
    value_type complex_eq1 = (e1 + e2) * (e3 + e4);

    std::cout << "e1 * e3 + e1 * e4 + e2 * e3 + e2 * e4 value: ";

    print_field_element(complex_eq);

    std::cout << "(e1 + e2) * (e3 + e4) value: ";

    print_field_element(complex_eq1);

    std::cout << "Doubled e1 value: ";

    print_field_element(e1.doubled());

    e1 += e2;

    std::cout << "e1 += e2 value: ";

    print_field_element(e1);

    // std::cout << "e1 inversed value: " ;

    // print_field_element(e1.inversed());
}

template<typename T, typename S> struct multiexp_test_case {
        typename std::vector<T> bases;
        typename std::vector<S> scalars;
        size_t num_groups;
        size_t bucket_size;
        size_t workers_in_group;

        multiexp_test_case(typename std::vector<T> bases, typename std::vector<S> scalars, size_t num_groups, size_t bucket_size, size_t workers_in_group) {
            this->bases = bases;
            this->scalars = scalars;
            this->num_groups = num_groups;
            this->bucket_size = bucket_size;
            this->workers_in_group = workers_in_group;
        }
};

template<typename FieldType>
void multiexp_test() {
    using value_type = typename FieldType::value_type;

    std::function<value_type (value_type, value_type)> base_op = [](value_type a, value_type b) -> value_type {return a * b; };
    std::function<value_type (int, value_type)> s_op = [](int s, value_type a) -> value_type { return a.pow(s); };
    std::function<value_type (value_type)> dbl_op = [](value_type a) -> value_type { return a * a; };
    nil::algebra::multiexp::operation_set<value_type, int> op_set(base_op, s_op, dbl_op);

    multiexp_test_case<value_type, int> test1(std::vector<value_type>{value_type(500), value_type(352546561), value_type(7)},
                                            std::vector<int>{200, 757, 2}, 2, 3, 2);
    multiexp_test_case<value_type, int> test2(std::vector<value_type>(300, value_type(500)),
                                            std::vector<int>(300, 37), 5, 3, 5);
    multiexp_test_case<value_type, int> test3(std::vector<value_type>(700, value_type(5641651231)),
                                            std::vector<int>(700, 65465), 100, 10, 5);
    multiexp_test_case<value_type, int> test4(std::vector<value_type>{value_type(3525465617)},
                                            std::vector<int>{1024}, 1, 10, 1);

    std::vector<multiexp_test_case<value_type, int>> tests{ test1, test2, test3, test4};

    for (size_t i = 0; i < tests.capacity(); i++) {
        typename std::vector<value_type> bases = tests[i].bases;
        std::vector<int> scalars = tests[i].scalars;

        typename std::vector<value_type>::const_iterator bases_iter = bases.begin();
        std::vector<int>::const_iterator scalaras_iter = scalars.begin();

        value_type res = nil::algebra::multiexp::eval_multi_exp<value_type, int>(bases_iter, scalaras_iter, tests[i].num_groups, tests[i].bucket_size, tests[i].workers_in_group, bases.capacity(), value_type::one(), 31, op_set);
        value_type naive_res = nil::algebra::multiexp::eval_multi_exp_naive<value_type, int>(bases_iter, scalaras_iter, bases.capacity(), value_type::one(), op_set);

        print_field_element(res);
        print_field_element(naive_res);
        if (res == naive_res) {
            std::cout << "Test " << i << " OK" << std::endl;
        }
        else {
            std::cout << "Test " << i << " FAILED" << std::endl;
        }   
    }
}

int main()
{
    /*std::cout << "ALT_BN128-254 Fq basic math:" << std::endl;
    fields_fp_basic_math_examples<fields::alt_bn128_fq<254>>();

    std::cout << "----------------------------" << std::endl;

    std::cout << "ALT_BN128-254 Fq2 basic math:" << std::endl;
    fields_fp2_basic_math_examples<fields::fp2<fields::alt_bn128_fq<254>>>();

    std::cout << "----------------------------" << std::endl;

    std::cout << "ALT_BN128-254 Fr basic math:" << std::endl;
    fields_fp_basic_math_examples<fields::alt_bn128_fr<254>>();

    std::cout << "----------------------------" << std::endl;

    std::cout << "BN128-254 Fq basic math:" << std::endl;
    fields_fp_basic_math_examples<fields::bn128_fq<254>>();

    std::cout << "----------------------------" << std::endl;

    std::cout << "BN128-254 Fq2 basic math:" << std::endl;
    fields_fp2_basic_math_examples<fields::fp2<fields::bn128_fq<254>>>();

    std::cout << "----------------------------" << std::endl;

    std::cout << "BN128-254 Fr basic math:" << std::endl;
    fields_fp_basic_math_examples<fields::bn128_fr<254>>();

    std::cout << "----------------------------" << std::endl;

    std::cout << "BLS12-381 Fq basic math:" << std::endl;
    fields_fp_basic_math_examples<fields::bls12_fq<381>>();

    std::cout << "----------------------------" << std::endl;

    std::cout << "BLS12-381 Fq2 basic math:" << std::endl;
    fields_fp2_basic_math_examples<fields::fp2<fields::bls12_fq<381>>>();

    std::cout << "----------------------------" << std::endl;

    std::cout << "BLS12-381 Fr basic math:" << std::endl;
    fields_fp_basic_math_examples<fields::bls12_fr<381>>();

    std::cout << "----------------------------" << std::endl;

    std::cout << "BLS12-377 Fq basic math:" << std::endl;
    fields_fp_basic_math_examples<fields::bls12_fq<377>>();

    std::cout << "----------------------------" << std::endl;

    std::cout << "BLS12-377 Fq2 basic math:" << std::endl;
    fields_fp2_basic_math_examples<fields::fp2<fields::bls12_fq<377>>>();

    std::cout << "----------------------------" << std::endl;

    std::cout << "BLS12-377 Fr basic math:" << std::endl;
    fields_fp_basic_math_examples<fields::bls12_fr<377>>();

    std::cout << "----------------------------" << std::endl;

    std::cout << "DSA Botan 2048 basic math:" << std::endl;
    fields_fp_basic_math_examples<fields::dsa_botan<2048>>();

    std::cout << "----------------------------" << std::endl;

    std::cout << "DSA JCE 1024 basic math:" << std::endl;
    fields_fp_basic_math_examples<fields::dsa_jce<1024>>();

    /*    std::cout << "----------------------------" << std::endl;

        std::cout << "FFDHE IETF 2048 basic math:" << std::endl;
        fields_fp_basic_math_examples<fields::ffdhe_ietf<2048>>();

        std::cout << "----------------------------" << std::endl;

        std::cout << "MODP IETF 1024 basic math:" << std::endl;
        fields_fp_basic_math_examples<fields::modp_ietf<1024>>();

        std::cout << "----------------------------" << std::endl;

        std::cout << "MODP SRP 1024 basic math:" << std::endl;
        fields_fp_basic_math_examples<fields::modp_srp<1024>>();*/

    std::cout << "----------------------------" << std::endl;

    std::cout << "MultiExpoinentation BLS12-381 Fq: " << std::endl;

    multiexp_test<fields::bls12_fq<381>>();

    std::cout << "----------------------------" << std::endl;

    std::cout << "MultiExpoinentation BN128-254 Fq: " << std::endl;

    multiexp_test<fields::bn128_fq<254>>();

    /*std::cout << "----------------------------" << std::endl;

    std::cout << "MultiExpoinentation DSA Botan 3072: " << std::endl;

    multiexp_test<fields::dsa_botan<2048>>();*/


    return 0;
}