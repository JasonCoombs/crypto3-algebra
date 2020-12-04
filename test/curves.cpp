//---------------------------------------------------------------------------//
// Copyright (c) 2020 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020 Nikita Kaskov <nbering@nil.foundation>
// Copyright (c) 2020 Ilias Khairullin <ilias@nil.foundation>
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------//

#define BOOST_TEST_MODULE curves_algebra_test

#include <iostream>
#include <type_traits>

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <nil/crypto3/algebra/curves/alt_bn128.hpp>
#include <nil/crypto3/algebra/curves/bls12.hpp>
// #include <nil/crypto3/algebra/curves/brainpool_r1.hpp>
#include <nil/crypto3/algebra/curves/edwards.hpp>
// #include <nil/crypto3/algebra/curves/frp_v1.hpp>
// #include <nil/crypto3/algebra/curves/gost_A.hpp>
#include <nil/crypto3/algebra/curves/mnt4.hpp>
#include <nil/crypto3/algebra/curves/mnt6.hpp>
// #include <nil/crypto3/algebra/curves/p192.hpp>
// #include <nil/crypto3/algebra/curves/p224.hpp>
// #include <nil/crypto3/algebra/curves/p256.hpp>
// #include <nil/crypto3/algebra/curves/p384.hpp>
// #include <nil/crypto3/algebra/curves/p521.hpp>
// #include <nil/crypto3/algebra/curves/secp.hpp>
// #include <nil/crypto3/algebra/curves/sm2p_v1.hpp>
// #include <nil/crypto3/algebra/curves/x962_p.hpp>

#include <boost/multiprecision/cpp_int.hpp>

using namespace nil::crypto3::algebra;

template<typename FpCurveGroupElement>
void print_fp_curve_group_element(std::ostream &os, const FpCurveGroupElement &e) {
    os << "( " << e.X.data << " : " << e.Y.data << " : " << e.Z.data << " )";
}

template<typename Fp2CurveGroupElement>
void print_fp2_curve_group_element(std::ostream &os, const Fp2CurveGroupElement &e) {
    os << "(" << e.X.data[0].data << " , " << e.X.data[1].data << ") : (" << e.Y.data[0].data << " , "
       << e.Y.data[1].data << ") : (" << e.Z.data[0].data << " , " << e.Z.data[1].data << ")" << std::endl;
}

template<typename Fp3CurveGroupElement>
void print_fp3_curve_group_element(std::ostream &os, const Fp3CurveGroupElement &e) {
    os << "(" << e.X.data[0].data << " , " << e.X.data[1].data << " , " << e.X.data[2].data << ") : ("
       << e.Y.data[0].data << " , " << e.Y.data[1].data << " , " << e.Y.data[2].data << ") : (" << e.Z.data[0].data
       << " , " << e.Z.data[1].data << " , " << e.Z.data[2].data << ")" << std::endl;
}

namespace boost {
    namespace test_tools {
        namespace tt_detail {

            template<>
            struct print_log_value<typename curves::edwards<183>::g1_type::value_type> {
                void operator()(std::ostream &os, typename curves::edwards<183>::g1_type::value_type const &e) {
                    print_fp_curve_group_element(os, e);
                }
            };

            template<>
            struct print_log_value<typename curves::mnt4<298>::g1_type::value_type> {
                void operator()(std::ostream &os, typename curves::mnt4<298>::g1_type::value_type const &e) {
                    print_fp_curve_group_element(os, e);
                }
            };

            template<>
            struct print_log_value<typename curves::mnt6<298>::g1_type::value_type> {
                void operator()(std::ostream &os, typename curves::mnt6<298>::g1_type::value_type const &e) {
                    print_fp_curve_group_element(os, e);
                }
            };

            template<>
            struct print_log_value<typename curves::alt_bn128<254>::g1_type::value_type> {
                void operator()(std::ostream &os, typename curves::alt_bn128<254>::g1_type::value_type const &e) {
                    print_fp_curve_group_element(os, e);
                }
            };

