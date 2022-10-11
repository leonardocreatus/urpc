/* INTERFACE TO THE MODEL */
#include "arithmetic_coding.hpp"
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>

/* THE SET OF SYMBOLS THAT MAY BE ENCODED */

#define No_of_chars 256 /* Number of character symbols */
#define EOF_symbol (No_of_chars+1) /* Index of EOF symbol */

#define No_of_symbols (No_of_chars+1) /* Total number of symbols */

extern int char_to_index[No_of_chars]; /* To index from character */
extern unsigned char index_to_char[No_of_symbols+1]; /* To character from index */

/* CUMULATIVE FREQUENCY TABLE */

#define Max_frequency 16383 /* Maximum allowed frequency count */

extern int  cum_freq[No_of_symbols+1]; /* Cumulative symbol frequencies */

void start_model();
void update_model(int symbol);
void start_outputing_bits();
void output_bit(int bit);
std::string done_outputing_bits();
void start_inputing_bits();
int input_bit();
void start_decoding(std::string str);
int decode_symbol( int cum_freq[]);
void start_encoding();
void encode_symbol( int symbol, int cum_freq[]);
void done_encoding();
