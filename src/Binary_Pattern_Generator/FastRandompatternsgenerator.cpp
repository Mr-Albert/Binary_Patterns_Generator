/*
 * FastRandompatternsgenerator.cpp
 *
 *  Created on: May 25, 2019
 *      Author: Mina
 */

#include "FastRandompatternsgenerator.h"

namespace PatternGeneratorNS {
template <class row_block_type>
Fast_Random_patterns_generator<row_block_type>::Fast_Random_patterns_generator
	(ull t_pattern_size,unsigned short t_number_of_threads,std::string t_directory_path,std::string t_files_prefix)
	:PatternGenerator(t_pattern_size,t_number_of_threads),m_fWriter(t_pattern_size,t_files_prefix,t_directory_path)
	{
	//setting the rows, and  threads array sizes
	ull _blocks_per_row	=	t_pattern_size/sizeof(row_block_type)+1;
	m_previous_row.resize(_blocks_per_row);
	m_current_row.resize(_blocks_per_row);
	m_current_row.resize(_blocks_per_row);
	m_shared_random_row.resize(t_number_of_threads);
    m_parts_per_thread=_blocks_per_row/t_number_of_threads;
	//init RNG
    m_RNG	=	std::mt19937_64(m_rd);
    m_generate_pattern(m_previous_row,m_previous_row,false);



}
template <class row_block_type>
bool Fast_Random_patterns_generator <row_block_type>::m_generate_pattern(std::vector<row_block_type> &r_destination,
		std::vector<row_block_type> const &r_HISTORY,bool const t_HISTORY_TAG)
{
	if(t_HISTORY_TAG	==	false )
	{
		m_generate_random_row();
		//threads
		for(unsigned short thread_indx=0;thread_indx<noThreads-1;thread_indx++)
		{
			 m_threads_array[thread_indx]=std::thread(m_generate_first_row,this,
					thread_indx*(m_parts_per_thread),(thread_indx+1)*(m_parts_per_thread));
		}
		 m_threads_array[noThreads-1]=std::thread(m_generate_first_row,this,
				(noThreads-1)*(m_parts_per_thread),std::max( (noThreads)*(m_parts_per_thread),patternSize )   );
		//join
		for(unsigned short thread_indx=0;thread_indx<noThreads;thread_indx++)
		{
			m_threads_array[thread_indx].join();
		}
//	    m_fWriter.savePattern(m_previous_row);
	}
	else
	{
		for(ull row_number=1;row_number<patternSize;row_number++)
		{
			m_generate_random_row();
			std::thread backGroundWriterThread=std::thread(&FileWriter::savePatterns,&m_fWriter,std::ref(m_previous_row));
			for(unsigned short thread_indx=0;thread_indx<noThreads-1;thread_indx++)
			{
				m_threads_array[thread_indx]=std::thread(
						m_generate_row_worker,this,std::ref(m_current_row),std::ref(m_previous_row),
						thread_indx*(m_parts_per_thread),(thread_indx+1)*(m_parts_per_thread));
			}
			randomPatternsThreadArray[noThreads-1]=std::thread(m_generate_row_worker,this,std::ref(m_current_row),,std::ref(m_previous_row),
					(noThreads-1)*(m_parts_per_thread),std::max((noThreads)*(m_parts_per_thread),patternSize));
			//join
			for(unsigned short thread_indx=0;thread_indx<noThreads;thread_indx++)
			{
				m_threads_array[thread_indx].join();
			}
			backGroundWriterThread.join();
//			threads for generating the current row
//			_generate_row_worker(previous_row,previous_row,false);

		}
//		//for all remaining row..i.e pattern_size-1 rows
//		 std::thread backGroundWriterThread=std::thread(&FileWriter::savePatterns,&m_fWriter,std::ref(m_previous_row));
//
//		 for(unsigned short threadIdx=0;threadIdx<noThreads-1;threadIdx++)
//		{
//			randomPatternsThreadArray[threadIdx]=std::thread(
//					_generate_row_worker,this,std::ref(_current_row),std::ref(_previous_row),
//						threadIdx*(partPerThread),(threadIdx+1)*(partPerThread));
//		}
//		randomPatternsThreadArray[noThreads-1]=std::thread(_generate_row_worker,this,std::ref(currentRow),,std::ref(_previous_row),
//				(noThreads-1)*(partPerThread),Random_patterns_generator::max((noThreads)*(partPerThread),patternSize));
//		//join
//		for(unsigned short threadIdx=0;threadIdx<noThreads;threadIdx++)
//		{
//			randomPatternsThreadArray[threadIdx].join();
//		}
//		backGroundWriterThread.join();
		//threads for generating the current row
//	    _generate_row_worker(previous_row,previous_row,false);
	    //a thread for writing the previous row
		//join
	}

}

template <class row_block_type>
inline row_block_type Fast_Random_patterns_generator<row_block_type>::m_get_random_number()
{
	return m_uniformly_dist_random_number(m_RNG);
}
//
template <class row_block_type>
bool Fast_Random_patterns_generator <row_block_type>::m_generate_row_worker(std::vector<row_block_type> &r_destination,std::vector<row_block_type> const &r_HISTORY)
{

	{
		//threads
		for(ull idx=0;idx<r_destination.size();idx++)
			{
				r_destination[idx]=m_singularityChecker(r_HISTORY[idx],m_get_random_number());
			}
	}
	return true;
}


template <class row_block_type>
inline row_block_type Fast_Random_patterns_generator<row_block_type>::m_singularity_checker(row_block_type &t_to_be_ckecked,row_block_type &t_to_be_ckecked_with)
{
//	return static_cast<row_block_type>
//			(~
//			((      (t_to_be_ckecked_with&t_to_be_ckecked)
//					& ((t_to_be_ckecked_with<<1 & t_to_be_ckecked) | (t_to_be_ckecked_with>>1 & t_to_be_ckecked)))) & t_to_be_ckecked);
	//after simplifiying
	return static_cast<row_block_type>
		(t_to_be_ckecked & (t_to_be_ckecked_with<<1)
		 & (t_to_be_ckecked_with>>1) ) | (t_to_be_ckecked_with & t_to_be_ckecked);


}

template <class row_block_type>
void Fast_Random_patterns_generator<row_block_type>::m_generate_first_row(ull t_row_start,ull t_row_end)
{
	for(t_row_start;t_row_start<t_row_end;t_row_start++)
	{
		m_previous_row[t_row_start]=m_shared_random_row[t_row_start];
	}
}

bool m_generate_random_row()
{
	for(ull random_row_indx=0;random_row_indx<m_shared_random_row.size();random_row_indx++)
		m_shared_random_row[random_row_indx]=m_get_random_number();
}
template <class row_block_type>
Fast_Random_patterns_generator <row_block_type> ::~Fast_Random_patterns_generator() {
	// TODO Auto-generated destructor stub
}

} /* namespace PatternGeneratorNS */
