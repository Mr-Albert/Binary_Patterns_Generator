/*
 * FastRandompatternsgenerator.h
 *
 *  Created on: May 25, 2019
 *      Author: Mina
 */

#ifndef BINARY_PATTERN_GENERATOR_FASTRANDOMPATTERNSGENERATOR_H_
#define BINARY_PATTERN_GENERATOR_FASTRANDOMPATTERNSGENERATOR_H_
#include "PatternGenerator.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include<iostream>
#include <fstream>
#include<string>
#include <time.h>
#include <iostream>
#include <experimental/filesystem>
#include <thread>
#include <stdexcept>
#include <random>
#include <algorithm>
#include "../FileWriter/FileWriter.h"
namespace PatternGeneratorNS {
template <class row_block_type>
class Fast_Random_patterns_generator: public  PatternGenerator  {
	typedef unsigned long long ull;

	friend FileWriter;
	FileWriter m_fWriter;
	ull m_parts_per_thread;
	protected:
	std::vector<row_block_type> m_previous_row,m_current_row,m_shared_random_row;
	std::vector<std::thread> m_threads_array;
    std::random_device m_rd;     //Get a random seed from the OS entropy device
    std::mt19937_64 m_RNG; //Use the 64-bit Mersenne Twister 19937 generator and seed
    //Define the distribution
    std::uniform_int_distribution<row_block_type> m_uniformly_dist_random_number;
    inline row_block_type m_get_random_number();
    inline row_block_type m_singularity_checker(row_block_type &r_to_be_ckecked,row_block_type &r_to_be_ckecked_with);
    bool m_generate_row(std::vector<row_block_type> &r_destination,std::vector<row_block_type> const &r_HISTORY,bool const t_HISTORY_TAG=true);
    bool m_generate_pattern(std::vector<row_block_type> &r_destination,std::vector<row_block_type> const &r_HISTORY,bool const t_HISTORY_TAG);
    void m_generate_first_row(ull t_row_start,ull t_row_end);
    bool m_generate_row_worker(std::vector<row_block_type> &r_destination,std::vector<row_block_type> const &r_HISTORY);
	bool m_generate_random_row();
	public:
		Fast_Random_patterns_generator(ull t_pattern_size=1,unsigned short t_number_of_threads=1,std::string t_directory_path="",std::string t_files_prefix="test");
		//entry point for pattern generation
		bool generatePattern();
		virtual ~Fast_Random_patterns_generator();


};

} /* namespace PatternGeneratorNS */

#endif /* BINARY_PATTERN_GENERATOR_FASTRANDOMPATTERNSGENERATOR_H_ */
