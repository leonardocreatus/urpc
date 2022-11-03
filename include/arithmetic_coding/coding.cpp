#include <stdio.h>
#include "coding.hpp"


std::string decode(std::string str) {
    start_model();
    start_inputing_bits();
    start_decoding(str);
    std::string out;

    for(;;){
        int ch; int symbol;
        symbol = decode_symbol(cum_freq);
        if (symbol == EOF_symbol) break;
        ch = index_to_char[symbol];
        out += ch;
        update_model(symbol);
    }
    return out;
}

std::string encode(std::string str){
    start_model();
    start_outputing_bits();
    start_encoding();

    for(int i = 0; i < str.length(); i++){
        char c = str[i];
        int ch; int symbol;
        ch = c;
        
        if (ch == EOF) break;
        symbol = char_to_index[ch > 0 ? ch : ch * -1];
        encode_symbol(symbol, cum_freq);
        update_model(symbol);
    }
    encode_symbol(EOF_symbol, cum_freq);
    done_encoding();
    return done_outputing_bits();
}