            template<>
            struct print_log_value<typename curves::bls12<381>::g1_type::value_type> {
                void operator()(std::ostream &os, typename curves::bls12<381>::g1_type::value_type const &e) {
                    print_fp_curve_group_element(os, e);
                }
            };

            template<>
            struct print_log_value<typename curves::bls12<377>::g1_type::value_type> {
                void operator()(std::ostream &os, typename curves::bls12<377>::g1_type::value_type const &e) {
                    print_fp_curve_group_element(os, e);
                }
            };

            template<>
            struct print_log_value<typename curves::mnt4<298>::g2_type::value_type> {
                void operator()(std::ostream &os, typename curves::mnt4<298>::g2_type::value_type const &e) {
                    print_fp2_curve_group_element(os, e);
                }
            };

            template<>
            struct print_log_value<typename curves::bls12<381>::g2_type::value_type> {
                void operator()(std::ostream &os, typename curves::bls12<381>::g2_type::value_type const &e) {
                    print_fp2_curve_group_element(os, e);
                }
            };

            template<>
            struct print_log_value<typename curves::bls12<377>::g2_type::value_type> {
                void operator()(std::ostream &os, typename curves::bls12<377>::g2_type::value_type const &e) {
                    print_fp2_curve_group_element(os, e);
                }
            };

            template<>
            struct print_log_value<typename curves::alt_bn128<254>::g2_type::value_type> {
                void operator()(std::ostream &os, typename curves::alt_bn128<254>::g2_type::value_type const &e) {
                    print_fp2_curve_group_element(os, e);
                }
            };

            template<>
            struct print_log_value<typename curves::edwards<183>::g2_type::value_type> {
                void operator()(std::ostream &os, typename curves::edwards<183>::g2_type::value_type const &e) {
                    print_fp3_curve_group_element(os, e);
                }
            };

            template<>
            struct print_log_value<typename curves::mnt6<298>::g2_type::value_type> {
                void operator()(std::ostream &os, typename curves::mnt6<298>::g2_type::value_type const &e) {
                    print_fp3_curve_group_element(os, e);
                }
            };

            template<template<typename, typename> class P, typename K, typename V>
            struct print_log_value<P<K, V>> {
                void operator()(std::ostream &, P<K, V> const &) {
                }
            };

        }    // namespace tt_detail
    }        // namespace test_tools
}    // namespace boost

// if target == check-algebra just data/curves.json
const char *test_data = "../../../../libs/algebra/test/data/curves.json";

boost::property_tree::ptree string_data(std::string test_name) {
    boost::property_tree::ptree string_data;
    boost::property_tree::read_json(test_data, string_data);

    return string_data.get_child(test_name);
}

enum curve_operation_test_constants : std::size_t { C1, C2 };

enum curve_operation_test_points : std::size_t {
    p1,
    p2,
    p1_plus_p2,
    p1_minus_p2,
    p1_mul_C1,
    p2_mul_C1_plus_p2_mul_C2,
    p1_dbl,
    p1_mixed_add_p2,
    p1_to_affine_coordinates,
    p2_to_special
};

template<typename CurveGroup>
void check_curve_operations(const std::vector<typename CurveGroup::value_type> &points,
                            const std::vector<std::size_t> &constants) {
    using boost::multiprecision::cpp_int;

    BOOST_CHECK_EQUAL(points[p1] + points[p2], points[p1_plus_p2]);
    BOOST_CHECK_EQUAL(points[p1] - points[p2], points[p1_minus_p2]);
    BOOST_CHECK_EQUAL(points[p1].doubled(), points[p1_dbl]);
    BOOST_CHECK_EQUAL(points[p1].mixed_add(points[p2]), points[p1_mixed_add_p2]);
    typename CurveGroup::value_type p1_copy = typename CurveGroup::value_type(points[p1]).to_affine_coordinates();
    BOOST_CHECK_EQUAL(p1_copy, points[p1_to_affine_coordinates]);
    typename CurveGroup::value_type p2_copy = typename CurveGroup::value_type(points[p2]).to_special();
    BOOST_CHECK_EQUAL(p2_copy, points[p2_to_special]);
    BOOST_CHECK_EQUAL(points[p1] * static_cast<cpp_int>(constants[C1]), points[p1_mul_C1]);
    BOOST_CHECK_EQUAL((points[p2] * static_cast<cpp_int>(constants[C1])) +
                          (points[p2] * static_cast<cpp_int>(constants[C2])),
                      points[p2_mul_C1_plus_p2_mul_C2]);
    BOOST_CHECK_EQUAL((points[p2] * static_cast<cpp_int>(constants[C1])) +
                          (points[p2] * static_cast<cpp_int>(constants[C2])),
                      points[p2] * static_cast<cpp_int>(constants[C1] + constants[C2]));
}

template<typename FpCurveGroup, typename TestSet>
void fp_curve_test_init(std::vector<typename FpCurveGroup::value_type> &points,
                        std::vector<std::size_t> &constants,
                        const TestSet &test_set) {
    typedef typename FpCurveGroup::underlying_field_type::value_type field_value_type;
    std::array<field_value_type, 3> coordinates;

    for (auto &point : test_set.second.get_child("point_coordinates")) {
        auto i = 0;
        for (auto &coordinate : point.second) {
            coordinates[i++] = field_value_type(typename field_value_type::modulus_type(coordinate.second.data()));
        }
        points.emplace_back(typename FpCurveGroup::value_type(coordinates[0], coordinates[1], coordinates[2]));
    }

    for (auto &constant : test_set.second.get_child("constants")) {
        constants.emplace_back(std::stoul(constant.second.data()));
    }
}

template<typename Fp2CurveGroup, typename TestSet>
void fp2_curve_test_init(std::vector<typename Fp2CurveGroup::value_type> &points,
                         std::vector<std::size_t> &constants,
                         const TestSet &test_set) {
    using fp2_value_type = typename Fp2CurveGroup::underlying_field_type::value_type;
    using modulus_type = typename fp2_value_type::underlying_type::modulus_type;
    std::array<modulus_type, 6> coordinates;

    for (auto &point : test_set.second.get_child("point_coordinates")) {
        auto i = 0;
        for (auto &coordinate_pairs : point.second) {
            for (auto &coordinate : coordinate_pairs.second) {
                coordinates[i++] = modulus_type(coordinate.second.data());
            }
        }
        points.emplace_back(typename Fp2CurveGroup::value_type(fp2_value_type(coordinates[0], coordinates[1]),
                                                               fp2_value_type(coordinates[2], coordinates[3]),
                                                               fp2_value_type(coordinates[4], coordinates[5])));
    }

    for (auto &constant : test_set.second.get_child("constants")) {
        constants.emplace_back(std::stoul(constant.second.data()));
    }
}

template<typename Fp3CurveGroup, typename TestSet>
void fp3_curve_test_init(std::vector<typename Fp3CurveGroup::value_type> &points,
                         std::vector<std::size_t> &constants,
                         const TestSet &test_set) {
    using fp3_value_type = typename Fp3CurveGroup::underlying_field_type::value_type;
    using modulus_type = typename fp3_value_type::underlying_type::modulus_type;

    std::array<modulus_type, 9> coordinates;

    for (auto &point : test_set.second.get_child("point_coordinates")) {
        auto i = 0;
        for (auto &coordinate_pairs : point.second) {
            for (auto &coordinate : coordinate_pairs.second) {
                coordinates[i++] = modulus_type(coordinate.second.data());
            }
        }
        points.emplace_back(
            typename Fp3CurveGroup::value_type(fp3_value_type(coordinates[0], coordinates[1], coordinates[2]),
                                               fp3_value_type(coordinates[3], coordinates[4], coordinates[5]),
                                               fp3_value_type(coordinates[6], coordinates[7], coordinates[8])));
    }

    for (auto &constant : test_set.second.get_child("constants")) {
        constants.emplace_back(std::stoul(constant.second.data()));
    }
}

template<typename CurveGroup, typename TestSet>
void curve_operation_test(const TestSet &test_set,
                          void (&test_init)(std::vector<typename CurveGroup::value_type> &,
                                            std::vector<std::size_t> &,
                                            const TestSet &)) {

    std::vector<typename CurveGroup::value_type> points;
    std::vector<std::size_t> constants;

    test_init(points, constants, test_set);

    check_curve_operations<CurveGroup>(points, constants);
}

BOOST_AUTO_TEST_SUITE(curves_manual_tests)

BOOST_DATA_TEST_CASE(curve_operation_test_edwards_g1, string_data("curve_operation_test_edwards_g1"), data_set) {
    using policy_type = curves::edwards<183>::g1_type;

    curve_operation_test<policy_type>(data_set, fp_curve_test_init<policy_type>);
}

BOOST_DATA_TEST_CASE(curve_operation_test_mnt4_g1, string_data("curve_operation_test_mnt4_g1"), data_set) {
    using policy_type = curves::mnt4<298>::g1_type;

    curve_operation_test<policy_type>(data_set, fp_curve_test_init<policy_type>);
}

BOOST_DATA_TEST_CASE(curve_operation_test_mnt6_g1, string_data("curve_operation_test_mnt6_g1"), data_set) {
    using policy_type = curves::mnt6<298>::g1_type;

    curve_operation_test<policy_type>(data_set, fp_curve_test_init<policy_type>);
}

BOOST_DATA_TEST_CASE(curve_operation_test_mnt4_g2, string_data("curve_operation_test_mnt4_g2"), data_set) {
    using policy_type = curves::mnt4<298>::g2_type;

    curve_operation_test<policy_type>(data_set, fp2_curve_test_init<policy_type>);
}

BOOST_DATA_TEST_CASE(curve_operation_test_edwards_g2, string_data("curve_operation_test_edwards_g2"), data_set) {
    using policy_type = curves::edwards<183>::g2_type;

    curve_operation_test<policy_type>(data_set, fp3_curve_test_init<policy_type>);
}

BOOST_DATA_TEST_CASE(curve_operation_test_mnt6_g2, string_data("curve_operation_test_mnt6_g2"), data_set) {
    using policy_type = curves::mnt6<298>::g2_type;

    curve_operation_test<policy_type>(data_set, fp3_curve_test_init<policy_type>);
}

BOOST_DATA_TEST_CASE(curve_operation_test_bls12_381_g1, string_data("curve_operation_test_bls12_381_g1"), data_set) {
    using policy_type = curves::bls12<381>::g1_type;

    curve_operation_test<policy_type>(data_set, fp_curve_test_init<policy_type>);
}

BOOST_DATA_TEST_CASE(curve_operation_test_bls12_377_g1, string_data("curve_operation_test_bls12_377_g1"), data_set) {
    using policy_type = curves::bls12<377>::g1_type;

    curve_operation_test<policy_type>(data_set, fp_curve_test_init<policy_type>);
}

BOOST_DATA_TEST_CASE(curve_operation_test_bls12_381_g2, string_data("curve_operation_test_bls12_381_g2"), data_set) {
    using policy_type = curves::bls12<381>::g2_type;

    curve_operation_test<policy_type>(data_set, fp2_curve_test_init<policy_type>);
}

BOOST_DATA_TEST_CASE(curve_operation_test_bls12_377_g2, string_data("curve_operation_test_bls12_377_g2"), data_set) {
    using policy_type = curves::bls12<377>::g2_type;

    curve_operation_test<policy_type>(data_set, fp2_curve_test_init<policy_type>);
}

BOOST_DATA_TEST_CASE(curve_operation_test_alt_bn128_g1, string_data("curve_operation_test_alt_bn128_g1"), data_set) {
    using policy_type = curves::alt_bn128<254>::g1_type;

    curve_operation_test<policy_type>(data_set, fp_curve_test_init<policy_type>);
}

BOOST_DATA_TEST_CASE(curve_operation_test_alt_bn128_g2, string_data("curve_operation_test_alt_bn128_g2"), data_set) {
    using policy_type = curves::alt_bn128<254>::g2_type;

    curve_operation_test<policy_type>(data_set, fp2_curve_test_init<policy_type>);
}

BOOST_AUTO_TEST_SUITE_END()
